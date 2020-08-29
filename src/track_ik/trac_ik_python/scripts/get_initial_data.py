import utils
import numpy as np
import rospy


rospy.init_node("Get_initial_data")
tf = utils.Tf_listener()
str = ["Ref Pose", "Target Pose", "Bin Pose"]
pose = np.zeros((3,7)); 
count = 0

while (count < 3):
	ch = raw_input("Enter {} (Y/N)? \n".format(str[count]))
	if (ch == 'y'):
		pose[count] = tf.get_pose()
		print("{} = {}".format(str[count],pose[count]))
		count += 1
	else:
		print("Cannot continue without {} \n".format(str[count]))
print("Thank You\n")
np.savetxt("initial_pose.txt",pose,delimiter= ',',fmt='%1.3f')