#! /usr/bin/env python

from __future__ import print_function
import rclpy
import sys
from rclpy.action import ActionClient
from rclpy.node import Node
from om_aiv_msg.action import Action

"""
TODO:
- Make the function a NODE
"""

def goto_client(node):
    # Creates the SimpleActionClient, passing the type of the action
    # (FibonacciAction) to the constructor.
    client = ActionClient(node, Action, 'action_server')

    # Waits until the action server has started up and started
    # listening for goals.
    client.wait_for_server()

    # Creates a goal to send to the action server.
    goal = Action.Goal()
    goal.command = "goto Goal2"
    goal.identifier = ["Arrived at Goal2"]

    client.wait_for_server()
    # Sends the goal to the action server.
    return client.send_goal_async(goal)


def main():
    try:
        # Initializes a rospy node so that the SimpleActionClient can
        # publish and subscribe over ROS.
        rclpy.init()
        node = rclpy.create_node('goto_goal2_action_py')
        result = goto_client(node)
        # rospy.INFO("Result:")
        print("Result:", result.)
    except KeyboardInterrupt:
        print("program interrupted before completion", file=sys.stderr)


if __name__ == '__main__':
    main()

    """
    try:
        # Initializes a rospy node so that the SimpleActionClient can
        # publish and subscribe over ROS.
        rclpy.init()
        node = rclpy.create_node('goto_goal2_action_py')
        result = goto_client(node)
        # rospy.INFO("Result:")
        print("Result:", result)
    except KeyboardInterrupt:
        print("program interrupted before completion", file=sys.stderr)
    """
