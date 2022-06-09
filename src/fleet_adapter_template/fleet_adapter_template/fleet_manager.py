import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

import sys
import argparse
import yaml
import threading
import math
import time

from typing import List, Optional, Dict
from pydantic import BaseModel

from fastapi import FastAPI
import uvicorn

import rmf_adapter as adpt
import rmf_adapter.vehicletraits as traits
import rmf_adapter.geometry as geometry

from om_aiv_msg.msg import Status, Location
from om_aiv_msg.action import Action
from om_aiv_msg.srv import ArclApi


app = FastAPI()

class RobotState:
    def __init__(self, extended_status:str, status: str, battery: float, 
                 location: List[float], localization: float, temperature: float):
        self.extended_status = extended_status
        self.status = status
        self.battery = battery
        self.location = location
        self.localization = localization
        self.temperature = temperature

class NavigateRequest(BaseModel):
    map_name: str
    pose: Optional[Dict] # [x, y, theta] in metres and radians


class FleetManager(Node):
    def __init__(self, config, nav_graph):
        self.config = config
        self.fleet_name = self.config["rmf_fleet"]["name"]
        
        super().__init__(f'{self.fleet_name}_fleet_manager')
        
        profile = traits.Profile(geometry.make_final_convex_circle(
            self.config['rmf_fleet']['profile']['footprint']),
            geometry.make_final_convex_circle(config['rmf_fleet']['profile']['vicinity']))
        
        self.vehicle_traits = traits.VehicleTraits(
            linear=traits.Limits(*self.config['rmf_fleet']['limits']['linear']),
            angular=traits.Limits(*self.config['rmf_fleet']['limits']['angular']),
            profile=profile)
        self.vehicle_traits.differential.reversible = self.config['rmf_fleet']['reversible']
        
        # Map: robot name -> robot_state
        self.robots = {}
        
        for robot_name, robot_config in self.config["robots"].items():
            self.robots[robot_name] = Status()
        
        # Robot status subscription
        self.create_subscription(Status, 'ldarcl_status', self.robot_status_cb, 10)
        
        self.client = self.create_client(ArclApi, 'arcl_api_service')
        
        # Action client to navigate the robot
        self._action_client = ActionClient(self, Action, 'action_server')
        
        self.previous_navigation_request_result = None
        
        self.requested_destination = None 
        
        """_summary_

        Returns:
            data: Robot pose in metres and radians, along with success status of the request
        """
        @app.get('/position')
        async def position(robot_name: Optional[str] = None):
            data = {'position': {},
                    'success': False}
            if not robot_name:
                return data
            data['position'] = self.get_robot_state(self.robots.get(robot_name), robot_name).get('position')
            data['position']['x'] /= 1000.0
            data['position']['y'] /= 1000.0
            data['position']['theta'] = math.radians(data['position']['theta'])
            data['success'] = True
            return data
        
        @app.post('/navigate')
        async def navigate(robot_name: str, destination: NavigateRequest):
            data = {'navigation_request_received': False}
            pose = destination.pose
            self.requested_destination = pose
            if not pose:
                return data
            
            x = int(pose['x'] * 1000)
            y = int(pose['y'] * 1000)
            theta = int(math.degrees(pose['theta']))
            
            self.send_goal(f"gotoPoint {x} {y} {theta}", ["Arrived at point ", "Failed going to goal "])
            # if not self.previous_navigation_request_result:
            #     return data
            # if "Arrived at point " in self.previous_navigation_request_result:
            data['navigation_request_received'] = True
            return data
        
        @app.get('/navigation_remaining_duration')
        async def navigation_remaining_duration(robot_name: str):
            data = {'navigation_remaining_duration': 0.0, 'success': False}
            if not self.requested_destination:
                return data
            
            target_x = self.requested_destination['x']
            target_y = self.requested_destination['y']
            target_theta = self.requested_destination['theta']
            
            position = self.get_robot_state(self.robots.get(robot_name), robot_name).get('position')
            curr_x = position['x'] / 1000.0
            curr_y = position['y'] / 1000.0
            curr_theta = math.radians(position['theta'])
            
            dist_to_target = self.dist([target_x, target_y], [curr_x, curr_y])
            angular_diff = abs(abs(curr_theta) - abs(target_theta))
            
            if angular_diff > math.pi:
                angular_diff -= 2 * math.pi
            if angular_diff < -math.pi:
                angular_diff += 2 * math.pi
                
            duration = int(dist_to_target / self.vehicle_traits.linear.nominal_velocity) + \
                int(angular_diff / self.vehicle_traits.rotational.nominal_velocity)
            
            data['navigation_remaining_duration'] = duration
            data['success'] = True
            return data
        
        
        @app.get('/stop')
        async def stop(robot_name: str):
            data = {'success': False}
            
            if self.check_idle(robot_name):
                data['success'] = True
                return data            
            
            req = ArclApi.Request()
            req.command = "stop"
            req.line_identifier = "Stopped"
            
            res = self.client.call(req)
            
            # if not self.previous_navigation_request_result:
            #     return data
            # if "Arrived at point " in self.previous_navigation_request_result:
            data['success'] = True
            return data
            
        @app.get('/navigation_completed')
        async def navigation_completed(robot_name: str):
            data = {'navigation_request_completed': False}
            if not self.previous_navigation_request_result:
                return data
            if "Arrived at point " in self.previous_navigation_request_result:
                data['navigation_request_completed'] = True
                
            return data
        
        """
        Returns the robot battery as a number between 0.0 and 1.0
        """
        @app.get('/battery')
        async def battery(robot_name: str):
            data = {'battery': 0.0,
                    'success': False}
            data['battery'] = self.get_robot_state(self.robots.get(robot_name), robot_name).get('battery')
            data['battery'] /= 100.0
            data['success'] = True
            return data
        
    def robot_status_cb(self, msg):
        location = msg.location
        x = location.x
        y = location.y
        theta = location.theta
        loc = [x, y, theta]
        
        robot_state = RobotState(msg.extended_status, msg.status, msg.state_of_charge, loc, 
                                 msg.localization_score, msg.temperature)
        
        self.robots["amr1"] = robot_state
        
    def get_robot_state(self, state: RobotState, robot_name: str):
        data = {}
        data['robot_name'] = robot_name
        data['position'] = {"x": state.location[0], "y": state.location[1], "theta": state.location[2]}
        data['battery'] = state.battery
        data['status'] = state.status
        data['localization'] = state.localization
        
        return data
    
    def check_idle(self, robot_name: str):
        p1 = self.get_robot_state(self.robots.get(robot_name), robot_name).get('position')
        time.sleep(0.1)
        p2 = self.get_robot_state(self.robots.get(robot_name), robot_name).get('position')
        
        return abs(p1['x'] - p2['x']) < 1e-3 and abs(p1['y'] - p2['y']) < 1e-3 and abs(p1['theta'] - p2['theta']) < 1e-3
    
    def send_goal(self, command, identifier):
        self.goal = Action.Goal()
        self.goal.command = command
        self.goal.identifier = identifier
        
        self._action_client.wait_for_server()
        
        self._send_goal_future = self._action_client.send_goal_async(self.goal, feedback_callback=self.feedback_callback)
        self._send_goal_future.add_done_callback(self.goal_response_callback)
        

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return

        self.get_logger().info('Goal accepted :)')

        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info(result.res_msg)
        self.previous_navigation_request_result = result.res_msg

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback.feed_msg
        self.get_logger().info(feedback)   
    
    def dist(self, A, B):
        ''' Euclidian distance between A(x,y) and B(x,y)'''
        assert(len(A) > 1)
        assert(len(B) > 1)
        return math.sqrt((A[0] - B[0])**2 + (A[1] - B[1])**2)
        
def main(argv=sys.argv):
    rclpy.init(args=argv)
    adpt.init_rclcpp()
    args_without_ros = rclpy.utilities.remove_ros_args(argv)

    parser = argparse.ArgumentParser(
        prog="fleet_manager",
        description="Configure and spin up fleet manager"
    )
    parser.add_argument("-c", "--config_file", type=str, required=True,
                        help="Path to the config.yaml file")
    parser.add_argument("-n", "--nav_graph", type=str, required=True,
                        help="Path to the nav_graph for this fleet manager")
    
    args = parser.parse_args(args_without_ros[1:])
    # print(f"Starting fleet adapter...")

    # Load config and nav graph yamls
    with open(args.config_file, "r") as f:
        config = yaml.safe_load(f)
    
    fleet_manager = FleetManager(config, args.nav_graph)
    
    spin_thread = threading.Thread(target=rclpy.spin, args=(fleet_manager,))
    spin_thread.start()
    
    uvicorn.run(app,
                host=config['rmf_fleet']['fleet_manager']['ip'],
                port=config['rmf_fleet']['fleet_manager']['port'],
                log_level='warning')    

if __name__ == '__main__':
    main(sys.argv)        