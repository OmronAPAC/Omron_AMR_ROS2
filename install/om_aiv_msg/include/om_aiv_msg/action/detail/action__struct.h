// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from om_aiv_msg:action/Action.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__ACTION__DETAIL__ACTION__STRUCT_H_
#define OM_AIV_MSG__ACTION__DETAIL__ACTION__STRUCT_H_

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
// Member 'identifier'
#include "rosidl_runtime_c/string.h"

// Struct defined in action/Action in the package om_aiv_msg.
typedef struct om_aiv_msg__action__Action_Goal
{
  rosidl_runtime_c__String command;
  rosidl_runtime_c__String__Sequence identifier;
} om_aiv_msg__action__Action_Goal;

// Struct for a sequence of om_aiv_msg__action__Action_Goal.
typedef struct om_aiv_msg__action__Action_Goal__Sequence
{
  om_aiv_msg__action__Action_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__action__Action_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'res_msg'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in action/Action in the package om_aiv_msg.
typedef struct om_aiv_msg__action__Action_Result
{
  rosidl_runtime_c__String res_msg;
} om_aiv_msg__action__Action_Result;

// Struct for a sequence of om_aiv_msg__action__Action_Result.
typedef struct om_aiv_msg__action__Action_Result__Sequence
{
  om_aiv_msg__action__Action_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__action__Action_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'feed_msg'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in action/Action in the package om_aiv_msg.
typedef struct om_aiv_msg__action__Action_Feedback
{
  rosidl_runtime_c__String feed_msg;
} om_aiv_msg__action__Action_Feedback;

// Struct for a sequence of om_aiv_msg__action__Action_Feedback.
typedef struct om_aiv_msg__action__Action_Feedback__Sequence
{
  om_aiv_msg__action__Action_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__action__Action_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "om_aiv_msg/action/detail/action__struct.h"

// Struct defined in action/Action in the package om_aiv_msg.
typedef struct om_aiv_msg__action__Action_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  om_aiv_msg__action__Action_Goal goal;
} om_aiv_msg__action__Action_SendGoal_Request;

// Struct for a sequence of om_aiv_msg__action__Action_SendGoal_Request.
typedef struct om_aiv_msg__action__Action_SendGoal_Request__Sequence
{
  om_aiv_msg__action__Action_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__action__Action_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

// Struct defined in action/Action in the package om_aiv_msg.
typedef struct om_aiv_msg__action__Action_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} om_aiv_msg__action__Action_SendGoal_Response;

// Struct for a sequence of om_aiv_msg__action__Action_SendGoal_Response.
typedef struct om_aiv_msg__action__Action_SendGoal_Response__Sequence
{
  om_aiv_msg__action__Action_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__action__Action_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

// Struct defined in action/Action in the package om_aiv_msg.
typedef struct om_aiv_msg__action__Action_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} om_aiv_msg__action__Action_GetResult_Request;

// Struct for a sequence of om_aiv_msg__action__Action_GetResult_Request.
typedef struct om_aiv_msg__action__Action_GetResult_Request__Sequence
{
  om_aiv_msg__action__Action_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__action__Action_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "om_aiv_msg/action/detail/action__struct.h"

// Struct defined in action/Action in the package om_aiv_msg.
typedef struct om_aiv_msg__action__Action_GetResult_Response
{
  int8_t status;
  om_aiv_msg__action__Action_Result result;
} om_aiv_msg__action__Action_GetResult_Response;

// Struct for a sequence of om_aiv_msg__action__Action_GetResult_Response.
typedef struct om_aiv_msg__action__Action_GetResult_Response__Sequence
{
  om_aiv_msg__action__Action_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__action__Action_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "om_aiv_msg/action/detail/action__struct.h"

// Struct defined in action/Action in the package om_aiv_msg.
typedef struct om_aiv_msg__action__Action_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  om_aiv_msg__action__Action_Feedback feedback;
} om_aiv_msg__action__Action_FeedbackMessage;

// Struct for a sequence of om_aiv_msg__action__Action_FeedbackMessage.
typedef struct om_aiv_msg__action__Action_FeedbackMessage__Sequence
{
  om_aiv_msg__action__Action_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} om_aiv_msg__action__Action_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OM_AIV_MSG__ACTION__DETAIL__ACTION__STRUCT_H_
