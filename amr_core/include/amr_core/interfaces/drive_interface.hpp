#pragma once

#include <ArNetworking/ArClientRatioDrive.h>
#include <ArNetworking/ArNetworking.h>

#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <cmath>
#include <mutex>
#include <algorithm>
#include <stdexcept>

#include "rclcpp/rclcpp.hpp"
#include <tf2_ros/transform_broadcaster.h>
#include "std_msgs/msg/empty.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "nav_msgs/msg/path.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include "amr_core/utils/libaria_runtime.hpp"

/**
 * @brief ROS 2 drive interface backed by libaria/ArNetworking.
 */
class DriverInterface
{
public:
  /**
   * @brief Constructor. Initializes publishers, subscribers, and libaria callbacks.
   * @param node Shared pointer to rclcpp::Node.
   */
  DriverInterface(rclcpp::Node::SharedPtr node)
    : node_(std::move(node)), ratio_drive_(&client_), update_callback_(this, &DriverInterface::handleUpdateNumbers)
  {
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(node_);
  }

  ~DriverInterface()
  {
    client_.disconnect();
  }

  /**
   * @brief Initializes parameters, publishers, and subscribers.
   *
   * This should be called after the node is fully constructed.
   * @param host Robot server IP address.
   * @param port Robot server port.
   * @param user Username for robot server authentication.
   * @param password Password for robot server authentication.
   * @param protocol Optional protocol version to enforce on the robot server connection.
   *
   * Throws std::runtime_error if connection to the robot server fails or is rejected by the robot.
   */
  void initialize(const std::string& host, int port, const std::string& user, const std::string& password,
                  const std::string& protocol)
  {
    host_ = host;
    port_ = port;
    user_ = user;
    password_ = password;
    protocol_ = protocol;

    odom_topic_ = getOrDeclareParameter<std::string>("driver.odom_topic", "amr/odom");
    cmd_vel_topic_ = getOrDeclareParameter<std::string>("driver.cmd_vel_topic", "amr/cmd_vel");
    stop_topic_ = getOrDeclareParameter<std::string>("driver.stop_topic", "amr/stop");
    publish_odom_ = getOrDeclareParameter<bool>("driver.publish_odom", true);
    publish_robot_tf_ = getOrDeclareParameter<bool>("driver.publish_robot_tf", true);

    odom_frame_ = getOrDeclareParameter<std::string>("driver.odom_frame", "amr/odom");
    base_frame_ = getOrDeclareParameter<std::string>("driver.base_frame", "amr/base_link");

    expected_cmd_vel_freq_ = getOrDeclareParameter<double>("driver.expected_cmd_vel_freq", 20.0);
    min_ang_speed_ = getOrDeclareParameter<double>("driver.min_angular_speed", -60.0);  // deg/s
    max_ang_speed_ = getOrDeclareParameter<double>("driver.max_angular_speed", 60.0);   // deg/s
    min_lin_speed_ = getOrDeclareParameter<double>("driver.min_linear_speed", -200.0);  // mm/s
    max_lin_speed_ = getOrDeclareParameter<double>("driver.max_linear_speed", 1200.0);  // mm/s
    drive_throttle_pct_ = getOrDeclareParameter<double>("driver.drive_throttle_pct", 100.0);
    unsafe_drive_ = getOrDeclareParameter<bool>("driver.unsafe_drive", true);
    cmd_vel_timeout_sec_ = getOrDeclareParameter<double>("driver.cmd_vel_timeout_sec", 0.2);

    // Publishers
    if (publish_odom_)
    {
      odom_pub_ = node_->create_publisher<nav_msgs::msg::Odometry>(odom_topic_, 10);
    }

    // Subscribers
    stop_sub_ = node_->create_subscription<std_msgs::msg::Empty>(
        stop_topic_, 10, std::bind(&DriverInterface::stopCB, this, std::placeholders::_1));

    cmd_vel_sub_ = node_->create_subscription<geometry_msgs::msg::Twist>(
        cmd_vel_topic_, 10, std::bind(&DriverInterface::cmdVelCB, this, std::placeholders::_1));

    connectClient();
    configureHandlers();
    ratio_drive_.setThrottle(drive_throttle_pct_);
    configureDriveMode();
    client_.runAsync();

    const int watchdog_ms = std::max(50, static_cast<int>(1000.0 / std::max(expected_cmd_vel_freq_, 1.0)));
    cmd_vel_watchdog_timer_ = node_->create_wall_timer(std::chrono::milliseconds(watchdog_ms),
                                                       std::bind(&DriverInterface::handleCmdVelWatchdog, this));
  }

private:
  /**
   * @brief Helper function to get a parameter value or declare it with a default if it doesn't exist.
   * @tparam T Parameter type.
   * @param name Parameter name.
   * @param default_value Default value to declare if parameter doesn't exist.
   * @return Parameter value.
   */
  template <typename T>
  T getOrDeclareParameter(const std::string& name, const T& default_value)
  {
    if (!node_->has_parameter(name))
    {
      return node_->declare_parameter<T>(name, default_value);
    }

    T value = default_value;
    node_->get_parameter(name, value);
    return value;
  }

  /**
   * @brief Connects to the robot server using libaria and handles connection errors.
   * @throws std::runtime_error if connection fails or is rejected by the robot.
   */
  void connectClient()
  {
    if (!protocol_.empty())
    {
      client_.enforceProtocolVersion(protocol_.c_str());
    }

    const char* password = password_.empty() ? nullptr : password_.c_str();
    if (!client_.blockingConnect(host_.c_str(), port_, true, user_.c_str(), password))
    {
      if (client_.wasRejected())
      {
        throw std::runtime_error("Robot rejected the drive interface connection.");
      }
      throw std::runtime_error("Could not connect drive interface to Omron robot server.");
    }

    client_.setRobotName(host_.c_str());
    RCLCPP_INFO(node_->get_logger(), "DriverInterface connected to %s:%d using libaria", host_.c_str(), port_);
  }

  /**
   * @brief Configures handlers for the robot server.
   */
  void configureHandlers()
  {
    if (!client_.dataExists("updateNumbers"))
    {
      RCLCPP_WARN(node_->get_logger(), "Server does not advertise updateNumbers; odometry will not update");
      return;
    }

    client_.addHandler("updateNumbers", &update_callback_);
    client_.request("updateNumbers", 50);
  }

  /**
   * @brief Configures the drive mode for the robot.
   */
  void configureDriveMode()
  {
    if (!client_.dataExists("setSafeDrive"))
    {
      RCLCPP_WARN(node_->get_logger(), "Server does not advertise setSafeDrive; leaving drive mode unchanged");
      return;
    }

    if (unsafe_drive_)
    {
      ratio_drive_.unsafeDrive();
      RCLCPP_WARN(node_->get_logger(), "Unsafe drive enabled for cmd_vel control");
    }
    else
    {
      ratio_drive_.safeDrive();
      RCLCPP_INFO(node_->get_logger(), "Safe drive enabled for cmd_vel control");
    }
  }

  /**
   * @brief Handles update numbers from the robot server.
   * @param packet The packet containing the update numbers.
   */
  void handleUpdateNumbers(ArNetPacket* packet)
  {
    // The packet structure is assumed to be:
    // byte: update type (ignored)
    // byte4: x in mm
    // byte4: y in mm
    // byte2: theta in degrees
    // byte2: x velocity in mm/s
    // byte2: theta velocity in deg/s
    // byte2: y velocity in mm/s

    packet->bufToByte2();
    const double x = static_cast<double>(packet->bufToByte4()) / 1000.0;
    const double y = static_cast<double>(packet->bufToByte4()) / 1000.0;
    const double theta_deg = static_cast<double>(packet->bufToByte2());
    const double x_vel_mps = static_cast<double>(packet->bufToByte2()) / 1000.0;
    const double theta_vel_rad_s = static_cast<double>(packet->bufToByte2()) * M_PI / 180.0;
    const double y_vel_mps = static_cast<double>(packet->bufToByte2()) / 1000.0;
    packet->bufToByte();

    // Update internal pose state within a mutex to ensure thread safety with the ROS callbacks that may access the pose.
    {
      std::lock_guard<std::mutex> lock(pose_mutex_);
      pose_x_ = x;
      pose_y_ = y;
      pose_theta_deg_ = theta_deg;
      have_pose_ = true;
    }

    // Capture the first pose as the odom origin. Subsequent updates are transformed into that initial frame,
    // so the published odom is a proper relative pose even when the robot starts with a non-zero heading.
    if (!initial_pose_set_)
    {
      initial_pose_x_ = pose_x_;
      initial_pose_y_ = pose_y_;
      initial_pose_theta_deg_ = pose_theta_deg_;
      initial_pose_set_ = true;
      return;
    }

    const double initial_theta_rad = initial_pose_theta_deg_ * M_PI / 180.0;
    const double delta_x = pose_x_ - initial_pose_x_;
    const double delta_y = pose_y_ - initial_pose_y_;
    const double cos_initial = std::cos(initial_theta_rad);
    const double sin_initial = std::sin(initial_theta_rad);

    const double relative_x = cos_initial * delta_x + sin_initial * delta_y;
    const double relative_y = -sin_initial * delta_x + cos_initial * delta_y;
    const double relative_theta_rad = std::atan2(std::sin((pose_theta_deg_ - initial_pose_theta_deg_) * M_PI / 180.0),
                                                 std::cos((pose_theta_deg_ - initial_pose_theta_deg_) * M_PI / 180.0));
    const double relative_x_vel_mps = cos_initial * x_vel_mps + sin_initial * y_vel_mps;
    const double relative_y_vel_mps = -sin_initial * x_vel_mps + cos_initial * y_vel_mps;

    theta_rad_ = relative_theta_rad;

    nav_msgs::msg::Odometry odom_msg;
    odom_msg.header.stamp = node_->now();
    odom_msg.header.frame_id = odom_frame_;
    odom_msg.child_frame_id = base_frame_;
    odom_msg.pose.pose.position.x = relative_x;
    odom_msg.pose.pose.position.y = relative_y;
    odom_msg.pose.pose.position.z = 0.0;

    odom_msg.pose.pose.orientation.z = std::sin(theta_rad_ / 2.0);
    odom_msg.pose.pose.orientation.w = std::cos(theta_rad_ / 2.0);

    odom_msg.twist.twist.linear.x = relative_x_vel_mps;
    odom_msg.twist.twist.linear.y = relative_y_vel_mps;
    odom_msg.twist.twist.angular.z = theta_vel_rad_s;

    if (publish_odom_ && odom_pub_)
    {
      odom_pub_->publish(odom_msg);
    }

    if (publish_robot_tf_)
    {
      geometry_msgs::msg::TransformStamped tf_msg;
      tf_msg.header = odom_msg.header;
      tf_msg.child_frame_id = base_frame_;

      tf_msg.transform.translation.x = relative_x;
      tf_msg.transform.translation.y = relative_y;
      tf_msg.transform.translation.z = 0.0;

      tf_msg.transform.rotation = odom_msg.pose.pose.orientation;

      tf_broadcaster_->sendTransform(tf_msg);
    }
  }

  /**
   * @brief Callback for stop messages. Stops the robot immediately.
   * @param msg The received stop message (empty).
   */
  void stopCB(const std_msgs::msg::Empty& /*msg*/)
  {
    cmd_vel_active_ = false;
    stop_sent_ = true;
    ratio_drive_.stop();
    if (client_.dataExists("stop"))
    {
      client_.requestOnce("stop");
    }
  }

  /**
   * @brief Callback for cmd_vel messages. Converts Twist messages to drive commands and sends them to the robot.
   * Also updates the last command time for the watchdog.
   * 
   * @param msg The received cmd_vel message.
   */
  void cmdVelCB(const geometry_msgs::msg::Twist& msg)
  {
    last_cmd_vel_time_ = node_->now();
    stop_sent_ = false;
    cmd_vel_active_ = std::fabs(msg.linear.x) > 1e-3 || std::fabs(msg.angular.z) > 1e-3;
    if (!cmd_vel_active_)
    {
      ratio_drive_.stop();
      return;
    }

    if (!client_.dataExists("ratioDrive"))
    {
      RCLCPP_WARN_THROTTLE(node_->get_logger(), *node_->get_clock(), 5000, "Server does not advertise ratioDrive");
      return;
    }

    const double max_linear_mps = std::max(std::fabs(min_lin_speed_), std::fabs(max_lin_speed_)) / 1000.0;
    const double max_angular_rad_s = std::max(std::fabs(min_ang_speed_), std::fabs(max_ang_speed_)) * M_PI / 180.0;
    const double trans_ratio = toPercent(msg.linear.x, max_linear_mps);
    const double rot_ratio = toPercent(msg.angular.z, max_angular_rad_s);

    ratio_drive_.setThrottle(drive_throttle_pct_);
    ratio_drive_.setLatVelRatio(0.0);
    ratio_drive_.setTransVelRatio(trans_ratio);
    ratio_drive_.setRotVelRatio(rot_ratio);
  }

  void handleCmdVelWatchdog()
  {
    if (!cmd_vel_active_)
    {
      return;
    }

    if ((node_->now() - last_cmd_vel_time_).seconds() > cmd_vel_timeout_sec_)
    {
      cmd_vel_active_ = false;
      if (!stop_sent_)
      {
        ratio_drive_.stop();
        stop_sent_ = true;
      }
    }
  }


private:
  /**
   * @brief Helper function to convert a velocity value to a percentage of the maximum, clamped to [-100, 100].
   * @param value The velocity value to convert.
   * @param max_abs_value The maximum absolute velocity corresponding to 100%.
   * @return The velocity as a percentage of the maximum, clamped to [-100, 100].
   */
  static double toPercent(double value, double max_abs_value)
  {
    if (max_abs_value <= 0.0)
    {
      return 0.0;
    }

    const double percent = (value / max_abs_value) * 100.0;
    return std::clamp(percent, -100.0, 100.0);
  }

  // ROS node and libaria client
  rclcpp::Node::SharedPtr node_;

  // Libaria runtime manager to ensure proper initialization and shutdown of libaria
  amr_core::LibAriaRuntime aria_runtime_;

  // Libaria client and drive interface
  ArClientBase client_;
  ArClientRatioDrive ratio_drive_;

  //
  ArFunctor1C<DriverInterface, ArNetPacket*> update_callback_;

  // Parameters
  std::string host_;
  int port_{ 7272 };
  std::string user_;
  std::string password_;
  std::string protocol_;

  std::string odom_topic_{ "amr/odom" };
  std::string cmd_vel_topic_{ "amr/cmd_vel" };
  std::string stop_topic_{ "amr/stop" };
  bool publish_odom_{ true };
  bool publish_robot_tf_{ true };

  std::string odom_frame_{ "odom" };
  std::string base_frame_{ "base_link" };

  double expected_cmd_vel_freq_{ 20.0 };
  double min_lin_speed_{ -1000.0 };
  double max_lin_speed_{ 1000.0 };
  double min_ang_speed_{ -30.0 };
  double max_ang_speed_{ 30.0 };
  double drive_throttle_pct_{ 100.0 };
  double cmd_vel_timeout_sec_{ 0.2 };
  bool unsafe_drive_{ true };

  std::mutex pose_mutex_;
  
  double pose_x_{ 0.0 };
  double pose_y_{ 0.0 };
  double pose_theta_deg_{ 0.0 };

  double initial_pose_x_{ 0.0 };
  double initial_pose_y_{ 0.0 };
  double initial_pose_theta_deg_{ 0.0 };
  double theta_rad_{ 0.0 };

  bool have_pose_{ false };
  bool cmd_vel_active_{ false };
  bool stop_sent_{ false };
  bool initial_pose_set_{ false };

  rclcpp::Time last_cmd_vel_time_{ 0, 0, RCL_ROS_TIME };

  // Subscribers
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr stop_sub_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr odom_reset_sub_;
  rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr local_plan_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr goal_pose_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr initial_pose_sub_;

  // Publishers
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr cmd_vel_watchdog_timer_;
};
