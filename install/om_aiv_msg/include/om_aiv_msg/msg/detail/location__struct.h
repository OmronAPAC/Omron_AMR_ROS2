// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from om_aiv_msg:msg/Location.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__MSG__DETAIL__LOCATION__STRUCT_H_
#define OM_AIV_MSG__MSG__DETAIL__LOCATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Location in the package om_aiv_msg.
typedef struct om_aiv_msg__msg__Location
{
  double x;
  double y;
  double theta;
} om_aiv_msg__msg__Location;

// Struct for a sequence of om_aiv_msg__msg__Location.
typedef struct om_aiv_msg__msg__Location__Sequence
{
  om_aiv_msg__msg__Location * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__msg__Location__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OM_AIV_MSG__MSG__DETAIL__LOCATION__STRUCT_H_
