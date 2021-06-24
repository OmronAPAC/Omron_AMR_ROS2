#include "rclcpp/rclcpp.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "geometry_msgs/msg/quaternion.hpp"
#include "std_msgs/msg/string.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "om_aiv_msg/srv/arcl_api.hpp"
#include "om_aiv_msg/srv/arcl_listen.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

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

// Global variables
visualization_msgs::msg::Marker laser_points;

// Function prototypes
bool get_map_data(std::string filename, 
    std::vector<geometry_msgs::msg::Point>& points, 
    std::vector<geometry_msgs::msg::Point>& lines,
    visualization_msgs::msg::Marker& fa,
    visualization_msgs::msg::MarkerArray& f_areas);
void laser_sub_cb(const std_msgs::msg::String::SharedPtr msg);

// createQuaternionMsgFromYaw function
geometry_msgs::msg::Quaternion createQuaternionMsgFromYaw(double yaw)
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

// Node declaration
rclcpp::Node::SharedPtr node = nullptr;

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    node = std::make_shared<rclcpp::Node>("data_points_marker");
    rclcpp::Rate rate(5);

    // Get all parameters.
    node->declare_parameter(PACK_NAME_PARAM, "pkg");
    node->declare_parameter(MAP_NAME_PARAM, "data.map");
    node->declare_parameter(HEAD_FRAME_PARAM, "/pose");
    node->declare_parameter(VIS_TOPIC_PARAM, "visualization_marker");
    node->declare_parameter(RNG_DEVICE_PARAM, "Laser_1");
    node->declare_parameter(POINTS_A_CLR_PARAM, 1.0);
    node->declare_parameter(POINTS_R_CLR_PARAM, 0.0);
    node->declare_parameter(POINTS_G_CLR_PARAM, 0.0);
    node->declare_parameter(POINTS_B_CLR_PARAM, 0.0);
    node->declare_parameter(LINES_A_CLR_PARAM, 1.0);
    node->declare_parameter(LINES_R_CLR_PARAM, 0.0);
    node->declare_parameter(LINES_G_CLR_PARAM, 0.0);
    node->declare_parameter(LINES_B_CLR_PARAM, 0.0);
    node->declare_parameter(LS_POINTS_A_CLR_PARAM, 1.0);
    node->declare_parameter(LS_POINTS_R_CLR_PARAM, 0.0);
    node->declare_parameter(LS_POINTS_G_CLR_PARAM, 0.0);
    node->declare_parameter(LS_POINTS_B_CLR_PARAM, 0.0);
    node->declare_parameter(FA_A_CLR_PARAM, 0.5);
    node->declare_parameter(FA_R_CLR_PARAM, 1.0);
    node->declare_parameter(FA_G_CLR_PARAM, 0.0);
    node->declare_parameter(FA_B_CLR_PARAM, 0.0);

    PACK_NAME = node->get_parameter(PACK_NAME_PARAM).as_string();
    MAP_NAME = node->get_parameter(MAP_NAME_PARAM).as_string();
    HEAD_FRAME = node->get_parameter(HEAD_FRAME_PARAM).as_string();
    VIS_TOPIC = node->get_parameter(VIS_TOPIC_PARAM).as_string();
    rng_device = node->get_parameter(RNG_DEVICE_PARAM).as_string();
    POINTS_A_CLR = node->get_parameter(POINTS_A_CLR_PARAM).as_double();
    POINTS_R_CLR = node->get_parameter(POINTS_R_CLR_PARAM).as_double();
    POINTS_G_CLR = node->get_parameter(POINTS_G_CLR_PARAM).as_double();
    POINTS_B_CLR = node->get_parameter(POINTS_B_CLR_PARAM).as_double();
    LINES_A_CLR = node->get_parameter(LINES_A_CLR_PARAM).as_double();
    LINES_R_CLR = node->get_parameter(LINES_R_CLR_PARAM).as_double();
    LINES_G_CLR = node->get_parameter(LINES_G_CLR_PARAM).as_double();
    LINES_B_CLR = node->get_parameter(LINES_B_CLR_PARAM).as_double();
    LS_POINTS_A_CLR = node->get_parameter(LS_POINTS_A_CLR_PARAM).as_double();
    LS_POINTS_R_CLR = node->get_parameter(LS_POINTS_R_CLR_PARAM).as_double();
    LS_POINTS_G_CLR = node->get_parameter(LS_POINTS_G_CLR_PARAM).as_double();
    LS_POINTS_B_CLR = node->get_parameter(LS_POINTS_B_CLR_PARAM).as_double();
    FA_A_CLR = node->get_parameter(FA_A_CLR_PARAM).as_double();
    FA_R_CLR = node->get_parameter(FA_R_CLR_PARAM).as_double();
    FA_G_CLR = node->get_parameter(FA_G_CLR_PARAM).as_double();
    FA_B_CLR = node->get_parameter(FA_B_CLR_PARAM).as_double();

    std::cout << "PACKNAME: " << PACK_NAME << std::endl;
    std::cout << "MAP_NAME: " << MAP_NAME << std::endl;
    std::cout << "HEAD_FRAME: " << HEAD_FRAME << std::endl;
    std::cout << "VIS_TOPIC: " << VIS_TOPIC << std::endl;
    std::cout << "rng_device: " << rng_device << std::endl;


    auto points_pub = node->create_publisher<visualization_msgs::msg::Marker>(VIS_TOPIC, 10);
    auto fa_pub = node->create_publisher<visualization_msgs::msg::MarkerArray>("f_areas", 10);
    auto laser_scan_pub = node->create_publisher<visualization_msgs::msg::Marker>(VIS_TOPIC, 10);
    auto laser_data_sub = node->create_subscription<std_msgs::msg::String>(LS_SUB_TOPIC, 10, laser_sub_cb);

    //// Begin drawing points and line on RVIZ ////
    std::vector<geometry_msgs::msg::Point> points;
    std::vector<geometry_msgs::msg::Point> lines;
    visualization_msgs::msg::MarkerArray f_areas;
    visualization_msgs::msg::Marker fa;
    fa.header.frame_id = HEAD_FRAME;
    fa.action = visualization_msgs::msg::Marker::ADD;
    fa.ns = FA_NS;
    fa.pose.orientation.w = 1.0;
    fa.pose.position.z = 0;
    fa.type = visualization_msgs::msg::Marker::CUBE;
    fa.id = 0;
    fa.scale.z = 0.25;
    fa.color.a = FA_A_CLR;
    fa.color.r = FA_R_CLR;
    fa.color.g = FA_G_CLR;
    fa.color.b = FA_B_CLR;
    
    if (!get_map_data(MAP_NAME, points, lines, fa, f_areas)) RCLCPP_ERROR(node->get_logger(), "Reading map failed");
    RCLCPP_INFO(node->get_logger(), "Waiting for RVIZ");

    // Configure the messages to publish.
    visualization_msgs::msg::Marker points_arr;
    visualization_msgs::msg::Marker lines_list;
    points_arr.header.frame_id = lines_list.header.frame_id = HEAD_FRAME;
    points_arr.header.stamp = lines_list.header.stamp = node->now();
    points_arr.ns = POINTS_NS;
    lines_list.ns = LINES_NS;
    points_arr.action = lines_list.action = visualization_msgs::msg::Marker::ADD;
    points_arr.pose.orientation.w = lines_list.pose.orientation.w = 1.0;
    points_arr.id = POINTS_M_ID;
    lines_list.id = LINES_M_ID;
    points_arr.type = visualization_msgs::msg::Marker::POINTS;
    lines_list.type = visualization_msgs::msg::Marker::LINE_LIST;
    points_arr.scale.x = POINTS_X_SCALE;
    points_arr.scale.y = POINTS_Y_SCALE;
    lines_list.scale.x = LINES_X_SCALE;
    points_arr.color.a = POINTS_A_CLR;
    points_arr.color.r = POINTS_R_CLR;
    points_arr.color.g = POINTS_G_CLR;
    points_arr.color.b = POINTS_B_CLR;
    lines_list.color.a = LINES_A_CLR;
    lines_list.color.r = LINES_R_CLR;
    lines_list.color.g = LINES_G_CLR;
    lines_list.color.b = LINES_B_CLR;

    // Prepare all points.
    for (int i = 0; i < (int) points.size(); i++)
    {
        points_arr.points.push_back(points[i]);
    }

    // Prepare all lines.
    for (int i = 0; i < (int) lines.size(); i++)
    {
        lines_list.points.push_back(lines[i]);
    }
    
    /// Draw laser scan data ///
    laser_points.header.frame_id = HEAD_FRAME;
    laser_points.action = visualization_msgs::msg::Marker::ADD;
    laser_points.ns = LS_POINTS_NS;
    laser_points.pose.orientation.w = 1.0;
    laser_points.type = visualization_msgs::msg::Marker::POINTS;
    laser_points.id = LS_POINTS_M_ID;
    laser_points.scale.x = LS_POINTS_X_SCALE;
    laser_points.scale.y = LS_POINTS_Y_SCALE;
    laser_points.color.a = LS_POINTS_A_CLR;
    laser_points.color.r = LS_POINTS_R_CLR;
    laser_points.color.g = LS_POINTS_G_CLR;
    laser_points.color.b = LS_POINTS_B_CLR;
    
    // std::cout << laser_points.points[1].x << "HeaveHo" << std::endl;
    while (rclcpp::ok())
    {
        points_pub->publish(points_arr);
        points_pub->publish(lines_list);
        fa_pub->publish(f_areas);

        laser_points.header.stamp = node->now();
        laser_scan_pub->publish(laser_points);
        rclcpp::spin_some(node);
        rate.sleep();
    }
    return 0;
}

/**
 * @brief Attemps to open .map file with the given file name and read all points and lines coordinates.
 * 
 * @param filename name of .map file to read, including file extension.
 * @param points Vector to store all read points.
 * @param lines Vector to store all read lines.
 * @return true if data is read without issue.
 * @return false if file fails to open or there is error in reading data.
 */
bool get_map_data(std::string filename, 
    std::vector<geometry_msgs::msg::Point>& points,
    std::vector<geometry_msgs::msg::Point>& lines,
    visualization_msgs::msg::Marker& fa,
    visualization_msgs::msg::MarkerArray& f_areas)
{
    // Read map file
    //std::string path = ament_index_cpp::get_package_share_directory(PACK_NAME);
    //path = path.append(MAP_FOLDER).append("/");
    //std::string map_path = path.append(filename);
    std::string map_path = ament_index_cpp::get_package_share_directory("amr_visualisation") + "/map/" + filename;
    std::ifstream map_file(map_path);
    if (map_file.fail()) return false;

    int num_of_points = 0;
    int num_of_lines = 0;
    std::string line;
    std::string ignore_head;
    while (std::getline(map_file, line))
    {
        // Retrieve the number of points.
        if (line.find(POINTS_NUM_H) != std::string::npos)
        {
            std::istringstream iss(line);
            iss >> ignore_head;
            iss >> num_of_points;
        }

        // Retrieve the number of lines.
        if (line.find(LINES_NUM_H) != std::string::npos)
        {
            std::istringstream iss(line);
            iss >> ignore_head;
            iss >> num_of_lines;
        }

        // We have seen the points data, collect them.
        if (line.find(POINTS_H) != std::string::npos)
        {
            int x, y;
            for (int i = 0; i < num_of_points; i++)
            {
                std::getline(map_file, line);
                std::istringstream iss(line);
                if (!(iss >> x >> y)) 
                    RCLCPP_ERROR(node->get_logger(), "%s - Error reading points from file.", "amr_visualisation");
                geometry_msgs::msg::Point p;
                p.x = (double)x / 1000.0; // Values are in millimeter.
                p.y = (double)y / 1000.0;
                p.z = 0;
                points.push_back(p);
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
                    RCLCPP_ERROR(node->get_logger(), "%s - Error reading points from file.", "348");
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
        }

        // This line contains forbidden area information, collect them.
        if (line.find(FA_H) != std::string::npos)
        {
            // Read the raw info
            double x1, y1, x2, y2, dt_theta;
            std::istringstream iss(line);
            std::string dummy;
            for (int i = 0; i < 8; i++)
            {
                // The first 8 pieces of that line are irrelevant except for the 5th piece which is the angle/orientation of the forbidden area.
                if (i == 4)
                {
                    iss >> dt_theta;
                    dt_theta = dt_theta * 0.01745329;
                }
                else
                {
                    iss >> dummy;
                }
            }
            if (!(iss >> y1 >> x1 >> y2 >> x2)) 
                RCLCPP_ERROR(node->get_logger(), "%s - Error reading forbidden area from file: %s", 
                    "Hi", "Bye");

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
    }
    return true;
}

/**
 * @brief Callback function for subscribing to laser scan values topic.
 * 
 * @param msg Message containing a string of values.
 */
void laser_sub_cb(const std_msgs::msg::String::SharedPtr msg)
{
    std::string raw_resp = msg->data;
    std::string::size_type pos = raw_resp.find(rng_device);
    if (pos != std::string::npos)
    {
        laser_points.points.clear();
        std::string vals_str;
        try
        {
            vals_str = raw_resp.substr(pos + rng_device.length() + 1); // +1 to exclude the following space.
        }
        catch(const std::out_of_range& e)
        {
            // RCLCPP_ERROR(node->get_logger(), "ERROROROROROR");
            // std::cout <<  "CAUGHTEGEGEGEGEGEGE" << std::endl;
            vals_str.clear();
        }
        std::istringstream iss(vals_str);
        //std::istringstream iss("-2000 -20 -5555 -55");
        double x, y = 0.0;
        laser_points.points.clear();

        // std::cout << "0 iss is: " << iss.str() << std::endl;
        // iss >> x;
        // std::cout << "1 iss is: " << iss.str() << " but x is : " << x << std::endl;
        // iss >> x;
        // std::cout << "2 iss is: " << iss.str() << " but x is : " << x << std::endl;
        // iss >> x;
        // std::cout << "3 iss is: " << iss.str() << " but x is : " << x << std::endl;
        // iss >> x;
        // std::cout << "4 iss is: " << iss.str() << " but x is : " << x << std::endl;
        // std::cout << iss.str() << std::endl;
        // std::cout << "0BOOLEAN IS: " << (bool) (iss >> x >> y) << std::endl;
        // std::cout << "1BOOLEAN IS: " << (bool) (iss >> x >> y) << std::endl;
        // std::cout << "2BOOLEAN IS: " << (bool) (iss >> x >> y) << std::endl;
        // std::cout << "3BOOLEAN IS: " << (bool) (iss >> x >> y) << std::endl;
        // std::cout << "4BOOLEAN IS: " << (bool) (iss >> x >> y) << std::endl;
        // std::cout << "5BOOLEAN IS: " << (bool) (iss >> x >> y) << std::endl;
        
        //std::cout << vals_str << std::endl;
        //std::cout << (bool) (iss >> x) << " " << y << " HUEHUEHUEHUE" << std::endl;
        while (iss >> x >> y)
        {
            geometry_msgs::msg::Point p;
            p.x = x / 1000.0;
            p.y = y / 1000.0;
            p.z = 0;
            laser_points.points.push_back(p);
            //std::cout << laser_points.points[1].x << std::endl;
            //std::cout << p.x << " " << p.y << " TRTRTRTRT" << std::endl;
        }
        //std::cout <<  x << " " << y << " TRTRTRTRT" << std::endl;

    }
}