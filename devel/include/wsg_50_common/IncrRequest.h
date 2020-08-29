// Generated by gencpp from file wsg_50_common/IncrRequest.msg
// DO NOT EDIT!


#ifndef WSG_50_COMMON_MESSAGE_INCRREQUEST_H
#define WSG_50_COMMON_MESSAGE_INCRREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace wsg_50_common
{
template <class ContainerAllocator>
struct IncrRequest_
{
  typedef IncrRequest_<ContainerAllocator> Type;

  IncrRequest_()
    : direction()
    , increment(0.0)  {
    }
  IncrRequest_(const ContainerAllocator& _alloc)
    : direction(_alloc)
    , increment(0.0)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _direction_type;
  _direction_type direction;

   typedef float _increment_type;
  _increment_type increment;





  typedef boost::shared_ptr< ::wsg_50_common::IncrRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::wsg_50_common::IncrRequest_<ContainerAllocator> const> ConstPtr;

}; // struct IncrRequest_

typedef ::wsg_50_common::IncrRequest_<std::allocator<void> > IncrRequest;

typedef boost::shared_ptr< ::wsg_50_common::IncrRequest > IncrRequestPtr;
typedef boost::shared_ptr< ::wsg_50_common::IncrRequest const> IncrRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::wsg_50_common::IncrRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::wsg_50_common::IncrRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace wsg_50_common

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'wsg_50_common': ['/home/ravi/classic_ur_ws/src/wsg50-ros-pkg/wsg_50_common/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::wsg_50_common::IncrRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::wsg_50_common::IncrRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::wsg_50_common::IncrRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::wsg_50_common::IncrRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::wsg_50_common::IncrRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::wsg_50_common::IncrRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::wsg_50_common::IncrRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cca1e2c685538b4c18fbfec9ea6b6b36";
  }

  static const char* value(const ::wsg_50_common::IncrRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xcca1e2c685538b4cULL;
  static const uint64_t static_value2 = 0x18fbfec9ea6b6b36ULL;
};

template<class ContainerAllocator>
struct DataType< ::wsg_50_common::IncrRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "wsg_50_common/IncrRequest";
  }

  static const char* value(const ::wsg_50_common::IncrRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::wsg_50_common::IncrRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string direction\n\
float32 increment\n\
";
  }

  static const char* value(const ::wsg_50_common::IncrRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::wsg_50_common::IncrRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.direction);
      stream.next(m.increment);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct IncrRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::wsg_50_common::IncrRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::wsg_50_common::IncrRequest_<ContainerAllocator>& v)
  {
    s << indent << "direction: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.direction);
    s << indent << "increment: ";
    Printer<float>::stream(s, indent + "  ", v.increment);
  }
};

} // namespace message_operations
} // namespace ros

#endif // WSG_50_COMMON_MESSAGE_INCRREQUEST_H
