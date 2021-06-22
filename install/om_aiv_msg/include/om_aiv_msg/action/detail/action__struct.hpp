// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from om_aiv_msg:action/Action.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__ACTION__DETAIL__ACTION__STRUCT_HPP_
#define OM_AIV_MSG__ACTION__DETAIL__ACTION__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__action__Action_Goal __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__action__Action_Goal __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Action_Goal_
{
  using Type = Action_Goal_<ContainerAllocator>;

  explicit Action_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
    }
  }

  explicit Action_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : command(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
    }
  }

  // field types and members
  using _command_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _command_type command;
  using _identifier_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>, typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>>::other>;
  _identifier_type identifier;

  // setters for named parameter idiom
  Type & set__command(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__identifier(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>, typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>>::other> & _arg)
  {
    this->identifier = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::action::Action_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::action::Action_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__action__Action_Goal
    std::shared_ptr<om_aiv_msg::action::Action_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__action__Action_Goal
    std::shared_ptr<om_aiv_msg::action::Action_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Action_Goal_ & other) const
  {
    if (this->command != other.command) {
      return false;
    }
    if (this->identifier != other.identifier) {
      return false;
    }
    return true;
  }
  bool operator!=(const Action_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Action_Goal_

// alias to use template instance with default allocator
using Action_Goal =
  om_aiv_msg::action::Action_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace om_aiv_msg


#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__action__Action_Result __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__action__Action_Result __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Action_Result_
{
  using Type = Action_Result_<ContainerAllocator>;

  explicit Action_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->res_msg = "";
    }
  }

  explicit Action_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : res_msg(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->res_msg = "";
    }
  }

  // field types and members
  using _res_msg_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _res_msg_type res_msg;

  // setters for named parameter idiom
  Type & set__res_msg(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->res_msg = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::action::Action_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::action::Action_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__action__Action_Result
    std::shared_ptr<om_aiv_msg::action::Action_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__action__Action_Result
    std::shared_ptr<om_aiv_msg::action::Action_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Action_Result_ & other) const
  {
    if (this->res_msg != other.res_msg) {
      return false;
    }
    return true;
  }
  bool operator!=(const Action_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Action_Result_

// alias to use template instance with default allocator
using Action_Result =
  om_aiv_msg::action::Action_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace om_aiv_msg


#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__action__Action_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__action__Action_Feedback __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Action_Feedback_
{
  using Type = Action_Feedback_<ContainerAllocator>;

  explicit Action_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->feed_msg = "";
    }
  }

  explicit Action_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : feed_msg(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->feed_msg = "";
    }
  }

  // field types and members
  using _feed_msg_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _feed_msg_type feed_msg;

  // setters for named parameter idiom
  Type & set__feed_msg(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->feed_msg = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::action::Action_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::action::Action_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__action__Action_Feedback
    std::shared_ptr<om_aiv_msg::action::Action_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__action__Action_Feedback
    std::shared_ptr<om_aiv_msg::action::Action_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Action_Feedback_ & other) const
  {
    if (this->feed_msg != other.feed_msg) {
      return false;
    }
    return true;
  }
  bool operator!=(const Action_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Action_Feedback_

// alias to use template instance with default allocator
using Action_Feedback =
  om_aiv_msg::action::Action_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace om_aiv_msg


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "om_aiv_msg/action/detail/action__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__action__Action_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__action__Action_SendGoal_Request __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Action_SendGoal_Request_
{
  using Type = Action_SendGoal_Request_<ContainerAllocator>;

  explicit Action_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit Action_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    om_aiv_msg::action::Action_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const om_aiv_msg::action::Action_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__action__Action_SendGoal_Request
    std::shared_ptr<om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__action__Action_SendGoal_Request
    std::shared_ptr<om_aiv_msg::action::Action_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Action_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const Action_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Action_SendGoal_Request_

// alias to use template instance with default allocator
using Action_SendGoal_Request =
  om_aiv_msg::action::Action_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace om_aiv_msg


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__action__Action_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__action__Action_SendGoal_Response __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Action_SendGoal_Response_
{
  using Type = Action_SendGoal_Response_<ContainerAllocator>;

  explicit Action_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit Action_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__action__Action_SendGoal_Response
    std::shared_ptr<om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__action__Action_SendGoal_Response
    std::shared_ptr<om_aiv_msg::action::Action_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Action_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const Action_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Action_SendGoal_Response_

// alias to use template instance with default allocator
using Action_SendGoal_Response =
  om_aiv_msg::action::Action_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace om_aiv_msg

namespace om_aiv_msg
{

namespace action
{

struct Action_SendGoal
{
  using Request = om_aiv_msg::action::Action_SendGoal_Request;
  using Response = om_aiv_msg::action::Action_SendGoal_Response;
};

}  // namespace action

}  // namespace om_aiv_msg


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__action__Action_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__action__Action_GetResult_Request __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Action_GetResult_Request_
{
  using Type = Action_GetResult_Request_<ContainerAllocator>;

  explicit Action_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit Action_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__action__Action_GetResult_Request
    std::shared_ptr<om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__action__Action_GetResult_Request
    std::shared_ptr<om_aiv_msg::action::Action_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Action_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const Action_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Action_GetResult_Request_

// alias to use template instance with default allocator
using Action_GetResult_Request =
  om_aiv_msg::action::Action_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace om_aiv_msg


// Include directives for member types
// Member 'result'
// already included above
// #include "om_aiv_msg/action/detail/action__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__action__Action_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__action__Action_GetResult_Response __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Action_GetResult_Response_
{
  using Type = Action_GetResult_Response_<ContainerAllocator>;

  explicit Action_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit Action_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    om_aiv_msg::action::Action_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const om_aiv_msg::action::Action_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__action__Action_GetResult_Response
    std::shared_ptr<om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__action__Action_GetResult_Response
    std::shared_ptr<om_aiv_msg::action::Action_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Action_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const Action_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Action_GetResult_Response_

// alias to use template instance with default allocator
using Action_GetResult_Response =
  om_aiv_msg::action::Action_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace om_aiv_msg

namespace om_aiv_msg
{

namespace action
{

struct Action_GetResult
{
  using Request = om_aiv_msg::action::Action_GetResult_Request;
  using Response = om_aiv_msg::action::Action_GetResult_Response;
};

}  // namespace action

}  // namespace om_aiv_msg


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "om_aiv_msg/action/detail/action__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__action__Action_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__action__Action_FeedbackMessage __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Action_FeedbackMessage_
{
  using Type = Action_FeedbackMessage_<ContainerAllocator>;

  explicit Action_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit Action_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    om_aiv_msg::action::Action_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const om_aiv_msg::action::Action_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__action__Action_FeedbackMessage
    std::shared_ptr<om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__action__Action_FeedbackMessage
    std::shared_ptr<om_aiv_msg::action::Action_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Action_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const Action_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Action_FeedbackMessage_

// alias to use template instance with default allocator
using Action_FeedbackMessage =
  om_aiv_msg::action::Action_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace om_aiv_msg

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace om_aiv_msg
{

namespace action
{

struct Action
{
  /// The goal message defined in the action definition.
  using Goal = om_aiv_msg::action::Action_Goal;
  /// The result message defined in the action definition.
  using Result = om_aiv_msg::action::Action_Result;
  /// The feedback message defined in the action definition.
  using Feedback = om_aiv_msg::action::Action_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = om_aiv_msg::action::Action_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = om_aiv_msg::action::Action_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = om_aiv_msg::action::Action_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct Action Action;

}  // namespace action

}  // namespace om_aiv_msg

#endif  // OM_AIV_MSG__ACTION__DETAIL__ACTION__STRUCT_HPP_
