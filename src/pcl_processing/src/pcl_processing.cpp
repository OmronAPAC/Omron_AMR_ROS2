
#include "pcl_processing/pcl_processing.hpp"


PclProcessing::PclProcessing()
: Node("pcl_processing", rclcpp::NodeOptions()
  .allow_undeclared_parameters(true)
  .automatically_declare_parameters_from_overrides(true))
{
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
  rclcpp::Parameter camera_topic_param = this->get_parameter("camera_topic");

  min_bound_x = min_bound_x_param.as_double();
  max_bound_x = max_bound_x_param.as_double();
  min_bound_y = min_bound_y_param.as_double();
  max_bound_y = max_bound_y_param.as_double();
  min_bound_z = min_bound_z_param.as_double();
  max_bound_z = max_bound_z_param.as_double();
  points_count = points_to_add.as_int();
  cam_horizontal_fov = camera_horizontal_fov.as_double();
  std::string camera_topic = camera_topic_param.as_string();

  subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(camera_topic, 10, 
    std::bind(&PclProcessing::topic_callback, this, std::placeholders::_1));
  status_sub = this->create_subscription<om_aiv_msg::msg::Status>("ldarcl_status", 10, 
    std::bind(&PclProcessing::status_callback, this, std::placeholders::_1));
  publisher_ = this->create_publisher<geometry_msgs::msg::Point>("obstacle_point", 10);
  cloud_publisher = this->create_publisher<sensor_msgs::msg::PointCloud2>("cloud_in", 10);
}

void PclProcessing::status_callback(om_aiv_msg::msg::Status::SharedPtr msg)
{
  odom_pos_x = msg->location.x / 1000;
  odom_pos_y = msg->location.y / 1000;
  theta = msg->location.theta / RADIAN_CONST;
}

void PclProcessing::topic_callback(sensor_msgs::msg::PointCloud2::SharedPtr msg)
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

    // Convert points to robot centre reference
    geometry_msgs::msg::Point current_point;
    current_point.x = *iter_x;
    current_point.y = *iter_y;
    current_point = calibrator.TranslateRobotOrigin(current_point, camera_offset_x, camera_offset_y);

    // Check if points are within bounding box
    if (*iter_x >= min_bound_x && *iter_x <= max_bound_x &&
      *iter_y >= min_bound_y && *iter_y <= max_bound_y &&
      *iter_z >= min_bound_z && *iter_z <= max_bound_z)
    {
      // check which slice points lie in
      float slice = check_slice(current_point);

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
    auto world_obstacle = convert_world_coord(obstruction[i]);
    if (smallest_distance[i] != INT_MAX) 
    {
      publisher_->publish(world_obstacle);
    }
  }
}

geometry_msgs::msg::Point PclProcessing::convert_world_coord(geometry_msgs::msg::Point current_point)
{
  float hypot = std::hypot(current_point.x, current_point.y);
  float angle = std::atan(std::abs(current_point.y) / std::abs(current_point.x));
  RCLCPP_INFO(this->get_logger(), "angle is %f", angle);
  float combined_angle;

  // Conditional to add angle
  if(current_point.y>=0)
  {
    combined_angle = theta + angle;
  } // Conditional to subtract angle
  else if (current_point.y<0)
  {
    combined_angle = theta - angle;
  }
  RCLCPP_INFO(this->get_logger(), "combined angle is %f", combined_angle);

  auto difference = get_world_base_coord(combined_angle, hypot);
  difference.x += odom_pos_x;
  difference.y += odom_pos_y;

  return difference;
}

/** \brief This function takes in heading in radians and distance and returns the coordinate relative position to the robot */
geometry_msgs::msg::Point PclProcessing::get_world_base_coord(double theta, double distance)
{
  // sin and cos functions take in radians
  geometry_msgs::msg::Point rel_pos;
  // 0 to 90 degrees
  if (theta >= 0 && theta <= (PI / 2))
  {
    rel_pos.x = distance * cos(theta);
    rel_pos.y = distance * sin(theta);
    RCLCPP_INFO(this->get_logger(), "0 to 90 coord of rel_pos is x %f y %f", rel_pos.x, rel_pos.y);
  }
  // 90 to 180 degrees
  else if (theta > (PI / 2) && theta <= PI)
  {
    rel_pos.x = distance * cos(PI - theta);
    rel_pos.y = -(distance * sin(PI - theta));
    RCLCPP_INFO(this->get_logger(), "90 to 180 coord of rel_pos is x %f y %f", rel_pos.x, rel_pos.y);
  }
  // 0 to -90 degrees
  else if (theta < 0 && theta >= -(PI / 2))
  {
    rel_pos.x = distance * cos(-theta);
    rel_pos.y = -(distance * sin(-theta));
    RCLCPP_INFO(this->get_logger(), "0 to -90 coord of rel_pos is x %f y %f", rel_pos.x, rel_pos.y);
  }
  // -90 to -180 degrees
  else if (theta < -(PI / 2) && theta >= -PI)
  {
    // assumes that theta is a negative value
    rel_pos.x = -(distance * cos(theta + PI));
    rel_pos.y = -(distance * sin(theta + PI));
  }
  return rel_pos;
}

// check which slice points lie in
float PclProcessing::check_slice(geometry_msgs::msg::Point current_point)
{
  float angle = std::atan2(current_point.y, current_point.x);
  angle += cam_horizontal_fov / 2;
  float slice = angle / (cam_horizontal_fov / points_count);
  return slice;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions node_options;
  node_options.allow_undeclared_parameters(true);
  rclcpp::spin(std::make_shared<PclProcessing>());
  rclcpp::shutdown();
  return 0;
}
