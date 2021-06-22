// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from om_aiv_msg:srv/ArclListen.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__TRAITS_HPP_
#define OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__TRAITS_HPP_

#include "om_aiv_msg/srv/detail/arcl_listen__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::srv::ArclListen_Request>()
{
  return "om_aiv_msg::srv::ArclListen_Request";
}

template<>
inline const char * name<om_aiv_msg::srv::ArclListen_Request>()
{
  return "om_aiv_msg/srv/ArclListen_Request";
}

template<>
struct has_fixed_size<om_aiv_msg::srv::ArclListen_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<om_aiv_msg::srv::ArclListen_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<om_aiv_msg::srv::ArclListen_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::srv::ArclListen_Response>()
{
  return "om_aiv_msg::srv::ArclListen_Response";
}

template<>
inline const char * name<om_aiv_msg::srv::ArclListen_Response>()
{
  return "om_aiv_msg/srv/ArclListen_Response";
}

template<>
struct has_fixed_size<om_aiv_msg::srv::ArclListen_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<om_aiv_msg::srv::ArclListen_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<om_aiv_msg::srv::ArclListen_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::srv::ArclListen>()
{
  return "om_aiv_msg::srv::ArclListen";
}

template<>
inline const char * name<om_aiv_msg::srv::ArclListen>()
{
  return "om_aiv_msg/srv/ArclListen";
}

template<>
struct has_fixed_size<om_aiv_msg::srv::ArclListen>
  : std::integral_constant<
    bool,
    has_fixed_size<om_aiv_msg::srv::ArclListen_Request>::value &&
    has_fixed_size<om_aiv_msg::srv::ArclListen_Response>::value
  >
{
};

template<>
struct has_bounded_size<om_aiv_msg::srv::ArclListen>
  : std::integral_constant<
    bool,
    has_bounded_size<om_aiv_msg::srv::ArclListen_Request>::value &&
    has_bounded_size<om_aiv_msg::srv::ArclListen_Response>::value
  >
{
};

template<>
struct is_service<om_aiv_msg::srv::ArclListen>
  : std::true_type
{
};

template<>
struct is_service_request<om_aiv_msg::srv::ArclListen_Request>
  : std::true_type
{
};

template<>
struct is_service_response<om_aiv_msg::srv::ArclListen_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__TRAITS_HPP_
