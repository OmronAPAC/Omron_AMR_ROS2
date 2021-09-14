#include "amr_visualisation/laser_scans.hpp"

LaserScans::LaserScans() : Node("laser_node")
{
  using namespace std::chrono_literals;

  init_laser_scans();
  laser_scan_pub = this->create_publisher<visualization_msgs::msg::Marker>("visualization_marker", 10);
  laser_data_sub = this->create_subscription<std_msgs::msg::String>(
    "ldarcl_laser", 10, std::bind(&LaserScans::laser_sub_cb, this, std::placeholders::_1));
  clear_laser_timer = this->create_wall_timer(10000ms, std::bind(&LaserScans::timer_callback, this));
  geometry_msgs::msg::Point p;
  p.x = 0;
  p.y = 0;
  p.z = 0;
  for (int i=0; i<455; i++)
  {
    laser_points.points.push_back(p);
  }
}

void LaserScans::timer_callback()
{
  laser_points.action = 3;
  laser_scan_pub->publish(laser_points);
  laser_points.action = visualization_msgs::msg::Marker::ADD;
  laser_scan_pub->publish(laser_points);
}

void LaserScans::laser_sub_cb(const std_msgs::msg::String::SharedPtr msg)
{
  std::string raw_resp = msg->data;
  rng_device = "Laser_1";
  std::string::size_type pos = raw_resp.find(rng_device);
  if (pos != std::string::npos)
  {
    laser_points.points.clear();
    std::string vals_str;
    try
    {
      // +1 to exclude the following space.
      vals_str = raw_resp.substr(pos + rng_device.length() + 1); 
    }
    catch(const std::out_of_range& e)
    {
      vals_str.clear();
    }
    populate_laser_scans(vals_str);
  }
  update_laser_points();
  laser_scan_pub->publish(laser_points);
}

void LaserScans::populate_laser_scans(std::string vals_str)
{
    std::istringstream iss(vals_str);
    double x, y = 0.0;
    laser_points.points.clear();
    while (iss >> x >> y)
    {
      add_laser_point(x, y);
    }
}

void LaserScans::update_laser_points()
{
  laser_points.header.stamp = this->now();
  laser_points.action = 3;
  laser_points.action = visualization_msgs::msg::Marker::ADD;
}

void LaserScans::add_laser_point(double x, double y)
{
  geometry_msgs::msg::Point p;
  p.x = x / 1000.0;
  p.y = y / 1000.0;
  p.z = 0;
  laser_points.points.push_back(p);
}

void LaserScans::init_laser_scans()
{
    /// Draw laser scan data ///
    laser_points.header.frame_id = "pose";
    laser_points.action = visualization_msgs::msg::Marker::ADD;
    laser_points.ns = "ls_points";
    laser_points.pose.orientation.w = 1.0;
    laser_points.type = visualization_msgs::msg::Marker::POINTS;
    laser_points.id = 0;
    laser_points.scale.x = 0.045;
    laser_points.scale.y = 0.045;
    laser_points.color.a = 1;
    laser_points.color.r = 0;
    laser_points.color.g = 1;
    laser_points.color.b = 1;
    laser_points.lifetime.sec = 2;
    laser_points.lifetime.nanosec = 0;
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LaserScans>());
  rclcpp::shutdown();
  return 0;
}
