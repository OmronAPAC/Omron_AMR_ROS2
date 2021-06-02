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
        self.get_logger().info(goal.command + "   " + goal.identifier[0])
        return self._action_client.send_goal_async(goal)


def main(args=None):
    rclpy.init(args=args)
    action_client = LdActionClient()
    future = action_client.send_goal('Goal2')
    rclpy.spin_until_future_complete(action_client, future)


if __name__ == '__main__':
    main()
