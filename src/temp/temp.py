#!/usr/bin/env python
import rclpy
import sys
import time
from om_aiv_util.socket_driver import *
from om_aiv_msg.srv import ArclApi

def custom_spin(socket_driver):
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
    print("TEST")
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

    socket_driver = SocketDriver(node)
    socket_driver.connect(str(ip_address), int(port))
    req_id = socket_driver.login(bytes(passwd, "utf-8"))
    service = node.create_service(ArclApi, 'arcl_api_service', req_handler)
    node.get_logger().info("ARCL API Service initialised!")
    
    custom_spin(socket_driver)

if __name__ == "__main__":
    main()