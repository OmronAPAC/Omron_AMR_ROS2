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

class Pcl_Filter : public rclcpp::Node
{
  public:
    Pcl_Filter()
    : Node("pcl_filter")
    {
      subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/zed2/zed_node/point_cloud/cloud_registered", 10, std::bind(&Pcl_Filter::topic_callback, this, std::placeholders::_1));
      publisher_ = this->create_publisher<geometry_msgs::msg::Point>("obstacle_point", 10);
    }

  private:
    void topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) const
    {
      float min_bound_x = -0.55;
      float min_bound_y = 0.55;
      float max_bound_x = -0.55;
      float max_bound_y = 1.2;
      float min_x = INT_MAX;
      float min_y = INT_MAX;
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
          if (*iter_x < min_x)
          {
            min_x = *iter_x;
          }
          if (*iter_y < min_y)
          {
            min_y = *iter_y;
          }
          RCLCPP_INFO(this->get_logger(), "coord of bound point is x %f y %f", *iter_x, *iter_y);
        }
      }
      geometry_msgs::msg::Point closest_point;
      closest_point.x = min_x;
      closest_point.y = min_y;
      publisher_->publish(closest_point);
    }
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Pcl_Filter>());
  rclcpp::shutdown();
  return 0;
}
