#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SVD>
#include <sensor_msgs/JointState.h>
#include <fstream>
#include <iostream>

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
//#include <moveit/move_group_interface/move_group.h>
//#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <math.h>

#include</home/mohit/grasp_region_ws/devel/include/visualization_msgs/Marker.h>


using namespace std;
using namespace Eigen;







int main(int argc, char **argv)
{

    ros::init(argc, argv, "visualize_marker_from_kinect");
    ros::AsyncSpinner spinner(1);
    spinner.start();
//    moveit::planning_interface::MoveGroup group("arm");
    ros::NodeHandle nh;


    ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("/visualization_kinect_marker", 10);

    tf::TransformListener listener;

    geometry_msgs::PointStamped centroid_point_wrt_kinect;
    geometry_msgs::PointStamped centroid_point_wrt_world;

    fstream myfile;
    std::string data_folder_path("/home/mohit/vision_ws/src/extrinsic_calibration/data_files/");

    char c;
    float a;


    myfile.open (data_folder_path + "kinect_points_wrt_camera_link.txt", std::ios::in);

    int num_points = 0;

    while (myfile.get(c))
    {
        if(c == '\n')
            num_points = num_points + 1;
    }

    myfile.close();


    MatrixXf matrix_points(num_points, 3);


    myfile.open (data_folder_path + "kinect_points_wrt_camera_link.txt", std::ios::in);
    int row = 0;
    int column = 0;

    do
    {

        myfile >> a;
        matrix_points(row, column) = a;

        column = column + 1;
        column = column % 3;
        if(column == 0)
            row = row + 1;

        if(row == num_points)
            break;

    }while (myfile.get(c));

    myfile.close();




    while(ros::ok())
    {
        visualization_msgs::Marker centroid_point;
        centroid_point.header.frame_id = "/odom";
        centroid_point.header.stamp = ros::Time::now();
        centroid_point.ns = "kinect_points";
        centroid_point.action = visualization_msgs::Marker::ADD;
        centroid_point.pose.orientation.w  = 1.0;


        centroid_point.id = 0;



        centroid_point.type = visualization_msgs::Marker::POINTS;



        centroid_point.scale.x = 0.02;
        centroid_point.scale.y = 0.02;

        centroid_point.color.g = 1.0f;
        centroid_point.color.a = 1.0;


        for (int i=0 ;i< num_points; i++)
        {
            geometry_msgs::Point p_c;

            centroid_point_wrt_kinect.point.x = matrix_points(i, 0);
            centroid_point_wrt_kinect.point.y = matrix_points(i, 1);
            centroid_point_wrt_kinect.point.z = matrix_points(i, 2);

            centroid_point_wrt_kinect.header.frame_id = "camera_link";
            listener.waitForTransform( "odom", "camera_link", ros::Time(0), ros::Duration(3));
            listener.transformPoint("odom", centroid_point_wrt_kinect, centroid_point_wrt_world);

            p_c = centroid_point_wrt_world.point;
            centroid_point.points.push_back(p_c);

        }

        marker_pub.publish(centroid_point);

    }



    return 0;
}

