#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <fstream>
#include <iostream>
#include <math.h>






int main(int argc, char** argv)
{
    ros::init(argc, argv, "store_marker");
    ros::AsyncSpinner spinner(1);
    spinner.start();


    geometry_msgs::PointStamped tip_point_wrt_world;
    geometry_msgs::PointStamped reference_point_wrt_tip_link;

    tf::TransformListener listener;
    std::string data_folder_path("/home/mohit/vision_ws/src/extrinsic_calibration/data_files/");

    std::ofstream myfile;
    myfile.open (data_folder_path + "/marker_coordinates_wrt_base_link.txt", std::ios::out);
    char choice;

    while(1)
    {

        std::cout << "press f to store marker point wrt base link\n"
                  << "press s to exit\n";
        std::cin >> choice;

        if (choice == 'f')
        {
            reference_point_wrt_tip_link.header.frame_id = "tip_link";

            reference_point_wrt_tip_link.point.x = 0;
            reference_point_wrt_tip_link.point.y = 0;
            reference_point_wrt_tip_link.point.z = 0;

            listener.waitForTransform( "ur5_base_link", "tip_link", ros::Time(0), ros::Duration(3));

            listener.transformPoint("ur5_base_link", reference_point_wrt_tip_link, tip_point_wrt_world);

            std::cout << tip_point_wrt_world.point.x << ", "
                      << tip_point_wrt_world.point.y << ", "
                      << tip_point_wrt_world.point.z << "\n";


            myfile << tip_point_wrt_world.point.x << ", "
                   << tip_point_wrt_world.point.y << ", "
                   << tip_point_wrt_world.point.z << "\n";


        }

        if (choice == 's')
        {

            break;
        }

    }

    myfile.close();


    return 0;
}
