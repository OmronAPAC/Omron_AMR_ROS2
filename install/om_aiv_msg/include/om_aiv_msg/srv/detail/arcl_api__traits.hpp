// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from om_aiv_msg:srv/ArclApi.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__SRV__DETAIL__ARCL_API__TRAITS_HPP_
#define OM_AIV_MSG__SRV__DETAIL__ARCL_API__TRAITS_HPP_

#include "om_aiv_msg/srv/detail/arcl_api__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::srv::ArclApi_Request>()
{
  return "om_aiv_msg::srv::ArclApi_Request";
}

template<>
inline const char * name<om_aiv_msg::srv::ArclApi_Request>()
{
  return "om_aiv_msg/srv/ArclApi_Request";
}

template<>
struct has_fixed_size<om_aiv_msg::srv::ArclApi_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<om_aiv_msg::srv::ArclApi_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<om_aiv_msg::srv::ArclApi_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::srv::ArclApi_Response>()
{
  return "om_aiv_msg::srv::ArclApi_Response";
}

template<>
inline const char * name<om_aiv_msg::srv::ArclApi_Response>()
{
  return "om_aiv_msg/srv/ArclApi_Response";
}

template<>
struct has_fixed_size<om_aiv_msg::srv::ArclApi_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<om_aiv_msg::srv::ArclApi_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<om_aiv_msg::srv::ArclApi_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::srv::ArclApi>()
{
  return "om_aiv_msg::srv::ArclApi";
}

template<>
inline const char * name<om_aiv_msg::srv::ArclApi>()
{
  return "om_aiv_msg/srv/ArclApi";
}

template<>
struct has_fixed_size<om_aiv_msg::srv::ArclApi>
  : std::integral_constant<
    bool,
    has_fixed_size<om_aiv_msg::srv::ArclApi_Request>::value &&
    has_fixed_size<om_aiv_msg::srv::ArclApi_Response>::value
  >
{
};

template<>
struct has_bounded_size<om_aiv_msg::srv::ArclApi>
  : std::integral_constant<
    bool,
    has_bounded_size<om_aiv_msg::srv::ArclApi_Request>::value &&
    has_bounded_size<om_aiv_msg::srv::ArclApi_Response>::value
  >
{
};

template<>
struct is_service<om_aiv_msg::srv::ArclApi>
  : std::true_type
{
};

template<>
struct is_service_request<om_aiv_msg::srv::ArclApi_Request>
  : std::true_type
{
};

template<>
struct is_service_response<om_aiv_msg::srv::ArclApi_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // OM_AIV_MSG__SRV__DETAIL__ARCL_API__TRAITS_HPP_
