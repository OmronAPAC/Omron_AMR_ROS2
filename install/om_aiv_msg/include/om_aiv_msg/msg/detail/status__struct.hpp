// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from om_aiv_msg:msg/Status.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__MSG__DETAIL__STATUS__STRUCT_HPP_
#define OM_AIV_MSG__MSG__DETAIL__STATUS__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'location'
#include "om_aiv_msg/msg/detail/location__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__msg__Status __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__msg__Status __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Status_
{
  using Type = Status_<ContainerAllocator>;

  explicit Status_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : location(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->extended_status = "";
      this->status = "";
      this->state_of_charge = 0.0f;
      this->localization_score = 0.0f;
      this->temperature = 0.0f;
    }
  }

  explicit Status_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : extended_status(_alloc),
    status(_alloc),
    location(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->extended_status = "";
      this->status = "";
      this->state_of_charge = 0.0f;
      this->localization_score = 0.0f;
      this->temperature = 0.0f;
    }
  }

  // field types and members
  using _extended_status_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _extended_status_type extended_status;
  using _status_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _status_type status;
  using _state_of_charge_type =
    float;
  _state_of_charge_type state_of_charge;
  using _localization_score_type =
    float;
  _localization_score_type localization_score;
  using _temperature_type =
    float;
  _temperature_type temperature;
  using _location_type =
    om_aiv_msg::msg::Location_<ContainerAllocator>;
  _location_type location;

  // setters for named parameter idiom
  Type & set__extended_status(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->extended_status = _arg;
    return *this;
  }
  Type & set__status(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__state_of_charge(
    const float & _arg)
  {
    this->state_of_charge = _arg;
    return *this;
  }
  Type & set__localization_score(
    const float & _arg)
  {
    this->localization_score = _arg;
    return *this;
  }
  Type & set__temperature(
    const float & _arg)
  {
    this->temperature = _arg;
    return *this;
  }
  Type & set__location(
    const om_aiv_msg::msg::Location_<ContainerAllocator> & _arg)
  {
    this->location = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::msg::Status_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::msg::Status_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::msg::Status_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::msg::Status_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::msg::Status_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::msg::Status_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::msg::Status_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::msg::Status_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::msg::Status_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::msg::Status_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__msg__Status
    std::shared_ptr<om_aiv_msg::msg::Status_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__msg__Status
    std::shared_ptr<om_aiv_msg::msg::Status_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Status_ & other) const
  {
    if (this->extended_status != other.extended_status) {
      return false;
    }
    if (this->status != other.status) {
      return false;
    }
    if (this->state_of_charge != other.state_of_charge) {
      return false;
    }
    if (this->localization_score != other.localization_score) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    if (this->location != other.location) {
      return false;
    }
    return true;
  }
  bool operator!=(const Status_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Status_

// alias to use template instance with default allocator
using Status =
  om_aiv_msg::msg::Status_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace om_aiv_msg

#endif  // OM_AIV_MSG__MSG__DETAIL__STATUS__STRUCT_HPP_
