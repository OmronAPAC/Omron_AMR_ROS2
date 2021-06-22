// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from om_aiv_msg:msg/Status.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__MSG__DETAIL__STATUS__TRAITS_HPP_
#define OM_AIV_MSG__MSG__DETAIL__STATUS__TRAITS_HPP_

#include "om_aiv_msg/msg/detail/status__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'location'
#include "om_aiv_msg/msg/detail/location__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::msg::Status>()
{
  return "om_aiv_msg::msg::Status";
}

template<>
inline const char * name<om_aiv_msg::msg::Status>()
{
  return "om_aiv_msg/msg/Status";
}

template<>
struct has_fixed_size<om_aiv_msg::msg::Status>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<om_aiv_msg::msg::Status>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<om_aiv_msg::msg::Status>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OM_AIV_MSG__MSG__DETAIL__STATUS__TRAITS_HPP_
