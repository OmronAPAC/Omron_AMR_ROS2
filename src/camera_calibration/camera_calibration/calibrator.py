import sys

from std_srvs.srv import Empty
import rclpy
from rclpy.node import Node


class CalibratorProgram(Node):

    def __init__(self):
        super().__init__('calibrate_async')
        self.store_pose_cli = self.create_client(Empty, 'store_poses')
        self.calc_calib_cli = self.create_client(Empty, 'calculate_calibration')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = Empty.Request()

    def send_request_store_pose(self):
        self.future = self.store_pose_cli.call_async(self.req)
        
    def send_request_calc_calib(self):
        self.future = self.calc_calib_cli.call_async(self.req)


def main(args=None):
    rclpy.init(args=args)

    calibrate = CalibratorProgram()
    calibrate.send_request_store_pose()

    while rclpy.ok():
        rclpy.spin_once(calibrate)
        if calibrate.future.done():
            try:
                response = calibrate.future.result()
            except Exception as e:
                calibrate.get_logger().info(
                    'Service call failed %r' % (e,))
            else:
                calibrate.get_logger().info('calibration fail')
            break

    calibrate.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
    