#! /usr/bin/env python
"""
from __future__ import print_function
import rclpy
import sys
from rclpy.action import ActionClient
from rclpy.node import Node
from om_aiv_navigation.msg import ActionAction, ActionGoal

def goto_client(node):
    # Creates the SimpleActionClient, passing the type of the action
    # (FibonacciAction) to the constructor.
    client = ActionClient(node, ActionAction, 'action_server')

    # Waits until the action server has started up and started
    # listening for goals.
    client.wait_for_server()

    # Creates a goal to send to the action server.
    goal = ActionGoal("goto Goal3", ["Arrived at Goal3"])


    # Sends the goal to the action server.
    client.send_goal(goal)

    # Waits for the server to finish performing the action.
    client.wait_for_result()

    # Prints out the result of executing the action
    return client.get_result()  

if __name__ == '__main__':
    try:
        # Initializes a rospy node so that the SimpleActionClient can
        # publish and subscribe over ROS.
        rclpy.init()
        node = rclpy.create_node('goto_goal3_action_py')
        result = goto_client()
        # rospy.INFO("Result:")
        print("Result:", result)
    except KeyboardInterrupt:
        print("program interrupted before completion", file=sys.stderr)
"""