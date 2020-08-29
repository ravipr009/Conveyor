#include <ros/ros.h>

#include <pcl_ros/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/point_types.h>
#include <pcl/registration/transformation_estimation_svd.h>
#include <pcl/common/transforms.h>


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>

#include <algorithm>
#include <chrono>
#include <ctime>
#include <math.h>
#include <new>

#include <pthread.h>
#include <opencv2/aruco.hpp>

#include <fstream>
#include <iostream>


typedef pcl::PointXYZRGBA PointType;



char a;

int *centroid_row_pntr;
int *centroid_col_pntr;

bool flag_click = false;

int number_of_points = 3;
int number_of_points_selected = 0;


char au = 'g';

void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    while(1)
    {
        std::cout << "press d for marker detection" << std::endl
                  << "press l for link" << std::endl
                  << "press v for visualize" << std::endl
                  << "press p for service" << std::endl
                  << "press a to save raw cloud image" << std::endl
                  << "press b to save edge cloud image" << std::endl
                  << std::endl;
        std::cin >> au;
    }
}


Eigen::MatrixXf calculate_transformation(Eigen::MatrixXf points_in_object_frame, Eigen::MatrixXf points_in_camera_frame)
{

    int total_number_of_points_in_camera_frame = points_in_camera_frame.rows();

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_camera (new pcl::PointCloud<pcl::PointXYZ> ());
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_object (new pcl::PointCloud<pcl::PointXYZ> ());

    cloud_camera->width = total_number_of_points_in_camera_frame;
    cloud_camera->height = 1;
    cloud_camera->resize(cloud_camera->width * cloud_camera->height);


    cloud_object->width = total_number_of_points_in_camera_frame;
    cloud_object->height = 1;
    cloud_object->resize(cloud_object->width * cloud_object->height);

    for(int i=0; i<total_number_of_points_in_camera_frame; i++)
    {
        cloud_camera->points[i].x = points_in_camera_frame(i, 0);
        cloud_camera->points[i].y = points_in_camera_frame(i, 1);
        cloud_camera->points[i].z = points_in_camera_frame(i, 2);

        cloud_object->points[i].x = points_in_object_frame(i, 0);
        cloud_object->points[i].y = points_in_object_frame(i, 1);
        cloud_object->points[i].z = points_in_object_frame(i, 2);
    }

    pcl::registration::TransformationEstimationSVD<pcl::PointXYZ,pcl::PointXYZ> TESVD;
    pcl::registration::TransformationEstimationSVD<pcl::PointXYZ,pcl::PointXYZ>::Matrix4 transformation2;

    TESVD.estimateRigidTransformation (*cloud_object, *cloud_camera, transformation2);
    return transformation2;

}



cv::Mat current_image;
void image_call_back(const sensor_msgs::ImageConstPtr &msg)
{
    current_image = cv_bridge::toCvShare(msg, "bgr8")->image ;
    return;
}


pcl::PointCloud<PointType>::Ptr current_point_cloud (new pcl::PointCloud<PointType>);
void cloud_call_back (const sensor_msgs::PointCloud2ConstPtr& msg)
{
    pcl::PCLPointCloud2 pcl_pc2;
    pcl_conversions::toPCL(*msg, pcl_pc2);
    pcl::fromPCLPointCloud2(pcl_pc2,*current_point_cloud);
    return;
}


void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{

    if(!flag_click)
    {

        if  ( event == cv::EVENT_LBUTTONDOWN )
        {
            std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;

            *(centroid_row_pntr + number_of_points_selected) = y;
            *(centroid_col_pntr + number_of_points_selected) = x;

            if ( std::isnan(current_point_cloud->at(x, y).x))
            {
                std::cout << "Nan detected " << std::endl;

            }
            else
            {
                number_of_points_selected = number_of_points_selected + 1;

                if (number_of_points_selected == number_of_points)
                    flag_click = 1;
            }
        }

    }

}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "main");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    ros::NodeHandle n;
    ros::Subscriber image_sub = n.subscribe <sensor_msgs::Image> ("/camera/rgb/image_raw", 1, image_call_back);
    ros::Subscriber cloud_sub = n.subscribe <sensor_msgs::PointCloud2> ("/camera/depth_registered/points", 1, cloud_call_back);

    centroid_row_pntr = new int [number_of_points];
    centroid_col_pntr = new int [number_of_points];

    pthread_t threads[1];
    pthread_create(&threads[0], NULL, PrintHello, (void *)1);

    pcl::visualization::PCLVisualizer viewer;
    viewer.addPointCloud (current_point_cloud, "current_point_cloud");


    std::vector<std::vector<PointType>> markerCorners_3D_points;
    std::vector<Eigen::Affine3f> all_trans;

    std::string data_folder_path("/home/mohit/grasp_region_ws/src/all_services/data_files/");

    std::ofstream myfile;
    myfile.open (data_folder_path + "/Keypoints.txt", std::ios::out);




    while (ros::ok())
    {

        while(current_image.rows == 0 or current_point_cloud->height == 0)
        {
            ros::spinOnce();
        }

        break;
    }




    cv::namedWindow("select board frame");
    cv::startWindowThread();
    cv::setMouseCallback("select board frame", CallBackFunc, NULL);

    while(!flag_click)
    {
        cv::imshow("select board frame", current_image);
        cv::waitKey(25);
    }


    pcl::KdTreeFLANN<PointType> kdtree;
    kdtree.setInputCloud (current_point_cloud);


    PointType searchPoint, p0, px, py;

    std::vector<int> pointIdxRadiusSearch;
    std::vector<float> pointRadiusSquaredDistance;

    float radius = 0.02;

    Eigen::MatrixXf board_points(3, 3), board_points_in_camera_frame(3, 3);


    int i = 0;
    while (i < number_of_points)
    {

        pointIdxRadiusSearch.clear();
        pointRadiusSquaredDistance.clear();


        searchPoint.x = current_point_cloud->at(*(centroid_col_pntr + i), *(centroid_row_pntr + i)).x;
        searchPoint.y = current_point_cloud->at(*(centroid_col_pntr + i), *(centroid_row_pntr + i)).y;
        searchPoint.z = current_point_cloud->at(*(centroid_col_pntr + i), *(centroid_row_pntr + i)).z;
        searchPoint.r = current_point_cloud->at(*(centroid_col_pntr + i), *(centroid_row_pntr + i)).r;
        searchPoint.g = current_point_cloud->at(*(centroid_col_pntr + i), *(centroid_row_pntr + i)).g;
        searchPoint.b = current_point_cloud->at(*(centroid_col_pntr + i), *(centroid_row_pntr + i)).b;

        kdtree.radiusSearch (searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance);

        if (i == 0)
        {
            p0 = current_point_cloud->points[pointIdxRadiusSearch[0]];
            board_points.row(i) << 0, 0, -0.0375;
            board_points_in_camera_frame.row(i) << p0.x, p0.y, p0.z;
        }
        if (i == 1)
        {
            px = current_point_cloud->points[pointIdxRadiusSearch[0]];
            board_points.row(i) << 0.1, 0, -0.0375;
            board_points_in_camera_frame.row(i) << px.x, px.y, px.z;
        }
        if (i == 2)
        {
            py = current_point_cloud->points[pointIdxRadiusSearch[0]];
            board_points.row(i) << 0, 0.1, -0.0375;
            board_points_in_camera_frame.row(i) << py.x, py.y, py.z;
        }




        i = i+1;
    }


    Eigen::Affine3f board_trans;
    board_trans.matrix() = calculate_transformation(board_points, board_points_in_camera_frame);
    viewer.addCoordinateSystem (0.1, board_trans, "board_trans");



    Eigen::Matrix4f trans_m;
    Eigen::MatrixXf pi(4, 1), pt(4, 1);
    float p_m[3];

    trans_m = board_trans.matrix();

    pi(0, 0) = 0.1;
    pi(1, 0) = 0;
    pi(2, 0) = 0;
    pi(3, 0) = 1;

    pt = trans_m * pi;

    p_m[0] = pt(0, 0)/pt(3, 0);
    p_m[1] = pt(1, 0)/pt(3, 0);
    p_m[2] = pt(2, 0)/pt(3, 0);

    std::cout << p_m[0] << " " << p_m[1] << " "<< p_m[2] << std::endl;
    std::cout << px.x << " " << px.y << " "<< px.z << std::endl;




    while (ros::ok())
    {
        try
        {
            while(current_image.rows == 0 or current_point_cloud->height == 0)
            {
                ros::spinOnce();
            }


            viewer.updatePointCloud (current_point_cloud, "current_point_cloud");
            cv::Mat img;
            current_image.copyTo(img);

            std::vector<int> markerIds;
            std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
            cv::Ptr<cv::aruco::DetectorParameters> parameters (new cv::aruco::DetectorParameters);
            cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

            cv::aruco::detectMarkers(img, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);

            cv::Mat outputImage;
            current_image.copyTo(outputImage);
            cv::aruco::drawDetectedMarkers(outputImage, markerCorners, markerIds);

            float keypoints[4*markerIds.size()][5];


            int keypoint_number = 0;
            for(int i=0; i<markerIds.size(); i++)
            {

                std::vector<cv::Point2f> corner_pixels = markerCorners[i];
                std::vector<PointType> corner_pixels_3D_points;

                Eigen::MatrixXf points_in_object_frame(4, 3), points_in_camera_frame(4, 3);
                for(int j=0; j<corner_pixels.size(); j++)
                {

                    PointType single_corner_pixels_3D_point = current_point_cloud->at(corner_pixels[j].x, corner_pixels[j].y);
                    if (j == 0)
                    {
                        corner_pixels_3D_points.push_back(single_corner_pixels_3D_point);
                        viewer.addSphere (single_corner_pixels_3D_point, 0.02, 255, 255, 255,
                                          "sphere0" + std::to_string(i));

                        points_in_object_frame.row(0) << -2.65, 2.65, 0;
                        points_in_camera_frame.row(0) << single_corner_pixels_3D_point.x,
                                single_corner_pixels_3D_point.y,
                                single_corner_pixels_3D_point.z;
                    }

                    if (j == 1)
                    {
                        corner_pixels_3D_points.push_back(single_corner_pixels_3D_point);
                        viewer.addSphere (single_corner_pixels_3D_point, 0.02, 255, 0, 0,
                                          "sphere1" + std::to_string(i));

                        points_in_object_frame.row(1) << 2.65, 2.65, 0;
                        points_in_camera_frame.row(1) << single_corner_pixels_3D_point.x,
                                single_corner_pixels_3D_point.y,
                                single_corner_pixels_3D_point.z;
                    }

                    if (j == 2)
                    {
                        corner_pixels_3D_points.push_back(single_corner_pixels_3D_point);
                        viewer.addSphere (single_corner_pixels_3D_point, 0.02, 0, 255, 0,
                                          "sphere2" + std::to_string(i));

                        points_in_object_frame.row(2) << 2.65, -2.65, 0;
                        points_in_camera_frame.row(2) << single_corner_pixels_3D_point.x,
                                single_corner_pixels_3D_point.y,
                                single_corner_pixels_3D_point.z;
                    }

                    if (j == 3)
                    {
                        corner_pixels_3D_points.push_back(single_corner_pixels_3D_point);
                        viewer.addSphere (single_corner_pixels_3D_point, 0.02, 0, 0, 255,
                                          "sphere3" + std::to_string(i));

                        points_in_object_frame.row(3) << -2.65, -2.65, 0;
                        points_in_camera_frame.row(3) << single_corner_pixels_3D_point.x,
                                single_corner_pixels_3D_point.y,
                                single_corner_pixels_3D_point.z;
                    }

                    keypoints[keypoint_number][0] = markerIds[i];
                    keypoints[keypoint_number][1] = j;

                    pi(0, 0) = single_corner_pixels_3D_point.x;
                    pi(1, 0) = single_corner_pixels_3D_point.y;
                    pi(2, 0) = single_corner_pixels_3D_point.z;
                    pi(3, 0) = 1;

                    pt = trans_m.inverse() * pi;

                    p_m[0] = pt(0, 0)/pt(3, 0);
                    p_m[1] = pt(1, 0)/pt(3, 0);
                    p_m[2] = pt(2, 0)/pt(3, 0);

                    keypoints[keypoint_number][2] = p_m[0];
                    keypoints[keypoint_number][3] = p_m[1];
                    keypoints[keypoint_number][4] = p_m[2];



                    myfile << keypoints[keypoint_number][0] << ", "
                                                            << keypoints[keypoint_number][1] << ", "
                                                            << keypoints[keypoint_number][2] << ", "
                                                            << keypoints[keypoint_number][3] << ", "
                                                            << keypoints[keypoint_number][4] << "\n";

                    keypoint_number += 1;
                }

                Eigen::Affine3f trans;
                trans.matrix() = calculate_transformation(points_in_object_frame, points_in_camera_frame);
                all_trans.push_back(trans);

                viewer.addCoordinateSystem (0.1, trans, "reference" + std::to_string(i));
                markerCorners_3D_points.push_back(corner_pixels_3D_points);
            }

            myfile.close();

            while(!viewer.wasStopped())
            {
                cv::imshow("real_image", img);
                cv::imshow("detected_markers", outputImage);

                //                viewer.saveScreenshot("/home/mohit/clouid_img.png");
                //                cv::imwrite("/home/mohit/img.png", outputImage);

                viewer.spinOnce ();
                cv::waitKey(50);
                usleep(10000);

            }


            ros::spinOnce();


        }
        catch (std::exception& e)
        {
            current_image.rows = 0;

            while(current_image.rows == 0 or current_point_cloud->height == 0)
            {
                ros::spinOnce();
            }

        }

    }

    return 0;
}
