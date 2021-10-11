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
// #include "pcl_processing/pcl_processing.hpp"

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

      rclcpp::Parameter points_to_add = this->get_parameter("points_to_add");
      rclcpp::Parameter camera_horizontal_fov = this->get_parameter("camera_horizontal_fov");

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
      points_count = points_to_add.as_int();
      cam_horizontal_fov = camera_horizontal_fov.as_double();
    }

  private:
    void topic_callback(sensor_msgs::msg::PointCloud2::SharedPtr msg) const
    {
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
      std::vector<geometry_msgs::msg::Point> obstruction;
      std::vector<float> smallest_distance;

      // Initialize vector sizes
      for (int i=0; i<points_count; i++){
        geometry_msgs::msg::Point point;
        obstruction.push_back(point);
        float init_max_distance = INT_MAX;
        smallest_distance.push_back(init_max_distance);
      }

      // Iterate through each point in point cloud
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

        // Check if points are within bounding box
        if (*iter_x >= min_bound_x && *iter_x <= max_bound_x &&
          *iter_y >= min_bound_y && *iter_y <= max_bound_y &&
          *iter_z >= min_bound_z && *iter_z <= max_bound_z)
        {
          // Convert points to robot centre reference
          geometry_msgs::msg::Point current_point;
          current_point.x = *iter_x;
          current_point.y = *iter_y;
          current_point = calibrator.TranslateRobotOrigin(current_point, camera_offset_x, camera_offset_y);

          // check which slice points lie in
          float angle = std::atan2(current_point.y, current_point.x);
          angle += cam_horizontal_fov / 2;
          float slice = angle / (cam_horizontal_fov / points_count);

          // Adjust closest point in slice, record down coordinates
          float dist = std::hypot(current_point.x, current_point.y);
          if (dist < smallest_distance[slice])
          {
            // RCLCPP_INFO(this->get_logger(), "dist is %f smallest is %f", dist, smallest_distance);
            smallest_distance[slice] = dist;
            obstruction[slice].x = current_point.x;
            obstruction[slice].y = current_point.y;
            // RCLCPP_INFO(this->get_logger(), "coord of min points is x %f y %f", obstruction.x, obstruction.y);
          }
        }
      }
      // Publishes the filtered cloud for visualization and testing purposes
      cloud_publisher->publish(pub_msg);

      // RCLCPP_INFO(this->get_logger(), "coord of min points is x %f y %f", obstruction.x, obstruction.y);
      // RCLCPP_INFO(this->get_logger(), "coord of MODIFIED points is x %f y %f", obstruction.x, obstruction.y);
      for (int i=0; i < points_count; i++)
      {
        if (smallest_distance[i] != INT_MAX) 
        {
          publisher_->publish(obstruction[i]);
        }
      }
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
    float cam_horizontal_fov;
    int points_count;
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
