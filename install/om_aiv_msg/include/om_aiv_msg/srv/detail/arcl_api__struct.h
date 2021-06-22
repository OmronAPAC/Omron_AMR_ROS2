// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from om_aiv_msg:srv/ArclApi.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__SRV__DETAIL__ARCL_API__STRUCT_H_
#define OM_AIV_MSG__SRV__DETAIL__ARCL_API__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'command'
// Member 'line_identifier'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/ArclApi in the package om_aiv_msg.
typedef struct om_aiv_msg__srv__ArclApi_Request
{
  rosidl_runtime_c__String command;
  rosidl_runtime_c__String line_identifier;
} om_aiv_msg__srv__ArclApi_Request;

// Struct for a sequence of om_aiv_msg__srv__ArclApi_Request.
typedef struct om_aiv_msg__srv__ArclApi_Request__Sequence
{
  om_aiv_msg__srv__ArclApi_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__srv__ArclApi_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'response'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/ArclApi in the package om_aiv_msg.
typedef struct om_aiv_msg__srv__ArclApi_Response
{
  rosidl_runtime_c__String response;
} om_aiv_msg__srv__ArclApi_Response;

// Struct for a sequence of om_aiv_msg__srv__ArclApi_Response.
typedef struct om_aiv_msg__srv__ArclApi_Response__Sequence
{
  om_aiv_msg__srv__ArclApi_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__srv__ArclApi_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OM_AIV_MSG__SRV__DETAIL__ARCL_API__STRUCT_H_
