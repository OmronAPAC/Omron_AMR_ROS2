#! /usr/bin/env python

from __future__ import print_function
import rclpy
import math
from rclpy.action import ActionClient
from rclpy.node import Node
from om_aiv_msg.action import Action
from om_aiv_msg.srv import ArclApi
from geometry_msgs.msg import Point
from visualization_msgs.msg import Marker
from geometry_msgs.msg import PoseArray

ADD_POINT_COMMAND = "customreadingaddlidar "
GOAL_POSE_TOPIC = "goal_pose"


class AddPoint(Node):
    
    # initializes class as action client to ARCL action server
    def __init__(self):
        super().__init__("add_point_client")
        self.subscription = self.create_subscription(PoseArray, 'aruco_poses', self.subscription_callback, 10)
        
    # callback for subscription from pc
    def subscription_callback(self, msg):
        self.euler_from_quaternion(msg.poses[0].position.x, msg.poses[0].position.y, msg.poses[0].position.z, msg.poses[0].orientation.w, msg.poses[0].orientation.x, msg.poses[0].orientation.y, msg.poses[0].orientation.z)
    
    def euler_from_quaternion(self, x, y, z, rw, rx, ry, rz):
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
        self.get_logger().info("point of x " + str(roll_x) + " and y " + str(pitch_y) + " yaw z " + str(yaw_z))
        return ([x, y, z, roll_x, pitch_y, yaw_z]) # in meters and radians
    
def main(args=None):
    rclpy.init(args=args)
    action_client = AddPoint()
    rclpy.spin(action_client)
    
if __name__ == '__main__':
    main()