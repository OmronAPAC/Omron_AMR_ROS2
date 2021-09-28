#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include <pcl/PCLPointCloud2.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/passthrough.h>
#include "sensor_msgs/point_cloud2_iterator.hpp"
#include "geometry_msgs/msg/point.hpp"

class CheckBox : public rclcpp::Node
{
  public:
    CheckBox()
    : Node("CheckBox")
    {
      subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "cloud_in", 10, std::bind(&CheckBox::topic_callback, this, std::placeholders::_1));
      publisher_ = this->create_publisher<geometry_msgs::msg::Point>("obstacle_point", 10);
    }

  private:
    void topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) const
    {
      float min_bound_x = -0.55;
      float max_bound_x = 1.2;
      float min_bound_y = -0.55;
      float max_bound_y = 0.55;
      float position_offset_y = 0.35;
      float position_offset_x = 0;
      float smallest_distance = INT_MAX;
      geometry_msgs::msg::Point obstruction;
      bool has_obstruction = false;

      for (sensor_msgs::PointCloud2ConstIterator<float> iter_x(*msg, "x"),
        iter_y(*msg, "y"), iter_z(*msg, "z");
        iter_x != iter_x.end(); ++iter_x, ++iter_y, ++iter_z)
      {
        if (std::isnan(*iter_x) || std::isnan(*iter_y) || std::isnan(*iter_z)) 
        {
          RCLCPP_DEBUG(
            this->get_logger(),
            "rejected for nan in point(%f, %f, %f)\n",
            *iter_x, *iter_y, *iter_z);
          continue;
        }

        if (*iter_x >= min_bound_x && *iter_x <= max_bound_x &&
          *iter_y >= min_bound_y && *iter_y <= max_bound_y)
        {
          // RCLCPP_INFO(this->get_logger(), "coord of bound point is x %f y %f", *iter_x, *iter_y);
          // obstruction.x = *iter_x;
          // obstruction.y = *iter_y;
          // has_obstruction = true;
          // // RCLCPP_INFO(this->get_logger(), "coord of point is x %f y %f", obstruction.x, obstruction.y);
          
          // break;

          float dist = std::hypot(*iter_x, *iter_y);
          if (dist < smallest_distance)
          {
            // RCLCPP_INFO(this->get_logger(), "dist is %f smallest is %f", dist, smallest_distance);
            smallest_distance = dist;
            obstruction.x = *iter_y;
            obstruction.y = *iter_x;
            has_obstruction = true;
            // RCLCPP_INFO(this->get_logger(), "coord of min points is x %f y %f", min_x, min_y);
          }
        }

      }
      
      if (has_obstruction)
      {
        RCLCPP_INFO(this->get_logger(), "coord of point is x %f y %f", obstruction.x, obstruction.y);
        publisher_->publish(obstruction);
      }
      // RCLCPP_INFO(this->get_logger(), "Finished a loop");
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CheckBox>());
  rclcpp::shutdown();
  return 0;
}
