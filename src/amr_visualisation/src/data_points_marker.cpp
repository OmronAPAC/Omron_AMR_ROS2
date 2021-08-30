#include "amr_visualisation/data_points_marker.hpp"


DataPointsMarker::DataPointsMarker() : Node("map_publisher")
{
  using namespace std::chrono_literals;
  
  map_pub = this->create_publisher<nav_msgs::msg::OccupancyGrid>("map_grid", 10);
  fa_pub = this->create_publisher<visualization_msgs::msg::MarkerArray>("f_areas", 10);

  set_forbidden_area_params();

  if (!get_map_data("data.map")) 
  {
      RCLCPP_ERROR(this->get_logger(), "Reading map failed");
  }
  RCLCPP_INFO(this->get_logger(), "Waiting for RVIZ");
  get_min_max_coordinates();
  set_grid_attributes();
  initialize_map();
  fill_map();

  timer = this->create_wall_timer(
    500ms, std::bind(&DataPointsMarker::timer_callback, this));
}

void DataPointsMarker::timer_callback()
{
  fa_pub->publish(f_areas);
  map_pub->publish(grid);
}

geometry_msgs::msg::Quaternion DataPointsMarker::createQuaternionMsgFromYaw(double yaw)
{
  tf2::Quaternion tfq;
  tfq.setRPY(0, 0, yaw);
  geometry_msgs::msg::Quaternion gmq;

  double roll = 0;
  double pitch = 0;

  double cy = cos(yaw * 0.5);
  double sy = sin(yaw * 0.5);
  double cp = cos(pitch * 0.5);
  double sp = sin(pitch * 0.5);
  double cr = cos(roll * 0.5);
  double sr = sin(roll * 0.5);

  gmq.w = cy * cp * cr + sy * sp * sr; //w
  gmq.x = cy * cp * sr - sy * sp * cr; //x
  gmq.y = sy * cp * sr + cy * sp * cr; //y
  gmq.z = sy * cp * cr - cy * sp * sr; //z

  return gmq;
}

void DataPointsMarker::get_min_max_coordinates()
{    
  minx = INT32_MAX;
  miny = INT32_MAX; 
  maxx = -INT32_MAX;
  maxy = -INT32_MAX;
  for (int i = 0; i < (int) points.size(); i++)
  {
    if (points[i].x < minx)
      minx = points[i].x;
    if (points[i].x > maxx)
      maxx = points[i].x;
    if (points[i].y < miny)
      miny = points[i].y;
    if (points[i].y > maxy)
      maxy = points[i].y;
  }
}

void DataPointsMarker::get_points_count(std::string* line, std::string* ignore_head, int* num_of_points)
{
  if ((*line).find(POINTS_NUM_H) != std::string::npos)
  {
    std::istringstream iss(*line);
    iss >> *ignore_head;
    iss >> *num_of_points;
  }
}

void DataPointsMarker::get_lines_count(std::string* line, std::string* ignore_head, int* num_of_lines)
{
  if ((*line).find(LINES_NUM_H) != std::string::npos)
  {
    std::istringstream iss(*line);
    iss >> *ignore_head;
    iss >> *num_of_lines;
  }
}

void DataPointsMarker::set_point(int x, int y)
{
  geometry_msgs::msg::Point p;
  p.x = (double)x / 1000.0; // Values are in millimeter.
  p.y = (double)y / 1000.0;
  p.z = 0;
  points.push_back(p);
}

void DataPointsMarker::set_line(int x1, int y1, int x2, int y2)
{
  geometry_msgs::msg::Point p1;
  geometry_msgs::msg::Point p2;
  p1.x = (double)x1 / 1000.0; // Values are in millimeter.
  p1.y = (double)y1 / 1000.0;
  p1.z = 0;
  p2.x = (double)x2 / 1000.0;
  p2.y = (double)y2 / 1000.0;
  p2.z = 0;

  // Needs two consecutive points to form a line.
  lines.push_back(p1);
  lines.push_back(p2);
}

void DataPointsMarker::get_forbidden_area_information(std::string line, double *dt_theta,
  double *x1, double *y1, double *x2, double *y2)
{
  std::istringstream iss(line);
  std::string dummy;
  for (int i = 0; i < 8; i++)
  {
    // The first 8 pieces of that line are irrelevant except for the 5th piece which is the angle/orientation of the forbidden area.
    if (i == 4)
    {
      iss >> *dt_theta;
      *dt_theta *= 0.01745329;
    }
    else
    {
      iss >> dummy;
    }
  }
  if (!(iss >> *y1 >> *x1 >> *y2 >> *x2)) 
    {
      RCLCPP_ERROR(this->get_logger(), "%s - Error reading forbidden area from file: %s", 
        "Hi", "Bye");
    }
}

void DataPointsMarker::set_forbidden_area_information(
  double dt_theta, double x1, double y1, double x2, double y2)
{
  // Compute the actual forbidden area from the transformed area.
  // The raw info in the map file is a transformed coordinates of the actual forbidden area.
  // We transform back to the actual area.
  double cx = (x1 + x2) / 2000.0; // Centre of transformed X coord.
  double cy = (y1 + y2) / 2000.0; // Centre of transformed Y coord.
  double r = sqrt((cx * cx) + (cy * cy)); // Distance from centre of transformed area to origin. Polar coordinates, r component.
  double theta = atan2(cy, cx); // Polar coordinates, theta component.

  // Get back the centre point of actual forbidden area.
  double o_theta = theta - dt_theta; 
  double ocx = r * sin(o_theta);
  double ocy = r * cos(o_theta);
  dt_theta -= M_PI_2;
    
  // Convert to quaternion
  geometry_msgs::msg::Quaternion q;

  q = createQuaternionMsgFromYaw(dt_theta);

  // Push to vector that will be published.
  fa.pose.position.x = ocx;
  fa.pose.position.y = ocy;
  fa.pose.orientation = q;
  fa.scale.x = (x2 - x1) / 1000.0;
  fa.scale.y = (y2 - y1) / 1000.0;
  f_areas.markers.push_back(fa);
  fa.id += 1;
}

void DataPointsMarker::set_forbidden_area_params()
{
  fa.header.frame_id = "pose";
  fa.action = visualization_msgs::msg::Marker::ADD;
  fa.ns = "f_areas";
  fa.pose.orientation.w = 1.0;
  fa.pose.position.z = 0;
  fa.type = visualization_msgs::msg::Marker::CUBE;
  fa.id = 0;
  fa.scale.z = 0.25;
  fa.color.a = 0.5;
  fa.color.r = 1.0;
  fa.color.g = 0.0;
  fa.color.b = 0.0;
}

bool DataPointsMarker::get_map_data(std::string filename)
{
  // Read map file
  std::string map_path = ament_index_cpp::get_package_share_directory("amr_visualisation") + "/map/" + filename;
  std::ifstream map_file(map_path);

  if (map_file.fail()) 
  {
    return false;
  }

  int num_of_points = 0;
  int num_of_lines = 0;
  std::string line;
  std::string ignore_head;
  while (std::getline(map_file, line))
  {
    get_points_count(&line, &ignore_head, &num_of_points);
    get_lines_count(&line, &ignore_head, &num_of_lines);

    // We have seen the points data, collect them.
    if (line.find(POINTS_H) != std::string::npos)
    {
      int x, y;
      for (int i = 0; i < num_of_points; i++)
      {
        std::getline(map_file, line);
        std::istringstream iss(line);
        if (!(iss >> x >> y))
        {
          RCLCPP_ERROR(this->get_logger(), "%s - Error reading points from file.", "amr_visualisation");
        }
        set_point(x, y);
      }
    }

    // We have seen the lines data, collect them.
    if (line.find(LINES_H) != std::string::npos)
    {
      int x1, y1, x2, y2;
      for (int i = 0; i < num_of_lines; i++)
      {
        std::getline(map_file, line);
        std::istringstream iss(line);
        if(!(iss >> x1 >> y1 >> x2 >> y2))
        {
          RCLCPP_ERROR(this->get_logger(), "%s - Error reading points from file.", "348");
        }
        set_line(x1, y1, x2, y2);
      }
    }

    // This line contains forbidden area information, collect them.
    if (line.find(FA_H) != std::string::npos)
    {
      // Read the raw info
      double x1, y1, x2, y2, dt_theta;
      get_forbidden_area_information(line, &dt_theta, &x1, &y1, &x2, &y2);
      set_forbidden_area_information(dt_theta, x1, y1, x2, x2);
    }
  }
    return true;
}

void DataPointsMarker::fill_map()
{
  for (int i = 0; i < (int) points.size(); i++)
  {
    float relx = points[i].x - minx;
    float rely = points[i].y - miny;
    rely /= grid.info.resolution;
    relx /= grid.info.resolution;

    // This is 2D array represented by 1D. correct position would be (height_position * width) + width
    grid.data[int((int(rely)*grid.info.width) + relx)] = 100;
  }
}

void DataPointsMarker::initialize_map() 
{
  for (int i=0; i < int(grid.info.height * grid.info.width); i++) 
  {
    grid.data.push_back(-1);
  }    
}

void DataPointsMarker::set_grid_attributes()
{
  grid.header.stamp = this->get_clock()->now();
  grid.info.resolution = 0.02;
  grid.info.origin.orientation = createQuaternionMsgFromYaw(0);
  grid.header.frame_id = "/map";

  // set starting point of grid to be at minimum coordinates of points
  geometry_msgs::msg::Point origin;
  origin.x = minx;
  origin.y = miny;
  origin.z = 0;
  grid.info.origin.position = origin;

  // convert max map size into grids and +1 as int casting rounds down
  grid.info.width = int((maxx-minx)/grid.info.resolution + 1);
  grid.info.height = int((maxy-miny)/grid.info.resolution + 1);
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DataPointsMarker>());
  rclcpp::shutdown();
  return 0;
}
