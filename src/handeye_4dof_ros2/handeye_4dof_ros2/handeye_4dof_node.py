import rclpy
from rclpy.node import Node

import numpy as np
from .handeye_4dof import Calibrator4DOF, robot_pose_selector
from .handeye_4dof import transformations as tf

from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose
from std_srvs.srv import Empty

from ament_index_python.packages import get_package_share_directory
HANDEYE_4DOF_SHARE = get_package_share_directory('handeye_4dof_ros2')

class Handeye4Dof(Node):

    def __init__(self):
        super().__init__('handeye_4dof_node')
        self.declare_parameters(
            namespace='',
            parameters=[
                ('base_to_hand_topic', 'base_to_robot'),
                ('robot_to_marker_topic', 'robot_to_marker'),
                ('calculate_nonlinear', False),
                ('antiparallel_screw_axes', True),
                ('calibrated_pose_topic', 'calibrated_pose')
            ]
        )
        base_to_hand_topic = self.get_parameter('base_to_hand_topic').value
        robot_to_marker_topic = self.get_parameter('robot_to_marker_topic').value
        self.calculate_nonlinear = self.get_parameter('calculate_nonlinear').value
        self.antiparallel_screw_axes = self.get_parameter('antiparallel_screw_axes').value
        calibrated_pose_topic = self.get_parameter('calibrated_pose_topic').value
        self.base_to_hand = self.create_subscription(
            PoseArray,
            base_to_hand_topic,
            self.base_to_hand_callback,
            10)
        self.robot_to_marker = self.create_subscription(
            PoseArray,
            robot_to_marker_topic,
            self.camera_to_marker_callback,
            10)
        self.calibrated_pose = self.create_publisher(
            Pose, 
            calibrated_pose_topic, 10)
        self.calculate_calib_srv = self.create_service(Empty, 'calculate_calibration', self.calculate_calib_callback)
        self.calibration_pose = Pose()
        self.base_to_hand_list = []
        self.camera_to_marker_list = []

    
    # this is connected to an empty service to keep message types generic
    def calculate_calib_callback(self, req, res):
        if len(self.base_to_hand_list) > 0 and len(self.camera_to_marker_list) > 0:
            self.calculate_handeye_calibration()
            self.calibrated_pose.publish(self.calibration_pose)
        else:
            self.get_logger().info("Lists are empty!")
        return res
    
    # Takes in a pose array and converts it to a list of numpy arrays
    def base_to_hand_callback(self, msg):
        self.base_to_hand_list = []
        for i in range(0, len(msg.poses)):
            self.base_to_hand_list.append(self.convert_pose_to_transform_matrix(msg.poses[i]))

    # Takes in a pose array and converts it to a list of numpy arrays        
    def camera_to_marker_callback(self, msg):
        self.camera_to_marker_list = []
        for i in range(0, len(msg.poses)):
            self.camera_to_marker_list.append(self.convert_pose_to_transform_matrix(msg.poses[i]))
        
    #convert ROS2 pose message to 4x4 transform matrix
    def convert_pose_to_transform_matrix(self, pose):
        quat_matrix = tf.quaternion_matrix([pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w])
        matrix4x4 = np.array([[quat_matrix[0][0], quat_matrix[0][1], quat_matrix[0][2], pose.position.x], 
                     [quat_matrix[1][0], quat_matrix[1][1], quat_matrix[1][2], pose.position.y],
                     [quat_matrix[2][0], quat_matrix[2][1], quat_matrix[2][2], pose.position.z],
                     [0, 0, 0, 1]])
        return matrix4x4
    
    # Obtain optimal motions as dual quaternions.
    def calculate_handeye_calibration(self):
        motions = robot_pose_selector(self.camera_to_marker_list, self.base_to_hand_list)

        # Initialize calibrator with precomputed motions.
        cb = Calibrator4DOF(motions)

        dq_x = cb.calibrate(antiparallel_screw_axes=self.antiparallel_screw_axes)

        # Hand to Camera TF obtained from handeye calibration.
        hand_to_camera = np.linalg.inv(dq_x.as_transform())
        quat = tf.quaternion_from_matrix(hand_to_camera)

        # Hand to Camera TF obtained from post nonlinear refinement.
        if self.calculate_nonlinear:
            hand_to_camera = cb.nonlinear_refinement(self.base_to_hand_list, self.camera_to_marker_list, hand_to_camera)
            quat = tf.quaternion_from_matrix(hand_to_camera)

        # z-translation is an invalid number.
        # tf transformations follow xyzw convention
        calibration_pose = Pose()
        calibration_pose.position.x = hand_to_camera[0][3]
        calibration_pose.position.y = hand_to_camera[1][3]
        calibration_pose.position.z = hand_to_camera[2][3]
        calibration_pose.orientation.x = quat[0]
        calibration_pose.orientation.y = quat[1]
        calibration_pose.orientation.z = quat[2]
        calibration_pose.orientation.w = quat[3]
        self.calibration_pose = calibration_pose
        print(calibration_pose)

def main(args=None):
    rclpy.init(args=args)
    handeye_4dof_node = Handeye4Dof()
    rclpy.spin(handeye_4dof_node)
    handeye_4dof_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()