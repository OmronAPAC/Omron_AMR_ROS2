# Copyright 2021 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

'''
    The RobotAPI class is a wrapper for API calls to the robot. Here users
    are expected to fill up the implementations of functions which will be used
    by the RobotCommandHandle. For example, if your robot has a REST API, you
    will need to make http request calls to the appropriate endpoints within
    these functions.
'''
from om_aiv_util.socket_driver import SocketDriver
from om_aiv_util.socket_listener import SocketListener
from om_aiv_util.socket_taskmaster import SocketTaskmaster
from typing import List

class RobotState:
    def __init__(self, status: str, battery: float, location: List[float], localization: float):
        self.status = status
        self.battery = battery
        self.location = location
        self.localization = localization


class RobotAPI:
    # The constructor below accepts parameters typically required to submit
    # http requests. Users should modify the constructor as per the
    # requirements of their robot's API
    def __init__(self, prefix: str, user: str, password: str):
        self.prefix = prefix
        self.user = user
        self.password = password
        self.connected = False  
        
        # Listen to incoming ARCL commands
        self.listener = SocketListener("192.168.1.132", 7179) # Computer IP and port
        self.listener.begin()
        
        # Handle actions such as navigation and docking
        self.socket_taskmaster = SocketTaskmaster()
        self.socket_taskmaster.connect("192.168.1.191", 7171) # Robot IP and port
        self.socket_taskmaster.login(bytes('omron', 'utf-8'))        
        
        # Test connectivity
        connected = self.check_connection()
        if connected:
            print("Successfully able to query API server")
            self.connected = True
        else:
            print("Unable to query API server")
            
        self.previous_navigation_request_result = None

    def handle_action(self, command, identifiers):
        self.socket_taskmaster.push_command(bytes(command, "utf-8"), True, list(map(lambda x: bytes(x, "utf-8"), identifiers)))
        while True:
            done, result, feedback = self.socket_taskmaster.wait_command()
            print(f'Feedback: {feedback.decode()}')
            if done:
                print(f'Result: {result.decode()}')
                return result
            
    def get_current_robot_state(self):
        events = self.listener.selector.select()
        for key, mask in events:
            self.listener.process_events(mask)
        
        # Retrieve data through socket listener    
        status_status = self.listener.get_response(b"Status")
        status_batt = self.listener.get_response(b"StateOfCharge")
        status_loc = self.listener.get_response(b"Location")
        status_loc_score = self.listener.get_response(b"LocalizationScore")
        
        status = status_status[0].decode()
        battery = float(status_batt[0])
        localization = float(status_loc_score[0])
        location = list(map(float, status_loc[0].split()))
        
        return RobotState(status, battery, location, localization)
            

    def check_connection(self):
        ''' Return True if connection to the robot API server is successful'''
        # ------------------------ #
        # IMPLEMENT YOUR CODE HERE #
        # ------------------------ #
        return True

    def position(self, robot_name: str):
        ''' Return [x, y, theta] expressed in the robot's coordinate frame or
            None if any errors are encountered'''
        # ------------------------ #
        # IMPLEMENT YOUR CODE HERE #
        # ------------------------ #
        current_robot_state = self.get_current_robot_state()
        print(f'Current position is {current_robot_state.location}')
        return current_robot_state.location

    def navigate(self, robot_name: str, pose, map_name: str):
        ''' Request the robot to navigate to pose:[x,y,theta] where x, y and
            and theta are in the robot's coordinate convention. This function
            should return True if the robot has accepted the request,
            else False'''
        # ------------------------ #
        # IMPLEMENT YOUR CODE HERE #
        # ------------------------ #
        x, y, theta = pose
        command = f'gotoPoint {int(x)} {int(y)} {int(theta)}'
        identifiers = ['Arrived at point ', 'Failed ']
        print(command)
        self.previous_navigation_request_result = self.handle_action(command, identifiers).decode()
        return True

    def start_process(self, robot_name: str, process: str, map_name: str):
        ''' Request the robot to begin a process. This is specific to the robot
            and the use case. For example, load/unload a cart for Deliverybot
            or begin cleaning a zone for a cleaning robot.
            Return True if the robot has accepted the request, else False'''
        # ------------------------ #
        # IMPLEMENT YOUR CODE HERE #
        # ------------------------ #
        return True

    def stop(self, robot_name: str):
        ''' Command the robot to stop.
            Return True if robot has successfully stopped. Else False'''
        # ------------------------ #
        # IMPLEMENT YOUR CODE HERE #
        # ------------------------ #
        command = 'stop'
        identifiers = ['Stopped']
        self.handle_action(command, identifiers)
        return True

    def navigation_remaining_duration(self, robot_name: str):
        ''' Return the number of seconds remaining for the robot to reach its
            destination'''
        # ------------------------ #
        # IMPLEMENT YOUR CODE HERE #
        # ------------------------ #
        return 0.0

    def navigation_completed(self, robot_name: str):
        ''' Return True if the robot has successfully completed its previous
            navigation request. Else False.'''
        # ------------------------ #
        # IMPLEMENT YOUR CODE HERE #
        # ------------------------ #
        return 'Arrived at ' in self.previous_navigation_request_result

    def process_completed(self, robot_name: str):
        ''' Return True if the robot has successfully completed its previous
            process request. Else False.'''
        # ------------------------ #
        # IMPLEMENT YOUR CODE HERE #
        # ------------------------ #
        return True

    def battery_soc(self, robot_name: str):
        ''' Return the state of charge of the robot as a value between 0.0
            and 1.0. Else return None if any errors are encountered'''
        # ------------------------ #
        # IMPLEMENT YOUR CODE HERE #
        # ------------------------ #
        current_robot_state = self.get_current_robot_state()
        return current_robot_state.battery / 100.0
