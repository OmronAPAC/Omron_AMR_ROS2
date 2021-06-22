// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from om_aiv_msg:msg/Location.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__MSG__DETAIL__LOCATION__FUNCTIONS_H_
#define OM_AIV_MSG__MSG__DETAIL__LOCATION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "om_aiv_msg/msg/rosidl_generator_c__visibility_control.h"

#include "om_aiv_msg/msg/detail/location__struct.h"

/// Initialize msg/Location message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * om_aiv_msg__msg__Location
 * )) before or use
 * om_aiv_msg__msg__Location__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
bool
om_aiv_msg__msg__Location__init(om_aiv_msg__msg__Location * msg);

/// Finalize msg/Location message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__msg__Location__fini(om_aiv_msg__msg__Location * msg);

/// Create msg/Location message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * om_aiv_msg__msg__Location__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
om_aiv_msg__msg__Location *
om_aiv_msg__msg__Location__create();

/// Destroy msg/Location message.
/**
 * It calls
 * om_aiv_msg__msg__Location__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__msg__Location__destroy(om_aiv_msg__msg__Location * msg);


/// Initialize array of msg/Location messages.
/**
 * It allocates the memory for the number of elements and calls
 * om_aiv_msg__msg__Location__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
bool
om_aiv_msg__msg__Location__Sequence__init(om_aiv_msg__msg__Location__Sequence * array, size_t size);

/// Finalize array of msg/Location messages.
/**
 * It calls
 * om_aiv_msg__msg__Location__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__msg__Location__Sequence__fini(om_aiv_msg__msg__Location__Sequence * array);

/// Create array of msg/Location messages.
/**
 * It allocates the memory for the array and calls
 * om_aiv_msg__msg__Location__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
om_aiv_msg__msg__Location__Sequence *
om_aiv_msg__msg__Location__Sequence__create(size_t size);

/// Destroy array of msg/Location messages.
/**
 * It calls
 * om_aiv_msg__msg__Location__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__msg__Location__Sequence__destroy(om_aiv_msg__msg__Location__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // OM_AIV_MSG__MSG__DETAIL__LOCATION__FUNCTIONS_H_
