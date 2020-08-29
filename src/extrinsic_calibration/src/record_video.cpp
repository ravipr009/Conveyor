#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/tracking.hpp>
#include <opencv2/aruco.hpp>


#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/pcd_io.h>
#include <fstream>
#include <iostream>


#include <pthread.h>


char au = 'm';
//pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");


void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    while(1)
    {
        std::cout << "press r to record video " << std::endl
                  << "press n to record next video " << std::endl
                  << std::endl;
        std::cin >> au;
    }
}


cv::Mat current_image;
void image_call_back(const sensor_msgs::ImageConstPtr &msg)
{
    current_image = cv_bridge::toCvShare(msg, "bgr8")->image ;
    return;
}



//pcl::PointCloud<pcl::PointXYZRGB>::Ptr current_point_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
//void centroid_region_cb (const sensor_msgs::PointCloud2ConstPtr& msg)
//{

//    pcl::PCLPointCloud2 pcl_pc2;
//    pcl_conversions::toPCL(*msg, pcl_pc2);
//    pcl::fromPCLPointCloud2(pcl_pc2,*current_point_cloud);
//    return;
//}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "record_video");

    ros::AsyncSpinner spinner(4);
    spinner.start();
    ros::NodeHandle n;

    ros::Subscriber image_sub = n.subscribe <sensor_msgs::Image> ("/camera/rgb/image_raw", 1, image_call_back);
    //    ros::Subscriber cloud_sub = n.subscribe<sensor_msgs::PointCloud2> ("/camera/depth_registered/points", 1, centroid_region_cb);


    pthread_t threads[1];
    pthread_create(&threads[0], NULL, PrintHello, (void *)1);


    std::string base_file = "/home/ravi/classic_ur_ws/src/extrinsic_calibration/data_files/videos/images/";


    int image_number = 0;
    int video_number = 7;






    while(ros::ok())
    {

        while(current_image.rows == 0)
        {
            ros::spinOnce();
        }





        if (au == 'r')
        {
            std::stringstream str_video_number_id;
            str_video_number_id  << video_number;

            std::stringstream str_image_number_id;
            str_image_number_id  << image_number;

            cv::imwrite(base_file + "/" + str_video_number_id.str() + "/" + str_image_number_id.str() + ".png", current_image);
            //            pcl::io::savePCDFileASCII (base_file + "/" + str_video_number_id.str() + "/" + str_image_number_id.str() + ".pcd", *current_point_cloud);
            image_number += 1;
            //            au = 'm';


        }


        if (au == 'n')
        {

            image_number = 0;
            video_number += 1;

            std::cout << "saving images in folder " <<  video_number << std::endl;
            au = 's';

        }


        cv::imshow("current_image", current_image);
        cv::waitKey(10);

//        viewer.showCloud (current_point_cloud);


        ros::spinOnce();


    }

    return 0;
}
