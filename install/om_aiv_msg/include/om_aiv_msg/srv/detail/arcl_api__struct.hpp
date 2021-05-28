// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from om_aiv_msg:srv/ArclApi.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__SRV__DETAIL__ARCL_API__STRUCT_HPP_
#define OM_AIV_MSG__SRV__DETAIL__ARCL_API__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__srv__ArclApi_Request __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__srv__ArclApi_Request __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ArclApi_Request_
{
  using Type = ArclApi_Request_<ContainerAllocator>;

  explicit ArclApi_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
      this->line_identifier = "";
    }
  }

  explicit ArclApi_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : command(_alloc),
    line_identifier(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
      this->line_identifier = "";
    }
  }

  // field types and members
  using _command_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _command_type command;
  using _line_identifier_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _line_identifier_type line_identifier;

  // setters for named parameter idiom
  Type & set__command(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__line_identifier(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->line_identifier = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__srv__ArclApi_Request
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__srv__ArclApi_Request
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArclApi_Request_ & other) const
  {
    if (this->command != other.command) {
      return false;
    }
    if (this->line_identifier != other.line_identifier) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArclApi_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArclApi_Request_

// alias to use template instance with default allocator
using ArclApi_Request =
  om_aiv_msg::srv::ArclApi_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace om_aiv_msg


#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__srv__ArclApi_Response __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__srv__ArclApi_Response __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ArclApi_Response_
{
  using Type = ArclApi_Response_<ContainerAllocator>;

  explicit ArclApi_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->response = "";
    }
  }

  explicit ArclApi_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : response(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->response = "";
    }
  }

  // field types and members
  using _response_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__response(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__srv__ArclApi_Response
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__srv__ArclApi_Response
    std::shared_ptr<om_aiv_msg::srv::ArclApi_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArclApi_Response_ & other) const
  {
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArclApi_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArclApi_Response_

// alias to use template instance with default allocator
using ArclApi_Response =
  om_aiv_msg::srv::ArclApi_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace om_aiv_msg

namespace om_aiv_msg
{

namespace srv
{

struct ArclApi
{
  using Request = om_aiv_msg::srv::ArclApi_Request;
  using Response = om_aiv_msg::srv::ArclApi_Response;
};

}  // namespace srv

}  // namespace om_aiv_msg

#endif  // OM_AIV_MSG__SRV__DETAIL__ARCL_API__STRUCT_HPP_
