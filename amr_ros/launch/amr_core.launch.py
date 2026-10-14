import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.conditions import UnlessCondition
from ament_index_python.packages import get_package_share_directory

def load_file(package_name, file_path):
    package_path = get_package_share_directory(package_name)
    absolute_file_path = os.path.join(package_path, file_path)

    try:
        with open(absolute_file_path, 'r') as file:
            return file.read()
    except EnvironmentError: # parent of IOError, OSError *and* WindowsError where available
        return None


def _create_nodes(context):
    params_file = LaunchConfiguration('params_file').perform(context)
    robot_description_override = LaunchConfiguration('robot_description_override')
    extra_params_file = LaunchConfiguration('extra_params_file').perform(context)

    robot_description = {'robot_description': load_file('amr_description', 'urdf/LD250.urdf')}

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='log',
        parameters=[robot_description],
        condition=UnlessCondition(robot_description_override)
    )

    parameter_files = [params_file]
    if extra_params_file:
        parameter_files.append(extra_params_file)

    core = Node(
        package='amr_core',
        executable='amr_core',
        name='amr_core',
        output='screen',
        parameters=parameter_files,
    )

    return [robot_state_publisher, core]


def generate_launch_description():
    default_core_params = os.path.join(get_package_share_directory('amr_ros'), 'config', 'parameters.yaml')

    declare_params_file = DeclareLaunchArgument(
        'params_file',
        default_value=default_core_params,
        description='Base parameter file passed to amr_core.',
    )

    declare_robot_description_override = DeclareLaunchArgument(
        'robot_description_override',
        default_value='false',
        description='URDF/Xacro file path inside the package'
    )

    declare_extra_params_file = DeclareLaunchArgument(
        'extra_params_file',
        default_value='',
        description='Optional extra ROS parameter file layered on top of the default amr_ros parameters'
    )

    return LaunchDescription([
        declare_params_file,
        declare_robot_description_override,
        declare_extra_params_file,
        OpaqueFunction(function=_create_nodes),
    ])

