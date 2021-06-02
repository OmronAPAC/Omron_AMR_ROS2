// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from om_aiv_msg:action/Action.idl
// generated code does not contain a copyright notice
#include "om_aiv_msg/action/detail/action__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `command`
// Member `identifier`
#include "rosidl_runtime_c/string_functions.h"

bool
om_aiv_msg__action__Action_Goal__init(om_aiv_msg__action__Action_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // command
  if (!rosidl_runtime_c__String__init(&msg->command)) {
    om_aiv_msg__action__Action_Goal__fini(msg);
    return false;
  }
  // identifier
  if (!rosidl_runtime_c__String__Sequence__init(&msg->identifier, 0)) {
    om_aiv_msg__action__Action_Goal__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__action__Action_Goal__fini(om_aiv_msg__action__Action_Goal * msg)
{
  if (!msg) {
    return;
  }
  // command
  rosidl_runtime_c__String__fini(&msg->command);
  // identifier
  rosidl_runtime_c__String__Sequence__fini(&msg->identifier);
}

om_aiv_msg__action__Action_Goal *
om_aiv_msg__action__Action_Goal__create()
{
  om_aiv_msg__action__Action_Goal * msg = (om_aiv_msg__action__Action_Goal *)malloc(sizeof(om_aiv_msg__action__Action_Goal));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__action__Action_Goal));
  bool success = om_aiv_msg__action__Action_Goal__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__action__Action_Goal__destroy(om_aiv_msg__action__Action_Goal * msg)
{
  if (msg) {
    om_aiv_msg__action__Action_Goal__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__action__Action_Goal__Sequence__init(om_aiv_msg__action__Action_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__action__Action_Goal * data = NULL;
  if (size) {
    data = (om_aiv_msg__action__Action_Goal *)calloc(size, sizeof(om_aiv_msg__action__Action_Goal));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__action__Action_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__action__Action_Goal__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
om_aiv_msg__action__Action_Goal__Sequence__fini(om_aiv_msg__action__Action_Goal__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__action__Action_Goal__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

om_aiv_msg__action__Action_Goal__Sequence *
om_aiv_msg__action__Action_Goal__Sequence__create(size_t size)
{
  om_aiv_msg__action__Action_Goal__Sequence * array = (om_aiv_msg__action__Action_Goal__Sequence *)malloc(sizeof(om_aiv_msg__action__Action_Goal__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__action__Action_Goal__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__action__Action_Goal__Sequence__destroy(om_aiv_msg__action__Action_Goal__Sequence * array)
{
  if (array) {
    om_aiv_msg__action__Action_Goal__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `res_msg`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
om_aiv_msg__action__Action_Result__init(om_aiv_msg__action__Action_Result * msg)
{
  if (!msg) {
    return false;
  }
  // res_msg
  if (!rosidl_runtime_c__String__init(&msg->res_msg)) {
    om_aiv_msg__action__Action_Result__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__action__Action_Result__fini(om_aiv_msg__action__Action_Result * msg)
{
  if (!msg) {
    return;
  }
  // res_msg
  rosidl_runtime_c__String__fini(&msg->res_msg);
}

om_aiv_msg__action__Action_Result *
om_aiv_msg__action__Action_Result__create()
{
  om_aiv_msg__action__Action_Result * msg = (om_aiv_msg__action__Action_Result *)malloc(sizeof(om_aiv_msg__action__Action_Result));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__action__Action_Result));
  bool success = om_aiv_msg__action__Action_Result__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__action__Action_Result__destroy(om_aiv_msg__action__Action_Result * msg)
{
  if (msg) {
    om_aiv_msg__action__Action_Result__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__action__Action_Result__Sequence__init(om_aiv_msg__action__Action_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__action__Action_Result * data = NULL;
  if (size) {
    data = (om_aiv_msg__action__Action_Result *)calloc(size, sizeof(om_aiv_msg__action__Action_Result));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__action__Action_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__action__Action_Result__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
om_aiv_msg__action__Action_Result__Sequence__fini(om_aiv_msg__action__Action_Result__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__action__Action_Result__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

om_aiv_msg__action__Action_Result__Sequence *
om_aiv_msg__action__Action_Result__Sequence__create(size_t size)
{
  om_aiv_msg__action__Action_Result__Sequence * array = (om_aiv_msg__action__Action_Result__Sequence *)malloc(sizeof(om_aiv_msg__action__Action_Result__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__action__Action_Result__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__action__Action_Result__Sequence__destroy(om_aiv_msg__action__Action_Result__Sequence * array)
{
  if (array) {
    om_aiv_msg__action__Action_Result__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `feed_msg`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
om_aiv_msg__action__Action_Feedback__init(om_aiv_msg__action__Action_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // feed_msg
  if (!rosidl_runtime_c__String__init(&msg->feed_msg)) {
    om_aiv_msg__action__Action_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__action__Action_Feedback__fini(om_aiv_msg__action__Action_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // feed_msg
  rosidl_runtime_c__String__fini(&msg->feed_msg);
}

om_aiv_msg__action__Action_Feedback *
om_aiv_msg__action__Action_Feedback__create()
{
  om_aiv_msg__action__Action_Feedback * msg = (om_aiv_msg__action__Action_Feedback *)malloc(sizeof(om_aiv_msg__action__Action_Feedback));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__action__Action_Feedback));
  bool success = om_aiv_msg__action__Action_Feedback__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__action__Action_Feedback__destroy(om_aiv_msg__action__Action_Feedback * msg)
{
  if (msg) {
    om_aiv_msg__action__Action_Feedback__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__action__Action_Feedback__Sequence__init(om_aiv_msg__action__Action_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__action__Action_Feedback * data = NULL;
  if (size) {
    data = (om_aiv_msg__action__Action_Feedback *)calloc(size, sizeof(om_aiv_msg__action__Action_Feedback));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__action__Action_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__action__Action_Feedback__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
om_aiv_msg__action__Action_Feedback__Sequence__fini(om_aiv_msg__action__Action_Feedback__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__action__Action_Feedback__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

om_aiv_msg__action__Action_Feedback__Sequence *
om_aiv_msg__action__Action_Feedback__Sequence__create(size_t size)
{
  om_aiv_msg__action__Action_Feedback__Sequence * array = (om_aiv_msg__action__Action_Feedback__Sequence *)malloc(sizeof(om_aiv_msg__action__Action_Feedback__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__action__Action_Feedback__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__action__Action_Feedback__Sequence__destroy(om_aiv_msg__action__Action_Feedback__Sequence * array)
{
  if (array) {
    om_aiv_msg__action__Action_Feedback__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "om_aiv_msg/action/detail/action__functions.h"

bool
om_aiv_msg__action__Action_SendGoal_Request__init(om_aiv_msg__action__Action_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    om_aiv_msg__action__Action_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!om_aiv_msg__action__Action_Goal__init(&msg->goal)) {
    om_aiv_msg__action__Action_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__action__Action_SendGoal_Request__fini(om_aiv_msg__action__Action_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  om_aiv_msg__action__Action_Goal__fini(&msg->goal);
}

om_aiv_msg__action__Action_SendGoal_Request *
om_aiv_msg__action__Action_SendGoal_Request__create()
{
  om_aiv_msg__action__Action_SendGoal_Request * msg = (om_aiv_msg__action__Action_SendGoal_Request *)malloc(sizeof(om_aiv_msg__action__Action_SendGoal_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__action__Action_SendGoal_Request));
  bool success = om_aiv_msg__action__Action_SendGoal_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__action__Action_SendGoal_Request__destroy(om_aiv_msg__action__Action_SendGoal_Request * msg)
{
  if (msg) {
    om_aiv_msg__action__Action_SendGoal_Request__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__action__Action_SendGoal_Request__Sequence__init(om_aiv_msg__action__Action_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__action__Action_SendGoal_Request * data = NULL;
  if (size) {
    data = (om_aiv_msg__action__Action_SendGoal_Request *)calloc(size, sizeof(om_aiv_msg__action__Action_SendGoal_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__action__Action_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__action__Action_SendGoal_Request__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
om_aiv_msg__action__Action_SendGoal_Request__Sequence__fini(om_aiv_msg__action__Action_SendGoal_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__action__Action_SendGoal_Request__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

om_aiv_msg__action__Action_SendGoal_Request__Sequence *
om_aiv_msg__action__Action_SendGoal_Request__Sequence__create(size_t size)
{
  om_aiv_msg__action__Action_SendGoal_Request__Sequence * array = (om_aiv_msg__action__Action_SendGoal_Request__Sequence *)malloc(sizeof(om_aiv_msg__action__Action_SendGoal_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__action__Action_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__action__Action_SendGoal_Request__Sequence__destroy(om_aiv_msg__action__Action_SendGoal_Request__Sequence * array)
{
  if (array) {
    om_aiv_msg__action__Action_SendGoal_Request__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
om_aiv_msg__action__Action_SendGoal_Response__init(om_aiv_msg__action__Action_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    om_aiv_msg__action__Action_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__action__Action_SendGoal_Response__fini(om_aiv_msg__action__Action_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

om_aiv_msg__action__Action_SendGoal_Response *
om_aiv_msg__action__Action_SendGoal_Response__create()
{
  om_aiv_msg__action__Action_SendGoal_Response * msg = (om_aiv_msg__action__Action_SendGoal_Response *)malloc(sizeof(om_aiv_msg__action__Action_SendGoal_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__action__Action_SendGoal_Response));
  bool success = om_aiv_msg__action__Action_SendGoal_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__action__Action_SendGoal_Response__destroy(om_aiv_msg__action__Action_SendGoal_Response * msg)
{
  if (msg) {
    om_aiv_msg__action__Action_SendGoal_Response__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__action__Action_SendGoal_Response__Sequence__init(om_aiv_msg__action__Action_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__action__Action_SendGoal_Response * data = NULL;
  if (size) {
    data = (om_aiv_msg__action__Action_SendGoal_Response *)calloc(size, sizeof(om_aiv_msg__action__Action_SendGoal_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__action__Action_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__action__Action_SendGoal_Response__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
om_aiv_msg__action__Action_SendGoal_Response__Sequence__fini(om_aiv_msg__action__Action_SendGoal_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__action__Action_SendGoal_Response__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

om_aiv_msg__action__Action_SendGoal_Response__Sequence *
om_aiv_msg__action__Action_SendGoal_Response__Sequence__create(size_t size)
{
  om_aiv_msg__action__Action_SendGoal_Response__Sequence * array = (om_aiv_msg__action__Action_SendGoal_Response__Sequence *)malloc(sizeof(om_aiv_msg__action__Action_SendGoal_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__action__Action_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__action__Action_SendGoal_Response__Sequence__destroy(om_aiv_msg__action__Action_SendGoal_Response__Sequence * array)
{
  if (array) {
    om_aiv_msg__action__Action_SendGoal_Response__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
om_aiv_msg__action__Action_GetResult_Request__init(om_aiv_msg__action__Action_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    om_aiv_msg__action__Action_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__action__Action_GetResult_Request__fini(om_aiv_msg__action__Action_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

om_aiv_msg__action__Action_GetResult_Request *
om_aiv_msg__action__Action_GetResult_Request__create()
{
  om_aiv_msg__action__Action_GetResult_Request * msg = (om_aiv_msg__action__Action_GetResult_Request *)malloc(sizeof(om_aiv_msg__action__Action_GetResult_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__action__Action_GetResult_Request));
  bool success = om_aiv_msg__action__Action_GetResult_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__action__Action_GetResult_Request__destroy(om_aiv_msg__action__Action_GetResult_Request * msg)
{
  if (msg) {
    om_aiv_msg__action__Action_GetResult_Request__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__action__Action_GetResult_Request__Sequence__init(om_aiv_msg__action__Action_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__action__Action_GetResult_Request * data = NULL;
  if (size) {
    data = (om_aiv_msg__action__Action_GetResult_Request *)calloc(size, sizeof(om_aiv_msg__action__Action_GetResult_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__action__Action_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__action__Action_GetResult_Request__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
om_aiv_msg__action__Action_GetResult_Request__Sequence__fini(om_aiv_msg__action__Action_GetResult_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__action__Action_GetResult_Request__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

om_aiv_msg__action__Action_GetResult_Request__Sequence *
om_aiv_msg__action__Action_GetResult_Request__Sequence__create(size_t size)
{
  om_aiv_msg__action__Action_GetResult_Request__Sequence * array = (om_aiv_msg__action__Action_GetResult_Request__Sequence *)malloc(sizeof(om_aiv_msg__action__Action_GetResult_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__action__Action_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__action__Action_GetResult_Request__Sequence__destroy(om_aiv_msg__action__Action_GetResult_Request__Sequence * array)
{
  if (array) {
    om_aiv_msg__action__Action_GetResult_Request__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `result`
// already included above
// #include "om_aiv_msg/action/detail/action__functions.h"

bool
om_aiv_msg__action__Action_GetResult_Response__init(om_aiv_msg__action__Action_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!om_aiv_msg__action__Action_Result__init(&msg->result)) {
    om_aiv_msg__action__Action_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__action__Action_GetResult_Response__fini(om_aiv_msg__action__Action_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  om_aiv_msg__action__Action_Result__fini(&msg->result);
}

om_aiv_msg__action__Action_GetResult_Response *
om_aiv_msg__action__Action_GetResult_Response__create()
{
  om_aiv_msg__action__Action_GetResult_Response * msg = (om_aiv_msg__action__Action_GetResult_Response *)malloc(sizeof(om_aiv_msg__action__Action_GetResult_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__action__Action_GetResult_Response));
  bool success = om_aiv_msg__action__Action_GetResult_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__action__Action_GetResult_Response__destroy(om_aiv_msg__action__Action_GetResult_Response * msg)
{
  if (msg) {
    om_aiv_msg__action__Action_GetResult_Response__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__action__Action_GetResult_Response__Sequence__init(om_aiv_msg__action__Action_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__action__Action_GetResult_Response * data = NULL;
  if (size) {
    data = (om_aiv_msg__action__Action_GetResult_Response *)calloc(size, sizeof(om_aiv_msg__action__Action_GetResult_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__action__Action_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__action__Action_GetResult_Response__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
om_aiv_msg__action__Action_GetResult_Response__Sequence__fini(om_aiv_msg__action__Action_GetResult_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__action__Action_GetResult_Response__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

om_aiv_msg__action__Action_GetResult_Response__Sequence *
om_aiv_msg__action__Action_GetResult_Response__Sequence__create(size_t size)
{
  om_aiv_msg__action__Action_GetResult_Response__Sequence * array = (om_aiv_msg__action__Action_GetResult_Response__Sequence *)malloc(sizeof(om_aiv_msg__action__Action_GetResult_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__action__Action_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__action__Action_GetResult_Response__Sequence__destroy(om_aiv_msg__action__Action_GetResult_Response__Sequence * array)
{
  if (array) {
    om_aiv_msg__action__Action_GetResult_Response__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "om_aiv_msg/action/detail/action__functions.h"

bool
om_aiv_msg__action__Action_FeedbackMessage__init(om_aiv_msg__action__Action_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    om_aiv_msg__action__Action_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!om_aiv_msg__action__Action_Feedback__init(&msg->feedback)) {
    om_aiv_msg__action__Action_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__action__Action_FeedbackMessage__fini(om_aiv_msg__action__Action_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  om_aiv_msg__action__Action_Feedback__fini(&msg->feedback);
}

om_aiv_msg__action__Action_FeedbackMessage *
om_aiv_msg__action__Action_FeedbackMessage__create()
{
  om_aiv_msg__action__Action_FeedbackMessage * msg = (om_aiv_msg__action__Action_FeedbackMessage *)malloc(sizeof(om_aiv_msg__action__Action_FeedbackMessage));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__action__Action_FeedbackMessage));
  bool success = om_aiv_msg__action__Action_FeedbackMessage__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__action__Action_FeedbackMessage__destroy(om_aiv_msg__action__Action_FeedbackMessage * msg)
{
  if (msg) {
    om_aiv_msg__action__Action_FeedbackMessage__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__action__Action_FeedbackMessage__Sequence__init(om_aiv_msg__action__Action_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__action__Action_FeedbackMessage * data = NULL;
  if (size) {
    data = (om_aiv_msg__action__Action_FeedbackMessage *)calloc(size, sizeof(om_aiv_msg__action__Action_FeedbackMessage));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__action__Action_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__action__Action_FeedbackMessage__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
om_aiv_msg__action__Action_FeedbackMessage__Sequence__fini(om_aiv_msg__action__Action_FeedbackMessage__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__action__Action_FeedbackMessage__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

om_aiv_msg__action__Action_FeedbackMessage__Sequence *
om_aiv_msg__action__Action_FeedbackMessage__Sequence__create(size_t size)
{
  om_aiv_msg__action__Action_FeedbackMessage__Sequence * array = (om_aiv_msg__action__Action_FeedbackMessage__Sequence *)malloc(sizeof(om_aiv_msg__action__Action_FeedbackMessage__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__action__Action_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__action__Action_FeedbackMessage__Sequence__destroy(om_aiv_msg__action__Action_FeedbackMessage__Sequence * array)
{
  if (array) {
    om_aiv_msg__action__Action_FeedbackMessage__Sequence__fini(array);
  }
  free(array);
}
