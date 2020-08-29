#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Aug  6 17:05:51 2020

@author: ravi
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Get 3d plot
#fig = plt.figure()
#ax = fig.add_subplot(111, projection='3d')

map = plt.figure()
map_ax = Axes3D(map)
map_ax.autoscale(enable=True, axis='both', tight=True)

map_ax.set_xlim3d([-2.0, 2.0])
map_ax.set_ylim3d([-2.0, 2.0])
map_ax.set_zlim3d([0.0, 1.0])

def update_hl(fig,data):
    xdata, ydata, zdata = fig._verts3d
    fig.set_xdata(list(np.append(xdata, data[0])))
    fig.set_ydata(list(np.append(ydata, data[1])))
    fig.set_3d_properties(list(np.append(zdata, data[2])))
    plt.draw()

# Initialise
runtime =4
sampling_time = 0.001
timesteps = int(runtime/sampling_time)
n_dmps = 3    # No. of dimensions
by = np.ones(n_dmps)*300
#ay = np.ones(n_dmps)*625/4
ay = by**2 /4
cy = np.ones(n_dmps)*30

dg=0.001

y_track = np.zeros((timesteps, n_dmps))
dy_track = np.zeros((timesteps, n_dmps))
ddy_track = np.zeros((timesteps, n_dmps))
G = np.array([0.348, 0.606, 0.176]) # Target start location

y0 = np.array([-0.180, 0.520, 0.376])  # DMP Start: Starting end-effector position of manipulator
goal =y0  # DMP goal

y_track[0] = y0;integral_error = 0
store_goals = []
for t in range(timesteps-1):
    G = G + dg*np.ones(3)
    goal=G-(G-y0)*np.exp(-2*t)
    dgoal = 2*(G-y0)*np.exp(-2*t)
#    goal = y0+ 3*((G - y0)*((t/timesteps)**2) - 2*((G - y0)*((t/timesteps)**3)))
    store_goals.append(G)
    integral_error = integral_error + (goal - y_track[t])
    ddy_track[t+1] = ay* (goal - y_track[t]) + by*(dgoal-dy_track[t])+ cy*integral_error
    dy_track[t+1] = dy_track[t] + ddy_track[t]*sampling_time
    y_track[t+1] = y_track[t] + dy_track[t]*sampling_time
    
#    y_track[t], dy_track[t], ddy_track[t] = step()
    print("Distance=",np.linalg.norm(G - y_track[t]),t)
    
store_goals = np.array(store_goals)
#ax.plot(store_goals[:,0],store_goals[:,1],store_goals[:,2],color='b',marker='o')
#ax.plot(y_track[:, 0], y_track[:, 1],y_track[:,2], color='g',marker='.',markersize=12)
#plt.title("DMP system - obstacle avoidance")
#ax.set_xlabel("X- axis")
#ax.set_ylabel("Y-Axis")
#ax.set_zlabel("Z Axix")
#
#ax.set_xlim([-1.1,1.1])
#ax.set_ylim([-1.1,1.1])
#ax.set_zlim([0,1.1])
#plt.show()
h1, = map_ax.plot3D([y_track[0,0]], [y_track[0,1]], [y_track[0,2]],marker='o',markersize=5)
h2, = map_ax.plot3D([store_goals[0,0]], [store_goals[0,1]], [store_goals[0,2]],marker='*',markersize=5)  

for i in range(len(y_track)-1):
    update_hl(h1,y_track[i])
    update_hl(h2,store_goals[i])
    plt.pause(0.0001)
 
orient = np.array([-0.500, 0.512, 0.500, 0.487 ])
Y_track = []
for i in range(len(y_track)):
    Y_track.append(np.hstack((y_track[i], orient)))
#    print(Y_track)
#np.savetxt("/home/ravi/ur_code/trajectory.txt",np.array(Y_track),delimiter=',') 
    




