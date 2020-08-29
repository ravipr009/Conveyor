#include<iostream>
#include<ros/ros.h>
#include <tf/transform_listener.h>


#include<signal.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sensor_msgs/JointState.h>
#include<std_msgs/String.h>






std::vector<double> current_jts;
std::vector<double> current_pose;
using namespace std;
void signal_callback_handler(int signum)
{
    cout << "Caught Signal" << signum << endl;

    exit(0);
}

void jointStateCallback(const sensor_msgs::JointStateConstPtr& msg)
{
        current_jts.clear();

        for(int i=0;i<msg->position.size();i++)
        {

            current_jts.push_back(msg->position[i]);
        }


        std::cout<<current_jts[0]<< "," << current_jts[1] << "," << current_jts[2]<< "," <<current_jts[3]<< "," << current_jts[4] << "," << current_jts[5]<< "," <<  std::endl;


    return;
}

void waitForEnter() {
    static std::string line;
    std::getline(std::cin, line);
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"save_data");
    ros::NodeHandle nh;
    signal(SIGINT, signal_callback_handler);



    std::ofstream myfile_pose,myfile_joint;


    myfile_pose.open("/home/ravi/Desktop/save_hjb/record_pose.txt");


//    myfile_joint.open("/home/ravi/Desktop/save_hjb/record_jts.txt");



//    ros::Subscriber sub = nh.subscribe("/joint_states", 1, jointStateCallback);
    std::cout<<"Press [Enter] to start displaying joint positions and pose \n"<<std::endl;
        int i;
        for(i=0; i<10;i++)
        {
        waitForEnter();
        {
            ros::spinOnce();
            tf::TransformListener transform_listener;
            tf::StampedTransform transform_ee;


            transform_listener.waitForTransform("/base", "/ee_link", ros::Time(0), ros::Duration(3));
            transform_listener.lookupTransform("/base" , "/ee_link", ros::Time(0), transform_ee);

           std::cout<<transform_ee.getOrigin().x()<<","<<transform_ee.getOrigin().y()<<","<<transform_ee.getOrigin().z()<<","<<std::endl;




            myfile_pose<<transform_ee.getOrigin().x()<< "," << transform_ee.getOrigin().y()<< "," << transform_ee.getOrigin().z()<< "," << std::endl;


//            myfile_joint <<current_jts[0]<< "," << current_jts[1] << "," << current_jts[2]<< "," <<current_jts[3]<< "," << current_jts[4] << "," << current_jts[5]<< "," <<  std::endl;

//            std::cout <<current_pose[0]<< "\t" << current_pose[1] << "\t" << current_pose[2] <<'\n';

        }
        }

      myfile_pose.close();
//      myfile_joint.close();

//        ros::MultiThreadedSpinner spinner(4);

//        spinner.spin();


return 0;
}
