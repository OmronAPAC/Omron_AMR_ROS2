#!/usr/bin/env python
import rclpy
import sys
import time
from om_aiv_util.socket_driver import *
from om_aiv_msg.srv import ArclApi

def custom_spin():
    """
    Customized version of rospy.spin()
    """
    rate = 0.02
    try:
        while rclpy.ok():
            events = socket_driver.selector.select()
            for key, mask in events:
                socket_driver.process_events(mask)
            time.sleep(rate)
    except KeyboardInterrupt:
        rclpy.shutdown()

def req_handler(req):
    global socket_driver
    req_id = socket_driver.queue_command(req.command, True, req.line_identifier)
    while True:
        try:
            resp = socket_driver.get_response(req_id)
        except KeyError:
            pass
        else:
            return resp

def main():
    rclpy.init(args=sys.argv)
    node = rclpy.create_node('arcl_api_server')
    # Connect and log in.
    ip_address = node.declare_parameter("ip_address").value
    port = node.declare_parameter("port").value
    passwd = node.declare_parameter("def_arcl_passwd").value
    socket_driver = SocketDriver()
    socket_driver.connect(str(ip_address), port)
    req_id = socket_driver.login(str(passwd))
    node.get_logger().info(passwd)

    service = node.create_service(ArclApi, 'arcl_api_service', req_handler)
    custom_spin()

if __name__ == "__main__":
    main()