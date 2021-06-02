// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from om_aiv_msg:action/Action.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__ACTION__DETAIL__ACTION__TRAITS_HPP_
#define OM_AIV_MSG__ACTION__DETAIL__ACTION__TRAITS_HPP_

#include "om_aiv_msg/action/detail/action__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_Goal>()
{
  return "om_aiv_msg::action::Action_Goal";
}

template<>
inline const char * name<om_aiv_msg::action::Action_Goal>()
{
  return "om_aiv_msg/action/Action_Goal";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<om_aiv_msg::action::Action_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_Result>()
{
  return "om_aiv_msg::action::Action_Result";
}

template<>
inline const char * name<om_aiv_msg::action::Action_Result>()
{
  return "om_aiv_msg/action/Action_Result";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<om_aiv_msg::action::Action_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_Feedback>()
{
  return "om_aiv_msg::action::Action_Feedback";
}

template<>
inline const char * name<om_aiv_msg::action::Action_Feedback>()
{
  return "om_aiv_msg/action/Action_Feedback";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<om_aiv_msg::action::Action_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "om_aiv_msg/action/detail/action__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_SendGoal_Request>()
{
  return "om_aiv_msg::action::Action_SendGoal_Request";
}

template<>
inline const char * name<om_aiv_msg::action::Action_SendGoal_Request>()
{
  return "om_aiv_msg/action/Action_SendGoal_Request";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<om_aiv_msg::action::Action_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<om_aiv_msg::action::Action_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<om_aiv_msg::action::Action_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_SendGoal_Response>()
{
  return "om_aiv_msg::action::Action_SendGoal_Response";
}

template<>
inline const char * name<om_aiv_msg::action::Action_SendGoal_Response>()
{
  return "om_aiv_msg/action/Action_SendGoal_Response";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<om_aiv_msg::action::Action_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_SendGoal>()
{
  return "om_aiv_msg::action::Action_SendGoal";
}

template<>
inline const char * name<om_aiv_msg::action::Action_SendGoal>()
{
  return "om_aiv_msg/action/Action_SendGoal";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<om_aiv_msg::action::Action_SendGoal_Request>::value &&
    has_fixed_size<om_aiv_msg::action::Action_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<om_aiv_msg::action::Action_SendGoal_Request>::value &&
    has_bounded_size<om_aiv_msg::action::Action_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<om_aiv_msg::action::Action_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<om_aiv_msg::action::Action_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<om_aiv_msg::action::Action_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_GetResult_Request>()
{
  return "om_aiv_msg::action::Action_GetResult_Request";
}

template<>
inline const char * name<om_aiv_msg::action::Action_GetResult_Request>()
{
  return "om_aiv_msg/action/Action_GetResult_Request";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<om_aiv_msg::action::Action_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "om_aiv_msg/action/detail/action__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_GetResult_Response>()
{
  return "om_aiv_msg::action::Action_GetResult_Response";
}

template<>
inline const char * name<om_aiv_msg::action::Action_GetResult_Response>()
{
  return "om_aiv_msg/action/Action_GetResult_Response";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<om_aiv_msg::action::Action_Result>::value> {};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<om_aiv_msg::action::Action_Result>::value> {};

template<>
struct is_message<om_aiv_msg::action::Action_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_GetResult>()
{
  return "om_aiv_msg::action::Action_GetResult";
}

template<>
inline const char * name<om_aiv_msg::action::Action_GetResult>()
{
  return "om_aiv_msg/action/Action_GetResult";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<om_aiv_msg::action::Action_GetResult_Request>::value &&
    has_fixed_size<om_aiv_msg::action::Action_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<om_aiv_msg::action::Action_GetResult_Request>::value &&
    has_bounded_size<om_aiv_msg::action::Action_GetResult_Response>::value
  >
{
};

template<>
struct is_service<om_aiv_msg::action::Action_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<om_aiv_msg::action::Action_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<om_aiv_msg::action::Action_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "om_aiv_msg/action/detail/action__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<om_aiv_msg::action::Action_FeedbackMessage>()
{
  return "om_aiv_msg::action::Action_FeedbackMessage";
}

template<>
inline const char * name<om_aiv_msg::action::Action_FeedbackMessage>()
{
  return "om_aiv_msg/action/Action_FeedbackMessage";
}

template<>
struct has_fixed_size<om_aiv_msg::action::Action_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<om_aiv_msg::action::Action_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<om_aiv_msg::action::Action_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<om_aiv_msg::action::Action_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<om_aiv_msg::action::Action_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<om_aiv_msg::action::Action>
  : std::true_type
{
};

template<>
struct is_action_goal<om_aiv_msg::action::Action_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<om_aiv_msg::action::Action_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<om_aiv_msg::action::Action_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // OM_AIV_MSG__ACTION__DETAIL__ACTION__TRAITS_HPP_
