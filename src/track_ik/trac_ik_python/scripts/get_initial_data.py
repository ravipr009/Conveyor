import utils
import numpy as np
import rospy
from sensor_msgs.msg import JointState

rospy.init_node("Get_initial_data")
tf = utils.Tf_listener()
str1 = ["Ref Pose", "Target Pose", "Bin Pose"]
str2 = ["Ref joint angles", "Target joint angles", "Bin joint angles"]
pose = np.zeros((3,7)); 
joint = np.zeros((3,6))
count = 0

while (count < 3):
	ch = raw_input("Enter {} (Y/N)? \n".format(str1[count]))
	if (ch == 'y'):
		pose[count] = tf.get_pose()
		joint_class = rospy.wait_for_message("/joint_states",JointState)
		joint[count] = joint_class.position
		print("{} = {}".format(str1[count],pose[count]))
		print("{} = {}".format(str2[count],joint[count]))
		count += 1
	else:
		print("Cannot continue without {} \n".format(str1[count]))
print("Thank You\n")
np.savetxt("initial_pose_ur10.txt",pose,delimiter= ',',fmt='%1.3f')
np.savetxt("initial_joints_ur10.txt",joint,delimiter= ',',fmt='%1.3f')