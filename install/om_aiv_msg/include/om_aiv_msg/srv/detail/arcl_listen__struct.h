// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from om_aiv_msg:srv/ArclListen.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__STRUCT_H_
#define OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'resp_header'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/ArclListen in the package om_aiv_msg.
typedef struct om_aiv_msg__srv__ArclListen_Request
{
  rosidl_runtime_c__String resp_header;
} om_aiv_msg__srv__ArclListen_Request;

// Struct for a sequence of om_aiv_msg__srv__ArclListen_Request.
typedef struct om_aiv_msg__srv__ArclListen_Request__Sequence
{
  om_aiv_msg__srv__ArclListen_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__srv__ArclListen_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'resp_text'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/ArclListen in the package om_aiv_msg.
typedef struct om_aiv_msg__srv__ArclListen_Response
{
  rosidl_runtime_c__String resp_text;
} om_aiv_msg__srv__ArclListen_Response;

// Struct for a sequence of om_aiv_msg__srv__ArclListen_Response.
typedef struct om_aiv_msg__srv__ArclListen_Response__Sequence
{
  om_aiv_msg__srv__ArclListen_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__srv__ArclListen_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__STRUCT_H_
