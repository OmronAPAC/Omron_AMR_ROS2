#!/usr/bin/env python
import rclpy
from rclpy.node import Node
import sys
import time
from om_aiv_util.socket_driver import *
from om_aiv_msg.srv import ArclApi

def custom_spin(arcl_service):
    """
    Customized version of rospy.spin()
    """
    rate = 0.02
    try:
        while rclpy.ok():
            events = arcl_service.socket_driver.selector.select()
            for key, mask in events:
                arcl_service.socket_driver.process_events(mask)
            time.sleep(rate)
            rclpy.spin_once(arcl_service)
    except KeyboardInterrupt:
        rclpy.shutdown()



class ArclApiService(Node):
    def __init__(self):
        super().__init__('arcl_api_server')
        self.srv = self.create_service(ArclApi, 'arcl_api_service', self.req_handler)
        ip_address = self.declare_parameter("ip_address").value
        port = self.declare_parameter("port").value
        passwd = self.declare_parameter("def_arcl_passwd").value

        self.socket_driver = SocketDriver()
        self.socket_driver.connect(str(ip_address), int(port))
        self.socket_driver.login(bytes(passwd, "utf-8"))
        self.get_logger().info("ARCL API Service initialised!")

    def req_handler(self, req, resp):
        req_id = self.socket_driver.queue_command(bytes(req.command, 'utf-8'), True, req.line_identifier)
        while True:
            try:
                resp = self.socket_driver.get_response(req_id)
                self.get_logger().info(str(resp))
            except KeyError:
                pass
            else:
                return resp


def main(args=None):
    # Connect and log in.
    rclpy.init()
    arcl_service = ArclApiService()
    custom_spin(arcl_service)
    rclpy.shutdown()



if __name__ == "__main__":
    main()