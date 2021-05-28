// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from om_aiv_msg:msg/Status.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__MSG__DETAIL__STATUS__BUILDER_HPP_
#define OM_AIV_MSG__MSG__DETAIL__STATUS__BUILDER_HPP_

#include "om_aiv_msg/msg/detail/status__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace om_aiv_msg
{

namespace msg
{

namespace builder
{

class Init_Status_location
{
public:
  explicit Init_Status_location(::om_aiv_msg::msg::Status & msg)
  : msg_(msg)
  {}
  ::om_aiv_msg::msg::Status location(::om_aiv_msg::msg::Status::_location_type arg)
  {
    msg_.location = std::move(arg);
    return std::move(msg_);
  }

private:
  ::om_aiv_msg::msg::Status msg_;
};

class Init_Status_temperature
{
public:
  explicit Init_Status_temperature(::om_aiv_msg::msg::Status & msg)
  : msg_(msg)
  {}
  Init_Status_location temperature(::om_aiv_msg::msg::Status::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return Init_Status_location(msg_);
  }

private:
  ::om_aiv_msg::msg::Status msg_;
};

class Init_Status_localization_score
{
public:
  explicit Init_Status_localization_score(::om_aiv_msg::msg::Status & msg)
  : msg_(msg)
  {}
  Init_Status_temperature localization_score(::om_aiv_msg::msg::Status::_localization_score_type arg)
  {
    msg_.localization_score = std::move(arg);
    return Init_Status_temperature(msg_);
  }

private:
  ::om_aiv_msg::msg::Status msg_;
};

class Init_Status_state_of_charge
{
public:
  explicit Init_Status_state_of_charge(::om_aiv_msg::msg::Status & msg)
  : msg_(msg)
  {}
  Init_Status_localization_score state_of_charge(::om_aiv_msg::msg::Status::_state_of_charge_type arg)
  {
    msg_.state_of_charge = std::move(arg);
    return Init_Status_localization_score(msg_);
  }

private:
  ::om_aiv_msg::msg::Status msg_;
};

class Init_Status_status
{
public:
  explicit Init_Status_status(::om_aiv_msg::msg::Status & msg)
  : msg_(msg)
  {}
  Init_Status_state_of_charge status(::om_aiv_msg::msg::Status::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Status_state_of_charge(msg_);
  }

private:
  ::om_aiv_msg::msg::Status msg_;
};

class Init_Status_extended_status
{
public:
  Init_Status_extended_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Status_status extended_status(::om_aiv_msg::msg::Status::_extended_status_type arg)
  {
    msg_.extended_status = std::move(arg);
    return Init_Status_status(msg_);
  }

private:
  ::om_aiv_msg::msg::Status msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::om_aiv_msg::msg::Status>()
{
  return om_aiv_msg::msg::builder::Init_Status_extended_status();
}

}  // namespace om_aiv_msg

#endif  // OM_AIV_MSG__MSG__DETAIL__STATUS__BUILDER_HPP_
