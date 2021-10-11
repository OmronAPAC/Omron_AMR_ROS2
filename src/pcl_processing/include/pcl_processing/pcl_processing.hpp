#include <memory>
#include <string>
#include <math.h>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include <pcl/PCLPointCloud2.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/passthrough.h>
#include "sensor_msgs/point_cloud2_iterator.hpp"
#include <pcl/filters/statistical_outlier_removal.h>
#include "geometry_msgs/msg/point.hpp"

#include "pcl_processing/camera_calibration.hpp"


#pragma once


class PclProcessing : public rclcpp::Node
{
public:
  PclProcessing();
  

private:
  /** \brief topic callback for pointcloud data*/
  void topic_callback(sensor_msgs::msg::PointCloud2::SharedPtr msg);

  /** \brief checks which partition of the horizontal */
  float check_slice(geometry_msgs::msg::Point current_point);


  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
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
  float cam_horizontal_fov;
  int points_count;
};