import cv2
import math
import numpy as np

import rclpy
from rclpy.node import Node

from ament_index_python.packages import get_package_share_directory
calibration_share = get_package_share_directory('camera_calibration')

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
        self.r_4x4 = []
        self.m_4x4 = []
        self.i = 0
        self.marker_pose = Pose()

    # takes a 4x4 matrix and returns the top left 3x3
    def slice_rot(self, mat):
        return mat[0:3,0:3]

    # takes a 4x4 and returns the top 3 from the rightmost column
    def slice_transl(self, mat):
        return mat[0:3,3:4]
    
    
    #this function converts a pose message into
    # p = 3x1 translation, r = 3x3 rotation, g = 4x4 transform matrix
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
        p2 = np.array([msg.position.x, msg.position.y, msg.position.z])
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
        g = self.quaternion_matrix_4x4(q)
        r = self.quaternion_matrix(q)
        g[0:3, -1] = p2 # for translation
        # g[0][3] = p[0]
        # g[1][3] = p[1]
        # g[2][3] = p[2]
        return p, r, g
    
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
        
    # subfunction that converts a quaternion to a 4x4 matrix
    def quaternion_matrix_4x4(self, quaternion):
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
                    0.0,
                ],
                [
                    q[1, 2] + q[3, 0],
                    1.0 - q[1, 1] - q[3, 3],
                    q[2, 3] - q[1, 0],
                    0.0,
                ],
                [
                    q[1, 3] - q[2, 0],
                    q[2, 3] + q[1, 0],
                    1.0 - q[1, 1] - q[2, 2],
                    0.0,
                ],
                [0.0, 0.0, 0.0, 1.0],
            ]
        )


    # function converts the yaw of the robot(theta) in radians and returns a normalized quaternion 
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
        # here, p is position, q is rotation and r is transform
        p, q, r = self.pose_to_pq(self.pos)
        self.odom_pose_rot_list.append(q)
        self.odom_pose_translation_list.append(p)
        self.r_4x4.append(r)
        # print("odom coords")
        # print(self.pos)
        # print(p)
        # print(q)
        
        # repeat conversion and storing process for fiducial aruco marker
        p, q, r = self.pose_to_pq(self.marker_pose)
        self.marker_pose_rot_list.append(q)
        self.marker_pose_translation_list.append(p)
        self.m_4x4.append(r)
        # print("marker pose coords")
        # print(self.marker_pose)
        # print(p)
        # print(q)
        self.get_logger().info("Stored current robot position and fiducial marker position")
        # empty return to signal to rqt that the service call is done if not rqt will crash
        return res
    
    # get calibration based on all the current data collected
    def calculate_hand_eye_calib(self, req, res):
        self.cam_rot, self.cam_translation = cv2.calibrateHandEye(
            self.odom_pose_rot_list,
            self.odom_pose_translation_list,
            self.marker_pose_rot_list,
            self.marker_pose_translation_list
        )
        self.get_logger().info("Calculated Calibration")
        print(self.cam_translation)
        print(self.cam_rot)
        
        print("robot 4x4 matrices")
        print(self.r_4x4)
        print("marker 4x4 matrices")
        print(self.m_4x4)
        print("\n")
        # empty return to signal to rqt that the service call is done
        return res


def main(args=None):
    rclpy.init(args=args)
    camera_calibration = CameraCalibration()

    rclpy.spin(camera_calibration)

    camera_calibration.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
    