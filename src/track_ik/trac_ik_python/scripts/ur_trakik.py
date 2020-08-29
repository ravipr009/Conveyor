import numpy as np
import rospy
import utils
from std_msgs.msg import String
import time
from sensor_msgs.msg import JointState

rospy.init_node("track_ik")

# Define Dmp and track_ik instance from utils
dmp = utils.DMP()
initial_pose = np.loadtxt("initial_pose.txt",delimiter= ',')
robot = utils.move()

ref_pose = initial_pose[0]
target_pose = initial_pose[1]

print(initial_pose)

# robot.ref_pos = ref_pose
# robot.bin_pos = bin_pose
# dmp.y0 = ref_pose # DMP Start: Starting end-effector position of manipulator
# dmp.G = target_pose # Target start location
robot.move_view()
while not rospy.is_shutdown():
	# robot.move_view()
	ch = raw_input("Continue ? (y/n)\n")
	if (ch == 'y'):
		continue
	else:
		print("Good Bye\n")
		break;
	y_track,d_track = dmp.step(target_pose[:3], ref_pose[:3],target_pose[3:])
	# print(target_pose, ref_pose)
	robot.move_servoj(y_track,d_track)
	robot.move_bin()
	robot.move_view()
	
