#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <math.h>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/quaternion.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "om_aiv_msg/msg/status.hpp"
#include "std_msgs/msg/string.hpp"

// Global Variables
rclcpp::Node::SharedPtr node = nullptr;
double pos_x = 0;
double pos_y = 0;
double pos_z = 0;
geometry_msgs::msg::Quaternion theta;
const int JOINTS_SIZE = 7;
const std::string HEAD_FRAME = "/pose";
const std::string CHILD_FRAME = "/base_link";
const std::string MAIN_BODY_JOINT = "main_body_to_base";
const std::string RIGHT_WHEEL_JOINT = "right_wheel_joint";
const std::string LEFT_WHEEL_JOINT = "left_wheel_joint";
const std::string RIGHT_FR_WHEEL_JOINT = "right_front_small_wheel_joint";
const std::string LEFT_FR_WHEEL_JOINT = "left_front_small_wheel_joint";
const std::string RIGHT_BK_WHEEL_JOINT = "left_back_small_wheel_joint";
const std::string LEFT_BK_WHEEL_JOINT = "right_back_small_wheel_joint";

geometry_msgs::msg::Quaternion createQuaternionMsgFromYaw(double yaw)
{
    tf2::Quaternion tfq;
    tfq.setRPY(0, 0, yaw);
    geometry_msgs::msg::Quaternion gmq;

    double roll = 0;
    double pitch = 0;

    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);

    gmq.w = cy * cp * cr + sy * sp * sr; //w
    gmq.x = cy * cp * sr - sy * sp * cr; //x
    gmq.y = sy * cp * sr + cy * sp * cr; //y
    gmq.z = sy * cp * cr - cy * sp * sr; //z

    return gmq;
}

// callback function for subscriber
void pose_cb(const om_aiv_msg::msg::Status::SharedPtr pose_msg)
{
    // The values are in millimeters, convert to meters.
    pos_x = pose_msg->location.x / 1000.0; 
    pos_y = pose_msg->location.y / 1000.0; 
    pos_z = 0;

    // Angle is in degree, convert to radians.
    double rad = pose_msg->location.theta;
    rad = rad * M_PI / 180;
    if (rad < 0) rad += (2 * M_PI);
    theta = createQuaternionMsgFromYaw(rad);
    
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    node = std::make_shared<rclcpp::Node>("joints_publisher");
    auto publisher = node->create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);
    auto subscriber = node->create_subscription<om_aiv_msg::msg::Status>("ldarcl_status", 10, pose_cb);
    tf2_ros::TransformBroadcaster tf_broadcaster(node);
    rclcpp::Rate loop_rate(50);

    // Joint state
    double main_body_to_base_pos = 0;
    double right_wheel_joint_pos = 0;
    double left_wheel_joint_pos = 0;
    double right_front_small_wheel_joint_pos = 0;
    double left_front_small_wheel_joint_pos = 0;
    double left_back_small_wheel_joint_pos = 0;
    double right_back_small_wheel_joint_pos = 0;

    // Messages to publish
    sensor_msgs::msg::JointState joint_state;
    geometry_msgs::msg::TransformStamped pose_trans;
    pose_trans.header.frame_id = HEAD_FRAME;
    pose_trans.child_frame_id = CHILD_FRAME;
    joint_state.name.resize(JOINTS_SIZE);
    joint_state.position.resize(JOINTS_SIZE);
    joint_state.name[0] = MAIN_BODY_JOINT;
    joint_state.name[1] = RIGHT_WHEEL_JOINT;
    joint_state.name[2] = LEFT_WHEEL_JOINT;
    joint_state.name[3] = RIGHT_FR_WHEEL_JOINT;
    joint_state.name[4] = LEFT_FR_WHEEL_JOINT;
    joint_state.name[5] = RIGHT_BK_WHEEL_JOINT;
    joint_state.name[6] = LEFT_BK_WHEEL_JOINT;

    while (rclcpp::ok()) 
    {
        // Update joints
        joint_state.header.stamp = node->now();
        joint_state.position[0] = main_body_to_base_pos;
        joint_state.position[1] = right_wheel_joint_pos;
        joint_state.position[2] = left_wheel_joint_pos;
        joint_state.position[3] = right_front_small_wheel_joint_pos;
        joint_state.position[4] = left_front_small_wheel_joint_pos;
        joint_state.position[5] = left_back_small_wheel_joint_pos;
        joint_state.position[6] = right_back_small_wheel_joint_pos;

        // update transform
        pose_trans.header.stamp = node->now();
        pose_trans.transform.translation.x = pos_x;
        pose_trans.transform.translation.y = pos_y;
        pose_trans.transform.translation.z = pos_z;
        pose_trans.transform.rotation = theta;

        // Update transforms
        // NOTE: The joints states does not change at the moment.
        // TODO: Calculate the next joint state.
        publisher->publish(joint_state);
        tf_broadcaster.sendTransform(pose_trans);

        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}

