#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""

Code to record robot kinematic demonstrations 

@author: ravi and amrut panda
"""
# import sys
# import rospy
# import tf

# sys.stdout = open("Record_tf.txt",'w')
# rospy.init_node('Listener')
# listener = tf.TransformListener()
# rate = rospy.Rate(10)

# while not rospy.is_shutdown():
# 	try:
# 		trans = listener.lookupTransform('/base_link','/ee_link',rospy.Time(0))
# 		# trans = list(trans)
# 		print(str(trans[0])[1:-1])
# 	except(tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
# 		continue

# 	rate.sleep()


import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import pyplot as plt
 
 
 
def update_line(hl, new_data):
	xdata, ydata, zdata = hl._verts3d
	hl.set_xdata(list(np.append(xdata, new_data[0])))
	hl.set_ydata(list(np.append(ydata, new_data[1])))
	hl.set_3d_properties(list(np.append(zdata, new_data[2])))
	plt.draw()
 
 
map = plt.figure()
map_ax = Axes3D(map)
map_ax.autoscale(enable=True, axis='both', tight=True)
 
# # # Setting the axes properties
map_ax.set_xlim3d([0.0, 10.0])
map_ax.set_ylim3d([0.0, 10.0])
map_ax.set_zlim3d([0.0, 10.0])
 
hl, = map_ax.plot3D([0], [0], [0])

for i in range(100):
    update_line(hl,np.random.randn(3))
    plt.pause(0.2)
 
update_line(hl, (2,2, 1))
plt.show(block=False)
plt.pause(1)
 
update_line(hl, (5,5, 5))
plt.show(block=False)
plt.pause(2)
 
update_line(hl, (8,1, 4))
plt.show(block=True)