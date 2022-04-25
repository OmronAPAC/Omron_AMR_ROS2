#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>
#include <string>

#include "om_aiv_msg/action/action.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

/*
This example shows how to make calls to the ARCL server using ROS2 action
to execute a macro and view the feedback during execution
*/
namespace demo
{
class ActionClient : public rclcpp::Node
{
public:
  using Action = om_aiv_msg::action::Action;
  using GoalHandleAction = rclcpp_action::ClientGoalHandle<Action>;

  explicit ActionClient(const rclcpp::NodeOptions & options)
  : Node("execute_macro", options)
  {
    this->client_ptr_ = rclcpp_action::create_client<Action>(this, "action_server");

    this->timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&ActionClient::send_goal, this));

  }

  void send_goal()
  {
    using namespace std::placeholders;

    this->timer_->cancel();

    if (!this->client_ptr_->wait_for_action_server()) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    auto goal_msg = Action::Goal();
    goal_msg.command = "executeMacro Macro4";
    goal_msg.identifier = std::vector<std::string>{"Completed macro Macro4"};


    RCLCPP_INFO(this->get_logger(), "Sending goal");

    auto send_goal_options = rclcpp_action::Client<Action>::SendGoalOptions();
    send_goal_options.goal_response_callback =
      std::bind(&ActionClient::goal_response_callback, this, _1);
    send_goal_options.feedback_callback =
      std::bind(&ActionClient::feedback_callback, this, _1, _2);
    send_goal_options.result_callback =
      std::bind(&ActionClient::result_callback, this, _1);
    this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
  }

private:
  rclcpp_action::Client<Action>::SharedPtr client_ptr_;
  rclcpp::TimerBase::SharedPtr timer_;

  void goal_response_callback(std::shared_future<GoalHandleAction::SharedPtr> future)
  {
    auto goal_handle = future.get();
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
  }

    void feedback_callback(GoalHandleAction::SharedPtr,
        const std::shared_ptr<const Action::Feedback> feedback)
    {
        RCLCPP_INFO(this->get_logger(), feedback->feed_msg);
    }

  void result_callback(const GoalHandleAction::WrappedResult & result)
  {
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        break;
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
        return;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        return;
      default:
        RCLCPP_ERROR(this->get_logger(), "Unknown result code");
        return;
    }
    RCLCPP_INFO(this->get_logger(), result.result->res_msg);
    rclcpp::shutdown();
  }
};  // class ActionClient

}  // namespace demo

RCLCPP_COMPONENTS_REGISTER_NODE(demo::ActionClient)