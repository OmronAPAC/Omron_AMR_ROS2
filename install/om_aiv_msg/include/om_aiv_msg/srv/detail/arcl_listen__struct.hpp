// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from om_aiv_msg:srv/ArclListen.idl
// generated code does not contain a copyright notice

#ifndef OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__STRUCT_HPP_
#define OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__srv__ArclListen_Request __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__srv__ArclListen_Request __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ArclListen_Request_
{
  using Type = ArclListen_Request_<ContainerAllocator>;

  explicit ArclListen_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resp_header = "";
    }
  }

  explicit ArclListen_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : resp_header(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resp_header = "";
    }
  }

  // field types and members
  using _resp_header_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _resp_header_type resp_header;

  // setters for named parameter idiom
  Type & set__resp_header(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->resp_header = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__srv__ArclListen_Request
    std::shared_ptr<om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__srv__ArclListen_Request
    std::shared_ptr<om_aiv_msg::srv::ArclListen_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArclListen_Request_ & other) const
  {
    if (this->resp_header != other.resp_header) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArclListen_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArclListen_Request_

// alias to use template instance with default allocator
using ArclListen_Request =
  om_aiv_msg::srv::ArclListen_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace om_aiv_msg


#ifndef _WIN32
# define DEPRECATED__om_aiv_msg__srv__ArclListen_Response __attribute__((deprecated))
#else
# define DEPRECATED__om_aiv_msg__srv__ArclListen_Response __declspec(deprecated)
#endif

namespace om_aiv_msg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ArclListen_Response_
{
  using Type = ArclListen_Response_<ContainerAllocator>;

  explicit ArclListen_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resp_text = "";
    }
  }

  explicit ArclListen_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : resp_text(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resp_text = "";
    }
  }

  // field types and members
  using _resp_text_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _resp_text_type resp_text;

  // setters for named parameter idiom
  Type & set__resp_text(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->resp_text = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__om_aiv_msg__srv__ArclListen_Response
    std::shared_ptr<om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__om_aiv_msg__srv__ArclListen_Response
    std::shared_ptr<om_aiv_msg::srv::ArclListen_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArclListen_Response_ & other) const
  {
    if (this->resp_text != other.resp_text) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArclListen_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArclListen_Response_

// alias to use template instance with default allocator
using ArclListen_Response =
  om_aiv_msg::srv::ArclListen_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace om_aiv_msg

namespace om_aiv_msg
{

namespace srv
{

struct ArclListen
{
  using Request = om_aiv_msg::srv::ArclListen_Request;
  using Response = om_aiv_msg::srv::ArclListen_Response;
};

}  // namespace srv

}  // namespace om_aiv_msg

#endif  // OM_AIV_MSG__SRV__DETAIL__ARCL_LISTEN__STRUCT_HPP_
