// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from om_aiv_msg:srv/ArclApi.idl
// generated code does not contain a copyright notice
#include "om_aiv_msg/srv/detail/arcl_api__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Include directives for member types
// Member `command`
// Member `line_identifier`
#include "rosidl_runtime_c/string_functions.h"

bool
om_aiv_msg__srv__ArclApi_Request__init(om_aiv_msg__srv__ArclApi_Request * msg)
{
  if (!msg) {
    return false;
  }
  // command
  if (!rosidl_runtime_c__String__init(&msg->command)) {
    om_aiv_msg__srv__ArclApi_Request__fini(msg);
    return false;
  }
  // line_identifier
  if (!rosidl_runtime_c__String__init(&msg->line_identifier)) {
    om_aiv_msg__srv__ArclApi_Request__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__srv__ArclApi_Request__fini(om_aiv_msg__srv__ArclApi_Request * msg)
{
  if (!msg) {
    return;
  }
  // command
  rosidl_runtime_c__String__fini(&msg->command);
  // line_identifier
  rosidl_runtime_c__String__fini(&msg->line_identifier);
}

om_aiv_msg__srv__ArclApi_Request *
om_aiv_msg__srv__ArclApi_Request__create()
{
  om_aiv_msg__srv__ArclApi_Request * msg = (om_aiv_msg__srv__ArclApi_Request *)malloc(sizeof(om_aiv_msg__srv__ArclApi_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__srv__ArclApi_Request));
  bool success = om_aiv_msg__srv__ArclApi_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__srv__ArclApi_Request__destroy(om_aiv_msg__srv__ArclApi_Request * msg)
{
  if (msg) {
    om_aiv_msg__srv__ArclApi_Request__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__srv__ArclApi_Request__Sequence__init(om_aiv_msg__srv__ArclApi_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__srv__ArclApi_Request * data = NULL;
  if (size) {
    data = (om_aiv_msg__srv__ArclApi_Request *)calloc(size, sizeof(om_aiv_msg__srv__ArclApi_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__srv__ArclApi_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__srv__ArclApi_Request__fini(&data[i - 1]);
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
om_aiv_msg__srv__ArclApi_Request__Sequence__fini(om_aiv_msg__srv__ArclApi_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__srv__ArclApi_Request__fini(&array->data[i]);
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

om_aiv_msg__srv__ArclApi_Request__Sequence *
om_aiv_msg__srv__ArclApi_Request__Sequence__create(size_t size)
{
  om_aiv_msg__srv__ArclApi_Request__Sequence * array = (om_aiv_msg__srv__ArclApi_Request__Sequence *)malloc(sizeof(om_aiv_msg__srv__ArclApi_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__srv__ArclApi_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__srv__ArclApi_Request__Sequence__destroy(om_aiv_msg__srv__ArclApi_Request__Sequence * array)
{
  if (array) {
    om_aiv_msg__srv__ArclApi_Request__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `response`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
om_aiv_msg__srv__ArclApi_Response__init(om_aiv_msg__srv__ArclApi_Response * msg)
{
  if (!msg) {
    return false;
  }
  // response
  if (!rosidl_runtime_c__String__init(&msg->response)) {
    om_aiv_msg__srv__ArclApi_Response__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__srv__ArclApi_Response__fini(om_aiv_msg__srv__ArclApi_Response * msg)
{
  if (!msg) {
    return;
  }
  // response
  rosidl_runtime_c__String__fini(&msg->response);
}

om_aiv_msg__srv__ArclApi_Response *
om_aiv_msg__srv__ArclApi_Response__create()
{
  om_aiv_msg__srv__ArclApi_Response * msg = (om_aiv_msg__srv__ArclApi_Response *)malloc(sizeof(om_aiv_msg__srv__ArclApi_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__srv__ArclApi_Response));
  bool success = om_aiv_msg__srv__ArclApi_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__srv__ArclApi_Response__destroy(om_aiv_msg__srv__ArclApi_Response * msg)
{
  if (msg) {
    om_aiv_msg__srv__ArclApi_Response__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__srv__ArclApi_Response__Sequence__init(om_aiv_msg__srv__ArclApi_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__srv__ArclApi_Response * data = NULL;
  if (size) {
    data = (om_aiv_msg__srv__ArclApi_Response *)calloc(size, sizeof(om_aiv_msg__srv__ArclApi_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__srv__ArclApi_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__srv__ArclApi_Response__fini(&data[i - 1]);
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
om_aiv_msg__srv__ArclApi_Response__Sequence__fini(om_aiv_msg__srv__ArclApi_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__srv__ArclApi_Response__fini(&array->data[i]);
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

om_aiv_msg__srv__ArclApi_Response__Sequence *
om_aiv_msg__srv__ArclApi_Response__Sequence__create(size_t size)
{
  om_aiv_msg__srv__ArclApi_Response__Sequence * array = (om_aiv_msg__srv__ArclApi_Response__Sequence *)malloc(sizeof(om_aiv_msg__srv__ArclApi_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__srv__ArclApi_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__srv__ArclApi_Response__Sequence__destroy(om_aiv_msg__srv__ArclApi_Response__Sequence * array)
{
  if (array) {
    om_aiv_msg__srv__ArclApi_Response__Sequence__fini(array);
  }
  free(array);
}
