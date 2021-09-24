#include <memory>
#include <functional>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <future>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include "om_aiv_msg/msg/status.hpp"
#include "om_aiv_msg/srv/get_path.hpp"
#include "om_aiv_msg/action/action.hpp"
#include <pcl/PCLPointCloud2.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/passthrough.h>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <std_msgs/msg/string.hpp>


using namespace std::chrono_literals;


class ObstacleCheck : public rclcpp::Node
{
  public:
    ObstacleCheck() : Node("obstacle_check")
    {
      map_sub = this->create_subscription<nav_msgs::msg::OccupancyGrid>(
      "projected_map", 10, std::bind(&ObstacleCheck::mapsub_cb, this, std::placeholders::_1));
      status_sub = this->create_subscription<om_aiv_msg::msg::Status>(
      "ldarcl_status", 10, std::bind(&ObstacleCheck::statussub_cb, this, std::placeholders::_1));
      goto_goal_sub = this->create_subscription<geometry_msgs::msg::Pose>(
      "goal_pose", 10, std::bind(&ObstacleCheck::getgoal_cb, this, std::placeholders::_1));
      arcl_client = rclcpp_action::create_client<om_aiv_msg::action::Action>(this, "action_server");
      path_planning_client = this->create_client<om_aiv_msg::srv::GetPath>("path_planner");
      // for testing, remember to remove
      marker_pub = this->create_publisher<visualization_msgs::msg::Marker>("width_arr", 10);

      // velocity is initialized to 1 as an indicator of any error
      transvel = 1;

      
      // to add, another function for getting velocity (probably action client)
      // to add, action client to call for AMR STOP  and also to get velocity from AMR (transvel)
      // same node to determine new goal pose
      // then call for path planning
      // after path planning, drive around obstacle
      // add in callback functions for the action client
    }

  private:
    /** \brief function that converts pose into x and y coordinates as the current goal position. */
    void getgoal_cb(geometry_msgs::msg::Pose::SharedPtr msg)
    {
      current_goal.x = msg->position.x;
      current_goal.y = msg->position.y;
      // to add: another function that collects Goal coordinates that are published to RViz
    }

    /** \brief gets angle between 2 vectors
     * currently it only calculates angle from x-axis to coordinate vector to robot position
     * TODO: refactor to use generics to make function reusable
     */
    double get_angle(double current_position_x, double current_position_y)
    {
      double goal_vector_x, goal_vector_y;
      goal_vector_x = current_goal.x - current_position_x;
      goal_vector_y = current_goal.y - current_position_y;
      // angle between 2 vector = atan2(w2v1-w1v2, w1v1+w2v2)
      // https://wumbo.net/formula/angle-between-two-vectors-2d/
      // here, v is unit vector in x axis, (1,0)
      double goal_angle = std::atan2((goal_vector_y*1) - (goal_vector_x*0),
      (goal_vector_x*1) + (goal_vector_y*0));
      return goal_angle;
    }

    /** \brief callback to update map to latest iteration */
    void mapsub_cb(nav_msgs::msg::OccupancyGrid::SharedPtr msg)
    {
      map = *msg;
      // RCLCPP_INFO(this->get_logger(), "map origin is %lf %lf", map.info.origin.position.x, map.info.origin.position.y);
      // RCLCPP_INFO(this->get_logger(), "map orientation is is %lf %lf %lf %lf", map.info.origin.orientation.w, map.info.origin.orientation.x, map.info.origin.orientation.y, map.info.origin.orientation.z);
    }

    /** \brief callback for status subscriber to check if there is obstacle in path */
    void statussub_cb(om_aiv_msg::msg::Status::SharedPtr msg)
    {
      // assume distance to look ahead is 3 units for now since get velocity not implemented yet
      get_velocity();
      double distance = get_distance_from_velocity();
      // assume width of robot is 0.8 units for now since params for robot not implemented yet
      double width = 0.8;
      double x, y, theta;
      bool has_collision;
      geometry_msgs::msg::Point extrapolated_coordinate;

      x = msg->location.x;
      y = msg->location.y;
      theta = msg->location.theta;
      // function only gives the difference between current and extrapolated coordinates
      extrapolated_coordinate = get_extrapolated_coordinates(theta / 57.296, distance);
      // add to the coordinates to make them world accurate
      extrapolated_coordinate.x += x;
      extrapolated_coordinate.y += y;

      RCLCPP_INFO(this->get_logger(), "extrap x is %lf", extrapolated_coordinate.x);
      RCLCPP_INFO(this->get_logger(), "extrap y is %lf", extrapolated_coordinate.y);
      // get a vector array of points that are the width of the robot
      auto points = calculate_width_points(extrapolated_coordinate.x, extrapolated_coordinate.y, width, theta);
      // check if any of the points collide with anything in the map
      has_collision = check_collision(points);
      if (has_collision)
      {
        RCLCPP_INFO(this->get_logger(), "COLLISION");
        stop();
      }
      else
      {
        RCLCPP_INFO(this->get_logger(), "NO COLLISION");
        return;
      }
      // create subscriber to GET goal pose from map
      // look for empty spot that robot can travel to i.e. the goal in path planning
      auto empty_spot = look_for_empty_spot(x, y, theta, distance);
      // create service client to initiate path planning
      // after path planning is done, have a client to the service which converts pose array to drive commands

    }

    /** \brief uses action server to stop the robot via ARCL commands */
    void stop()
    {
      std::string command = "stop";
      // this exact command returns a "GetDataStoreFieldValues: Transvel <velocity>"
      arcl_client->wait_for_action_server();
      auto msg = om_aiv_msg::action::Action::Goal();
      msg.command = command;
      msg.identifier.push_back("stop robot");
      auto future = arcl_client->async_send_goal(msg);
    }

    void get_velocity()
    {
      std::string command = "dsfv transvel";
      // this exact command returns a "GetDataStoreFieldValues: Transvel <velocity>"
      arcl_client->wait_for_action_server();
      auto msg = om_aiv_msg::action::Action::Goal();
      msg.command = command;
      msg.identifier.push_back("velocity: ");
      auto send_goal_options = rclcpp_action::Client<om_aiv_msg::action::Action>::SendGoalOptions();
      // figure out what's wrong with this function
      //send_goal_options.result_callback = std::bind(&ObstacleCheck::result_cb, this, std::placeholders::_1);
      auto future = arcl_client->async_send_goal(msg, send_goal_options);
    }

    void result_cb(rclcpp_action::ClientGoalHandle<om_aiv_msg::action::Action>::WrappedResult & result)
    {
      std::string vel = result.result->res_msg;
      // Remove all except number value "GetDataStoreFieldValues: Transvel <velocity>"
      vel = vel.replace(0, 33, "");
      // Convert string to float
      transvel = std::stof(vel);
    }

    /** \brief looks for empty spot beside obstacle that the robot can travel to */
    geometry_msgs::msg::Point look_for_empty_spot(double current_position_x, double current_position_y, double current_theta, double distance)
    {
      std::vector<geometry_msgs::msg::Point> empty_spot_coordinates;
      // TODO: convert variable below to parameter
      // currently an arbitrary number
      double max_lidar_width_angle = 50; // this is just half of the lidar horizontal fov
      double goal_theta = get_angle(current_goal.x, current_goal.y);
      double arc_length = (max_lidar_width_angle / 57.296) * distance;
      // improve sample point fidelity by 2 as arc might overlap some squares
      int sample_points_count = arc_length / (map.info.resolution / 2);
      float step = max_lidar_width_angle / sample_points_count;
      // if goal heading - current heading is positive value, search anti-clockwise 
      // else search clockwise

      // If negative value, convert the step to a negative value
      if (goal_theta - current_theta <= 0)
      {
        step *= -1;
      }

      for (int i=0; i<sample_points_count; i++)
      {
        auto test_point = get_extrapolated_coordinates(current_theta + (step*i), distance);
        empty_spot_coordinates.push_back(test_point);
        bool is_not_empty = check_collision(empty_spot_coordinates);
        if (!is_not_empty)
        {
          return empty_spot_coordinates[0];
        }
        empty_spot_coordinates.pop_back();
      }

      geometry_msgs::msg::Point empty_point;
      return empty_point;
    }

    /** \brief Checks if a point in occupancy grid is 40% or above occupied 
     *  returns true if there is collision
    */
    bool check_collision(std::vector<geometry_msgs::msg::Point> points)
    {
      // RCLCPP_INFO(this->get_logger(), "checking collision now");
      for (long unsigned int i=0; i < points.size(); i++)
      {
        // RCLCPP_INFO(this->get_logger(), "in for loop");
        geometry_msgs::msg::Point relative_point;
        relative_point.x = points[i].x - map.info.origin.position.x;
        relative_point.y = points[i].y - map.info.origin.position.y;
        if (!check_point_within_map(relative_point))
        {
          // RCLCPP_INFO(this->get_logger(), "NOT WITHIN MAP");
          continue;
        }
        relative_point.x /= map.info.resolution;
        relative_point.y /= map.info.resolution;      
        RCLCPP_INFO(this->get_logger(), "rel x is %lf", relative_point.x);
        RCLCPP_INFO(this->get_logger(), "rel y is %lf", relative_point.y);
        // 40 is arbitrary number picked to decide if occupancy grid has obstacle
        if (map.data[int((int(relative_point.y)*map.info.width) + relative_point.x)] > 40)
        {
          return true;
        }
      }
      return false;
    }

    /** \brief checks if the point lies within the boundary of the map */
    bool check_point_within_map(geometry_msgs::msg::Point point)
    {
      if (point.x < 0 || point.x > (map.info.width * map.info.resolution))
      {
        return false;
      }
      else if (point.y < 0 || point.y > (map.info.height * map.info.resolution))
      {
        return false;
      }
      return true;
    }

    /** \brief placeholder function for implementing x = f(v) */
    double get_distance_from_velocity()
    {
      // the max distance should be the maximum range of lidar
      double velocity = transvel;
      return velocity;
    }

    /** \brief calculate the coordinates of the points at the width of the robot */
    std::vector<geometry_msgs::msg::Point> calculate_width_points(double x, double y, double width, double theta)
    {
      int divisor = (width / map.info.resolution) / 2;
      double step = width / (2 * divisor);
      std::vector<geometry_msgs::msg::Point> points;
      geometry_msgs::msg::Point point = initialize_point(point, x, y);

      // RCLCPP_INFO(this->get_logger(), "x is %lf", x);
      // RCLCPP_INFO(this->get_logger(), "y is %lf", y);
      // points.push_back(point);
      geometry_msgs::msg::Point extrapolated_coordinate;
      double normal = get_normal(theta);
      RCLCPP_INFO(this->get_logger(), "theta is %lf", theta);
      // in addition to the origin point, extrapolate forwards and backwards and push_back them
      for (int i=0; i<divisor; i++)
      {
        points.clear();
        extrapolated_coordinate = get_extrapolated_coordinates(normal / 57.296, step);
        point.x += extrapolated_coordinate.x;
        point.y += extrapolated_coordinate.y;
        points.push_back(point);
        point = initialize_point(point, x, y);
        point.x -= extrapolated_coordinate.x;
        point.y -= extrapolated_coordinate.y;
        points.push_back(point);
        point = initialize_point(point, x, y);
        step += width / (2 * divisor);
      }
      publish_points(points);
      return points;
    }

    // test function for visualizing if the width extrapolating thing works
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub;
    void publish_points(std::vector<geometry_msgs::msg::Point> points)
    {
      visualization_msgs::msg::Marker width;
      width.header.frame_id = "pose";
      width.ns = "width_points";
      width.id = 0;
      width.type = 1;
      width.action = 0;
      width.scale.x = 0.05;
      width.scale.y = 0.05;
      width.scale.z = 0.05;
      width.color.a = 1;
      width.color.r = 0;
      width.color.g = 1;
      width.color.b = 0;
      for (unsigned long int i=0; i<points.size(); i++)
      {
        geometry_msgs::msg::Point temp;
        temp.x = points[i].x;
        temp.y = points[i].y;
        temp.z = 0;
        width.points.push_back(temp);
      }
      width.pose.orientation.w = 1;
      width.header.stamp = this->now();
      marker_pub->publish(width);
    }

    geometry_msgs::msg::Point initialize_point(geometry_msgs::msg::Point point ,double x, double y)
    {
      point.x = x;
      point.y = y;
      point.z = 0;
      return point;
    }

    /** \brief gets the normal angle for calculating width. assumes -180 to +180 degrees from 0 heading */
    double get_normal(double theta)
    {
      if (theta >= 90)
      {
        theta -= 90;
      }
      else
      {
        theta +=90;
      }
      return theta;
    }

    /** \brief This function takes in heading in radians and distance and returns the coordinate difference */
    geometry_msgs::msg::Point get_extrapolated_coordinates(double theta, double distance)
    {
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

    nav_msgs::msg::OccupancyGrid map;
    geometry_msgs::msg::Point current_goal;
    rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr goto_goal_sub;
    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr map_sub;
    rclcpp::Subscription<om_aiv_msg::msg::Status>::SharedPtr status_sub;
    // this arcl client is in charge of getting velocity and stopping the robot
    rclcpp_action::Client<om_aiv_msg::action::Action>::SharedPtr arcl_client;
    rclcpp::Client<om_aiv_msg::srv::GetPath>::SharedPtr path_planning_client;
    float transvel;
    double pi = 3.1415926535898;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ObstacleCheck>());
  rclcpp::shutdown();
  return 0;
}
