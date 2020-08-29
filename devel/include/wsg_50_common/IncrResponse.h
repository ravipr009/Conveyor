// Generated by gencpp from file wsg_50_common/IncrResponse.msg
// DO NOT EDIT!


#ifndef WSG_50_COMMON_MESSAGE_INCRRESPONSE_H
#define WSG_50_COMMON_MESSAGE_INCRRESPONSE_H


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
struct IncrResponse_
{
  typedef IncrResponse_<ContainerAllocator> Type;

  IncrResponse_()
    : error(0)  {
    }
  IncrResponse_(const ContainerAllocator& _alloc)
    : error(0)  {
  (void)_alloc;
    }



   typedef uint8_t _error_type;
  _error_type error;





  typedef boost::shared_ptr< ::wsg_50_common::IncrResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::wsg_50_common::IncrResponse_<ContainerAllocator> const> ConstPtr;

}; // struct IncrResponse_

typedef ::wsg_50_common::IncrResponse_<std::allocator<void> > IncrResponse;

typedef boost::shared_ptr< ::wsg_50_common::IncrResponse > IncrResponsePtr;
typedef boost::shared_ptr< ::wsg_50_common::IncrResponse const> IncrResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::wsg_50_common::IncrResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::wsg_50_common::IncrResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace wsg_50_common

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'wsg_50_common': ['/home/ravi/classic_ur_ws/src/wsg50-ros-pkg/wsg_50_common/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::wsg_50_common::IncrResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::wsg_50_common::IncrResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::wsg_50_common::IncrResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::wsg_50_common::IncrResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::wsg_50_common::IncrResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::wsg_50_common::IncrResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::wsg_50_common::IncrResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bf8e3bc5443691736455ca47e3128027";
  }

  static const char* value(const ::wsg_50_common::IncrResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xbf8e3bc544369173ULL;
  static const uint64_t static_value2 = 0x6455ca47e3128027ULL;
};

template<class ContainerAllocator>
struct DataType< ::wsg_50_common::IncrResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "wsg_50_common/IncrResponse";
  }

  static const char* value(const ::wsg_50_common::IncrResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::wsg_50_common::IncrResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8 error\n\
\n\
";
  }

  static const char* value(const ::wsg_50_common::IncrResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::wsg_50_common::IncrResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.error);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct IncrResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::wsg_50_common::IncrResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::wsg_50_common::IncrResponse_<ContainerAllocator>& v)
  {
    s << indent << "error: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.error);
  }
};

} // namespace message_operations
} // namespace ros

#endif // WSG_50_COMMON_MESSAGE_INCRRESPONSE_H
