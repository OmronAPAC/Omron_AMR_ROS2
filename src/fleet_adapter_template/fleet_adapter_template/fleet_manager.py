import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

import sys
import argparse
import yaml
import threading

from typing import List, Optional, Dict
from pydantic import BaseModel

from fastapi import FastAPI
import uvicorn

import rmf_adapter as adpt

from om_aiv_msg.msg import Status, Location
from om_aiv_msg.action import Action
from om_aiv_msg.srv import ArclApi


app = FastAPI()

class RobotState:
    def __init__(self, extended_status:str, status: str, battery: float, 
                 location: List[int], localization: float, temperature: float):
        self.extended_status = extended_status
        self.status = status
        self.battery = battery
        self.location = location
        self.localization = localization
        self.temperature = temperature

class NavigateRequest(BaseModel):
    map_name: str
    pose: Optional[Dict]


class FleetManager(Node):
    def __init__(self, config, nav_graph):
        self.config = config
        self.fleet_name = self.config["rmf_fleet"]["name"]
        
        super().__init__(f'{self.fleet_name}_fleet_manager')
        
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
        
        @app.get('/position')
        async def position(robot_name: Optional[str] = None):
            data = {'position': {},
                    'success': False}
            if not robot_name:
                return data
            data['position'] = self.get_robot_state(self.robots.get(robot_name), robot_name).get('position')
            data['success'] = True
            return data
        
        @app.post('/navigate')
        async def navigate(robot_name: str, destination: NavigateRequest):
            data = {'navigation_request_received': True}
            pose = destination.pose
            if not pose:
                return data
            self.send_goal(f"gotoPoint {pose['x']} {pose['y']} {pose['theta']}", ["Arrived at point ", "Failed going to goal "])
            # if not self.previous_navigation_request_result:
            #     return data
            # if "Arrived at point " in self.previous_navigation_request_result:
            #     data['success'] = True
            return data
        
        
        '''
        This function can only be called if the robot is not idle
        '''
        @app.get('/stop')
        async def stop(robot_name: str):
            data = {'success': True}
            
            req = ArclApi.Request()
            req.command = "stop"
            req.line_identifier = "Stopped"
            
            res = self.client.call(req)
            self.get_logger().info(res.response)
            
            # if not self.previous_navigation_request_result:
            #     return data
            # if "Arrived at point " in self.previous_navigation_request_result:
            #     data['success'] = True
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
        Returns the robot batter
        """
        @app.get('/battery')
        async def battery(robot_name: Optional[str] = None):
            data = {'battery': 0.0,
                    'success': False}
            if not robot_name:
                return data
            data['battery'] = self.get_robot_state(self.robots.get(robot_name), robot_name).get('battery')
            data['success'] = True
            return data
        
    def robot_status_cb(self, msg):
        location = msg.location
        x = location.x
        y = location.y
        theta = location.theta
        location = [x, y, theta]
        
        robot_state = RobotState(msg.extended_status, msg.status, msg.state_of_charge, location, 
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