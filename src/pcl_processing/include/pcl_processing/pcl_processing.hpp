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
  /** \brief topic callback for pointcloud data */
  void topic_callback(sensor_msgs::msg::PointCloud2::SharedPtr msg);

  /** \brief topic callback for points */
  void point_callback(geometry_msgs::msg::Point::SharedPtr msg);

  /** \brief topic callback for AMR status data */
  void status_callback(om_aiv_msg::msg::Status::SharedPtr msg);

  /** \brief topic callback for laser scans data */
  void laser_callback(visualization_msgs::msg::Marker::SharedPtr msg);

  /** \brief checks which partition of the horizontal */
  float check_slice(geometry_msgs::msg::Point current_point);

  /** \brief Coordinates in front of the robot are converted to world-based coordinates */
  geometry_msgs::msg::Point convert_world_coord(geometry_msgs::msg::Point current_point);

  /** \brief This function takes in heading in radians and distance and returns the coordinate relative position to the robot */
  geometry_msgs::msg::Point get_world_base_coord(double theta, double distance);

  /** \brief The point is compared against a stored array of past points to check whether a point nearby is already recently added */
  bool nearby_added(geometry_msgs::msg::Point current_point);

  /** \brief The point is compared against the latest laserscans from the AMR */
  bool near_laserscans(geometry_msgs::msg::Point current_point);

  /** \brief the point is added to the history array for comparison */
  void add_point_to_history(geometry_msgs::msg::Point current_point);

  /** \brief check if point being iterated is a valid point */
  bool isnan(const float iter_x, const float iter_y, const float iter_z);

  /** \brief check if points is outside bounding box */
  bool outside_bounds(const float iter_x, const float iter_y, const float iter_z);

  /** \brief restricts angle to -PI to +PI */
  float normalize_angle(float angle);

  /** \brief calculates compounded angle used for world coord conversion */
  float calc_combined_angle(geometry_msgs::msg::Point current_point, float robot_heading, float angle);


  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_subscriber;
  rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr point_subscriber;
  rclcpp::Subscription<om_aiv_msg::msg::Status>::SharedPtr status_subscriber;
  rclcpp::Subscription<visualization_msgs::msg::Marker>::SharedPtr laser_subscriber;

  rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr obstacle_publisher;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_publisher;
  CameraCalibration calibrator;

  float min_bound_x, max_bound_x;
  float min_bound_y, max_bound_y;
  float min_bound_z, max_bound_z;
  float camera_offset_x, camera_offset_y;
  float camera_roll_offset;
  float camera_pitch_offset;
  float camera_yaw_offset;
  float cam_horizontal_fov;
  float decay_time;
  float distance_threshold;
  std::vector<geometry_msgs::msg::PoseStamped> history;
  std::vector<geometry_msgs::msg::Point> laser_scan_data;
  int history_iter;
  int points_count;

  // Theta is robot heading based off the x axis, CCW gives positive value
  float odom_pos_x, odom_pos_y;
  float theta;

  float PI = 3.141592654;
  float RADIAN_CONST = 57.2958;
};