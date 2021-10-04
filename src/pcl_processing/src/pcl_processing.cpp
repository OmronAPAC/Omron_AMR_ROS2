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
#include <pcl/filters/statistical_outlier_removal.h>
#include "geometry_msgs/msg/point.hpp"
#include <string>
#include "pcl_processing/camera_calibration.hpp"

class PclProcessing : public rclcpp::Node
{
  public:
    PclProcessing()
    : Node("pcl_processing", rclcpp::NodeOptions()
            .allow_undeclared_parameters(true)
            .automatically_declare_parameters_from_overrides(true))
    {
      subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/zed2/zed_node/point_cloud/cloud_registered", 10, 
        std::bind(&PclProcessing::topic_callback, this, std::placeholders::_1));
      publisher_ = this->create_publisher<geometry_msgs::msg::Point>("obstacle_point", 10);
      cloud_publisher = this->create_publisher<sensor_msgs::msg::PointCloud2>("cloud_in", 10);
      calibrator = CameraCalibration();

      rclcpp::Parameter min_bound_x_param = this->get_parameter("min_bound_x");
      rclcpp::Parameter max_bound_x_param = this->get_parameter("max_bound_x");
      rclcpp::Parameter min_bound_y_param = this->get_parameter("min_bound_y");
      rclcpp::Parameter max_bound_y_param = this->get_parameter("max_bound_y");
      rclcpp::Parameter min_bound_z_param = this->get_parameter("min_bound_z");
      rclcpp::Parameter max_bound_z_param = this->get_parameter("max_bound_z");
      rclcpp::Parameter camera_offset_x = this->get_parameter("camera_x_offset");
      rclcpp::Parameter camera_offset_y = this->get_parameter("camera_y_offset");

      min_bound_x = min_bound_x_param.as_double();
      max_bound_x = max_bound_x_param.as_double();
      min_bound_y = min_bound_y_param.as_double();
      max_bound_y = max_bound_y_param.as_double();
      min_bound_z = min_bound_z_param.as_double();
      max_bound_z = max_bound_z_param.as_double();
    }

  private:
    void topic_callback(sensor_msgs::msg::PointCloud2::SharedPtr msg) const
    {
      // RCLCPP_INFO(this->get_logger(), "callback");

      bool has_obstruction = false;
      
      // this converts the pointcloud2 message into something that pcl can use
      pcl::PCLPointCloud2 pc;
      sensor_msgs::msg::PointCloud2 pub_msg;
      pcl_conversions::toPCL(*msg, pc);
      pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
      pcl::PointCloud<pcl::PointXYZ>::Ptr rotated_cloud(new pcl::PointCloud<pcl::PointXYZ>);
      pcl::fromPCLPointCloud2(pc,*temp_cloud);

      // Outlier filter
      pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
      sor.setInputCloud (temp_cloud);
      sor.setMeanK (50);
      sor.setStddevMulThresh (1);
      sor.filter (*rotated_cloud);

      pcl::toROSMsg(*rotated_cloud, pub_msg);
      pub_msg.header.frame_id = "processed_cloud";

      // Bounding box and nearest distance checker
      geometry_msgs::msg::Point obstruction;
      float smallest_distance = INT_MAX;

      for (sensor_msgs::PointCloud2ConstIterator<float> iter_x(pub_msg, "x"),
        iter_y(pub_msg, "y"), iter_z(pub_msg, "z");
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
          *iter_y >= min_bound_y && *iter_y <= max_bound_y &&
          *iter_z >= min_bound_z && *iter_z <= max_bound_z)
        {
          geometry_msgs::msg::Point current_point;
          current_point.x = *iter_x;
          current_point.y = *iter_y;
          current_point = calibrator.TranslateRobotOrigin(current_point, camera_offset_x, camera_offset_y);

          float dist = std::hypot(current_point.x, current_point.y);
          if (dist < smallest_distance)
          {
            // RCLCPP_INFO(this->get_logger(), "dist is %f smallest is %f", dist, smallest_distance);
            smallest_distance = dist;
            obstruction.x = current_point.x;
            obstruction.y = current_point.y;
            has_obstruction = true;
            // RCLCPP_INFO(this->get_logger(), "coord of min points is x %f y %f", obstruction.x, obstruction.y);
          }
        }
      }
      // Publishes the filtered cloud for visualization and testing purposes
      cloud_publisher->publish(pub_msg);
      if (!has_obstruction)
      {
        return;
      }
      // compensate for camera's position on the robot
      // RCLCPP_INFO(this->get_logger(), "coord of min points is x %f y %f", obstruction.x, obstruction.y);
      // obstruction.x += camera_offset_x;
      // obstruction.y += camera_offset_y;
      // RCLCPP_INFO(this->get_logger(), "coord of MODIFIED points is x %f y %f", obstruction.x, obstruction.y);

      publisher_->publish(obstruction);
      // obstruction.x = obstruction.x/2;
      // obstruction.y = obstruction.y/2;
      // publisher_->publish(obstruction);
    }

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
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions node_options;
  node_options.allow_undeclared_parameters(true);
  rclcpp::spin(std::make_shared<PclProcessing>());
  rclcpp::shutdown();
  return 0;
}
