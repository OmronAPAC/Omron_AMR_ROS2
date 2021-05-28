#!/usr/bin/env python
import rclpy
import sys
import time
from std_msgs.msg import String
from om_aiv_util.socket_listener import *
from om_aiv_msg.msg import Status, Location
from rclpy.node import Node

"""

"""
def pub_status(status_pub, listener):
    status_msg = Status()
    loc_msg = Location()
    try:
        status_status = listener.get_response("Status")
        status_batt = listener.get_response("StateOfCharge")
        status_loc = listener.get_response("Location")
        status_loc_score = listener.get_response("LocalizationScore")
        status_temp = listener.get_response("Temperature")
        status_ext = listener.get_response("ExtendedStatusForHumans")
    except KeyError:
        pass
    else:
        status_msg.status = status_status[0]
        status_msg.extended_status = status_ext[0]
        status_msg.state_of_charge = float(status_batt[0])
        status_msg.localization_score = float(status_loc_score[0])
        status_msg.temperature = float(status_temp[0])
        # Parse location values
        values = status_loc[0].split()
        if len(values) == 3:
            try:
                loc_msg.x = float(values[0])
                loc_msg.y = float(values[1])
                loc_msg.theta = float(values[2])
            except ValueError:
                loc_msg.x = 0
                loc_msg.y = 0
                loc_msg.theta = 0
                print("Value error with location coordinates. Setting them to zeroes.")
                pass
            else:
                status_msg.location = loc_msg
    finally:
        status_pub.publish(status_msg)

"""

"""
def pub_laser(laser_pub, listener):
    try:
        scans = listener.get_response("RangeDeviceGetCurrent")
    except KeyError:
        pass
    else:
        laser_pub.publish(" ".join(scans))

"""

"""
def pub_goals(goals_pub, listener):
    try:
        goals = listener.get_response("Goal")
    except KeyError:
        pass
    else:
        goals_pub.publish(" ".join(goals))

def pub_odometer(odom_pub, listener):
    try:
        odom = listener.get_response("Odometer")
    except KeyError:
        pass
    else:
        odom_pub.publish(" ".join(odom))

def pub_app_fault_query(app_fault_query_pub, listener):
    try:
        query = listener.get_response("ApplicationFaultQuery")
    except KeyError:
        pass
    else:
        app_fault_query_pub.publish(" ".join(query))

def pub_faults_get(faults_get_pub, listener):
    try:
        faults = listener.get_response("FaultList")
    except KeyError:
        pass
    else:
        faults_get_pub.publish(" ".join(faults))

def pub_query_faults(query_faults_pub, listener):
    try:
        faults = listener.get_response("RobotFaultQuery")
    except KeyError:
        pass
    else:
        query_faults_pub.publish(" ".join(faults))

"""

"""
class LdStatePublisher(Node):
    def __init__(self, listener):
        super().__init__('ld_states_publisher_node')
        self.listener = listener
        self.status_pub = self.create_publisher(Status, "ldarcl_status", 10)
        self.laser_pub = self.create_publisher(String, "ldarcl_laser", 10)
        self.goals_pub = self.create_publisher(String, "ldarcl_all_goals", 10)
        self.odom_pub = self.create_publisher(String, "ldarcl_odom", 10)
        self.app_fault_query_pub = self.create_publisher(String, "ldarcl_application_fault_query", 10)
        self.faults_get_pub = self.create_publisher(String, "ldarcl_faults_get", 10)
        self.query_faults_pub = self.create_publisher(String, "ldarcl_query_faults", 10)
        self.timer_period = 0.1
        self.timer = self.create_timer(self.timer_period, self.timer_callback)
    
    def timer_callback(self):
        events = self.listener.selector.select()
        for key, mask in events:
            self.listener.process_events(mask)

        pub_status(self.status_pub, self.listener)
        pub_laser(self.laser_pub, self.listener)
        pub_goals(self.goals_pub, self.listener)
        pub_odometer(self.odom_pub, self.listener)
        pub_app_fault_query(self.app_fault_query_pub, self.listener)
        pub_faults_get(self.faults_get_pub, self.listener)
        pub_query_faults(self.query_faults_pub, self.listener)
    
"""

"""
def main():
    rclpy.init(args=sys.argv)
    node = rclpy.create_node('ld_param_node')
    ip_address = node.declare_parameter("local_ip").value
    node.get_logger().info('IP ADDRESS IS.... ' + str(ip_address))
    port = node.declare_parameter("local_port").value
    node.get_logger().info('LOCAL PORT IS.... ' + str(port))
    listener = SocketListener(ip_address, port)
    listener.begin()

    ld_states_pub = LdStatePublisher(listener)
    
    try:
        rclpy.spin(ld_states_pub)
    except KeyboardInterrupt:
        listener.close()
        node.get_logger().info("Shutting down ARCL states publisher")
    

if __name__ == "__main__":
    main()
    """
    rclpy.init(args=sys.argv)
    node = rclpy.create_node('ld_param_node')
    ip_address = node.get_parameter("local_ip")
    port = node.get_parameter("local_port")
    listener = SocketListener(str(ip_address), int(port))
    listener.begin()
    """