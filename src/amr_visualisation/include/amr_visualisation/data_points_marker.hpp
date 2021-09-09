#include "rclcpp/rclcpp.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "geometry_msgs/msg/quaternion.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "std_msgs/msg/string.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "om_aiv_msg/srv/arcl_api.hpp"
#include "om_aiv_msg/srv/arcl_listen.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

#pragma once

// Configurable values.
std::string PACK_NAME;
std::string MAP_NAME;
std::string HEAD_FRAME;
std::string VIS_TOPIC;
std::string rng_device;
float POINTS_A_CLR;
float POINTS_R_CLR;
float POINTS_G_CLR;
float POINTS_B_CLR;
float LINES_A_CLR;
float LINES_R_CLR;
float LINES_G_CLR;
float LINES_B_CLR;
float LS_POINTS_A_CLR;
float LS_POINTS_R_CLR;
float LS_POINTS_G_CLR;
float LS_POINTS_B_CLR;
float FA_A_CLR;
float FA_R_CLR;
float FA_G_CLR;
float FA_B_CLR;

// Non configurable values.
const std::string MAP_FOLDER = "/map";
const std::string POINTS_NUM_H = "NumPoints";
const std::string LINES_NUM_H = "NumLines";
const std::string POINTS_H = "DATA";
const std::string LINES_H = "LINES";
const std::string FA_H = "Cairn: ForbiddenArea";
const std::string POINTS_NS = "points";
const std::string LINES_NS = "lines";
const std::string LS_POINTS_NS = "ls_points";
const std::string LS_SUB_TOPIC = "ldarcl_laser";
const std::string FA_NS = "f_areas";
const int32_t POINTS_M_ID = 0;
const int32_t LINES_M_ID = 1;
const int32_t LS_POINTS_M_ID = 2;
const double POINTS_X_SCALE = 0.045;
const double POINTS_Y_SCALE = 0.045;
const double LINES_X_SCALE = 0.045;
const double LS_POINTS_X_SCALE = 0.045;
const double LS_POINTS_Y_SCALE = 0.045;

// Names for all config parameters.
const std::string PACK_NAME_PARAM = "pkg_name";
const std::string MAP_NAME_PARAM = "map_name";
const std::string HEAD_FRAME_PARAM = "head_frame";
const std::string VIS_TOPIC_PARAM = "vis_topic";
const std::string RNG_DEVICE_PARAM = "range_device";
const std::string POINTS_A_CLR_PARAM = "points_a_colour";
const std::string POINTS_R_CLR_PARAM = "points_r_colour";
const std::string POINTS_G_CLR_PARAM = "points_g_colour";
const std::string POINTS_B_CLR_PARAM = "points_b_colour";
const std::string LINES_A_CLR_PARAM = "lines_a_colour";
const std::string LINES_R_CLR_PARAM = "lines_r_colour";
const std::string LINES_G_CLR_PARAM = "lines_g_colour";
const std::string LINES_B_CLR_PARAM = "lines_b_colour";
const std::string LS_POINTS_A_CLR_PARAM = "ls_points_a_colour";
const std::string LS_POINTS_R_CLR_PARAM = "ls_points_r_colour";
const std::string LS_POINTS_G_CLR_PARAM = "ls_points_g_colour";
const std::string LS_POINTS_B_CLR_PARAM = "ls_points_b_colour";
const std::string FA_A_CLR_PARAM = "fa_a_colour";
const std::string FA_R_CLR_PARAM = "fa_r_colour";
const std::string FA_G_CLR_PARAM = "fa_g_colour";
const std::string FA_B_CLR_PARAM = "fa_b_colour";


class DataPointsMarker : public rclcpp::Node
{
public:
  /** \brief Constructor */
  DataPointsMarker();

  /** \brief Creates a quaternion msg given only yaw*/
  geometry_msgs::msg::Quaternion createQuaternionMsgFromYaw(double yaw);

  double getYawFromQuaternionMsg(geometry_msgs::msg::Quaternion quaternion);

private:
  /** \brief checks if a point is within the map array and colours it */
  void check_and_colour_grid(geometry_msgs::msg::Point coordinate, int occupancy_value);

  /** \brief gets the normal angle of an input angle in radians */
  double get_normal(double theta);

  /** \brief This function takes in heading in radians and distance and returns the coordinate difference */
  geometry_msgs::msg::Point get_extrapolated_coordinates(double theta, double distance);

  /** \brief gets number of points in map */
  void get_points_count(std::string* line, std::string* ignore_head, int* num_of_points);

  /** \brief gets number of lines in map */
  void get_lines_count(std::string* line, std::string* ignore_head, int* num_of_lines);

  /** \brief sets a point from the map */
  void set_point(int x, int y);

  /** \brief sets a line from the map */
  void set_line(int x1, int y1, int x2, int y2);

  /** \brief reads all forbidden areas */
  void get_forbidden_area_information(std::string line, double *dt_theta,
    double *x1, double *y1, double *x2, double *y2);
  
  /** \brief sets all forbidden areas into the MarkerArray */
  void set_forbidden_area_information(double dt_theta, double x1, double y1, double x2, double y2);

  /** \brief sets the parameters used for the forbidden area */
  void set_forbidden_area_params();

  /**
   * @brief Attemps to open .map file with the given file name and read all points and lines coordinates.
   * 
   * @param filename name of .map file to read, including file extension.
   * @return true if data is read without issue.
   * @return false if file fails to open or there is error in reading data.
   */
  bool get_map_data(std::string filename);


  /** @brief Function for getting minimum and maximum coordinates in point vector */
  void get_min_max_coordinates();

  /** \brief sets entire OccupancyGrid to -1 for unknown value in grid */
  void initialize_map();

  /** \brief function for filling in map with point vector */
  void fill_map();
  
  /** \brief sets the necessary attributes in the occupancy grid to show up in RViz */
  void set_grid_attributes();
  
  /** \brief publishes map and forbidden areas at 5 Hz */
  void timer_callback();

  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr map_pub;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr fa_pub;
  rclcpp::TimerBase::SharedPtr timer;
  std::vector<geometry_msgs::msg::Point> points;
  std::vector<geometry_msgs::msg::Point> lines;
  visualization_msgs::msg::MarkerArray f_areas;
  visualization_msgs::msg::Marker fa;
  nav_msgs::msg::OccupancyGrid grid;
  double minx, miny, maxx, maxy;
};