#! /usr/bin/env python

import rclpy
import sys
import time
from om_aiv_navigation.goto_goal import AmrActionClient

def main():
    try:
        rclpy.init()
        action_client = AmrActionClient()
        goal2result = action_client.send_goal('Goal2')
        if not ("Arrived at" in goal2result):
            exit()

        goal1result = action_client.send_goal('Goal1')
        if not ("Arrived at" in goal1result):
            exit()

    except KeyboardInterrupt:
        print("program interrupted before completion", file=sys.stderr)


if __name__ == '__main__':
    main()
