import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
def generate_launch_description():
    ld = LaunchDescription()
    config = os.path.join(
        get_package_share_directory('handeye_4dof_ros2'),
        'config',
        'handeye_calib_params.yaml'
        )
        
    node=Node(
        package = 'handeye_4dof_ros2',
        name = 'handeye_4dof_node',
        executable = 'handeye_4dof_node',
        output='screen',
        parameters = [config]
    )
    ld.add_action(node)
    return ld