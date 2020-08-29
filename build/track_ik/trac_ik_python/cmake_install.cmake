# Install script for directory: /home/ravi/classic_ur_ws/src/track_ik/trac_ik_python

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ravi/classic_ur_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/ravi/classic_ur_ws/build/track_ik/trac_ik_python/catkin_generated/safe_execute_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/ravi/classic_ur_ws/build/track_ik/trac_ik_python/catkin_generated/installspace/trac_ik_python.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/trac_ik_python/cmake" TYPE FILE FILES
    "/home/ravi/classic_ur_ws/build/track_ik/trac_ik_python/catkin_generated/installspace/trac_ik_pythonConfig.cmake"
    "/home/ravi/classic_ur_ws/build/track_ik/trac_ik_python/catkin_generated/installspace/trac_ik_pythonConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/trac_ik_python" TYPE FILE FILES "/home/ravi/classic_ur_ws/src/track_ik/trac_ik_python/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages/trac_ik_python" TYPE FILE FILES
    "/home/ravi/classic_ur_ws/devel/lib/python2.7/dist-packages/trac_ik_python/trac_ik_wrap.py"
    "/home/ravi/classic_ur_ws/devel/lib/python2.7/dist-packages/trac_ik_python/_trac_ik_wrap.so"
    "/home/ravi/classic_ur_ws/src/track_ik/trac_ik_python/src/trac_ik_python/trac_ik.py"
    "/home/ravi/classic_ur_ws/src/track_ik/trac_ik_python/src/trac_ik_python/__init__.py"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/trac_ik_python" TYPE PROGRAM FILES "/home/ravi/classic_ur_ws/build/track_ik/trac_ik_python/catkin_generated/installspace/test_pkg.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/trac_ik_python" TYPE PROGRAM FILES "/home/ravi/classic_ur_ws/build/track_ik/trac_ik_python/catkin_generated/installspace/test_wrapper.py")
endif()

