// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from om_aiv_msg:srv/ArclApi.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__SRV__DETAIL__ARCL_API__BUILDER_HPP_
#define OM_AIV_MSG__SRV__DETAIL__ARCL_API__BUILDER_HPP_

#include "om_aiv_msg/srv/detail/arcl_api__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace om_aiv_msg
{

namespace srv
{

namespace builder
{

class Init_ArclApi_Request_line_identifier
{
public:
  explicit Init_ArclApi_Request_line_identifier(::om_aiv_msg::srv::ArclApi_Request & msg)
  : msg_(msg)
  {}
  ::om_aiv_msg::srv::ArclApi_Request line_identifier(::om_aiv_msg::srv::ArclApi_Request::_line_identifier_type arg)
  {
    msg_.line_identifier = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::srv::ArclApi_Request msg_;
};

class Init_ArclApi_Request_command
{
public:
  Init_ArclApi_Request_command()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArclApi_Request_line_identifier command(::om_aiv_msg::srv::ArclApi_Request::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_ArclApi_Request_line_identifier(msg_);
  }

private:
  ::om_aiv_msg::srv::ArclApi_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::srv::ArclApi_Request>()
{
  return om_aiv_msg::srv::builder::Init_ArclApi_Request_command();
}

}  // namespace om_aiv_msg


namespace om_aiv_msg
{

namespace srv
{

namespace builder
{

class Init_ArclApi_Response_response
{
public:
  Init_ArclApi_Response_response()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::om_aiv_msg::srv::ArclApi_Response response(::om_aiv_msg::srv::ArclApi_Response::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::srv::ArclApi_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::srv::ArclApi_Response>()
{
  return om_aiv_msg::srv::builder::Init_ArclApi_Response_response();
}

}  // namespace om_aiv_msg

#endif  // OM_AIV_MSG__SRV__DETAIL__ARCL_API__BUILDER_HPP_
