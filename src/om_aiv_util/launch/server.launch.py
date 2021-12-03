from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

#parameters_file_path = os.path.join(get_package_share_directory('om_aiv_util'), 'config', 'main_param.yaml')

def generate_launch_description():

    vis_config = get_package_share_directory('amr_visualisation') + "/param/vis_param.yaml"
    
    arcl_api = Node(
        package='om_aiv_util',
        executable='arcl_api_server',
        #name='arcl_api_server',
        output='log',
        parameters=[{
            'ip_address': "192.168.1.1",
            'port': 7171,
            'def_arcl_passwd': "omron"
        }]
    )
    
    # Data Points Marker
    data_points_node = Node(
        package='amr_visualisation',
        executable='data_points_marker',
        output='screen',
        parameters=[vis_config],
    )
    
    ld_states = Node(
        package='om_aiv_util',
        executable='ld_states_publisher',
        #name='ld_states_publi',
        output='screen',
        parameters=[{
            'local_ip': "192.168.1.50",
            'local_port': 7179
        }]
    )
    
    action_serve = Node(
        package='om_aiv_navigation',
        executable='action_server',
        #name = 'action_server',
        output='screen',
        parameters=[{
            'ip_address': "192.168.1.1",
            'port': 7171,
            'def_arcl_passwd': "omron"
        }]
    )
    

    return LaunchDescription([
        arcl_api, 
        ld_states,
        action_serve,
        data_points_node
        ])

