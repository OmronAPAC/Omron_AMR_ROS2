#! /usr/bin/env python

from __future__ import print_function
import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from om_aiv_msg.action import Action
from geometry_msgs.msg import Point

ADD_POINT_COMMAND = "customreadingaddlidar "
GOAL_POSE_TOPIC = "goal_pose"


class AddPointClient(Node):
    
    # initializes class as action client to ARCL action server
    def __init__(self):
        super().__init__("action_client")
        self._action_client = ActionClient(self, Action, 'action_server')
        self.subscription = self.create_subscription(Point, 'obstacle_point', self.subscription_callback, 10)
        self.free = True
        
    # callback for subscription from pc
    def subscription_callback(self, msg):
        if msg.x == 0 and msg.y == 0:
            return
        if not self.free:
            return
        self.free = False
        forward = int(msg.y * 1000)
        horizontal = int(-msg.x * 1000)
        obstacle_position = str(forward) + " " + str(horizontal)
        self.send_goto_point(obstacle_position)
    
    def send_goto_point(self, coords):
        self.command = ADD_POINT_COMMAND + coords
        self._action_client.wait_for_server()
        self.goal = Action.Goal()
        self.goal.command = self.command
        self.goal.identifier = ["Adding point"]
        self._future = self._action_client.send_goal_async(self.goal, feedback_callback=self.feedback_callback)
        self._future.add_done_callback(self.response_callback)
        
    def response_callback(self, future):
        if not future.result().accepted:
            self.get_logger().info('Goal Rejected!')
            return
        self.free = True
        return ("Goal:" + self.command)
        
    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback.feed_msg
        self.get_logger().info(feedback)
    
def main(args=None):
    rclpy.init(args=args)
    action_client = AddPointClient()
    rclpy.spin(action_client)
    
if __name__ == '__main__':
    main()