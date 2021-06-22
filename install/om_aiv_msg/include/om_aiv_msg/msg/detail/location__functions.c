// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from om_aiv_msg:msg/Location.idl
// generated code does not contain a copyright notice
#include "om_aiv_msg/msg/detail/location__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
om_aiv_msg__msg__Location__init(om_aiv_msg__msg__Location * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  // theta
  return true;
}

void
om_aiv_msg__msg__Location__fini(om_aiv_msg__msg__Location * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
  // theta
}

om_aiv_msg__msg__Location *
om_aiv_msg__msg__Location__create()
{
  om_aiv_msg__msg__Location * msg = (om_aiv_msg__msg__Location *)malloc(sizeof(om_aiv_msg__msg__Location));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(om_aiv_msg__msg__Location));
  bool success = om_aiv_msg__msg__Location__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
om_aiv_msg__msg__Location__destroy(om_aiv_msg__msg__Location * msg)
{
  if (msg) {
    om_aiv_msg__msg__Location__fini(msg);
  }
  free(msg);
}


bool
om_aiv_msg__msg__Location__Sequence__init(om_aiv_msg__msg__Location__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  om_aiv_msg__msg__Location * data = NULL;
  if (size) {
    data = (om_aiv_msg__msg__Location *)calloc(size, sizeof(om_aiv_msg__msg__Location));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = om_aiv_msg__msg__Location__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        om_aiv_msg__msg__Location__fini(&data[i - 1]);
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
om_aiv_msg__msg__Location__Sequence__fini(om_aiv_msg__msg__Location__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      om_aiv_msg__msg__Location__fini(&array->data[i]);
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

om_aiv_msg__msg__Location__Sequence *
om_aiv_msg__msg__Location__Sequence__create(size_t size)
{
  om_aiv_msg__msg__Location__Sequence * array = (om_aiv_msg__msg__Location__Sequence *)malloc(sizeof(om_aiv_msg__msg__Location__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = om_aiv_msg__msg__Location__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
om_aiv_msg__msg__Location__Sequence__destroy(om_aiv_msg__msg__Location__Sequence * array)
{
  if (array) {
    om_aiv_msg__msg__Location__Sequence__fini(array);
  }
  free(array);
}
