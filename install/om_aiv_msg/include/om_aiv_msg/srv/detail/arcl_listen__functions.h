// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from om_aiv_msg:srv/ArclListen.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__FUNCTIONS_H_
#define OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "om_aiv_msg/msg/rosidl_generator_c__visibility_control.h"

#include "om_aiv_msg/srv/detail/arcl_listen__struct.h"

/// Initialize srv/ArclListen message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * om_aiv_msg__srv__ArclListen_Request
 * )) before or use
 * om_aiv_msg__srv__ArclListen_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
bool
om_aiv_msg__srv__ArclListen_Request__init(om_aiv_msg__srv__ArclListen_Request * msg);

/// Finalize srv/ArclListen message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__srv__ArclListen_Request__fini(om_aiv_msg__srv__ArclListen_Request * msg);

/// Create srv/ArclListen message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * om_aiv_msg__srv__ArclListen_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
om_aiv_msg__srv__ArclListen_Request *
om_aiv_msg__srv__ArclListen_Request__create();

/// Destroy srv/ArclListen message.
/**
 * It calls
 * om_aiv_msg__srv__ArclListen_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__srv__ArclListen_Request__destroy(om_aiv_msg__srv__ArclListen_Request * msg);


/// Initialize array of srv/ArclListen messages.
/**
 * It allocates the memory for the number of elements and calls
 * om_aiv_msg__srv__ArclListen_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
bool
om_aiv_msg__srv__ArclListen_Request__Sequence__init(om_aiv_msg__srv__ArclListen_Request__Sequence * array, size_t size);

/// Finalize array of srv/ArclListen messages.
/**
 * It calls
 * om_aiv_msg__srv__ArclListen_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__srv__ArclListen_Request__Sequence__fini(om_aiv_msg__srv__ArclListen_Request__Sequence * array);

/// Create array of srv/ArclListen messages.
/**
 * It allocates the memory for the array and calls
 * om_aiv_msg__srv__ArclListen_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
om_aiv_msg__srv__ArclListen_Request__Sequence *
om_aiv_msg__srv__ArclListen_Request__Sequence__create(size_t size);

/// Destroy array of srv/ArclListen messages.
/**
 * It calls
 * om_aiv_msg__srv__ArclListen_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__srv__ArclListen_Request__Sequence__destroy(om_aiv_msg__srv__ArclListen_Request__Sequence * array);

/// Initialize srv/ArclListen message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * om_aiv_msg__srv__ArclListen_Response
 * )) before or use
 * om_aiv_msg__srv__ArclListen_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
bool
om_aiv_msg__srv__ArclListen_Response__init(om_aiv_msg__srv__ArclListen_Response * msg);

/// Finalize srv/ArclListen message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__srv__ArclListen_Response__fini(om_aiv_msg__srv__ArclListen_Response * msg);

/// Create srv/ArclListen message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * om_aiv_msg__srv__ArclListen_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
om_aiv_msg__srv__ArclListen_Response *
om_aiv_msg__srv__ArclListen_Response__create();

/// Destroy srv/ArclListen message.
/**
 * It calls
 * om_aiv_msg__srv__ArclListen_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__srv__ArclListen_Response__destroy(om_aiv_msg__srv__ArclListen_Response * msg);


/// Initialize array of srv/ArclListen messages.
/**
 * It allocates the memory for the number of elements and calls
 * om_aiv_msg__srv__ArclListen_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
bool
om_aiv_msg__srv__ArclListen_Response__Sequence__init(om_aiv_msg__srv__ArclListen_Response__Sequence * array, size_t size);

/// Finalize array of srv/ArclListen messages.
/**
 * It calls
 * om_aiv_msg__srv__ArclListen_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__srv__ArclListen_Response__Sequence__fini(om_aiv_msg__srv__ArclListen_Response__Sequence * array);

/// Create array of srv/ArclListen messages.
/**
 * It allocates the memory for the array and calls
 * om_aiv_msg__srv__ArclListen_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
om_aiv_msg__srv__ArclListen_Response__Sequence *
om_aiv_msg__srv__ArclListen_Response__Sequence__create(size_t size);

/// Destroy array of srv/ArclListen messages.
/**
 * It calls
 * om_aiv_msg__srv__ArclListen_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_om_aiv_msg
void
om_aiv_msg__srv__ArclListen_Response__Sequence__destroy(om_aiv_msg__srv__ArclListen_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__FUNCTIONS_H_
