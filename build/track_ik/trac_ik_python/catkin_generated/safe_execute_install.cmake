execute_process(COMMAND "/home/ravi/classic_ur_ws/build/track_ik/trac_ik_python/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/ravi/classic_ur_ws/build/track_ik/trac_ik_python/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
