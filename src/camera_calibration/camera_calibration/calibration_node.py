import cv2
import math
import numpy as np

import rclpy
from rclpy.node import Node

from om_aiv_msg.msg import Status
from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose
from std_srvs.srv import Empty

DEGREE_TO_RAD_CONST = 57.2958

class CameraCalibration(Node):
    
    
    def __init__(self):
        super().__init__('camera_calibration')
        self.robot_odometry_subscriber = self.create_subscription(Status, 'ldarcl_status', self.status_callback, 10)
        self.aruco_subscriber = self.create_subscription(PoseArray, 'aruco_poses', self.aruco_callback, 10)
        self.store_poses_srv = self.create_service(Empty, 'store_poses', self.store_poses)
        self.calculate_calib_srv = self.create_service(Empty, 'calculate_calibration', self.calculate_hand_eye_calib)
        self.odom_pose_rot_list = []
        self.odom_pose_translation_list = []
        self.marker_pose_rot_list = []
        self.marker_pose_translation_list = []
        self.i = 0
        self.marker_pose = Pose()

    def pose_to_pq(self, msg):
        """
        Modified from: https://answers.ros.org/question/332407/transformstamped-to-transformation-matrix-python/
        Convert a C{geometry_msgs/Pose} into position/quaternion np arrays

        @param msg: ROS message to be converted
        @return:
          - p: position as a np.array
          - q: quaternion as a numpy array (order = [x,y,z,w])
          - q: in the quaternion_matrix function here, it takes in w,x,y,z
        """
        p = np.array([[msg.position.x], [msg.position.y], [msg.position.z]])
        # q = np.array([msg.orientation.x, msg.orientation.y,
        #             msg.orientation.z, msg.orientation.w])
        q = np.array([msg.orientation.w, msg.orientation.x,
                    msg.orientation.y, msg.orientation.z])
        norm = np.linalg.norm(q)
        if np.abs(norm - 1.0) > 1e-3:
            raise ValueError(
                "Received un-normalized quaternion (q = {0:s} ||q|| = {1:3.6f})".format(
                    str(q), np.linalg.norm(q)))
        elif np.abs(norm - 1.0) > 1e-6:
            q = q / norm
        g = self.quaternion_matrix(q)
        # g[0:3, -1] = p
        return p, g
    
    def quaternion_matrix(self, quaternion):
        # this function uses w, x, y, z
        # acquired from: https://github.com/cgohlke/transformations/blob/master/transformations/transformations.py
        """Return homogeneous rotation matrix from quaternion.
        >>> M = quaternion_matrix([0.99810947, 0.06146124, 0, 0])
        >>> numpy.allclose(M, rotation_matrix(0.123, [1, 0, 0]))
        True
        >>> M = quaternion_matrix([1, 0, 0, 0])
        >>> numpy.allclose(M, numpy.identity(4))
        True
        >>> M = quaternion_matrix([0, 1, 0, 0])
        >>> numpy.allclose(M, numpy.diag([1, -1, -1, 1]))
        True
        """
        _EPS = np.finfo(float).eps * 4.0
        q = np.array(quaternion, dtype=np.float64, copy=True)
        n = np.dot(q, q)
        if n < _EPS:
            return np.identity(4)
        q *= math.sqrt(2.0 / n)
        q = np.outer(q, q)
        return np.array(
            [
                [
                    1.0 - q[2, 2] - q[3, 3],
                    q[1, 2] - q[3, 0],
                    q[1, 3] + q[2, 0],
                ],
                [
                    q[1, 2] + q[3, 0],
                    1.0 - q[1, 1] - q[3, 3],
                    q[2, 3] - q[1, 0],
                ],
                [
                    q[1, 3] - q[2, 0],
                    q[2, 3] + q[1, 0],
                    1.0 - q[1, 1] - q[2, 2],
                ]
            ]
        )


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
        # self.get_logger().info("pose of robot get")
        self.pos = Pose()
        self.pos.position.x = msg.location.x / 1000
        self.pos.position.y = msg.location.y / 1000
        
        radian = msg.location.theta / DEGREE_TO_RAD_CONST
        
        self.quat_from_yaw(radian)
        
    # get the first and only pose data from aruco service 
    def aruco_callback(self, msg):
        # self.get_logger().info("pose of marker get")
        self.marker_pose = msg.poses[0]
        
    # store in memory the current position of robot and the pose of the fiducial marker
    def store_poses(self, req, res):
        p, q = self.pose_to_pq(self.pos)
        self.odom_pose_rot_list.append(q)
        self.odom_pose_translation_list.append(p)
        print("odom coords")
        print(self.pos)
        print(p)
        print(q)
        
        p, q = self.pose_to_pq(self.marker_pose)
        self.marker_pose_rot_list.append(q)
        self.marker_pose_translation_list.append(p)
        print("marker pose coords")
        print(self.marker_pose)
        print(p)
        print(q)
        self.get_logger().info("Stored current robot position and fiducial marker position")
        return res
    
    # get calibration based on all the current data collected
    def calculate_hand_eye_calib(self, req, res):
        self.cam_rot, self.cam_translation = cv2.calibrateHandEye(
            self.odom_pose_rot_list,
            self.odom_pose_translation_list,
            self.marker_pose_rot_list,
            self.marker_pose_translation_list
        )
        self.get_logger().info("Calculated calibration")
        print(self.cam_translation)
        print(self.cam_rot)
        print("\n")
        print(self.rotationMatrixToEulerAngles(self.cam_rot))
        return res

    def rotationMatrixToEulerAngles(self, R) :
        sy = math.sqrt(R[0,0] * R[0,0] +  R[1,0] * R[1,0])
        singular = sy < 1e-6
        if  not singular :
            x = math.atan2(R[2,1] , R[2,2])
            y = math.atan2(-R[2,0], sy)
            z = math.atan2(R[1,0], R[0,0])
        else :
            x = math.atan2(-R[1,2], R[1,1])
            y = math.atan2(-R[2,0], sy)
            z = 0
        euler_arr = np.array([x, y, z])
        print(euler_arr)

def main(args=None):
    rclpy.init(args=args)
    camera_calibration = CameraCalibration()

    rclpy.spin(camera_calibration)

    camera_calibration.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
    