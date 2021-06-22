// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from om_aiv_msg:srv/ArclApi.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "om_aiv_msg/srv/detail/arcl_api__rosidl_typesupport_introspection_c.h"
#include "om_aiv_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "om_aiv_msg/srv/detail/arcl_api__functions.h"
#include "om_aiv_msg/srv/detail/arcl_api__struct.h"


// Include directives for member types
// Member `command`
// Member `line_identifier`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  om_aiv_msg__srv__ArclApi_Request__init(message_memory);
}

void ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_fini_function(void * message_memory)
{
  om_aiv_msg__srv__ArclApi_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_message_member_array[2] = {
  {
    "command",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(om_aiv_msg__srv__ArclApi_Request, command),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "line_identifier",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(om_aiv_msg__srv__ArclApi_Request, line_identifier),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_message_members = {
  "om_aiv_msg__srv",  // message namespace
  "ArclApi_Request",  // message name
  2,  // number of fields
  sizeof(om_aiv_msg__srv__ArclApi_Request),
  ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_message_member_array,  // message members
  ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_message_type_support_handle = {
  0,
  &ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_om_aiv_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, om_aiv_msg, srv, ArclApi_Request)() {
  if (!ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_message_type_support_handle.typesupport_identifier) {
    ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ArclApi_Request__rosidl_typesupport_introspection_c__ArclApi_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "om_aiv_msg/srv/detail/arcl_api__rosidl_typesupport_introspection_c.h"
// already included above
// #include "om_aiv_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "om_aiv_msg/srv/detail/arcl_api__functions.h"
// already included above
// #include "om_aiv_msg/srv/detail/arcl_api__struct.h"


// Include directives for member types
// Member `response`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  om_aiv_msg__srv__ArclApi_Response__init(message_memory);
}

void ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_fini_function(void * message_memory)
{
  om_aiv_msg__srv__ArclApi_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_message_member_array[1] = {
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(om_aiv_msg__srv__ArclApi_Response, response),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_message_members = {
  "om_aiv_msg__srv",  // message namespace
  "ArclApi_Response",  // message name
  1,  // number of fields
  sizeof(om_aiv_msg__srv__ArclApi_Response),
  ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_message_member_array,  // message members
  ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_message_type_support_handle = {
  0,
  &ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_om_aiv_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, om_aiv_msg, srv, ArclApi_Response)() {
  if (!ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_message_type_support_handle.typesupport_identifier) {
    ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ArclApi_Response__rosidl_typesupport_introspection_c__ArclApi_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "om_aiv_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "om_aiv_msg/srv/detail/arcl_api__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers om_aiv_msg__srv__detail__arcl_api__rosidl_typesupport_introspection_c__ArclApi_service_members = {
  "om_aiv_msg__srv",  // service namespace
  "ArclApi",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // om_aiv_msg__srv__detail__arcl_api__rosidl_typesupport_introspection_c__ArclApi_Request_message_type_support_handle,
  NULL  // response message
  // om_aiv_msg__srv__detail__arcl_api__rosidl_typesupport_introspection_c__ArclApi_Response_message_type_support_handle
};

static rosidl_service_type_support_t om_aiv_msg__srv__detail__arcl_api__rosidl_typesupport_introspection_c__ArclApi_service_type_support_handle = {
  0,
  &om_aiv_msg__srv__detail__arcl_api__rosidl_typesupport_introspection_c__ArclApi_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, om_aiv_msg, srv, ArclApi_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, om_aiv_msg, srv, ArclApi_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_om_aiv_msg
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, om_aiv_msg, srv, ArclApi)() {
  if (!om_aiv_msg__srv__detail__arcl_api__rosidl_typesupport_introspection_c__ArclApi_service_type_support_handle.typesupport_identifier) {
    om_aiv_msg__srv__detail__arcl_api__rosidl_typesupport_introspection_c__ArclApi_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)om_aiv_msg__srv__detail__arcl_api__rosidl_typesupport_introspection_c__ArclApi_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, om_aiv_msg, srv, ArclApi_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, om_aiv_msg, srv, ArclApi_Response)()->data;
  }

  return &om_aiv_msg__srv__detail__arcl_api__rosidl_typesupport_introspection_c__ArclApi_service_type_support_handle;
}
