// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from om_aiv_msg:msg/Location.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__MSG__DETAIL__LOCATION__TRAITS_HPP_
#define OM_AIV_MSG__MSG__DETAIL__LOCATION__TRAITS_HPP_

#include "om_aiv_msg/msg/detail/location__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::msg::Location>()
{
  return "om_aiv_msg::msg::Location";
}

template<>
inline const char * name<om_aiv_msg::msg::Location>()
{
  return "om_aiv_msg/msg/Location";
}

template<>
struct has_fixed_size<om_aiv_msg::msg::Location>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<om_aiv_msg::msg::Location>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<om_aiv_msg::msg::Location>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OM_AIV_MSG__MSG__DETAIL__LOCATION__TRAITS_HPP_
