from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    rviz = LaunchConfiguration('rviz')
    use_nav2 = LaunchConfiguration('use_nav2')
    use_slam = LaunchConfiguration('use_slam')
    extra_params_file = LaunchConfiguration('extra_params_file')
    robot_description_override = LaunchConfiguration('robot_description_override')
    nav2_params_file = LaunchConfiguration('nav2_params_file')

    declare_rviz = DeclareLaunchArgument(
        'rviz',
        default_value='false',
        description='Launch RViz with the LD250 configuration.',
    )

    declare_use_nav2 = DeclareLaunchArgument(
        'use_nav2',
        default_value='false',
        description='Launch the Nav2 stack for the LD250 platform.',
    )

    declare_use_slam = DeclareLaunchArgument(
        'use_slam',
        default_value='true',
        description='Launch SLAM inside the LD250 Nav2 bringup.',
    )

    declare_robot_description_override = DeclareLaunchArgument(
        'robot_description_override',
        default_value='false',
        description='Disable loading the default LD250 robot description.',
    )

    declare_nav2_params_file = DeclareLaunchArgument(
        'nav2_params_file',
        default_value=PathJoinSubstitution([FindPackageShare('amr_nav2'), 'config', 'ld250_nav2.yaml']),
        description='Nav2 parameter file to pass to the LD250 navigation launch.',
    )

    declare_extra_params_file = DeclareLaunchArgument(
        'extra_params_file',
        default_value='',
        description='Optional extra parameter file layered on top of the LD250 hardware parameters.',
    )

    core_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([
                FindPackageShare('amr_ros'),
                'launch',
                'amr_core.launch.py',
            ])
        ),
        launch_arguments={
            'params_file': PathJoinSubstitution([FindPackageShare('amr_ros'), 'config', 'ld250_parameters.yaml']),
            'extra_params_file': extra_params_file,
            'robot_description_override': robot_description_override,
        }.items(),
    )

    rviz_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([
                FindPackageShare('amr_ros'),
                'launch',
                'ld250_rviz.launch.py',
            ])
        ),
        condition=IfCondition(rviz),
    )

    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([
                FindPackageShare('amr_nav2'),
                'launch',
                'ld250.launch.py',
            ])
        ),
        condition=IfCondition(use_nav2),
        launch_arguments={
            'params_file': nav2_params_file,
            'slam': use_slam,
        }.items(),
    )

    return LaunchDescription([
        declare_rviz,
        declare_use_nav2,
        declare_use_slam,
        declare_robot_description_override,
        declare_nav2_params_file,
        declare_extra_params_file,
        core_launch,
        nav2_launch,
        rviz_launch,
    ])