/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>

#include <ros/ros.h>
#include <ros/package.h>
#include <cv_bridge/cv_bridge.h>

#include <opencv2/core/core.hpp>

#include "System.h"
#include "Tracking.h"
#include "Parameters.h"
#include "tictoc_profiler/profiler.hpp"

// Eigen
#include <Eigen/Dense>
#include <Eigen/Core>

//10.4new
#include<std_msgs/Float32MultiArray.h>
#include<line_msg/LinePoint.h>
// #include<darknet_ros_msgs/BoundingBoxes.h>
// #include<darknet_ros_msgs/BoundingBox.h>
#include "ros_mono.h"
#include<yolov5_ros/yolov5_data.h>

using namespace std;
using namespace Eigen;

// Eigen::MatrixXd all_lines_raw;   
// MatrixXd raw_all_obj2d_bbox;

class ImageGrabber
{
//10.4new
private:
    // Eigen::MatrixXd all_lines_raw_sub;   
    // Eigen::MatrixXd raw_all_obj2d_bbox_sub;
    line_msg::LinePoint pointdata;
    // darknet_ros_msgs::BoundingBoxes yolodata;
    // std::vector<string> object_classes;
    int n;

public:
    ImageGrabber(ORB_SLAM2::System *pSLAM) : mpSLAM(pSLAM) {}

    void GrabImage(const sensor_msgs::ImageConstPtr &msg);

    // Eigen::MatrixXd all_lines_raw;   
    // MatrixXd raw_all_obj2d_bbox;

    ORB_SLAM2::System *mpSLAM;


    //10.4new
    // void pointCallback(const line_msg::LinePoint::ConstPtr& pointdata)
    // {
    //     //ROS_INFO("point ok");
    //     int xyz;
    //     xyz = pointdata->startx.data.size();
    //     all_lines_raw.resize(xyz, 4);
    //     //Eigen::MatrixXd all_lines_raw(100,4);
    //     for (int j=0;j<pointdata->startx.data.size();j++)
    //     {
    //         all_lines_raw(j,0) = pointdata->startx.data[j];
    //         all_lines_raw(j,1) = pointdata->starty.data[j];
    //         all_lines_raw(j,2) = pointdata->endx.data[j];
    //         all_lines_raw(j,3) = pointdata->endy.data[j];
    //     }
    //     //Trackingslam->get_pointdata(all_lines_raw);
    // }

    void yoloCallback(const yolov5_ros::yolov5_data::ConstPtr& yolodata)
    {
        int s = yolodata->yolo_box_data.data.size();
        n = (s+1)/6;
        //object_classes.resize(n);
        raw_all_obj2d_bbox.resize(n,7);              // hard coded
        for(int b=0;b<n;b++)
        {
            //単眼用
            // raw_all_obj2d_bbox(b,0) = yolodata.data[6*b+1] - (yolodata.data[6*b+3]/2); //xmin
            // raw_all_obj2d_bbox(b,1) = yolodata.data[6*b+2] - (yolodata.data[6*b+4]/2); //ymin

            //複眼用
            raw_all_obj2d_bbox(b,0) = yolodata->yolo_box_data.data[6*b+1]; //xmin
            raw_all_obj2d_bbox(b,1) = yolodata->yolo_box_data.data[6*b+2]; //ymin

            raw_all_obj2d_bbox(b,2) = yolodata->yolo_box_data.data[6*b+3]; //width
            raw_all_obj2d_bbox(b,3) = yolodata->yolo_box_data.data[6*b+4]; //height
            raw_all_obj2d_bbox(b,4) = yolodata->yolo_box_data.data[6*b+5]; //conf
            raw_all_obj2d_bbox(b,5) = yolodata->yolo_box_data.data[6*b]; //class
            // raw_all_obj2d_bbox(b,6) = yolodata->object_depth_data.data[b]; //depth
            raw_all_obj2d_bbox(b,6) = 0; //depth kari
        }

        // object_classes2 = yolodata->bounding_boxes[1].Class;
        raw_all_obj2d_bbox.leftCols<2>().array() -= 1;    // change matlab coordinate to c++, minus 1
        ROS_WARN_STREAM("yolo sub");
        std::cout << raw_all_obj2d_bbox << std::endl;
        printf("yolo sub\n");
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Mono");
    ros::start();
    ca::Profiler::enable();

    if (argc != 3)
    {
        cerr << endl
             << "Usage: rosrun ORB_SLAM2 Mono path_to_vocabulary path_to_settings" << endl;
        ros::shutdown();
        return 1;
    }
    ros::NodeHandle nh;

    bool enable_loop_closing = true;
    nh.param<bool>("enable_viewer", ORB_SLAM2::enable_viewer, true);
    nh.param<bool>("enable_viewmap", ORB_SLAM2::enable_viewmap, true);
    nh.param<bool>("enable_viewimage", ORB_SLAM2::enable_viewimage, true);
    nh.param<bool>("enable_loop_closing", enable_loop_closing, true);
    nh.param<bool>("parallel_mapping", ORB_SLAM2::parallel_mapping, true);

    nh.param<bool>("whether_detect_object", ORB_SLAM2::whether_detect_object, false);
    nh.param<bool>("whether_read_offline_cuboidtxt", ORB_SLAM2::whether_read_offline_cuboidtxt, false);
    nh.param<bool>("associate_point_with_object", ORB_SLAM2::associate_point_with_object, false);

    nh.param<bool>("whether_dynamic_object", ORB_SLAM2::whether_dynamic_object, false);
    nh.param<bool>("remove_dynamic_features", ORB_SLAM2::remove_dynamic_features, false);

    nh.param<bool>("mono_firstframe_truth_depth_init", ORB_SLAM2::mono_firstframe_truth_depth_init, false);
    nh.param<bool>("mono_firstframe_Obj_depth_init", ORB_SLAM2::mono_firstframe_Obj_depth_init, false);
    nh.param<bool>("mono_allframe_Obj_depth_init", ORB_SLAM2::mono_allframe_Obj_depth_init, false);

    nh.param<bool>("enable_ground_height_scale", ORB_SLAM2::enable_ground_height_scale, false);
    nh.param<bool>("use_dynamic_klt_features", ORB_SLAM2::use_dynamic_klt_features, false);

    nh.param<bool>("bundle_object_opti", ORB_SLAM2::bundle_object_opti, false);
    nh.param<double>("camera_object_BA_weight", ORB_SLAM2::camera_object_BA_weight, 1.0);
    nh.param<double>("object_velocity_BA_weight", ORB_SLAM2::object_velocity_BA_weight, 1.0);

    // nh.param<bool>("draw_map_truth_paths", ORB_SLAM2::draw_map_truth_paths, true);
    nh.param<bool>("draw_nonlocal_mappoint", ORB_SLAM2::draw_nonlocal_mappoint, true);

    // temp debug
    nh.param<bool>("ba_dyna_pt_obj_cam", ORB_SLAM2::ba_dyna_pt_obj_cam, false);
    nh.param<bool>("ba_dyna_obj_velo", ORB_SLAM2::ba_dyna_obj_velo, true);
    nh.param<bool>("ba_dyna_obj_cam", ORB_SLAM2::ba_dyna_obj_cam, true);

    std::string scene_name;
    ros::param::get("/scene_name", scene_name);
    ros::param::get("/base_data_folder", ORB_SLAM2::base_data_folder);

    if (scene_name.compare(std::string("kitti")) == 0)
        ORB_SLAM2::scene_unique_id = ORB_SLAM2::kitti;

    cout << "Base_data_folder:  " << ORB_SLAM2::base_data_folder << endl;

    std::string packagePath = ros::package::getPath("orb_object_slam");

    if (!enable_loop_closing)
        ROS_WARN_STREAM("Turn off global loop closing!!");
    else
        ROS_WARN_STREAM("Turn on global loop closing!!");
    // Create SLAM system. It initializes all system threads and gets ready to process frames.

    ORB_SLAM2::System SLAM(argv[1], argv[2], ORB_SLAM2::System::MONOCULAR, enable_loop_closing);

    ImageGrabber igb(&SLAM);

    //10,4new
    // ros::Subscriber point_sub = nh.subscribe("/point_msg", 10, &ImageGrabber::pointCallback, &igb);
    ros::Subscriber yolo_sub = nh.subscribe("/multi_box_command", 10, &ImageGrabber::yoloCallback, &igb);

    // ros::Subscriber sub = nh.subscribe("/camera/rgb/image_raw", 10, &ImageGrabber::GrabImage, &igb);
    ros::Subscriber sub = nh.subscribe("/camera/color/image_raw", 10, &ImageGrabber::GrabImage, &igb);
    ros::spin(); //block here till I ctrl-C

    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    //     SLAM.SaveKeyFrameTrajectoryTUM(packagePath+"/Outputs/KeyFrameTrajectory.txt");

    // Save camera trajectory
    SLAM.SaveTrajectoryTUM(packagePath + "/Outputs/AllFrameTrajectory.txt");
    if (ORB_SLAM2::scene_unique_id == ORB_SLAM2::kitti)
        SLAM.SaveTrajectoryKITTI(packagePath + "/Outputs/AllFrameTrajectoryKITTI.txt");

    ca::Profiler::print_aggregated(std::cout);

    ros::shutdown();

    return 0;
}

void ImageGrabber::GrabImage(const sensor_msgs::ImageConstPtr &msg)
{
    // Copy the ros image message to cv::Mat.
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvShare(msg);
        // cv_ptr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::TYPE_8UC3);
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    mpSLAM->TrackMonocular(cv_ptr->image, cv_ptr->header.stamp.toSec(), msg->header.seq);
}