# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include;/usr/include/eigen3".split(';') if "${prefix}/include;/usr/include/eigen3" != "" else []
PROJECT_CATKIN_DEPENDS = "roscpp;rospy;moveit_core;moveit_visual_tools;moveit_ros_planning_interface;interactive_markers".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lrobot_control".split(';') if "-lrobot_control" != "" else []
PROJECT_NAME = "robot_control"
PROJECT_SPACE_DIR = "/home/ravi/classic_ur_ws/install"
PROJECT_VERSION = "0.0.0"
