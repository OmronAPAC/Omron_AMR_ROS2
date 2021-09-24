#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include <pcl/PCLPointCloud2.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/passthrough.h>
#include "geometry_msgs/msg/point.hpp"

class Add_Obstacle : public rclcpp::Node
{
  public:
    Add_Obstacle()
    : Node("add_obstacle")
    {
      subscription_ = this->create_subscription<geometry_msgs::msg::Point>(
      "obstacle_point", 10, std::bind(&Add_Obstacle::topic_callback, this, std::placeholders::_1));
    }

  private:
    void topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "filtered cloud");
    }

    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Add_Obstacle>());
  rclcpp::shutdown();
  return 0;
}
