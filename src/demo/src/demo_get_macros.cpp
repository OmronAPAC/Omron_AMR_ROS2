#include <vector>

#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "om_aiv_msg/srv/arcl_api.hpp"
#include "om_aiv_msg/srv/arcl_listen.hpp"
#include "demo/utils.hpp"


using namespace std::chrono_literals;

/*
This example shows how to make calls to the ARCL server using ROS2 service and client 
to get all defined macros in the robot
*/

int main(int argc, char const *argv[]) {
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("get_macros");
    auto srv_name = "arcl_api_service";
    auto client = node->create_client<om_aiv_msg::srv::ArclApi>(srv_name);

    auto request = std::make_shared<om_aiv_msg::srv::ArclApi::Request>();
    request->command = "getMacros";
    request->line_identifier = "End of macros";

    while (!client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(node->get_logger(), "service not available, waiting again...");
    }

    auto result = client->async_send_request(request);
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS) {
        std::vector<std::string> macros{};
        auto resp = result.get()->response;
        split(resp, '\n', macros);
        RCLCPP_INFO(node->get_logger(), "Macros:");

        // Skip the last two lines (identifier and empty line)
        for (auto iter = macros.begin(); iter != std::prev(std::prev(macros.end())); iter++) {
            std::cout << extract_macro_name(*iter) << std::endl;
        }
        
    } else {
        RCLCPP_ERROR(node->get_logger(), "Failed to call service %s", srv_name);
    }
    return 0;
}
