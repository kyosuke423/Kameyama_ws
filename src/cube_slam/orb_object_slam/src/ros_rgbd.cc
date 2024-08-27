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
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

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
#include<yolov5_ros/yolov5_data.h>
// #include<darknet_ros_msgs/BoundingBoxes.h>
// #include<darknet_ros_msgs/BoundingBox.h>
#include "ros_mono.h"
#include "boxdata_pub.h"

#include "line_lbd/line_lbd_allclass.h"

using namespace std;
using namespace Eigen;
using namespace cv;


class ImageGrabber
{
private: //12.6new
    line_msg::LinePoint pointdata;
    int n;

public:
    ImageGrabber(ORB_SLAM2::System *pSLAM) : mpSLAM(pSLAM) {}

    void GrabRGBD(const sensor_msgs::ImageConstPtr &msgRGB, const sensor_msgs::ImageConstPtr &msgD, const yolov5_ros::yolov5_dataConstPtr &yolodata, ros::Publisher box_pub);

    ORB_SLAM2::System *mpSLAM;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "RGBD");
    ros::start();
    ca::Profiler::enable();

    if (argc != 3)
    {
        cerr << endl
             << "Usage: rosrun ORB_SLAM2 RGBD path_to_vocabulary path_to_settings" << endl;
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

    nh.param<bool>("mono_firstframe_truth_depth_init", ORB_SLAM2::mono_firstframe_truth_depth_init, false);
    nh.param<bool>("mono_firstframe_Obj_depth_init", ORB_SLAM2::mono_firstframe_Obj_depth_init, false);
    nh.param<bool>("mono_allframe_Obj_depth_init", ORB_SLAM2::mono_allframe_Obj_depth_init, false);

    nh.param<bool>("bundle_object_opti", ORB_SLAM2::bundle_object_opti, false);
    nh.param<double>("camera_object_BA_weight", ORB_SLAM2::camera_object_BA_weight, 1.0);
    nh.param<double>("object_velocity_BA_weight", ORB_SLAM2::object_velocity_BA_weight, 1.0);

    // nh.param<bool>("draw_map_truth_paths", ORB_SLAM2::draw_map_truth_paths, true);
    nh.param<bool>("draw_nonlocal_mappoint", ORB_SLAM2::draw_nonlocal_mappoint, true);

    nh.param<bool>("enable_ground_height_scale", ORB_SLAM2::enable_ground_height_scale, false);

    nh.param<bool>("parallel_mapping", ORB_SLAM2::parallel_mapping, true);
    
    // nh.param<bool>("use_LSD_algorithm",use_LSD_algorithm,true);

    std::string scene_name;
    ros::param::get("/scene_name", scene_name);
    ros::param::get("/base_data_folder", ORB_SLAM2::base_data_folder);

    if (scene_name.compare(std::string("kitti")) == 0)
        ORB_SLAM2::scene_unique_id = ORB_SLAM2::kitti;

    if (!enable_loop_closing)
        ROS_WARN_STREAM("Turn off global loop closing!!");
    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1], argv[2], ORB_SLAM2::System::RGBD, enable_loop_closing);

    ImageGrabber igb(&SLAM);

    //10,4new
    // ros::Subscriber point_sub = nh.subscribe("/point_msg", 10, &ImageGrabber::pointCallback, &igb);
    // ros::Subscriber yolo_sub = nh.subscribe("/multi_command", 10, &ImageGrabber::yoloCallback, &igb);
    // ros::Publisher box_class_pub = nh.advertise<std_msgs::Float32MultiArray>("/boxclass", 10);
    // ros::Publisher box_x_pub = nh.advertise<std_msgs::Float32MultiArray>("/boxpointx", 10);
    // ros::Publisher box_y_pub = nh.advertise<std_msgs::Float32MultiArray>("/boxpointy", 10);
    ros::Publisher box_pub = nh.advertise<std_msgs::Float32MultiArray>("/boxdata", 10);

    message_filters::Subscriber<sensor_msgs::Image> rgb_sub(nh, "/mecanum2/camera/color/image_raw", 10);
    message_filters::Subscriber<sensor_msgs::Image> depth_sub(nh, "/mecanum2/camera/aligned_depth_to_color/image_raw", 10);
    message_filters::Subscriber<yolov5_ros::yolov5_data> yolo_sub(nh, "/mecanum2/multi_box_command", 10);
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image, yolov5_ros::yolov5_data> sync_pol;
    message_filters::Synchronizer<sync_pol> sync(sync_pol(10), rgb_sub, depth_sub, yolo_sub);
    sync.registerCallback(boost::bind(&ImageGrabber::GrabRGBD, &igb, _1, _2, _3, box_pub));
    // sync.registerCallback(boost::bind(&ImageGrabber::GrabRGBD, &igb, _1, _2, _3, box_class_pub, box_x_pub, box_y_pub, box_pub));

    // message_filters::Subscriber<sensor_msgs::Image> rgb_sub(nh, "/camera/color/image_raw", 10);
    // message_filters::Subscriber<sensor_msgs::Image> depth_sub(nh, "/camera/depth/image_rect_raw", 10);
    // typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> sync_pol;
    // message_filters::Synchronizer<sync_pol> sync(sync_pol(10), rgb_sub, depth_sub);
    // sync.registerCallback(boost::bind(&ImageGrabber::GrabRGBD, &igb, _1, _2));

    ros::spin();

    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    std::string packagePath = ros::package::getPath("orb_slam2");
    //     SLAM.SaveKeyFrameTrajectoryTUM(packagePath+"/Outputs/KeyFrameTrajectory.txt");
    // Save camera trajectory
    SLAM.SaveTrajectoryTUM(packagePath + "/Outputs/AllFrameTrajectory.txt");

    ca::Profiler::print_aggregated(std::cout);
    ros::shutdown();

    return 0;
}

void ImageGrabber::GrabRGBD(const sensor_msgs::ImageConstPtr &msgRGB, const sensor_msgs::ImageConstPtr &msgD, const yolov5_ros::yolov5_dataConstPtr &yolodata, ros::Publisher box_pub)
{
    // Copy the ros image message to cv::Mat.
    // std::cout << "image sub time : " << msgRGB->header.stamp << " yolo sub time : " << yolodata->header.stamp << std::endl;
    cv_bridge::CvImageConstPtr cv_ptrRGB;
    try
    {
        cv_ptrRGB = cv_bridge::toCvShare(msgRGB);
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    cv_bridge::CvImageConstPtr cv_ptrD;
    cv::Mat depth_mat;
    try
    {
        cv_ptrD = cv_bridge::toCvShare(msgD);
        depth_mat = cv_ptrD->image;
        // usually TYPE_32FC1   if TYPE_16UC1, convert it.
        if (msgD->encoding == sensor_msgs::image_encodings::TYPE_16UC1) // already uint, (already multiplied by 1000)
        {
            depth_mat.convertTo(depth_mat, CV_32FC1, 1.0 / 1000.0, 0);
        }
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    //line start
    // line_lbd_detect* line_lbd_ptr = new line_lbd_detect(numOfOctave_,Octave_ratio); 
    // line_lbd_ptr->use_LSD = use_LSD_algorithm;
    // line_lbd_ptr->line_length_thres = 15;  // remove short edges

    // // using my line detector class, could select LSD or edline.
    // cv::Mat out_edges;
    // std::vector< KeyLine> keylines_raw,keylines_out;
    // line_lbd_ptr->detect_raw_lines(cv_ptrRGB->image,keylines_raw);
    // line_lbd_ptr->filter_lines(keylines_raw,keylines_out);  // remove short lines

    // int xyz;
    // xyz = keylines_out.size();
    // all_lines_raw.resize(xyz, 4);

    // for (int j=0;j<xyz;j++)
    // {
    //     all_lines_raw(j,0) = keylines_out[j].startPointX;
    //     all_lines_raw(j,1) = keylines_out[j].startPointY;
    //     all_lines_raw(j,2) = keylines_out[j].endPointX;
    //     all_lines_raw(j,3) = keylines_out[j].endPointY;
    // }
    //line finish

    // yolo
    int s = yolodata->yolo_box_data.data.size();
    n = (s+1)/8;
    //object_classes.resize(n);
    raw_all_obj2d_bbox.resize(n,8);              // hard coded
    for(int b=0;b<n;b++)
    {
        //単眼用
        // raw_all_obj2d_bbox(b,0) = yolodata.data[6*b+1] - (yolodata.data[6*b+3]/2); //xmin
        // raw_all_obj2d_bbox(b,1) = yolodata.data[6*b+2] - (yolodata.data[6*b+4]/2); //ymin

        //複眼用
        raw_all_obj2d_bbox(b,0) = yolodata->yolo_box_data.data[8*b+1]; //xmin
        raw_all_obj2d_bbox(b,1) = yolodata->yolo_box_data.data[8*b+2]; //ymin

        raw_all_obj2d_bbox(b,2) = yolodata->yolo_box_data.data[8*b+3]; //width
        raw_all_obj2d_bbox(b,3) = yolodata->yolo_box_data.data[8*b+4]; //height
        raw_all_obj2d_bbox(b,4) = yolodata->yolo_box_data.data[8*b+5]; //conf
        raw_all_obj2d_bbox(b,5) = yolodata->yolo_box_data.data[8*b]; //class
        // raw_all_obj2d_bbox(b,6) = yolodata->object_depth_data.data[b]; //depth
        raw_all_obj2d_bbox(b,6) = yolodata->yolo_box_data.data[8*b+6]; //depth kari
        raw_all_obj2d_bbox(b,7) = yolodata->yolo_box_data.data[8*b+7]; //id
    }
    // yolofinish

    // object_classes2 = yolodata->bounding_boxes[1].Class;
    raw_all_obj2d_bbox.leftCols<2>().array() -= 1;    // change matlab coordinate to c++, minus 1

    cv::Mat pose = mpSLAM->TrackRGBD(cv_ptrRGB->image, depth_mat, cv_ptrRGB->header.stamp.toSec());
    //1.18new
    // box_class_pub.publish(box_class_data);
    // box_x_pub.publish(box_x_data);
    // box_y_pub.publish(box_y_data);
    box_pub.publish(box_data);
}
