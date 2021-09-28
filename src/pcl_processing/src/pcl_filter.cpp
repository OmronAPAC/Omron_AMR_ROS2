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

class Pcl_Filter : public rclcpp::Node
{
  public:
    Pcl_Filter()
    : Node("pcl_filter")
    {
      subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/zed2/zed_node/point_cloud/cloud_registered", 10, std::bind(&Pcl_Filter::topic_callback, this, std::placeholders::_1));
      publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("cloud_in", 10);
    }

  private:
    void topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) const
    {
      // this converts the pointcloud2 message into something that pcl can use
      pcl::PCLPointCloud2 pc;
      sensor_msgs::msg::PointCloud2 pub_msg;
      pcl_conversions::toPCL(*msg, pc);
      pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
      pcl::PointCloud<pcl::PointXYZ>::Ptr rotated_cloud(new pcl::PointCloud<pcl::PointXYZ>);
      pcl::fromPCLPointCloud2(pc,*temp_cloud);

      float min_bound_x = -0.55;
      float max_bound_x = 0.55;
      float min_bound_y = -0.55;
      float max_bound_y = 0.8;
      
      // do rotation on converted pointcloud message
      // float rot = 1.57;
      // Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
      // transform_2.rotate(Eigen::AngleAxisf(rot, Eigen::Vector3f(0,0,1)));
      // pcl::transformPointCloud (*temp_cloud, *rotated_cloud, transform_2);  

      // transform_2 = Eigen::Affine3f::Identity();
      // // transform_2.rotate(Eigen::AngleAxisf(rot, Eigen::Vector3f(0,0,1)));
      // transform_2.rotate(Eigen::AngleAxisf(rot, Eigen::Vector3f(1,1,1)));
      // pcl::transformPointCloud (*rotated_cloud, *temp_cloud, transform_2);
      

      // filter z-axis for point cloud maximum
      pcl::PassThrough<pcl::PointXYZ> passmax;
      passmax.setInputCloud(temp_cloud);
      passmax.setFilterFieldName ("z");
      passmax.setFilterLimits (1.0, 10000);
      passmax.setFilterLimitsNegative (true);
      passmax.filter (*rotated_cloud);
      // filter z-axis for point cloud minimum
      pcl::PassThrough<pcl::PointXYZ> passmin;
      passmin.setInputCloud(rotated_cloud);
      passmin.setFilterFieldName ("z");
      passmin.setFilterLimits (-10000, -0.5);
      passmin.setFilterLimitsNegative (true);
      passmin.filter (*temp_cloud);
      // convert back to ROS msg to publish

      // pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
      // sor.setInputCloud (temp_cloud);
      // sor.setMeanK (50);
      // sor.setStddevMulThresh (2.0);
      // sor.filter (*rotated_cloud);

      pcl::toROSMsg(*temp_cloud, pub_msg);
      pub_msg.header.frame_id = "map";

      ///////////////////////////////////////////////////////////////////////////////
      ////////////// EXPERIMENTATION ITERATING THROUGH POINT CLOUD //////////////////
      // for (sensor_msgs::PointCloud2ConstIterator<float> iter_x(pub_msg, "x"),
      //   iter_y(pub_msg, "y"), iter_z(pub_msg, "z");
      //   iter_x != iter_x.end(); ++iter_x, ++iter_y, ++iter_z)
      // {
      //   if (std::isnan(*iter_x) || std::isnan(*iter_y) || std::isnan(*iter_z)) 
      //   {
      //     RCLCPP_DEBUG(
      //       this->get_logger(),
      //       "rejected for nan in point(%f, %f, %f)\n",
      //       *iter_x, *iter_y, *iter_z);
      //     continue;
      //   }

      //   if (*iter_x >= min_bound_x && *iter_x <= max_bound_x &&
      //     *iter_y >= min_bound_y && *iter_y <= max_bound_y)
      //   {
      //     RCLCPP_INFO(this->get_logger(), "coord of bound point is x %f y %f", *iter_x, *iter_y);
      //   }
      // }
      ////////////// END EXPERIMENTATION ITERATING THROUGH POINT CLOUD //////////////////
      ///////////////////////////////////////////////////////////////////////////////////
      publisher_->publish(pub_msg);
      // RCLCPP_INFO(this->get_logger(), "filtered cloud");
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Pcl_Filter>());
  rclcpp::shutdown();
  return 0;
}
