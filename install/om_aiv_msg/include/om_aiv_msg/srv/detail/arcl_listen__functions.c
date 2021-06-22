// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from om_aiv_msg:srv/ArclListen.idl
// generated code does not contain a copyright notice
#include "om_aiv_msg/srv/detail/arcl_listen__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Include directives for member types
// Member `resp_header`
#include "rosidl_runtime_c/string_functions.h"

bool
om_aiv_msg__srv__ArclListen_Request__init(om_aiv_msg__srv__ArclListen_Request * msg)
{
  if (!msg) {
    return false;
  }
  // resp_header
  if (!rosidl_runtime_c__String__init(&msg->resp_header)) {
    om_aiv_msg__srv__ArclListen_Request__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__srv__ArclListen_Request__fini(om_aiv_msg__srv__ArclListen_Request * msg)
{
  if (!msg) {
    return;
  }
  // resp_header
  rosidl_runtime_c__String__fini(&msg->resp_header);
}

om_aiv_msg__srv__ArclListen_Request *
om_aiv_msg__srv__ArclListen_Request__create()
{
  om_aiv_msg__srv__ArclListen_Request * msg = (om_aiv_msg__srv__ArclListen_Request *)malloc(sizeof(om_aiv_msg__srv__ArclListen_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__srv__ArclListen_Request));
  bool success = om_aiv_msg__srv__ArclListen_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__srv__ArclListen_Request__destroy(om_aiv_msg__srv__ArclListen_Request * msg)
{
  if (msg) {
    om_aiv_msg__srv__ArclListen_Request__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__srv__ArclListen_Request__Sequence__init(om_aiv_msg__srv__ArclListen_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__srv__ArclListen_Request * data = NULL;
  if (size) {
    data = (om_aiv_msg__srv__ArclListen_Request *)calloc(size, sizeof(om_aiv_msg__srv__ArclListen_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__srv__ArclListen_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__srv__ArclListen_Request__fini(&data[i - 1]);
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
om_aiv_msg__srv__ArclListen_Request__Sequence__fini(om_aiv_msg__srv__ArclListen_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__srv__ArclListen_Request__fini(&array->data[i]);
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

om_aiv_msg__srv__ArclListen_Request__Sequence *
om_aiv_msg__srv__ArclListen_Request__Sequence__create(size_t size)
{
  om_aiv_msg__srv__ArclListen_Request__Sequence * array = (om_aiv_msg__srv__ArclListen_Request__Sequence *)malloc(sizeof(om_aiv_msg__srv__ArclListen_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__srv__ArclListen_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__srv__ArclListen_Request__Sequence__destroy(om_aiv_msg__srv__ArclListen_Request__Sequence * array)
{
  if (array) {
    om_aiv_msg__srv__ArclListen_Request__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `resp_text`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
om_aiv_msg__srv__ArclListen_Response__init(om_aiv_msg__srv__ArclListen_Response * msg)
{
  if (!msg) {
    return false;
  }
  // resp_text
  if (!rosidl_runtime_c__String__init(&msg->resp_text)) {
    om_aiv_msg__srv__ArclListen_Response__fini(msg);
    return false;
  }
  return true;
}

void
om_aiv_msg__srv__ArclListen_Response__fini(om_aiv_msg__srv__ArclListen_Response * msg)
{
  if (!msg) {
    return;
  }
  // resp_text
  rosidl_runtime_c__String__fini(&msg->resp_text);
}

om_aiv_msg__srv__ArclListen_Response *
om_aiv_msg__srv__ArclListen_Response__create()
{
  om_aiv_msg__srv__ArclListen_Response * msg = (om_aiv_msg__srv__ArclListen_Response *)malloc(sizeof(om_aiv_msg__srv__ArclListen_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__srv__ArclListen_Response));
  bool success = om_aiv_msg__srv__ArclListen_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__srv__ArclListen_Response__destroy(om_aiv_msg__srv__ArclListen_Response * msg)
{
  if (msg) {
    om_aiv_msg__srv__ArclListen_Response__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__srv__ArclListen_Response__Sequence__init(om_aiv_msg__srv__ArclListen_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__srv__ArclListen_Response * data = NULL;
  if (size) {
    data = (om_aiv_msg__srv__ArclListen_Response *)calloc(size, sizeof(om_aiv_msg__srv__ArclListen_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__srv__ArclListen_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__srv__ArclListen_Response__fini(&data[i - 1]);
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
om_aiv_msg__srv__ArclListen_Response__Sequence__fini(om_aiv_msg__srv__ArclListen_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__srv__ArclListen_Response__fini(&array->data[i]);
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

om_aiv_msg__srv__ArclListen_Response__Sequence *
om_aiv_msg__srv__ArclListen_Response__Sequence__create(size_t size)
{
  om_aiv_msg__srv__ArclListen_Response__Sequence * array = (om_aiv_msg__srv__ArclListen_Response__Sequence *)malloc(sizeof(om_aiv_msg__srv__ArclListen_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__srv__ArclListen_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__srv__ArclListen_Response__Sequence__destroy(om_aiv_msg__srv__ArclListen_Response__Sequence * array)
{
  if (array) {
    om_aiv_msg__srv__ArclListen_Response__Sequence__fini(array);
  }
  free(array);
}
