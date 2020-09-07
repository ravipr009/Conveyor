import numpy as np
from trac_ik_python.trac_ik_wrap import TRAC_IK
import rospy
import tf
import numpy as np
from std_msgs.msg import String
import time
from sensor_msgs.msg import JointState
from wsg_50_common.srv import Move
from std_srvs.srv import Empty
from multiprocessing import Process

class DMP:
	def __init__(self):
		self.runtime = 4
		self.sampling_time = 0.001
		self.timesteps = int(self.runtime/self.sampling_time)
		self.n_dmps = 3    # No. of dimensions
		# ay,by,cy are propertional, derivative and Integral gains respectively
		self.by = np.ones(self.n_dmps)*300
		#ay = np.ones(n_dmps)*625/4
		self.ay = self.by**2 /4
		self.cy = np.ones(self.n_dmps)*30

		# Speed of the target in m/s
		self.dg= 0.001*np.array([0.0,1.0,0.0])


		self.y_track = np.zeros((self.timesteps, self.n_dmps))
		self.dy_track = np.zeros((self.timesteps, self.n_dmps))
		self.ddy_track = np.zeros((self.timesteps, self.n_dmps))
		self.G = np.array([0.348, 0.606, 0.176]) # Target start location

		self.y0 = np.array([-0.180, 0.520, 0.376])  # DMP Start: Starting end-effector position of manipulator
		self.goal = self.y0  # DMP goal

		self.y_track[0] = self.y0;
		self.integral_error = 0
	def step(self,G,y0,orient):
		self.G = G
		self.y0 = y0
		self.y_track[0] = self.y0;
		self.integral_error = 0
		self.store_goals = []
		for t in range(self.timesteps-1):
			self.G = self.G + self.dg
			self.goal=self.G-(self.G-self.y0)*np.exp(-2*t)
			dgoal = 2*(self.G-self.y0)*np.exp(-2*t)
		#    goal = y0+ 3*((G - y0)*((t/timesteps)**2) - 2*((G - y0)*((t/timesteps)**3)))
			self.store_goals.append(self.G)
			self.integral_error = self.integral_error + (self.goal - self.y_track[t])
			self.ddy_track[t+1] = self.ay* (self.goal - self.y_track[t]) + self.by*(dgoal-self.dy_track[t])+ self.cy*self.integral_error
			self.dy_track[t+1] = self.dy_track[t] + self.ddy_track[t]*self.sampling_time
			self.y_track[t+1] = self.y_track[t] + self.dy_track[t]*self.sampling_time
			# print("Distance=",np.linalg.norm(self.G - self.y_track[t]),t)
			# if (np.linalg.norm(self.G - self.y_track[t]) < 0.008):
			# 	break;
		# orient = np.array([-0.640, -0.265, 0.662, -0.286 ])
		Y_track = []
		for i in range(t+1):
			Y_track.append(np.hstack((self.y_track[i], orient)))
		return np.array(Y_track), np.array(self.store_goals)

class IK(object):
	def __init__(self, base_link, tip_link,
				 timeout=0.005, epsilon=1e-5, solve_type="Speed",
				 urdf_string=None):
		"""
		Create a TRAC_IK instance and keep track of it.l

		:param str base_link: Starting link of the chain.
		:param str tip_link: Last link of the chain.
		:param float timeout: Timeout in seconds for the IK calls.
		:param float epsilon: Error epsilon.
		:param solve_type str: Type of solver, can be:
			Speed (default), Distance, Manipulation1, Manipulation2
		:param urdf_string str: Optional arg, if not given URDF is taken from
			the param server at /robot_description.
		"""
		if urdf_string is None:
			urdf_string = rospy.get_param('/robot_description')
		self._urdf_string = urdf_string
		self._timeout = timeout
		self._epsilon = epsilon
		self._solve_type = solve_type
		self.base_link = base_link
		self.tip_link = tip_link
		self._ik_solver = TRAC_IK(self.base_link,
								  self.tip_link,
								  self._urdf_string,
								  self._timeout,
								  self._epsilon,
								  self._solve_type)
		self.number_of_joints = self._ik_solver.getNrOfJointsInChain()
		self.joint_names = self._ik_solver.getJointNamesInChain(
			self._urdf_string)
		self.link_names = self._ik_solver.getLinkNamesInChain()

	def get_ik(self, qinit,
			   x, y, z,
			   rx, ry, rz, rw,
			   bx=1e-3, by=1e-3, bz=1e-3,
			   brx=0.5e-1, bry=0.5e-1, brz=0.5e-1):
		"""
		Do the IK call.

		:param list of float qinit: Initial status of the joints as seed.
		:param float x: X coordinates in base_frame.
		:param float y: Y coordinates in base_frame.
		:param float z: Z coordinates in base_frame.
		:param float rx: X quaternion coordinate.
		:param float ry: Y quaternion coordinate.
		:param float rz: Z quaternion coordinate.
		:param float rw: W quaternion coordinate.
		:param float bx: X allowed bound.
		:param float by: Y allowed bound.
		:param float bz: Z allowed bound.
		:param float brx: rotation over X allowed bound.
		:param float bry: rotation over Y allowed bound.
		:param float brz: rotation over Z allowed bound.

		:return: joint values or None if no solution found.
		:rtype: tuple of float.
		"""
		if len(qinit) != self.number_of_joints:
			raise Exception("qinit has length %i and it should have length %i" % (
				len(qinit), self.number_of_joints))
		solution = self._ik_solver.CartToJnt(qinit,
											 x, y, z,
											 rx, ry, rz, rw,
											 bx, by, bz,
											 brx, bry, brz)
		if solution:
			return solution
		else:
			return None

	def get_joint_limits(self):
		"""
		Return lower bound limits and upper bound limits for all the joints
		in the order of the joint names.
		"""
		lb = self._ik_solver.getLowerBoundLimits()
		ub = self._ik_solver.getUpperBoundLimits()
		return lb, ub

	def set_joint_limits(self, lower_bounds, upper_bounds):
		"""
		Set joint limits for all the joints.

		:arg list lower_bounds: List of float of the lower bound limits for
			all joints.
		:arg list upper_bounds: List of float of the upper bound limits for
			all joints.
		"""
		if len(lower_bounds) != self.number_of_joints:
			raise Exception("lower_bounds array size mismatch, it's size %i, should be %i" % (
				len(lower_bounds),
				self.number_of_joints))

		if len(upper_bounds) != self.number_of_joints:
			raise Exception("upper_bounds array size mismatch, it's size %i, should be %i" % (
				len(upper_bounds),
				self.number_of_joints))
		self._ik_solver.setKDLLimits(lower_bounds, upper_bounds)


# dmp = DMP()
# dmp.step(np.array([0.348, 0.606, 0.176]), np.array([-0.180, 0.520, 0.376]))


class move:
	def __init__(self):
		# rospy.init_node("Move arm")
		self.pub = rospy.Publisher('/ur_driver/URScript', String, queue_size=1,latch = True)
		self.joint_sub = rospy.Subscriber('joint_states',JointState,self.callback,queue_size=1)
		self.joint = None
		self.count = 0
		self.script = String()
		self.loop_rate = 10
		self.rate = rospy.Rate(self.loop_rate)
		self.ik = IK("base_link", "ee_link")
		self.ref_pos =  [0.03416740149259567, -1.7510932127581995, 2.2170276641845703, -1.9008978048907679, -1.5938809553729456, 0.8981828689575195]
		self.bin_pos =  [1.6449499130249023, -0.901740852986471, 1.2159690856933594, -1.9322336355792444, -1.5911839644061487, 2.138575315475464]
		self.move_serv = rospy.ServiceProxy('/wsg_50_driver/move',Move)
		self.home_serv = rospy.ServiceProxy('/wsg_50_driver/homing',Empty)
		time.sleep(0.1)
	def serv_callback(self):
		resp1 = self.move_serv(48,70)
		print("Hello")
	def home_callback(self):
		resp2 = self.home_serv()
	def callback(self,data):
		self.joints = np.array(data.position)
	def release(self):
		print("Released Gripper\n")
		pass
	def move_servoj(self,y_track,g_track):
		self.p_move = Process(target=self.serv_callback)
		print("Following the target\n")
		count = 0;grip_flag = 0
		sol =  self.joints
		for i in range(len(y_track)):
			dist = np.linalg.norm (y_track[i,:3] - g_track[i])
			# Gripping Condition
			if (dist < 0.01 and count >= 210):
				print("Gripping Finished \n")
				break;
			elif (dist < 0.01 and count == 10):
				print("Gripper in Action \n")
				if (grip_flag == 0):
					self.p_move.start()
					grip_flag = 1
				count += 1
			elif (dist < 0.01 and count < 210):
				count += 1
			else:
				pass
			# 
			sol = self.ik.get_ik(list(sol),*y_track[i])
			self.script.data = "servoj({},{},{},{},{},{})".format(list(sol),0,0,0.1,0.1,100)   # for Real robot experiment
			# self.script.data = "servoj({},{},{},{},{},{})".format(list(sol),0,0,0.1,0.1,300)  # for simulation
			self.pub.publish(self.script)
			print(dist)

			# Vary the loop rate
			if (dist < 0.02):
				val = 0.01
			else:
				val = 0.01
			time.sleep(val)
	def move_view(self):
		# print(self.ref_pos)
		# sol = self.ik.get_ik(list(self.joints),*self.ref_pos)
		self.script.data =  "movej({},a=1.4, v=1.05, t=3, r=0)".format(list(self.ref_pos))
		self.pub.publish(self.script)
		time.sleep(4)
		print("Reached Ref pos\n")

	def move_bin(self):
		self.p_move.join()
		# sol = self.ik.get_ik(list(self.joints),*self.bin_pos)
		self.script.data =  "movej({},a=1.4, v=1.05, t=3, r=0)".format(list(self.bin_pos))
		self.pub.publish(self.script)
		time.sleep(4)
		self.home_serv()
		print("Reached Bin\n")
		# time.sleep(2.5)


class Tf_listener:
	def __init__(self):
		# rospy.init_node("Tf_listener")
		self.listener = tf.TransformListener()
	def get_pose(self):
		while not rospy.is_shutdown():
			try:
				trans,rot = self.listener.lookupTransform('/base_link','/ee_link',rospy.Time(0))
				if (trans != None):
					break
			except(tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
				continue
		trans,rot = list(trans),list(rot)
		return np.array(trans+rot)

# class myThread(threading.Thread):
# 	def __init__(self,*args):
# 		threading.Thread.__init__(self)
# 		self.arg = args[0]
# 	def run(self):

