#! /usr/bin/env python

from __future__ import print_function
import rclpy
import sys
from rclpy.action import ActionClient
from rclpy.node import Node
from om_aiv_msg.action import Action

class AmrActionClient(Node):

    def __init__(self):
        super().__init__('action_client')
        self._action_client = ActionClient(self, Action, 'action_server')

    def send_goal(self, name):
        self._action_client.wait_for_server()
        self.goal = Action.Goal()
        self.goal.command = "dock"
        self.goal.identifier = ["Arrived at dock"]
        self._send_goal_future = self._action_client.send_goal_async(self.goal, feedback_callback=self.feedback_callback)
        self._send_goal_future.add_done_callback(self.goal_response_callback)
        rclpy.spin_until_future_complete(self, self._send_goal_future)

        self._get_result_future = self._send_goal_future.result().get_result_async()
        rclpy.spin_until_future_complete(self, self._get_result_future)

        self.get_logger().info(self._get_result_future.result().result.res_msg)
        return self._get_result_future.result().result.res_msg

    def goal_response_callback(self, future):
        self.goal_handle = future.result()
        if not self.goal_handle.accepted:
            self.get_logger().info('Goal Rejected!')
            return

        self.get_logger().info('Goal: ' + self.goal.command)


    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback.feed_msg
        self.get_logger().info(feedback)

def main(args=None):
    rclpy.init(args=args)
    action_client = AmrActionClient()
    action_client.send_goal('dock')
    rclpy.spin(action_client)


if __name__ == '__main__':
    main()
