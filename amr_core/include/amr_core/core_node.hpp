#pragma once

#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <string>

#include "amr_core/interfaces/status_interface.hpp"
#include "amr_core/interfaces/laser_interface.hpp"
#include "amr_core/interfaces/drive_interface.hpp"

class CoreNode : public rclcpp::Node
{
public:
  CoreNode() : rclcpp::Node("core_node")
  {
  }

  /**
   * @brief Initializes and wires the libaria-backed interfaces used by the core node.
   */
  void initialize()
  {
    host_ = getOrDeclareParameter<std::string>("robot.ip", "127.0.0.1");
    port_ = getOrDeclareParameter<int>("robot.port", 7272);
    user_ = getOrDeclareParameter<std::string>("robot.user", "admin");
    password_ = getOrDeclareParameter<std::string>("robot.password", "");
    protocol_ = getOrDeclareParameter<std::string>("robot.protocol", "6MTX");
    publish_status_ = getOrDeclareParameter<bool>("status.publish", true);
    publish_main_laser_ = getOrDeclareParameter<bool>("laser.main_laser.enabled", true);
    publish_low_laser_ = getOrDeclareParameter<bool>("laser.low_laser.enabled", false);

    if (publish_status_)
    {
      try
      {
        status_interface_ = std::make_shared<StatusInterface>(this->shared_from_this());
        status_interface_->initialize(host_, port_, user_, password_, protocol_);
        RCLCPP_INFO(this->get_logger(), "Publishing status information enabled");
      }
      catch (const std::exception& ex)
      {
        status_interface_.reset();
        RCLCPP_ERROR(this->get_logger(), "StatusInterface initialization failed: %s", ex.what());
      }
    }
    else
    {
      RCLCPP_INFO(this->get_logger(), "Publishing status information disabled");
    }

    if (publish_main_laser_ || publish_low_laser_)
    {
      try
      {
        laser_scans_ = std::make_shared<LaserInterface>(this->shared_from_this());
        laser_scans_->initialize(host_, port_, user_, password_, protocol_);
        RCLCPP_INFO(this->get_logger(), "Publishing laser scans enabled");
      }
      catch (const std::exception& ex)
      {
        laser_scans_.reset();
        RCLCPP_ERROR(this->get_logger(), "LaserInterface initialization failed: %s", ex.what());
      }
    }
    else
    {
      RCLCPP_INFO(this->get_logger(), "Publishing laser scans disabled");
    }

    // DriverInterface
    try
    {
      driver_ = std::make_shared<DriverInterface>(this->shared_from_this());
      driver_->initialize(host_, port_, user_, password_, protocol_);
    }
    catch (const std::exception& ex)
    {
      driver_.reset();
      RCLCPP_ERROR(this->get_logger(), "DriverInterface initialization failed: %s", ex.what());
    }

    RCLCPP_INFO(this->get_logger(), "CoreNode initialized");
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
    if (!this->has_parameter(name))
    {
      return this->declare_parameter<T>(name, default_value);
    }

    T value = default_value;
    this->get_parameter(name, value);
    return value;
  }

private:
  // Status information
  std::shared_ptr<StatusInterface> status_interface_;

  // Laser scans
  std::shared_ptr<LaserInterface> laser_scans_;

  // DriverInterface
  std::shared_ptr<DriverInterface> driver_;

  // Parameters
  std::string host_;
  int port_{ 7272 };
  std::string user_;
  std::string password_;
  std::string protocol_;
  bool publish_status_{ true };
  bool publish_main_laser_{ true };
  bool publish_low_laser_{ false };
};