// Generated by gencpp from file ld_actions/StopGoal.msg
// DO NOT EDIT!


#ifndef LD_ACTIONS_MESSAGE_STOPGOAL_H
#define LD_ACTIONS_MESSAGE_STOPGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ld_actions
{
template <class ContainerAllocator>
struct StopGoal_
{
  typedef StopGoal_<ContainerAllocator> Type;

  StopGoal_()
    : goal_stop()  {
    }
  StopGoal_(const ContainerAllocator& _alloc)
    : goal_stop(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _goal_stop_type;
  _goal_stop_type goal_stop;





  typedef boost::shared_ptr< ::ld_actions::StopGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ld_actions::StopGoal_<ContainerAllocator> const> ConstPtr;

}; // struct StopGoal_

typedef ::ld_actions::StopGoal_<std::allocator<void> > StopGoal;

typedef boost::shared_ptr< ::ld_actions::StopGoal > StopGoalPtr;
typedef boost::shared_ptr< ::ld_actions::StopGoal const> StopGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ld_actions::StopGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ld_actions::StopGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ld_actions

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'ld_actions': ['/home/tthmatt/ld_ROS/devel/.private/ld_actions/share/ld_actions/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ld_actions::StopGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ld_actions::StopGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ld_actions::StopGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ld_actions::StopGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ld_actions::StopGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ld_actions::StopGoal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ld_actions::StopGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cb7b95c39be20820c1c7a2575bd9c5d5";
  }

  static const char* value(const ::ld_actions::StopGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xcb7b95c39be20820ULL;
  static const uint64_t static_value2 = 0xc1c7a2575bd9c5d5ULL;
};

template<class ContainerAllocator>
struct DataType< ::ld_actions::StopGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ld_actions/StopGoal";
  }

  static const char* value(const ::ld_actions::StopGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ld_actions::StopGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Goal\n"
"string goal_stop\n"
"\n"
;
  }

  static const char* value(const ::ld_actions::StopGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ld_actions::StopGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.goal_stop);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct StopGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ld_actions::StopGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ld_actions::StopGoal_<ContainerAllocator>& v)
  {
    s << indent << "goal_stop: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.goal_stop);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LD_ACTIONS_MESSAGE_STOPGOAL_H
