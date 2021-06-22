// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from om_aiv_msg:msg/Status.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "om_aiv_msg/msg/detail/status__rosidl_typesupport_introspection_c.h"
#include "om_aiv_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "om_aiv_msg/msg/detail/status__functions.h"
#include "om_aiv_msg/msg/detail/status__struct.h"


// Include directives for member types
// Member `extended_status`
// Member `status`
#include "rosidl_runtime_c/string_functions.h"
// Member `location`
#include "om_aiv_msg/msg/location.h"
// Member `location`
#include "om_aiv_msg/msg/detail/location__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void Status__rosidl_typesupport_introspection_c__Status_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  om_aiv_msg__msg__Status__init(message_memory);
}

void Status__rosidl_typesupport_introspection_c__Status_fini_function(void * message_memory)
{
  om_aiv_msg__msg__Status__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember Status__rosidl_typesupport_introspection_c__Status_message_member_array[6] = {
  {
    "extended_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(om_aiv_msg__msg__Status, extended_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(om_aiv_msg__msg__Status, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "state_of_charge",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(om_aiv_msg__msg__Status, state_of_charge),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "localization_score",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(om_aiv_msg__msg__Status, localization_score),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "temperature",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(om_aiv_msg__msg__Status, temperature),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "location",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(om_aiv_msg__msg__Status, location),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers Status__rosidl_typesupport_introspection_c__Status_message_members = {
  "om_aiv_msg__msg",  // message namespace
  "Status",  // message name
  6,  // number of fields
  sizeof(om_aiv_msg__msg__Status),
  Status__rosidl_typesupport_introspection_c__Status_message_member_array,  // message members
  Status__rosidl_typesupport_introspection_c__Status_init_function,  // function to initialize message memory (memory has to be allocated)
  Status__rosidl_typesupport_introspection_c__Status_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t Status__rosidl_typesupport_introspection_c__Status_message_type_support_handle = {
  0,
  &Status__rosidl_typesupport_introspection_c__Status_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_om_aiv_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, om_aiv_msg, msg, Status)() {
  Status__rosidl_typesupport_introspection_c__Status_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, om_aiv_msg, msg, Location)();
  if (!Status__rosidl_typesupport_introspection_c__Status_message_type_support_handle.typesupport_identifier) {
    Status__rosidl_typesupport_introspection_c__Status_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &Status__rosidl_typesupport_introspection_c__Status_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
