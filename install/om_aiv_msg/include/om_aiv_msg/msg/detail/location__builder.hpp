// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from om_aiv_msg:msg/Location.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__MSG__DETAIL__LOCATION__BUILDER_HPP_
#define OM_AIV_MSG__MSG__DETAIL__LOCATION__BUILDER_HPP_

#include "om_aiv_msg/msg/detail/location__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace om_aiv_msg
{

namespace msg
{

namespace builder
{

class Init_Location_theta
{
public:
  explicit Init_Location_theta(::om_aiv_msg::msg::Location & msg)
  : msg_(msg)
  {}
  ::om_aiv_msg::msg::Location theta(::om_aiv_msg::msg::Location::_theta_type arg)
  {
    msg_.theta = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::msg::Location msg_;
};

class Init_Location_y
{
public:
  explicit Init_Location_y(::om_aiv_msg::msg::Location & msg)
  : msg_(msg)
  {}
  Init_Location_theta y(::om_aiv_msg::msg::Location::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Location_theta(msg_);
  }

private:
  ::om_aiv_msg::msg::Location msg_;
};

class Init_Location_x
{
public:
  Init_Location_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Location_y x(::om_aiv_msg::msg::Location::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Location_y(msg_);
  }

private:
  ::om_aiv_msg::msg::Location msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::msg::Location>()
{
  return om_aiv_msg::msg::builder::Init_Location_x();
}

}  // namespace om_aiv_msg

#endif  // OM_AIV_MSG__MSG__DETAIL__LOCATION__BUILDER_HPP_
