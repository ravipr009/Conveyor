import rospy
import numpy as np
from wsg_50_common.srv import Move
from std_srvs.srv import Empty
from multiprocessing import Process


service1 =  rospy.ServiceProxy('/wsg_50_driver/move',Move)
service2 =  rospy.ServiceProxy('/wsg_50_driver/homing',Empty)
# resp1 = service1(50,60)
# response2 = service2()

def srv1():
	resp1 = service1(50,60)
def srv2():
	resp2 = service2()

p = Process(target=srv1)

for i in range(30):
	if (i == 0):
		# service1(50,60)
		p.start()
		print(1)
	elif (i == 1):
		# service2()
		print(2)
	else:
		print("Hii")
p.join()

