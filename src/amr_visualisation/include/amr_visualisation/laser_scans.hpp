#include "rclcpp/rclcpp.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "geometry_msgs/msg/quaternion.hpp"
#include "std_msgs/msg/string.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "om_aiv_msg/srv/arcl_api.hpp"
#include "om_aiv_msg/srv/arcl_listen.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <chrono>

#pragma once

// Configurable values.
std::string PACK_NAME;
std::string MAP_NAME;
std::string HEAD_FRAME;
std::string VIS_TOPIC;
std::string rng_device;
float LS_POINTS_A_CLR;
float LS_POINTS_R_CLR;
float LS_POINTS_G_CLR;
float LS_POINTS_B_CLR;
// Non configurable values.

const std::string LS_POINTS_NS = "ls_points";
const std::string LS_SUB_TOPIC = "ldarcl_laser";
const std::string FA_NS = "f_areas";
const int32_t POINTS_M_ID = 0;
const int32_t LINES_M_ID = 1;
const int32_t LS_POINTS_M_ID = 2;
const double POINTS_X_SCALE = 0.045;
const double POINTS_Y_SCALE = 0.045;
const double LINES_X_SCALE = 0.045;
const double LS_POINTS_X_SCALE = 0.045;
const double LS_POINTS_Y_SCALE = 0.045;

// Names for all config parameters.
const std::string VIS_TOPIC_PARAM = "vis_topic";
const std::string RNG_DEVICE_PARAM = "range_device";
const std::string LS_POINTS_A_CLR_PARAM = "ls_points_a_colour";
const std::string LS_POINTS_R_CLR_PARAM = "ls_points_r_colour";
const std::string LS_POINTS_G_CLR_PARAM = "ls_points_g_colour";
const std::string LS_POINTS_B_CLR_PARAM = "ls_points_b_colour";

class LaserScans : public rclcpp::Node
{
public:
  /** \brief Constructor */
  LaserScans();

private:
  /**
   * @brief Callback function for subscribing to laser scan values topic.
   * 
   * @param msg Message containing a string of values.
   */
  void laser_sub_cb(const std_msgs::msg::String::SharedPtr msg);

  /** \brief populates the Marker with all points */
  void populate_laser_scans(std::string vals_str);

  /** \brief Updates stamp and clears RViz of the previously published points */
  void update_laser_points();

  /** \brief initializes constant parameters in laser scans */
  void init_laser_scans();

  /** \brief collects a set of x and y coordinates and adds them to the marker */
  void add_laser_point(double x, double y);

  void timer_callback();

  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr laser_scan_pub;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr laser_data_sub;
  rclcpp::TimerBase::SharedPtr clear_laser_timer;
  
  visualization_msgs::msg::Marker laser_points;
};
