import os
import sys
import yaml
import json
from launch import LaunchDescription
from launch.substitutions import Command
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def load_file(package_name, file_path):
    package_path = get_package_share_directory(package_name)
    absolute_file_path = os.path.join(package_path, file_path)

    try:
        with open(absolute_file_path, 'r') as file:
            return file.read()
    except EnvironmentError: # parent of IOError, OSError *and* WindowsError where available
        return None


def generate_launch_description():
    #robot_description_config = load_file('amr_visualisation', 'urdf/AMR_Platform.urdf')
    # robot_description_config = load_file('amr_visualisation', 'urdf/LD90.urdf')
    robot_description_config = load_file('amr_visualisation', 'urdf/LD250.urdf')
    robot_description = {'robot_description' : robot_description_config}

    vis_config = get_package_share_directory('amr_visualisation') + "/param/vis_param.yaml"

    # RViz
    rviz_config_file = "src/amr_visualisation/config/amr_rviz.rviz"
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        output='log',
        arguments=['-d', rviz_config_file],
        )


    # Publish Robot
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='log',
        parameters=[robot_description],
    )

    # Joints Publisher
    joints_publisher_node = Node(
        package='amr_visualisation',
        executable='joints_publisher',
        output='screen',
    )

    # Data Points Marker
    data_points_node = Node(
        package='amr_visualisation',
        executable='data_points_marker',
        output='screen',
        parameters=[vis_config],
    )
        
    # Goals Marker
    goals_node = Node(
        package='amr_visualisation',
        executable='goals_marker',
        output='screen',
    )
    
    # RViz goto point node
    goto_point_node = Node(
        package='om_aiv_navigation',
        executable='goto_point',
        output='screen',
    )
    
    # RViz goto point node
    localize_at_point_node = Node(
        package='om_aiv_navigation',
        executable='localize_at_point',
        output='screen',
    )
        
    map_node = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='world_publisher',
        output='log',
        arguments=['0.0', '0.0', '0.0', '0.0', '0.0', '0.0', 'map', 'pose']
    )
    
    laser_scans_node = Node(
        package='amr_visualisation',
        executable='laser_scans',
        output='screen',
    )

    return LaunchDescription([
        robot_state_publisher, 
        rviz_node, 
        joints_publisher_node,
        data_points_node,
        goals_node,
        goto_point_node,
        localize_at_point_node,
        map_node,
        laser_scans_node
        ])

