#include <memory>
#include <string>
#include <math.h>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/point_cloud2_iterator.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include <pcl/PCLPointCloud2.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/conditional_removal.h> 
#include <pcl/filters/radius_outlier_removal.h>
#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "om_aiv_msg/msg/status.hpp"
#include "visualization_msgs/msg/marker.hpp"

#include "pcl_processing/camera_calibration.hpp"


#pragma once


class PclProcessing : public rclcpp::Node
{
public:
  PclProcessing();
  

private:
  /** \brief topic callback for pointcloud data*/
  void topic_callback(sensor_msgs::msg::PointCloud2::SharedPtr msg);

  /** \brief topic callback for AMR status data*/
  void status_callback(om_aiv_msg::msg::Status::SharedPtr msg);

  /** \brief topic callback for laser scans data*/
  void laser_callback(visualization_msgs::msg::Marker::SharedPtr msg);

  /** \brief checks which partition of the horizontal */
  float check_slice(geometry_msgs::msg::Point current_point);

  /** \brief Coordinates in front of the robot are converted to world-based coordinates */
  geometry_msgs::msg::Point convert_world_coord(geometry_msgs::msg::Point current_point);

  /** \brief This function takes in heading in radians and distance and returns the coordinate relative position to the robot */
  geometry_msgs::msg::Point get_world_base_coord(double theta, double distance);

  /** \brief The point is compared against a stored array of past points to check whether a point nearby is already recently added */
  bool check_recency_and_proximity(geometry_msgs::msg::Point current_point);

  /** \brief The point is compared against the latest laserscans from the AMR */
  bool check_laserscans_proximity(geometry_msgs::msg::Point current_point);

  /** \brief the point is added to the history array for comparison */
  void add_point_to_history(geometry_msgs::msg::Point current_point);


  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
  rclcpp::Subscription<om_aiv_msg::msg::Status>::SharedPtr status_sub;
  rclcpp::Subscription<visualization_msgs::msg::Marker>::SharedPtr laser_sub;

  rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_publisher;
  CameraCalibration calibrator;

  float min_bound_x = -0.55;
  float max_bound_x = 1.5;
  float min_bound_y = -0.75;
  float max_bound_y = 0.75;
  float min_bound_z = -0.5;
  float max_bound_z = 1.5;
  float camera_offset_y = 0;
  float camera_offset_x = 0.35;
  float camera_horizontal_tilt = 0;
  float camera_yaw_offset = 0;
  float cam_horizontal_fov;
  float odom_pos_x;
  float odom_pos_y;
  float decay_time;
  std::vector<geometry_msgs::msg::PoseStamped> history;
  std::vector<geometry_msgs::msg::Point> laser_scan_data;
  int history_iter;
  float distance_threshold;

  // Theta is the robot heading based off the x axis, counter clockwise gives positive value
  float theta;
  int points_count;

  float PI = 3.141592654;
  float RADIAN_CONST = 57.2958;
};