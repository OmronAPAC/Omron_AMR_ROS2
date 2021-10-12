import cv2
import math
import numpy as np

import rclpy
from rclpy.node import Node

from om_aiv_msg.msg import Location, Status
from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose

DEGREE_TO_RAD_CONST = 57.2958

class CameraCalibration(Node):
    
    def __init__(self):
        super().__init__('camera_calibration')
        self.robot_odometry_subscriber = self.create_subscription(Status, 'ldarcl_status', self.status_callback, 10)
        self.aruco_subscriber = self.create_subscription(PoseArray, 'aruco_poses', self.aruco_callback, 10)
        self.odom_pose_rot_list = []
        self.odom_pose_translation_list = []
        self.marker_pose_rot_list = []
        self.marker_pose_translation_list = []
        self.i=0
        self.marker_pose = Pose()

    def pose_to_pq(self, msg):
        """
        Convert a C{geometry_msgs/Pose} into position/quaternion np arrays

        @param msg: ROS message to be converted
        @return:
          - p: position as a np.array
          - q: quaternion as a numpy array (order = [x,y,z,w])
        """
        p = np.array([msg.position.x, msg.position.y, msg.position.z])
        q = np.array([msg.orientation.x, msg.orientation.y,
                    msg.orientation.z, msg.orientation.w])
        return p, q
    
    def quat_from_yaw(self, yaw):
        roll = 0
        pitch = 0
        
        cy = math.cos(yaw * 0.5);
        sy = math.sin(yaw * 0.5);
        cp = math.cos(pitch * 0.5);
        sp = math.sin(pitch * 0.5);
        cr = math.cos(roll * 0.5);
        sr = math.sin(roll * 0.5);
        
        self.pos.orientation.w = cy * cp * cr + sy * sp * sr
        self.pos.orientation.x = cy * cp * sr - sy * sp * cr
        self.pos.orientation.y = sy * cp * sr + cy * sp * cr
        self.pos.orientation.z = sy * cp * cr - cy * sp * sr
    
    # get location data from status and convert to pose
    def status_callback(self, msg):
        self.get_logger().info("pose of robot get")
        self.pos = Pose()
        self.pos.position.x = msg.location.x / 1000
        self.pos.position.y = msg.location.y / 1000
        
        radian = msg.location.theta
        radian = radian / DEGREE_TO_RAD_CONST
        
        self.quat_from_yaw(radian)
        
        if self.marker_pose.position.x != 0:
            self.store_poses()
            self.i += 1
            if self.i > 3:
                self.calculate_hand_eye_calib()
        
    # get the first and only pose data from aruco service 
    def aruco_callback(self, msg):
        self.get_logger().info("pose of marker get")
        self.marker_pose = msg.poses[0]
        
    # get the current position of robot and the pose of the fiducial marker
    def store_poses(self):
        p, q = self.pose_to_pq(self.pos)
        self.odom_pose_rot_list.append(p)
        self.odom_pose_translation_list.append(q)
        p, q = self.pose_to_pq(self.marker_pose)
        self.marker_pose_rot_list.append(p)
        self.marker_pose_translation_list.append(q)
        self.get_logger().info("STOREDSTOREDSTORED")
    
    # get calibration based on all the current data collected
    def calculate_hand_eye_calib(self):
        self.cam_rot, self.cam_translation = cv2.calibrateHandEye(
            self.odom_pose_rot_list,
            self.odom_pose_translation_list,
            self.marker_pose_rot_list,
            self.marker_pose_translation_list
        )
        self.get_logger().info("CALCULATEDCALCULATEDCALCULATED")
        print(self.cam_rot)
        print(self.cam_translation)


def main(args=None):
    rclpy.init(args=args)
    camera_calibration = CameraCalibration()

    rclpy.spin(camera_calibration)

    camera_calibration.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()