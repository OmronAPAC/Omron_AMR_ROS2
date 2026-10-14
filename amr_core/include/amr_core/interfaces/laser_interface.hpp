#pragma once

#include <ArNetworking/ArNetworking.h>

#include <geometry_msgs/msg/transform_stamped.hpp>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "std_msgs/msg/string.hpp"
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <string>
#include <memory>
#include <mutex>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <limits>

#include "amr_core/utils/libaria_runtime.hpp"

/**
 * @brief Node for publishing LaserScan messages from libaria laser packets while preserving amr_core frame correction.
 */
class LaserInterface
{
public:
  /**
   * @brief Configuration for a laser device, including parameters for interpreting laser packets and the publisher
   * for the resulting LaserScan messages.
   *
   * @param frame_id TF frame ID to use for the LaserScan messages.
   * @param topic_name ROS topic name to publish the LaserScan messages on.
   * @param request_name Name of the laser data request to send to the robot server.
   * @param request_period_ms Period in milliseconds to request laser data from the robot server.
   * @param angle_min Minimum angle of the laser scan in radians.
   * @param angle_max Maximum angle of the laser scan in radians.
   * @param angle_increment Angle increment between laser scan readings in radians.
   * @param range_min Minimum valid range value for the laser scan in meters.
   * @param range_max Maximum valid range value for the laser scan in meters.
   * @param publisher ROS publisher for the resulting LaserScan messages.
   */
  struct LaserDeviceConfig
  {
    std::string frame_id;
    std::string topic_name;
    std::string request_name;
    int request_period_ms{ 200 };
    double angle_min{ -M_PI };
    double angle_max{ M_PI };
    double angle_increment{ M_PI / 360.0 };
    double range_min{ 0.02 };
    double range_max{ 30.0 };
    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr publisher;
  };

  /**
   * @brief Constructor. Initializes node pointer.
   * @param node Shared pointer to rclcpp::Node.
   */
  LaserInterface(rclcpp::Node::SharedPtr node)
    : node_(std::move(node))
    , primary_laser_callback_(this, &LaserInterface::handlePrimaryLaser)
    , low_laser_callback_(this, &LaserInterface::handleLowLaser)
    , update_callback_(this, &LaserInterface::handleUpdateNumbers)
  {
  }

  ~LaserInterface()
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
    enable_primary_laser_ = getOrDeclareParameter<bool>("laser.main_laser.enabled", true);
    enable_low_laser_ = getOrDeclareParameter<bool>("laser.low_laser.enabled", false);

    primary_laser_ = loadLaserDeviceConfig("laser.main_laser", LaserDeviceConfig{
                                                                   "laser_frame",
                                                                   "scan",
                                                                   "Laser_1Current",
                                                                   200,
                                                                   -2.0 * M_PI / 3.0,
                                                                   2.0 * M_PI / 3.0,
                                                                   M_PI / 360.0,
                                                                   0.02,
                                                                   15.0,
                                                                   nullptr,
                                                               });

    validateLaserDeviceConfig(primary_laser_, "laser.main_laser");
    if (enable_primary_laser_)
    {
      primary_laser_.publisher = node_->create_publisher<sensor_msgs::msg::LaserScan>(primary_laser_.topic_name, 10);
    }

    low_laser_ = loadLaserDeviceConfig("laser.low_laser", LaserDeviceConfig{
                                                              "laser_frame_low",
                                                              "scan_low",
                                                              "Laser_2Current",
                                                              200,
                                                              -63.0 * M_PI / 180.0,
                                                              63.0 * M_PI / 180.0,
                                                              M_PI / 360.0,
                                                              0.02,
                                                              4.0,
                                                              nullptr,
                                                          });
    validateLaserDeviceConfig(low_laser_, "laser.low_laser");

    base_frame_ = getOrDeclareParameter<std::string>("driver.base_frame", "base_link");
    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(node_->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_, node_, false);

    if (enable_low_laser_)
    {
      low_laser_.publisher = node_->create_publisher<sensor_msgs::msg::LaserScan>(low_laser_.topic_name, 10);
    }

    connectClient();
    configureHandlers();
    client_.runAsync();
  }

private:
  /**
   * @brief Helper function to get a parameter value or declare it with a default if it doesn't exist.
   * This simplifies the process of loading parameters with defaults and ensures that all parameters are declared on the
   * node.
   * @param name Name of the parameter to get or declare.
   * @param default_value Default value to use if the parameter does not already exist.
   * @return The value of the parameter, either existing or newly declared with the default.
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
   * @brief Loads laser device configuration from parameters with a given prefix, using defaults for any missing
   * parameters.
   * @param prefix Parameter name prefix for the laser device configuration.
   * @param defaults Default configuration values to use for any parameters that are not set.
   * @return Loaded LaserDeviceConfig with parameters from the node or defaults.
   */
  LaserDeviceConfig loadLaserDeviceConfig(const std::string& prefix, const LaserDeviceConfig& defaults)
  {
    LaserDeviceConfig config = defaults;
    config.frame_id = getOrDeclareParameter<std::string>(prefix + ".frame_id", defaults.frame_id);
    config.topic_name = getOrDeclareParameter<std::string>(prefix + ".topic", defaults.topic_name);
    config.request_name = getOrDeclareParameter<std::string>(prefix + ".request", defaults.request_name);
    config.request_period_ms = getOrDeclareParameter<int>(prefix + ".request_period_ms", defaults.request_period_ms);
    config.angle_min = getOrDeclareParameter<double>(prefix + ".angle_min", defaults.angle_min);
    config.angle_max = getOrDeclareParameter<double>(prefix + ".angle_max", defaults.angle_max);
    config.angle_increment = getOrDeclareParameter<double>(prefix + ".angle_increment", defaults.angle_increment);
    config.range_min = getOrDeclareParameter<double>(prefix + ".range_min", defaults.range_min);
    config.range_max = getOrDeclareParameter<double>(prefix + ".range_max", defaults.range_max);
    return config;
  }

  bool lookupLaserTransform(const LaserDeviceConfig& config, double& sensor_x, double& sensor_y, double& sensor_yaw)
  {
    if (!tf_buffer_)
    {
      return false;
    }

    try
    {
      const geometry_msgs::msg::TransformStamped transform =
          tf_buffer_->lookupTransform(base_frame_, config.frame_id, rclcpp::Time(0));
      sensor_x = transform.transform.translation.x;
      sensor_y = transform.transform.translation.y;

      const auto& rotation = transform.transform.rotation;
      const double siny_cosp = 2.0 * (rotation.w * rotation.z + rotation.x * rotation.y);
      const double cosy_cosp = 1.0 - 2.0 * (rotation.y * rotation.y + rotation.z * rotation.z);
      sensor_yaw = std::atan2(siny_cosp, cosy_cosp);
      return true;
    }
    catch (const std::exception& ex)
    {
      RCLCPP_WARN_THROTTLE(node_->get_logger(), *node_->get_clock(), 5000, "Could not resolve TF from %s to %s: %s",
                           base_frame_.c_str(), config.frame_id.c_str(), ex.what());
      return false;
    }
  }

  /**
   * @brief Validates laser device configuration parameters and applies defaults or corrections if necessary, while
   * logging warnings for any issues found.
   *
   * @param config LaserDeviceConfig to validate and correct if necessary.
   * @param prefix Parameter name prefix to use in warning messages.
   *
   * This function checks for the following issues:
   * - angle_increment must be positive; if not, it defaults to 0.5 degree (pi/360 radians).
   * - angle_max must be greater than angle_min; if not, it defaults to angle_min + angle_increment.
   * - range_max must be greater than range_min; if not, range_min defaults to 0.02 m and range_max defaults to 30.0 m.
   */
  void validateLaserDeviceConfig(LaserDeviceConfig& config, const char* prefix)
  {
    if (config.angle_increment <= 0.0)
    {
      RCLCPP_WARN(node_->get_logger(), "%s.angle_increment must be positive; defaulting to 0.5 degree", prefix);
      config.angle_increment = M_PI / 360.0;
    }
    if (config.angle_max <= config.angle_min)
    {
      RCLCPP_WARN(node_->get_logger(), "%s.angle_max must exceed angle_min; defaulting to full configured FOV", prefix);
      config.angle_max = config.angle_min + config.angle_increment;
    }
    if (config.range_max <= config.range_min)
    {
      RCLCPP_WARN(node_->get_logger(), "%s.range_max must exceed range_min; defaulting to 30.0 m", prefix);
      config.range_min = 0.02;
      config.range_max = 30.0;
    }
  }

  /**
   * @brief Connects to the robot server using the configured host, port, user, password, and protocol. Throws
   * std::runtime_error if the connection fails or is rejected by the robot.
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
        throw std::runtime_error("Robot rejected the laser interface connection.");
      }
      throw std::runtime_error("Could not connect laser interface to Omron robot server.");
    }

    client_.setRobotName(host_.c_str());
    RCLCPP_INFO(node_->get_logger(), "LaserInterface connected to %s:%d using libaria", host_.c_str(), port_);
  }

  /**
   * @brief Configures data handlers for the robot server client based on the loaded laser device configurations. This
   * includes requesting the appropriate data packets from the robot server at the configured periods and setting up
   * the corresponding handler functions to process incoming data.
   */
  void configureHandlers()
  {
    if (client_.dataExists("updateNumbers"))
    {
      client_.addHandler("updateNumbers", &update_callback_);
      client_.request("updateNumbers", 50);
    }

    if (enable_primary_laser_)
    {
      configureLaserHandler(primary_laser_, primary_laser_callback_);
    }
    if (enable_low_laser_)
    {
      configureLaserHandler(low_laser_, low_laser_callback_);
    }
  }

  /**
   * @brief Helper function to configure a laser data handler for a given LaserDeviceConfig and callback. This checks if
   * the requested data exists on the robot server, adds the handler for it, and sends the request to the robot server
   * at the configured period. If the requested data does not exist, a warning is logged.
   */
  void configureLaserHandler(LaserDeviceConfig& config, ArFunctor1C<LaserInterface, ArNetPacket*>& callback)
  {
    if (!client_.dataExists(config.request_name.c_str()))
    {
      RCLCPP_WARN(node_->get_logger(), "Server does not advertise %s", config.request_name.c_str());
      return;
    }

    client_.addHandler(config.request_name.c_str(), &callback);
    client_.request(config.request_name.c_str(), config.request_period_ms);
  }

  /**
   * @brief Handler function for processing "updateNumbers" packets from the robot server. This extracts the robot's
   * current pose (x, y, theta) from the packet and updates the internal state of the LaserInterface. The pose is stored
   * in millimeters for x and y, and degrees for theta, as provided by the robot server. This information is used to
   * correct the laser scan data for the robot's current position and orientation.
   * @param packet Incoming ArNetPacket containing the updateNumbers data from the robot server.
   *
   * The packet is expected to have the following structure based on the robot server's data format:
   * - Byte2: Some header or identifier (ignored in this handler)
   * - Byte4: Robot's x position in millimeters (signed integer)
   * - Byte4: Robot's y position in millimeters (signed integer)
   * - Byte2: Robot's orientation (theta) in degrees (signed integer)
   * - Byte2: Additional data (ignored in this handler)
   * - Byte2: Additional data (ignored in this handler)
   * - Byte2: Additional data (ignored in this handler)
   * - Byte: Additional data (ignored in this handler)
   */
  void handleUpdateNumbers(ArNetPacket* packet)
  {
    packet->bufToByte2();
    const double x = static_cast<double>(packet->bufToByte4());
    const double y = static_cast<double>(packet->bufToByte4());
    const double theta_deg = static_cast<double>(packet->bufToByte2());
    packet->bufToByte2();
    packet->bufToByte2();
    packet->bufToByte2();
    packet->bufToByte();

    std::lock_guard<std::mutex> lock(pose_mutex_);
    pose_x_mm_ = x;
    pose_y_mm_ = y;
    pose_theta_deg_ = theta_deg;
    have_pose_ = true;
  }

  /**
   * @brief Handler function for processing primary laser data packets from the robot server. This extracts the laser
   * scan data from the packet, applies corrections based on the robot's current pose, and publishes a LaserScan message
   * on the configured topic. The laser scan data is expected to be in the form of (x, y) coordinates of detected points
   * relative to the robot, which are then transformed into range and angle measurements for the LaserScan message.
   */
  void handlePrimaryLaser(ArNetPacket* packet)
  {
    handleLaserPacket(packet, primary_laser_);
  }

  /**
   * @brief Handler function for processing low laser data packets from the robot server. This functions similarly to
   * the primary laser handler, but uses the low laser configuration for interpreting the packet and publishing the
   * LaserScan message. This allows for handling a second laser device with different parameters and topic.
   */
  void handleLowLaser(ArNetPacket* packet)
  {
    handleLaserPacket(packet, low_laser_);
  }

  /**
   * @brief Common handler function for processing laser data packets from the robot server. This function is used by
   * both the primary and low laser handlers to extract laser scan data from the packet, apply pose corrections, and
   * publish a LaserScan message. The specific configuration for interpreting the packet and publishing is determined by
   * the provided LaserDeviceConfig.
   *
   * The packet is expected to have the following structure based on the robot server's data format for laser scans:
   * - Byte4: Number of laser readings (N)
   * - For each reading (repeated N times):
   *   - Byte4: x coordinate of the detected point in millimeters (signed integer)
   *   - Byte4: y coordinate of the detected point in millimeters (signed integer)
   */
  void handleLaserPacket(ArNetPacket* packet, const LaserDeviceConfig& config)
  {
    const int num_readings = packet->bufToByte4();
    if (num_readings <= 0)
    {
      RCLCPP_WARN_THROTTLE(node_->get_logger(), *node_->get_clock(), 5000, "Received empty laser packet");
      return;
    }

    if (!have_pose_)
    {
      RCLCPP_WARN_THROTTLE(node_->get_logger(), *node_->get_clock(), 5000,
                           "Skipping laser packet because robot pose is not available yet");
      return;
    }

    double sensor_x = 0.0;
    double sensor_y = 0.0;
    double sensor_yaw = 0.0;
    if (!lookupLaserTransform(config, sensor_x, sensor_y, sensor_yaw))
    {
      return;
    }

    double laser_x = 0.0;
    double laser_y = 0.0;
    double laser_theta = 0.0;
    {
      std::lock_guard<std::mutex> lock(pose_mutex_);
      laser_x = pose_x_mm_;
      laser_y = pose_y_mm_;
      laser_theta = pose_theta_deg_;
    }

    const double bounded_angle_max = std::max(config.angle_max, config.angle_min + config.angle_increment);
    const std::size_t bin_count =
        static_cast<std::size_t>(std::llround((bounded_angle_max - config.angle_min) / config.angle_increment)) + 1U;
    const double effective_angle_increment = config.angle_increment;

    sensor_msgs::msg::LaserScan scan_msg;
    scan_msg.header.stamp = node_->now();
    scan_msg.header.frame_id = config.frame_id;
    scan_msg.angle_min = static_cast<float>(config.angle_min);
    scan_msg.angle_max =
        static_cast<float>(config.angle_min + effective_angle_increment * static_cast<double>(bin_count - 1U));
    scan_msg.angle_increment = static_cast<float>(effective_angle_increment);
    scan_msg.range_min = static_cast<float>(config.range_min);
    scan_msg.range_max = static_cast<float>(config.range_max);
    scan_msg.scan_time = config.request_period_ms / 1000.0f;
    scan_msg.time_increment = bin_count > 1 ? scan_msg.scan_time / static_cast<float>(bin_count - 1U) : 0.0f;
    scan_msg.ranges.assign(bin_count, std::numeric_limits<float>::infinity());

    const double theta_rad = laser_theta * M_PI / 180.0;
    const double c = std::cos(theta_rad);
    const double s = std::sin(theta_rad);

    for (int i = 0; i < num_readings; ++i)
    {
      const double x_mm = static_cast<double>(packet->bufToByte4());
      const double y_mm = static_cast<double>(packet->bufToByte4());
      const double dx = x_mm - laser_x;
      const double dy = y_mm - laser_y;
      const double point_x_base = c * dx + s * dy;
      const double point_y_base = -s * dx + c * dy;
      const double point_x_sensor = point_x_base / 1000.0 - sensor_x;
      const double point_y_sensor = point_y_base / 1000.0 - sensor_y;

      const double sensor_c = std::cos(sensor_yaw);
      const double sensor_s = std::sin(sensor_yaw);
      const double point_x_laser = sensor_c * point_x_sensor + sensor_s * point_y_sensor;
      const double point_y_laser = -sensor_s * point_x_sensor + sensor_c * point_y_sensor;

      const double range = std::hypot(point_x_laser, point_y_laser);
      if (range < config.range_min || range > config.range_max)
      {
        continue;
      }

      const double angle = std::atan2(point_y_laser, point_x_laser);
      if (angle < config.angle_min || angle > scan_msg.angle_max)
      {
        continue;
      }

      const std::size_t index =
          static_cast<std::size_t>(std::floor((angle - config.angle_min) / effective_angle_increment));
      if (index >= scan_msg.ranges.size())
      {
        continue;
      }

      scan_msg.ranges[index] = std::min(scan_msg.ranges[index], static_cast<float>(range));
    }

    if (config.publisher)
    {
      config.publisher->publish(scan_msg);
    }
  }

  rclcpp::Node::SharedPtr node_;
  amr_core::LibAriaRuntime aria_runtime_;
  ArClientBase client_;
  ArFunctor1C<LaserInterface, ArNetPacket*> primary_laser_callback_;
  ArFunctor1C<LaserInterface, ArNetPacket*> low_laser_callback_;
  ArFunctor1C<LaserInterface, ArNetPacket*> update_callback_;

  std::mutex pose_mutex_;
  double pose_x_mm_{ 0.0 };
  double pose_y_mm_{ 0.0 };
  double pose_theta_deg_{ 0.0 };
  bool have_pose_{ false };

  std::string host_;
  int port_{ 7272 };
  std::string user_;
  std::string password_;
  std::string protocol_;
  std::string base_frame_{ "base_link" };

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  LaserDeviceConfig primary_laser_;
  LaserDeviceConfig low_laser_;
  bool enable_primary_laser_{ true };
  bool enable_low_laser_{ false };
};