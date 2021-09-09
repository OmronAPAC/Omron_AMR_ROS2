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

double DataPointsMarker::getYawFromQuaternionMsg(geometry_msgs::msg::Quaternion quaternion)
{
  double yaw;
  double varA = +2.0 * ((quaternion.w * quaternion.z) + (quaternion.x * quaternion.y));
  double varB = +1.0 - 2.0 * ((quaternion.y*quaternion.y) + (quaternion.z*quaternion.z));
  yaw = std::atan2(varA, varB);
  return yaw;
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

  // q = createQuaternionMsgFromYaw(0.375);
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

/** \brief gets the normal angle for calculating width. assumes -180 to +180 degrees from 0 heading */
double DataPointsMarker::get_normal(double theta)
{
  double pi = 3.141592654;
  if (theta >= pi/2)
  {
    theta -= pi/2;
  }
  else
  {
    theta += pi/2;
  }
  return theta;
}

/** \brief This function takes in heading in radians and distance and returns the coordinate difference */
geometry_msgs::msg::Point DataPointsMarker::get_extrapolated_coordinates(double theta, double distance)
{
  double pi = 3.141592654;
  // sin and cos functions take in radians
  geometry_msgs::msg::Point difference;
  // 0 to 90 degrees
  if (theta >= 0 && theta <= (pi / 2))
  {
    difference.x = distance * cos(theta);
    difference.y = distance * sin(theta);
  }
  // 90 to 180 degrees
  else if (theta > (pi / 2) && theta <= pi)
  {
    difference.x = distance * cos(pi - theta);
    difference.y = -(distance * sin(pi - theta));
  }
  // 0 to -90 degrees
  else if (theta < 0 && theta >= -(pi / 2))
  {
    difference.x = -(distance * cos(theta));
    difference.y = distance * sin(theta);
  }
  // -90 to -180 degrees
  else if (theta < -(pi / 2) && theta >= -pi)
  {
    // assumes that theta is a negative value
    difference.x = -(distance * cos(theta + pi));
    difference.y = -(distance * sin(theta + pi));
  }
  return difference;
}

void DataPointsMarker::check_and_colour_grid(geometry_msgs::msg::Point coordinate, int occupancy_value)
{
  float relx;
  float rely;
  int position_on_grid;
  relx = coordinate.x - minx;
  rely = coordinate.y - miny;
  rely /= grid.info.resolution;
  relx /= grid.info.resolution;

  // Check if point is within map
  if (rely <= grid.info.height && relx <= grid.info.width && rely >= 0 && relx >= 0)
  {
    // This is 2D array represented by 1D. correct position would be (height_position * width) + width
    position_on_grid = int((int(rely)*grid.info.width) + relx);
    grid.data[position_on_grid] = occupancy_value;
  }
}

void DataPointsMarker::fill_map()
{
  // For each forbidden area, get number of steps on each axis of rectangle
  for (long unsigned int i=0; i<f_areas.markers.size(); i++)
  {
    // Get number of steps to calculate to cover the full length and breadth of forbidden area
    int step_count_length = (f_areas.markers[i].scale.x / grid.info.resolution) + 1;
    int step_count_breadth = (f_areas.markers[i].scale.y / grid.info.resolution) + 1;
    // not sure if this should be radians or degree.
    double yaw = getYawFromQuaternionMsg(f_areas.markers[i].pose.orientation);
    // Get the x and y difference in step for length of forbidden area
    // The resolution here is divided by 2 to increase fidelity of the forbidden area
    auto step_length = get_extrapolated_coordinates(yaw, grid.info.resolution/2);
    // Get the x and y difference in step for breadh of forbidden area. The angle this is trigonometrically calculated from
    // is the normal of the yaw of the original orientation
    auto step_breadth = get_extrapolated_coordinates(get_normal(yaw), grid.info.resolution/2);

    // Since we have an origin point, begin filling rectangle from origin.
    // For each row in the forbidden area, get their starting coordinates
    for (int j=0; j<step_count_breadth; j++)
    {
      geometry_msgs::msg::Point starting_position_positive;
      starting_position_positive.x = f_areas.markers[i].pose.position.x + (step_breadth.x * j);
      starting_position_positive.y = f_areas.markers[i].pose.position.y + (step_breadth.y * j); 

      geometry_msgs::msg::Point starting_position_negative;
      starting_position_negative.x = f_areas.markers[i].pose.position.x - (step_breadth.x * j);
      starting_position_negative.y = f_areas.markers[i].pose.position.y - (step_breadth.y * j); 

      // get the position of every point in a row to check
      for (int k=0; k<step_count_length; k++)
      {
        // Occupancy value here is set to 85 just to distinguish between forbidden areas and actual map obstacles
        // They should be set to 100 if map is used for path planning
        geometry_msgs::msg::Point starting_position_positive_positive;
        starting_position_positive_positive.x = starting_position_positive.x + (step_length.x*k);
        starting_position_positive_positive.y = starting_position_positive.y + (step_length.y*k);
        check_and_colour_grid(starting_position_positive_positive, 85);
        geometry_msgs::msg::Point starting_position_positive_negative;
        starting_position_positive_negative.x = starting_position_positive.x - (step_length.x*k);
        starting_position_positive_negative.y = starting_position_positive.y - (step_length.y*k);
        check_and_colour_grid(starting_position_positive_negative, 85);
        geometry_msgs::msg::Point starting_position_negative_positive;
        starting_position_negative_positive.x = starting_position_negative.x + (step_length.x*k);
        starting_position_negative_positive.y = starting_position_negative.y + (step_length.y*k);
        check_and_colour_grid(starting_position_negative_positive, 85);
        geometry_msgs::msg::Point starting_position_negative_negative;
        starting_position_negative_negative.x = starting_position_negative.x - (step_length.x*k);
        starting_position_negative_negative.y = starting_position_negative.y - (step_length.y*k);
        check_and_colour_grid(starting_position_negative_negative, 85);
      }
    }
  }

  // for each point in point vector, convert to relative coordinates compared to grid origin
  // if point lies within a grid, colour it black
  for (int i = 0; i < (int) points.size(); i++)
  {
    check_and_colour_grid(points[i], 100);
  }

  for (int i = 0; i < (int) lines.size(); i++)
  {
    // for each 2 points in line vector, convert to relative coordinates compared to grid origin
    // break each line up into as many points as grid resolution allows
    // check if points lie within a grid and colour it black
    if (i % 2 == 1)
    {
      continue;
    }
    double vector_x, vector_y, distance;
    float step_x, step_y;
    int steps;

    // gets vector from 1 point to another
    vector_x = lines[i+1].x - lines[i].x;
    vector_y = lines[i+1].y - lines[i].y;
    // calculates magnitude of the vector
    distance = std::hypot(vector_x, vector_y);
    // break the distance into points based on grid resolution
    steps = distance / grid.info.resolution;
    step_x = vector_x / steps;
    step_y = vector_y / steps;
    // incrementally checks each point from the start of the line where they lie on the grid
    for(int j=0; j<steps; j++)
    {
      geometry_msgs::msg::Point step_temp;
      step_temp.x = lines[i].x + (step_x*j);
      step_temp.y = lines[i].y + (step_y*j);
      check_and_colour_grid(step_temp, 100);
    }
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
