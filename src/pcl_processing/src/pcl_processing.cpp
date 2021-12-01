
#include "pcl_processing/pcl_processing.hpp"

PclProcessing::PclProcessing()
: Node("pcl_processing", rclcpp::NodeOptions()
  .allow_undeclared_parameters(true)
  .automatically_declare_parameters_from_overrides(true))
{
  calibrator = CameraCalibration();

  // get parameters from yaml file
  rclcpp::Parameter points_to_add = this->get_parameter("points_to_add");
  rclcpp::Parameter camera_horizontal_fov = this->get_parameter("camera_horizontal_fov");
  rclcpp::Parameter min_bound_x_param = this->get_parameter("min_bound_x");
  rclcpp::Parameter max_bound_x_param = this->get_parameter("max_bound_x");
  rclcpp::Parameter min_bound_y_param = this->get_parameter("min_bound_y");
  rclcpp::Parameter max_bound_y_param = this->get_parameter("max_bound_y");
  rclcpp::Parameter min_bound_z_param = this->get_parameter("min_bound_z");
  rclcpp::Parameter max_bound_z_param = this->get_parameter("max_bound_z");
  rclcpp::Parameter camera_offset_x_param = this->get_parameter("camera_x_offset");
  rclcpp::Parameter camera_offset_y_param = this->get_parameter("camera_y_offset");
  rclcpp::Parameter camera_offset_roll_param = this->get_parameter("camera_roll_x_offset");
  rclcpp::Parameter camera_offset_pitch_param = this->get_parameter("camera_pitch_y_offset");
  rclcpp::Parameter camera_offset_yaw_param = this->get_parameter("camera_yaw_z_offset");
  rclcpp::Parameter camera_topic_param = this->get_parameter("camera_topic");
  rclcpp::Parameter point_topic_param = this->get_parameter("point_topic");
  rclcpp::Parameter decay_time_param = this->get_parameter("decay_time");
  rclcpp::Parameter distance_threshold_param = this->get_parameter("distance_threshold");

  min_bound_x = min_bound_x_param.as_double();
  max_bound_x = max_bound_x_param.as_double();
  min_bound_y = min_bound_y_param.as_double();
  max_bound_y = max_bound_y_param.as_double();
  min_bound_z = min_bound_z_param.as_double();
  max_bound_z = max_bound_z_param.as_double();
  camera_offset_x = camera_offset_x_param.as_double();
  camera_offset_y = camera_offset_y_param.as_double();
  camera_roll_offset = camera_offset_roll_param.as_double();
  camera_pitch_offset = camera_offset_pitch_param.as_double();
  camera_yaw_offset = camera_offset_yaw_param.as_double();
  decay_time = decay_time_param.as_double();
  points_count = points_to_add.as_int();
  distance_threshold = distance_threshold_param.as_double();
  cam_horizontal_fov = camera_horizontal_fov.as_double();
  std::string camera_topic = camera_topic_param.as_string();
  std::string point_topic = point_topic_param.as_string();

  // Initialize publisher and subscriber
  pointcloud_subscriber = this->create_subscription<sensor_msgs::msg::PointCloud2>(camera_topic, 10, 
    std::bind(&PclProcessing::topic_callback, this, std::placeholders::_1));
  point_subscriber = this->create_subscription<geometry_msgs::msg::Point>(point_topic, 10,
    std::bind(&PclProcessing::point_callback, this, std::placeholders::_1));
  status_subscriber = this->create_subscription<om_aiv_msg::msg::Status>("ldarcl_status", 10, 
    std::bind(&PclProcessing::status_callback, this, std::placeholders::_1));
  laser_subscriber = this->create_subscription<visualization_msgs::msg::Marker>("visualization_marker", 10, 
    std::bind(&PclProcessing::laser_callback, this, std::placeholders::_1));
  obstacle_publisher = this->create_publisher<geometry_msgs::msg::Point>("obstacle_point", 10);
  cloud_publisher = this->create_publisher<sensor_msgs::msg::PointCloud2>("cloud_in", 10);

  // Initialize point history vector
  history_iter = 0;
  for (int i=0; i<decay_time*points_count; i++) {
    geometry_msgs::msg::PoseStamped temp;
    history.push_back(temp);
  }
}

void PclProcessing::laser_callback(visualization_msgs::msg::Marker::SharedPtr msg)
{
  laser_scan_data = msg->points;
}

void PclProcessing::status_callback(om_aiv_msg::msg::Status::SharedPtr msg)
{
  odom_pos_x = msg->location.x / 1000;
  odom_pos_y = msg->location.y / 1000;
  theta = msg->location.theta / RADIAN_CONST;
}

void PclProcessing::point_callback(geometry_msgs::msg::Point::SharedPtr msg)
{
  auto world_obstacle = convert_world_coord(*msg);
  add_point_to_history(world_obstacle);
  obstacle_publisher->publish(world_obstacle);
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

  // a radius filter is in searching for outlier points
  std::vector<int> indices;
  pcl::removeNaNFromPointCloud(*temp_cloud, *temp_cloud, indices);
  pcl::RadiusOutlierRemoval<pcl::PointXYZ> radiusoutlier;  //Create filter
  radiusoutlier.setInputCloud(temp_cloud);    //Set input point cloud
  radiusoutlier.setRadiusSearch(0.15);     
  radiusoutlier.setMinNeighborsInRadius(15); 
  radiusoutlier.filter(*rotated_cloud);

  // The point cloud is rotated to a standardized format using 
  // rpy values from config file
  Eigen::Affine3f transform = Eigen::Affine3f::Identity();
  transform.rotate(Eigen::AngleAxisf(camera_roll_offset, Eigen::Vector3f(1,0,0)));
  transform.rotate(Eigen::AngleAxisf(camera_pitch_offset, Eigen::Vector3f(0,1,0)));
  transform.rotate(Eigen::AngleAxisf(camera_yaw_offset, Eigen::Vector3f(0,0,1)));
  pcl::transformPointCloud (*rotated_cloud, *temp_cloud, transform);

  pcl::toROSMsg(*temp_cloud, pub_msg);
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
    if (isnan(*iter_x, *iter_y, *iter_z))
    {
      continue;
    }

    // Convert points to robot centre reference
    geometry_msgs::msg::Point current_point;
    current_point.x = *iter_x;
    current_point.y = *iter_y;
    current_point = calibrator.TranslateRobotOrigin(current_point, camera_offset_x, camera_offset_y);

    // check if points are within bounding box
    if (outside_bounds(*iter_x, *iter_y, *iter_z))
    {
      continue;
    }

    // get partition of current point
    float slice = check_slice(current_point);

    // Check proximity of current point to robot origin
    float dist = std::hypot(current_point.x, current_point.y);
    if (dist < smallest_distance[slice])
    {
      smallest_distance[slice] = dist;
      obstruction[slice].x = current_point.x;
      obstruction[slice].y = current_point.y;
      // RCLCPP_INFO(this->get_logger(), "coord of min points is x %f y %f", obstruction.x, obstruction.y);
    }
  }

  // Takes the closest points within each slice and
  // convert to world coordinates and check proximity to other obstacles
  for (int i=0; i < points_count; i++)
  {
    RCLCPP_INFO(this->get_logger(), "coord of min points is x %f y %f", obstruction[i].x, obstruction[i].y);
    auto world_obstacle = convert_world_coord(obstruction[i]);

    // These conditionals check if the world obstacle is near to other previously added points,
    // near to input laser scans, or are of an invalid number 
    if (nearby_added(world_obstacle) || near_laserscans(world_obstacle) || smallest_distance[i] == INT_MAX
      || std::isnan(world_obstacle.x) || std::isnan(world_obstacle.y)
      || (world_obstacle.x == odom_pos_x && world_obstacle.y == odom_pos_y))
    {
      continue;
    }
    add_point_to_history(world_obstacle);
    obstacle_publisher->publish(world_obstacle);
  }

  // Publishes the filtered cloud for visualization and testing purposes
  // Comment out to improve performance
  cloud_publisher->publish(pub_msg);
}

bool PclProcessing::near_laserscans(geometry_msgs::msg::Point current_point)
{
  for (long unsigned int i = 0; i < laser_scan_data.size(); i++) {
    if (i >= laser_scan_data.size()) {
      break;
    }
    float y_diff = laser_scan_data[i].y - current_point.y;
    float x_diff = laser_scan_data[i].x - current_point.x;

    float distance = std::hypot(x_diff, y_diff);
    if (distance < distance_threshold) {
      return true;
    }
  }
  return false;
}

bool PclProcessing::outside_bounds(const float iter_x, const float iter_y, const float iter_z)
{
  if (iter_x >= min_bound_x && iter_x <= max_bound_x &&
    iter_y >= min_bound_y && iter_y <= max_bound_y &&
    iter_z >= min_bound_z && iter_z <= max_bound_z)
  {
    return false;
  }
  return true;
}

bool PclProcessing::isnan(const float iter_x, const float iter_y, const float iter_z)
{
  if (std::isnan(iter_x) || std::isnan(iter_y) || std::isnan(iter_z)) 
  {
    RCLCPP_DEBUG(
      this->get_logger(),
      "rejected for nan in point(%f, %f, %f)\n",
      iter_x, iter_y, iter_z);
    return true;
  }
  return false;
}

void PclProcessing::add_point_to_history(geometry_msgs::msg::Point current_point)
{
  history[history_iter].header.stamp.sec = this->get_clock()->now().seconds();
  history[history_iter].pose.position.x = current_point.x;
  history[history_iter].pose.position.y = current_point.y;
  history_iter += 1;
  if (history_iter >= int(decay_time*points_count))
  {
    history_iter = 0;
  }
}

bool PclProcessing::nearby_added(geometry_msgs::msg::Point current_point)
{
  bool is_nearby = false;
  for (int i=0; i<decay_time*points_count; i++)
  {
    // If a point is at origin, pass
    if (history[i].pose.position.x == 0 && history[i].pose.position.y == 0)
    {
      continue;
    }
    // Check if difference between node time and stamp is more than decay time
    if (this->get_clock()->now().seconds() - history[i].header.stamp.sec < decay_time/2)
    {
      // Check if current point is nearby any point
      float x_diff = history[i].pose.position.x - current_point.x;
      float y_diff = history[i].pose.position.y - current_point.y;
      float distance = std::hypot(x_diff, y_diff);
      if (distance < distance_threshold)
      {
        is_nearby = true;
      }
    }
  }
  return is_nearby;
}

geometry_msgs::msg::Point PclProcessing::convert_world_coord(geometry_msgs::msg::Point current_point)
{
  // distance between point cloud origin and point
  float distance = std::hypot(current_point.x, current_point.y);

  // angle from origin to current point
  float angle = std::atan(std::abs(current_point.y) / std::abs(current_point.x));
  float robot_heading = theta;
  float combined_angle;

  combined_angle = calc_combined_angle(current_point, robot_heading, angle);
  combined_angle = normalize_angle(combined_angle);
  auto difference = get_world_base_coord(combined_angle, distance);

  // RCLCPP_INFO(this->get_logger(), "current point is x %f y %f, theta is %f", current_point.x, current_point.y,theta);
  // RCLCPP_INFO(this->get_logger(), "coord diff is x %f y %f", difference.x, difference.y);
  difference.x += odom_pos_x;
  difference.y += odom_pos_y;

  return difference;
}

float PclProcessing::calc_combined_angle(geometry_msgs::msg::Point current_point, float robot_heading, float angle)
{
  // If points occur from PI/2 to -PI/2 of robot
  float combined_angle;
  if (current_point.x>=0)
  {
    if(current_point.y>=0)
    {
      combined_angle = robot_heading + angle;
    }
    else if (current_point.y<0)
    {
      combined_angle = robot_heading - angle;
    }
  }
  // If points occur from PI/2 to PI or -PI/2 to -PI
  else if (current_point.x<0)
  {
    // Flip heading to opposite direction
    robot_heading = normalize_angle(PI + robot_heading);
    if(current_point.y>=0)
    {
      combined_angle = robot_heading - angle;
    }
    else if (current_point.y<0)
    {
      combined_angle = robot_heading + angle;
    }
  }
  return combined_angle;
}

float PclProcessing::normalize_angle(float angle)
{
  // trigonometric functions return invalid results when angular range is not normalized
  // to between -PI and +PI
  while (angle < -PI)
  {
    angle += 2 * PI;
  }
  while (angle > PI)
  {
    angle -= 2 * PI;
  }
  return angle;
}

geometry_msgs::msg::Point PclProcessing::get_world_base_coord(double theta, double distance)
{
  // sin and cos functions take in radians
  geometry_msgs::msg::Point rel_pos;
  rel_pos.x = distance * cos(theta);
  rel_pos.y = distance * sin(theta);
  return rel_pos;
}

float PclProcessing::check_slice(geometry_msgs::msg::Point current_point)
{
  // check which slice points lie in
  float angle = std::atan2(current_point.y, current_point.x);
  angle += ((cam_horizontal_fov / 2) - camera_yaw_offset);
  float slice = angle / (cam_horizontal_fov / points_count);
  return slice;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PclProcessing>());
  rclcpp::shutdown();
  return 0;
}
