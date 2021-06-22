#! /usr/bin/env python

from __future__ import print_function
import rclpy
import sys
from rclpy.action import ActionClient
from rclpy.node import Node
from om_aiv_msg.action import Action

class LdActionClient(Node):

    def __init__(self):
        super().__init__('action_client')
        self._action_client = ActionClient(self, Action, 'action_server')

    def send_goal(self, name):
        goal = Action.Goal()
        goal.command = "goto " + name
        goal.identifier = ["Arrived at " + name]
        self._action_client.wait_for_server()
        self._send_goal_future = self._action_client.send_goal_async(goal)
        #return self._send_goal_future
        self._send_goal_future.add_done_callback(self.goal_response_callback)

        # self.get_logger().info(str(resp.result()))
        # return resp

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info('Goal Rejected!')
            return

        self.get_logger().info('Goal Accepted!')

        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info('Result: ' + str(result.res_msg))
        rclpy.shutdown()

def main(args=None):
    rclpy.init(args=args)
    action_client = LdActionClient()
    action_client.send_goal('Goal2')
    rclpy.spin(action_client)


if __name__ == '__main__':
    main()
