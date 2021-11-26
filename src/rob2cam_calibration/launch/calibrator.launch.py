from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import os.path as osp

from launch import LaunchDescription
from launch_ros.actions import Node



#parameters_file_path = os.path.join(get_package_share_directory('om_aiv_util'), 'config', 'main_param.yaml')

def generate_launch_description():
    
    config = os.path.join(
        get_package_share_directory('handeye_4dof_ros2'),
        'config',
        'handeye_calib_params.yaml'
    )
    
    handeye_4dof_node = Node(
        package = 'handeye_4dof_ros2',
        name = 'handeye_4dof_node',
        executable = 'handeye_4dof_node',
        output='screen',
        parameters = [config]
    )
    
    calibration_node = Node(
        package='rob2cam_calibration',
        executable='calibration_node',
        output='screen'
    )

    return LaunchDescription([
        handeye_4dof_node,
        calibration_node,
        ])
