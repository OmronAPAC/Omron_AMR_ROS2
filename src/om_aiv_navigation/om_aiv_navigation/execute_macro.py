#! /usr/bin/env python

from __future__ import print_function
import rclpy
import sys
from rclpy.action import ActionClient
from rclpy.node import Node
from om_aiv_msg.action import Action

class AmrActionClient(Node):

    def __init__(self):
        super().__init__('execute_macro')
        self._action_client = ActionClient(self, Action, 'action_server')

    def send_goal(self, name):
        self.goal = Action.Goal()
        self.goal.command = "executeMacro " + name
        self.goal.identifier = ["Completed macro " + name]
        
        self._action_client.wait_for_server()
        
        self._send_goal_future = self._action_client.send_goal_async(self.goal, feedback_callback=self.feedback_callback)
        self._send_goal_future.add_done_callback(self.goal_response_callback)
        
        # rclpy.spin_until_future_complete(self, self._send_goal_future)

        # self._get_result_future = self._send_goal_future.result().get_result_async()
        # rclpy.spin_until_future_complete(self, self._get_result_future)

        # self.get_logger().info(self._get_result_future.result().result.res_msg)
        # return self._get_result_future.result().result.res_msg

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
        rclpy.shutdown()

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback.feed_msg
        self.get_logger().info(feedback)

def main(args=None):
    rclpy.init(args=args)
    action_client = AmrActionClient()
    action_client.send_goal('Macro4')
    rclpy.spin(action_client)

if __name__ == '__main__':
    main()
