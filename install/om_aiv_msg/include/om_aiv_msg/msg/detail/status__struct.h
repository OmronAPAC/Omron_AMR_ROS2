// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from om_aiv_msg:msg/Status.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__MSG__DETAIL__STATUS__STRUCT_H_
#define OM_AIV_MSG__MSG__DETAIL__STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'extended_status'
// Member 'status'
#include "rosidl_runtime_c/string.h"
// Member 'location'
#include "om_aiv_msg/msg/detail/location__struct.h"

// Struct defined in msg/Status in the package om_aiv_msg.
typedef struct om_aiv_msg__msg__Status
{
  rosidl_runtime_c__String extended_status;
  rosidl_runtime_c__String status;
  float state_of_charge;
  float localization_score;
  float temperature;
  om_aiv_msg__msg__Location location;
} om_aiv_msg__msg__Status;

// Struct for a sequence of om_aiv_msg__msg__Status.
typedef struct om_aiv_msg__msg__Status__Sequence
{
  om_aiv_msg__msg__Status * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__msg__Status__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OM_AIV_MSG__MSG__DETAIL__STATUS__STRUCT_H_
