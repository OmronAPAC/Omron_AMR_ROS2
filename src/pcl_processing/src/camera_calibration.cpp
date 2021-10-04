#include "pcl_processing/camera_calibration.hpp"

geometry_msgs::msg::Point CameraCalibration::TranslateRobotOrigin(geometry_msgs::msg::Point input, float offset_x, float offset_y) const
{
  geometry_msgs::msg::Point translated_point;
  translated_point.x = input.x + offset_x;
  translated_point.y = input.y + offset_y;
  return translated_point;
}