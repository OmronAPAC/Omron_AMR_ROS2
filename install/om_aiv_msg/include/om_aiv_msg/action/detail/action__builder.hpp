// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from om_aiv_msg:action/Action.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__ACTION__DETAIL__ACTION__BUILDER_HPP_
#define OM_AIV_MSG__ACTION__DETAIL__ACTION__BUILDER_HPP_

#include "om_aiv_msg/action/detail/action__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace om_aiv_msg
{

namespace action
{

namespace builder
{

class Init_Action_Goal_identifier
{
public:
  explicit Init_Action_Goal_identifier(::om_aiv_msg::action::Action_Goal & msg)
  : msg_(msg)
  {}
  ::om_aiv_msg::action::Action_Goal identifier(::om_aiv_msg::action::Action_Goal::_identifier_type arg)
  {
    msg_.identifier = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::action::Action_Goal msg_;
};

class Init_Action_Goal_command
{
public:
  Init_Action_Goal_command()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Action_Goal_identifier command(::om_aiv_msg::action::Action_Goal::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_Action_Goal_identifier(msg_);
  }

private:
  ::om_aiv_msg::action::Action_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::action::Action_Goal>()
{
  return om_aiv_msg::action::builder::Init_Action_Goal_command();
}

}  // namespace om_aiv_msg


namespace om_aiv_msg
{

namespace action
{

namespace builder
{

class Init_Action_Result_res_msg
{
public:
  Init_Action_Result_res_msg()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::om_aiv_msg::action::Action_Result res_msg(::om_aiv_msg::action::Action_Result::_res_msg_type arg)
  {
    msg_.res_msg = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::action::Action_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::action::Action_Result>()
{
  return om_aiv_msg::action::builder::Init_Action_Result_res_msg();
}

}  // namespace om_aiv_msg


namespace om_aiv_msg
{

namespace action
{

namespace builder
{

class Init_Action_Feedback_feed_msg
{
public:
  Init_Action_Feedback_feed_msg()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::om_aiv_msg::action::Action_Feedback feed_msg(::om_aiv_msg::action::Action_Feedback::_feed_msg_type arg)
  {
    msg_.feed_msg = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::action::Action_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::action::Action_Feedback>()
{
  return om_aiv_msg::action::builder::Init_Action_Feedback_feed_msg();
}

}  // namespace om_aiv_msg


namespace om_aiv_msg
{

namespace action
{

namespace builder
{

class Init_Action_SendGoal_Request_goal
{
public:
  explicit Init_Action_SendGoal_Request_goal(::om_aiv_msg::action::Action_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::om_aiv_msg::action::Action_SendGoal_Request goal(::om_aiv_msg::action::Action_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::action::Action_SendGoal_Request msg_;
};

class Init_Action_SendGoal_Request_goal_id
{
public:
  Init_Action_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Action_SendGoal_Request_goal goal_id(::om_aiv_msg::action::Action_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Action_SendGoal_Request_goal(msg_);
  }

private:
  ::om_aiv_msg::action::Action_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::action::Action_SendGoal_Request>()
{
  return om_aiv_msg::action::builder::Init_Action_SendGoal_Request_goal_id();
}

}  // namespace om_aiv_msg


namespace om_aiv_msg
{

namespace action
{

namespace builder
{

class Init_Action_SendGoal_Response_stamp
{
public:
  explicit Init_Action_SendGoal_Response_stamp(::om_aiv_msg::action::Action_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::om_aiv_msg::action::Action_SendGoal_Response stamp(::om_aiv_msg::action::Action_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::action::Action_SendGoal_Response msg_;
};

class Init_Action_SendGoal_Response_accepted
{
public:
  Init_Action_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Action_SendGoal_Response_stamp accepted(::om_aiv_msg::action::Action_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_Action_SendGoal_Response_stamp(msg_);
  }

private:
  ::om_aiv_msg::action::Action_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::action::Action_SendGoal_Response>()
{
  return om_aiv_msg::action::builder::Init_Action_SendGoal_Response_accepted();
}

}  // namespace om_aiv_msg


namespace om_aiv_msg
{

namespace action
{

namespace builder
{

class Init_Action_GetResult_Request_goal_id
{
public:
  Init_Action_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::om_aiv_msg::action::Action_GetResult_Request goal_id(::om_aiv_msg::action::Action_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::action::Action_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::action::Action_GetResult_Request>()
{
  return om_aiv_msg::action::builder::Init_Action_GetResult_Request_goal_id();
}

}  // namespace om_aiv_msg


namespace om_aiv_msg
{

namespace action
{

namespace builder
{

class Init_Action_GetResult_Response_result
{
public:
  explicit Init_Action_GetResult_Response_result(::om_aiv_msg::action::Action_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::om_aiv_msg::action::Action_GetResult_Response result(::om_aiv_msg::action::Action_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::action::Action_GetResult_Response msg_;
};

class Init_Action_GetResult_Response_status
{
public:
  Init_Action_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Action_GetResult_Response_result status(::om_aiv_msg::action::Action_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Action_GetResult_Response_result(msg_);
  }

private:
  ::om_aiv_msg::action::Action_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::action::Action_GetResult_Response>()
{
  return om_aiv_msg::action::builder::Init_Action_GetResult_Response_status();
}

}  // namespace om_aiv_msg


namespace om_aiv_msg
{

namespace action
{

namespace builder
{

class Init_Action_FeedbackMessage_feedback
{
public:
  explicit Init_Action_FeedbackMessage_feedback(::om_aiv_msg::action::Action_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::om_aiv_msg::action::Action_FeedbackMessage feedback(::om_aiv_msg::action::Action_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::action::Action_FeedbackMessage msg_;
};

class Init_Action_FeedbackMessage_goal_id
{
public:
  Init_Action_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Action_FeedbackMessage_feedback goal_id(::om_aiv_msg::action::Action_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Action_FeedbackMessage_feedback(msg_);
  }

private:
  ::om_aiv_msg::action::Action_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::action::Action_FeedbackMessage>()
{
  return om_aiv_msg::action::builder::Init_Action_FeedbackMessage_goal_id();
}

}  // namespace om_aiv_msg

#endif  // OM_AIV_MSG__ACTION__DETAIL__ACTION__BUILDER_HPP_
