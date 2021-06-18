#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "geometry_msgs/msg/quaternion.hpp"
#include "std_msgs/msg/string.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "om_aiv_msg/srv/arcl_api.hpp"
#include "om_aiv_msg/srv/arcl_listen.hpp"

// Configurable values.
std::string head_frame;
std::string goals_vis_topic;
float goals_a_clr;
float goals_r_clr;
float goals_g_clr;
float goals_b_clr;
float goal_texts_a_clr;
float goal_texts_r_clr;
float goal_texts_g_clr;
float goal_texts_b_clr;
int32_t goals_id = 0;
int32_t goal_texts_id = 0;

// Non configurable values.
const std::string GOALS_NS = "goals";
const std::string GOALS_TEXT_NS = "goal_texts";
const std::string GOAL_RESP_H = "Goal";
const std::string COORD_H = "MapObjectInfoCoord: ";
const std::string GOAL_CMD = "MapObjectInfo ";
const std::string GOALS_LIST_END = "End of MapObjectInfo";
const std::string API_SRV_NAME = "arcl_api_service";
const std::string ALL_GOALS_TOPIC = "ldarcl_all_goals";
const double GOALS_X_SCALE = 0.5;
const double GOALS_Y_SCALE = 0.1;
const double GOALS_Z_SCALE = 0.07;
const double GOAL_TEXT_X_SCALE = 0.1;
const double GOAL_TEXT_Y_SCALE = 0.1;
const double GOAL_TEXT_Z_SCALE = 0.5;
const double GOAL_TEXT_HEIGHT_Z = 0.5;

// Names for all config parameters.
const std::string HEAD_FRAME_PARAM = "head_frame";
const std::string GOALS_VIS_TOPIC = "goals_vis_topic";
const std::string GOALS_A_CLR_PARAM = "goals_a_colour";
const std::string GOALS_R_CLR_PARAM = "goals_r_colour";
const std::string GOALS_G_CLR_PARAM = "goals_g_colour";
const std::string GOALS_B_CLR_PARAM = "goals_b_colour";
const std::string GOAL_TEXTS_A_CLR_PARAM = "goal_texts_a_colour";
const std::string GOAL_TEXTS_R_CLR_PARAM = "goal_texts_r_colour";
const std::string GOAL_TEXTS_G_CLR_PARAM = "goal_texts_g_colour";
const std::string GOAL_TEXTS_B_CLR_PARAM = "goal_texts_b_colour";

// Global variables
std::vector<std::string> goals_list;

// Function prototypes
void req_goals_coord(
    rclcpp::Client<om_aiv_msg::srv::ArclApi>::SharedPtr& arcl_api_client, 
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Request_<std::allocator<void>>>& goals_info_req, 
    visualization_msgs::msg::MarkerArray& goals,
    visualization_msgs::msg::MarkerArray& goals_text,
    visualization_msgs::msg::Marker one_goal,
    visualization_msgs::msg::Marker one_goal_text);
void all_goals_cb(const std_msgs::msg::String::SharedPtr msg);

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
    node = std::make_shared<rclcpp::Node>("goals_marker");
    rclcpp::Rate rate(0.1);

    node->declare_parameter(HEAD_FRAME_PARAM, "/pose");
    node->declare_parameter(GOALS_VIS_TOPIC, "visualization_marker_array");
    node->declare_parameter(GOALS_A_CLR_PARAM, 1.0);
    node->declare_parameter(GOALS_R_CLR_PARAM, 0.0);
    node->declare_parameter(GOALS_G_CLR_PARAM, 1.0);
    node->declare_parameter(GOALS_B_CLR_PARAM, 0.0);
    node->declare_parameter(GOAL_TEXTS_A_CLR_PARAM, 1.0);
    node->declare_parameter(GOAL_TEXTS_R_CLR_PARAM, 0.0);
    node->declare_parameter(GOAL_TEXTS_G_CLR_PARAM, 1.0);
    node->declare_parameter(GOAL_TEXTS_B_CLR_PARAM, 0.0);

    head_frame = node->get_parameter(HEAD_FRAME_PARAM).as_string();
    goals_vis_topic = node->get_parameter(GOALS_VIS_TOPIC).as_string();
    goals_a_clr = node->get_parameter(GOALS_A_CLR_PARAM).as_double();
    goals_r_clr = node->get_parameter(GOALS_R_CLR_PARAM).as_double();
    goals_g_clr = node->get_parameter(GOALS_G_CLR_PARAM).as_double();
    goals_b_clr= node->get_parameter(GOALS_B_CLR_PARAM).as_double();
    goal_texts_a_clr = node->get_parameter(GOAL_TEXTS_A_CLR_PARAM).as_double();
    goal_texts_r_clr = node->get_parameter(GOAL_TEXTS_R_CLR_PARAM).as_double();
    goal_texts_g_clr = node->get_parameter(GOAL_TEXTS_G_CLR_PARAM).as_double();
    goal_texts_b_clr = node->get_parameter(GOAL_TEXTS_B_CLR_PARAM).as_double();

    auto arcl_api_client = node->create_client<om_aiv_msg::srv::ArclApi>(API_SRV_NAME);
    auto goals_pub = node->create_publisher<visualization_msgs::msg::MarkerArray>(goals_vis_topic, 10);
    auto all_goals_sub = node->create_subscription<std_msgs::msg::String>(ALL_GOALS_TOPIC, 10, all_goals_cb);

    // TODO: ARROW is used wrongly, read the documentation!
    // Create MarkerArray for all goals Markers. Each goal is one Marker object that is of ARROW type.
    // Cannot use Marker.points, it works differently from POINTS type.
    // ALSO LOOK AT getGoals, think its a simpler way to get goal coordinates.
    visualization_msgs::msg::MarkerArray goals;
    visualization_msgs::msg::Marker one_goal;
    visualization_msgs::msg::MarkerArray goals_text;
    visualization_msgs::msg::Marker one_goal_text;
    one_goal.header.frame_id = head_frame;
    one_goal.ns = GOALS_NS;
    one_goal.action = visualization_msgs::msg::Marker::MODIFY;
    one_goal.id = goals_id;
    one_goal.type = visualization_msgs::msg::Marker::ARROW;
    one_goal.scale.x = GOALS_X_SCALE;
    one_goal.scale.y = GOALS_Y_SCALE;
    one_goal.scale.z = GOALS_Z_SCALE;
    one_goal.color.a = goals_a_clr;
    one_goal.color.r = goals_r_clr;
    one_goal.color.g = goals_g_clr;
    one_goal.color.b = goals_b_clr;
    one_goal_text.header.frame_id = head_frame;
    one_goal_text.ns = GOALS_TEXT_NS;
    one_goal_text.action = visualization_msgs::msg::Marker::MODIFY;
    one_goal_text.pose.orientation.w = 1.0;
    one_goal_text.id = goal_texts_id;
    one_goal_text.type = visualization_msgs::msg::Marker::TEXT_VIEW_FACING;
    one_goal_text.pose.position.z = GOAL_TEXT_HEIGHT_Z;
    one_goal_text.scale.z = GOAL_TEXT_Z_SCALE;
    one_goal_text.color.a = goals_a_clr;
    one_goal_text.color.r = goals_r_clr;
    one_goal_text.color.g = goals_g_clr;
    one_goal_text.color.b = goals_b_clr;

    // Create the service request messages to get goals data.
    auto goals_list_req = std::make_shared<om_aiv_msg::srv::ArclListen::Request>();
    //std::cout << "HELLO DARKNESS POKEMON OF TYPE: " << 
    goals_list_req->resp_header = GOAL_RESP_H;

    auto goals_info_req = std::make_shared<om_aiv_msg::srv::ArclApi::Request>();
    goals_info_req->line_identifier = GOALS_LIST_END;

    while (rclcpp::ok())
    {
        req_goals_coord(arcl_api_client, goals_info_req, goals, goals_text, one_goal, one_goal_text);
        for (int i = 0; i < (int) goals.markers.size(); i++)
        {
            goals.markers[i].header.stamp = node->now();
        }

        goals_pub->publish(goals);
        goals_pub->publish(goals_text);
        
        rclcpp::spin_some(node);
        rate.sleep();
    }

    return 0;
}

void req_goals_coord(
    rclcpp::Client<om_aiv_msg::srv::ArclApi>::SharedPtr& arcl_api_client, 
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Request_<std::allocator<void>>>& goals_info_req, 
    visualization_msgs::msg::MarkerArray& goals,
    visualization_msgs::msg::MarkerArray& goals_text,
    visualization_msgs::msg::Marker one_goal,
    visualization_msgs::msg::Marker one_goal_text)
{
    // Request for every known goal's coordinates.
    goals.markers.clear();
    goals_id = 0;
    goal_texts_id = 0;
    std::string cmd = GOAL_CMD;

    for (int i = 0; i < (int) goals_list.size(); i++)
    {
        goals_info_req->command = cmd + goals_list[i];

        // Send request to rclcpp service.
        auto result = arcl_api_client->async_send_request(goals_info_req);
        rclcpp::spin_until_future_complete(node, result);
        std::string info_resp = result.get()->response;
        std::string::size_type pos = info_resp.find(COORD_H);
        // std::cout << "info_resp is:   " << info_resp << std::endl;
        if (pos != std::string::npos)
        {
            // We have found the line containing the coordinates, collect them.
            std::string::size_type end = info_resp.find("\r\n", pos);
            std::string val_str = info_resp.substr(pos+COORD_H.size(), end);
            //std::cout << "VAL_STR is: " << val_str << std::endl;
            std::istringstream val_iss(val_str);
            std::string dummy;
            double x, y, theta;
            if (!(val_iss >> dummy >> x >> y >> theta)) RCLCPP_ERROR(node->get_logger(), "Error reading goal coordinates");
            x /= 1000.0;
            y /= 1000.0;
            one_goal.pose.position.x = x; // Convert from mm to metre.
            one_goal.pose.position.y = y;
            one_goal.pose.position.z = 0;
            if (theta < 0) theta += 360.0;
            theta = theta * 0.01745329252; // Convert line to radian
            one_goal.pose.orientation = createQuaternionMsgFromYaw(theta);
            one_goal.id = goals_id++;
            goals.markers.push_back(one_goal);
            one_goal_text.pose.position.x = x;
            one_goal_text.pose.position.y = y;
            one_goal_text.text = goals_list[i];
            one_goal_text.id = goal_texts_id++;
            goals_text.markers.push_back(one_goal_text);
        }
        // }
        else
        {
            RCLCPP_ERROR(node->get_logger(), "Failed to call %s service for goal info.", API_SRV_NAME.c_str());
        }
    }
}

/**
 * @brief Callback function for subscribing to list of goals.
 * 
 * @param msg Message containing the string of list of goals.
 */
void all_goals_cb(const std_msgs::msg::String::SharedPtr msg)
{
    goals_list.clear();
    std::string raw_resp = msg->data;
    std::istringstream iss(raw_resp);
    // Retrieve all goals' name.
    std::string name;
    while (iss >> name)
    {
        goals_list.push_back(name);
    }
}