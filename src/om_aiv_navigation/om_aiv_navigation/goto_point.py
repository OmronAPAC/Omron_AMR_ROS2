#! /usr/bin/env python

from __future__ import print_function
import rclpy
import math
from rclpy.action import ActionClient
from rclpy.node import Node
from om_aiv_msg.action import Action
from geometry_msgs.msg import PoseStamped

GOTO_POINT_COMMAND = "doTask gotoPoint "
GOAL_POSE_TOPIC = "goal_pose"


class GotoPoint(Node):
    
    # initializes class as action client to ARCL action server
    def __init__(self):
        super().__init__("action_client")
        self._action_client = ActionClient(self, Action, 'action_server')
        self.subscription = self.create_subscription(PoseStamped, GOAL_POSE_TOPIC, self.subscription_callback, 10)
        
    # callback for subscription to "goal_pose"
    def subscription_callback(self, msg):
        position = msg.pose.position
        orientation = msg.pose.orientation
        degree = self.euler_from_quaternion(orientation.w, orientation.x, orientation.y, orientation.z)[2]
        #converting from radian to degree
        degree *= 57.296
        # ensure that AMR does not over-turn in one direction
        if degree > 180:
            degree -=360
        goto_coordinates = str(int(position.x*1000)) + " " + str(int(position.y*1000)) + " " + str(int(degree))
        self.send_goto_point(goto_coordinates)
    
    def send_goto_point(self, coords):
        self.command = GOTO_POINT_COMMAND + coords
        self._action_client.wait_for_server()
        self.goal = Action.Goal()
        self.goal.command = self.command
        self.goal.identifier = ["Going to point"]
        self._future = self._action_client.send_goal_async(self.goal, feedback_callback=self.feedback_callback)
        self._future.add_done_callback(self.response_callback)
        
    def response_callback(self, future):
        if not future.result().accepted:
            self.get_logger().info('Goal Rejected!')
            return
        return ("Goal:" + self.command)
        
    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback.feed_msg
        self.get_logger().info(feedback)
        
    def euler_from_quaternion(self, rw, rx, ry, rz):
        """
        Convert a quaternion into euler angles (roll, pitch, yaw)
        roll is rotation around x in radians (counterclockwise)
        pitch is rotation around y in radians (counterclockwise)
        yaw is rotation around z in radians (counterclockwise)
        """
        t0 = +2.0 * (rw * rx + ry * rz)
        t1 = +1.0 - 2.0 * (rx * rx + ry * ry)
        roll_x = round(math.atan2(t0, t1), 5)
        
        t2 = +2.0 * (rw * ry - rz * rx)
        t2 = +1.0 if t2 > +1.0 else t2
        t2 = -1.0 if t2 < -1.0 else t2
        pitch_y = round(math.asin(t2), 5)
        
        t3 = +2.0 * (rw * rz + rx * ry)
        t4 = +1.0 - 2.0 * (ry * ry + rz * rz)
        yaw_z = round(math.atan2(t3, t4), 5)
        
        return ([roll_x, pitch_y, yaw_z]) # in meters and radians
    
def main(args=None):
    rclpy.init(args=args)
    action_client = GotoPoint()
    rclpy.spin(action_client)
    
if __name__ == '__main__':
    main()