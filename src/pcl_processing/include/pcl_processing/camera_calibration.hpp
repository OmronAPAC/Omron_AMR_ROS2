#include "geometry_msgs/msg/point.hpp"

#pragma once

class CameraCalibration
{
public:
  CameraCalibration() {};
  
  geometry_msgs::msg::Point TranslateRobotOrigin(geometry_msgs::msg::Point input, float offset_x, float offset_y) const;
};