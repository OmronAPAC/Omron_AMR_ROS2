// Generated by gencpp from file ld_actions/DoTaskActionGoal.msg
// DO NOT EDIT!


#ifndef LD_ACTIONS_MESSAGE_DOTASKACTIONGOAL_H
#define LD_ACTIONS_MESSAGE_DOTASKACTIONGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <actionlib_msgs/GoalID.h>
#include <ld_actions/DoTaskGoal.h>

namespace ld_actions
{
template <class ContainerAllocator>
struct DoTaskActionGoal_
{
  typedef DoTaskActionGoal_<ContainerAllocator> Type;

  DoTaskActionGoal_()
    : header()
    , goal_id()
    , goal()  {
    }
  DoTaskActionGoal_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , goal_id(_alloc)
    , goal(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::actionlib_msgs::GoalID_<ContainerAllocator>  _goal_id_type;
  _goal_id_type goal_id;

   typedef  ::ld_actions::DoTaskGoal_<ContainerAllocator>  _goal_type;
  _goal_type goal;





  typedef boost::shared_ptr< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> const> ConstPtr;

}; // struct DoTaskActionGoal_

typedef ::ld_actions::DoTaskActionGoal_<std::allocator<void> > DoTaskActionGoal;

typedef boost::shared_ptr< ::ld_actions::DoTaskActionGoal > DoTaskActionGoalPtr;
typedef boost::shared_ptr< ::ld_actions::DoTaskActionGoal const> DoTaskActionGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ld_actions::DoTaskActionGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ld_actions

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'ld_actions': ['/home/tthmatt/ld_ROS/devel/.private/ld_actions/share/ld_actions/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c5b39d7c4aef8261fef977b3f7b90411";
  }

  static const char* value(const ::ld_actions::DoTaskActionGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc5b39d7c4aef8261ULL;
  static const uint64_t static_value2 = 0xfef977b3f7b90411ULL;
};

template<class ContainerAllocator>
struct DataType< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ld_actions/DoTaskActionGoal";
  }

  static const char* value(const ::ld_actions::DoTaskActionGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalID goal_id\n"
"DoTaskGoal goal\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: actionlib_msgs/GoalID\n"
"# The stamp should store the time at which this goal was requested.\n"
"# It is used by an action server when it tries to preempt all\n"
"# goals that were requested before a certain time\n"
"time stamp\n"
"\n"
"# The id provides a way to associate feedback and\n"
"# result message with specific goal requests. The id\n"
"# specified must be unique.\n"
"string id\n"
"\n"
"\n"
"================================================================================\n"
"MSG: ld_actions/DoTaskGoal\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Goal\n"
"string goaltask\n"
"\n"
;
  }

  static const char* value(const ::ld_actions::DoTaskActionGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.goal_id);
      stream.next(m.goal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DoTaskActionGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ld_actions::DoTaskActionGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ld_actions::DoTaskActionGoal_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "goal_id: ";
    s << std::endl;
    Printer< ::actionlib_msgs::GoalID_<ContainerAllocator> >::stream(s, indent + "  ", v.goal_id);
    s << indent << "goal: ";
    s << std::endl;
    Printer< ::ld_actions::DoTaskGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.goal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LD_ACTIONS_MESSAGE_DOTASKACTIONGOAL_H