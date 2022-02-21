#! /usr/bin/env python

from __future__ import print_function
import rclpy
from rclpy.node import Node
from om_aiv_msg.srv import ArclApi
from geometry_msgs.msg import Point
from visualization_msgs.msg import Marker

ADD_POINT_COMMAND = "customreadingaddabsolute"
GOAL_POSE_TOPIC = "goal_pose"


class AddPoint(Node):
    
    # initializes class as action client to ARCL action server
    def __init__(self):
        super().__init__("add_point_client")
        self.declare_parameter('sensor_name', 'lidar')
        self.sensor_name = self.get_parameter('sensor_name').value
        self.get_logger().info(self.sensor_name)
        self.client = self.create_client(ArclApi, 'arcl_api_service')
        self.subscription = self.create_subscription(Point, 'obstacle_point', self.subscription_callback, 10)
        self.publisher = self.create_publisher(Marker, 'obs_points', 10)
        self.id = 0
        
    # callback for subscription from pc
    def subscription_callback(self, msg):
        # self.get_logger().info("point of x " + str(msg.x) + " and y " + str(msg.y) + " received")
        self.publisher.publish(self.init_marker(msg))
        if msg.x == 0 and msg.y == 0:
            self.get_logger().info("return")
            return
        x_coord = int(msg.x * 1000)
        y_coord = int(msg.y * 1000)
        obstacle_position = str(x_coord) + " " + str(y_coord)
        self.send_goto_point(obstacle_position)
    
    def send_goto_point(self, coords):
        command = ADD_POINT_COMMAND + self.sensor_name + " " + coords
        self.client.wait_for_service()
        goal = ArclApi.Request()
        goal.command = command
        goal.line_identifier = "Added absolute reading"

        self._future = self.client.call_async(goal)
        self._future.add_done_callback(self.response_callback)
        
    def response_callback(self, future):
        self.get_logger().info(future.result().response)
        return ("Goal:" + future.result().response)
    
    def init_marker(self, msg):
        marker = Marker()
        marker.header.frame_id = "obstacle_points"
        marker.header.stamp = self.get_clock().now().to_msg()
        marker.type = 1
        marker.color.r = 0.0
        marker.color.g = 0.8
        marker.color.b = 0.0
        marker.color.a = 1.0
        marker.scale.x = 0.05
        marker.scale.y = 0.05
        marker.scale.z = 0.05
        marker.pose.orientation.w = 1.0
        marker.pose.position = msg
        marker.id = self.id
        self.id += 1
        if self.id > 1000:
            self.id = 0
        marker.lifetime.sec = 8
        return marker
    
def main(args=None):
    rclpy.init(args=args)
    add_points_client = AddPoint()
    rclpy.spin(add_points_client)
    
if __name__ == '__main__':
    main()