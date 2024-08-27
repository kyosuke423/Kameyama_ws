/*
 * line_detection interface
 * Copyright Shichao Yang,2018, Carnegie Mellon University
 * Email: shichaoy@andrew.cmu.edu
 *
 */

#include <line_lbd/line_descriptor.hpp>

// #include "opencv2/core/utility.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <iostream>
#include <fstream>
#include <ctime>
#include <line_lbd/line_lbd_allclass.h>

#include <ros/ros.h>

#include<std_msgs/Float32MultiArray.h>

#include<line_msg/LinePoint.h>

using namespace cv;
using namespace std;

//9/14 new
static const std::string OPENCV_WINDOW = "Image window";

//std::string save_folder;
bool use_LSD_algorithm;
bool save_to_txts;

std_msgs::Float32MultiArray startx;
std_msgs::Float32MultiArray starty;
std_msgs::Float32MultiArray endx;
std_msgs::Float32MultiArray endy;

int numOfOctave_ = 1;
float Octave_ratio = 2.0;  

class ImageConverter
{
  ros::NodeHandle nh;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  // image_transport::Publisher image_pub_;
  ros::Publisher point_pub = nh.advertise<line_msg::LinePoint>("point_msg",1);
  ros::Publisher startx_pub = nh.advertise<std_msgs::Float32MultiArray>("startx",1);
  ros::Publisher starty_pub = nh.advertise<std_msgs::Float32MultiArray>("starty",10);
  ros::Publisher endx_pub = nh.advertise<std_msgs::Float32MultiArray>("endx",10);
  ros::Publisher endy_pub = nh.advertise<std_msgs::Float32MultiArray>("endy",10);

public:
  ImageConverter()
    : it_(nh)
  {
      image_sub_ = it_.subscribe("/camera/color/image_raw", 10, &ImageConverter::imageCb, this);
      // image_pub_ = it_.advertise("/image_converter/output_video", 1);

      cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      //yoloがsubscribeのとき
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      //yoloがpublishのとき
      // cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_8UC3);
    }
    catch(cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    } 

    nh.param<bool>("use_LSD_algorithm",use_LSD_algorithm,true);
    nh.param<bool>("save_to_txts",save_to_txts,true);

    line_lbd_detect* line_lbd_ptr = new line_lbd_detect(numOfOctave_,Octave_ratio); 
    line_lbd_ptr->use_LSD = use_LSD_algorithm;
    line_lbd_ptr->line_length_thres = 15;  // remove short edges

    // using my line detector class, could select LSD or edline.
    cv::Mat out_edges;
    std::vector< KeyLine> keylines_raw,keylines_out;
    line_lbd_ptr->detect_raw_lines(cv_ptr->image,keylines_raw);
    line_lbd_ptr->filter_lines(keylines_raw,keylines_out);  // remove short lines
      
    // show image
    if( cv_ptr->image.channels() == 1 )
      cvtColor( cv_ptr->image, cv_ptr->image, COLOR_GRAY2BGR );
    cv::Mat raw_img_cp;
    drawKeylines(cv_ptr->image, keylines_out, raw_img_cp, cv::Scalar( 0, 150, 0 ),2); // B G R

    cv::imshow(OPENCV_WINDOW, raw_img_cp);

    //std_msgs::Float32MultiArray startx;
    line_msg::LinePoint linedata;
  
    if (save_to_txts)
    {
      linedata.startx.data.clear();
      linedata.starty.data.clear();
      linedata.endx.data.clear();
      linedata.endy.data.clear();
      int xy;
      xy = keylines_out.size();
      linedata.startx.data.resize(xy);
      linedata.starty.data.resize(xy);
      linedata.endx.data.resize(xy);
      linedata.endy.data.resize(xy);

      for (int j=0;j<keylines_out.size();j++)
      {
        linedata.startx.data[j] = keylines_out[j].startPointX;
        linedata.starty.data[j] = keylines_out[j].startPointY;
        linedata.endx.data[j] = keylines_out[j].endPointX;
        linedata.endy.data[j] = keylines_out[j].endPointY;
        // resultsFile <<keylines_out[j].startPointX <<"\t" <<keylines_out[j].startPointY  <<"\t"
        //         <<keylines_out[j].endPointX   <<"\t" <<keylines_out[j].endPointY    <<endl;
      }
    }

    linedata.header.stamp = ros::Time::now();
    //image_pub_.publish(cv_ptr->toImageMsg());
    point_pub.publish(linedata);
    startx_pub.publish(startx);
    starty_pub.publish(starty);
    endx_pub.publish(endx);
    endy_pub.publish(endy);

    cv::waitKey(3);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  
  // std::string save_folder;
  // nh.param<std::string>("save_folder", save_folder, "$(find line_lbd)/data"); 
  
    // 保存するかどうかを指定
  // nh.param<bool>("use_LSD_algorithm", use_LSD_algorithm, true);
  // nh.param<bool>("save_to_txts", save_to_txts, false);

  ImageConverter ic;
  
  ros::spin();
  return 0;
}



// int main( int argc, char** argv )
// {
//       /* get parameters from comand line */
//       if(argc<2){
//       std::cout<<"Provide an image name"<<endl;
//       return -1;
//       }
 
//       ros::init(argc, argv, "detect lines");
//       ros::NodeHandle nh; 
 
//       std::string image_path(argv[1]);
            
//       cv::Mat raw_img = imread( image_path, 1 );
//       if( raw_img.data == NULL )
//       {
//       std::cout << "Error, image could not be loaded. Please, check its path \n"<<image_path << std::endl;
//       return -1;
//       }
      
      
//       std::string save_folder;
//       bool use_LSD_algorithm;
//       bool save_to_imgs;
//       bool save_to_txts;
//       nh.param<std::string>("save_folder", save_folder, "$(find line_lbd)/data"); 
//       nh.param<bool>("use_LSD_algorithm",use_LSD_algorithm,true);
//       nh.param<bool>("save_to_imgs",save_to_imgs,true);
//       nh.param<bool>("save_to_txts",save_to_txts,true); 
      
            
//       int numOfOctave_ = 1;
//       float Octave_ratio = 2.0;  

//       line_lbd_detect* line_lbd_ptr = new line_lbd_detect(numOfOctave_,Octave_ratio); 
//       line_lbd_ptr->use_LSD = use_LSD_algorithm;
//       line_lbd_ptr->line_length_thres = 15;  // remove short edges
      
      
//       // using my line detector class, could select LSD or edline.
//       cv::Mat out_edges;
//       std::vector< KeyLine> keylines_raw,keylines_out;
//       line_lbd_ptr->detect_raw_lines(raw_img,keylines_raw);
//       line_lbd_ptr->filter_lines(keylines_raw,keylines_out);  // remove short lines
      
//       // show image
//       if( raw_img.channels() == 1 )
//         cvtColor( raw_img, raw_img, COLOR_GRAY2BGR );
//       cv::Mat raw_img_cp;
//       drawKeylines(raw_img, keylines_out, raw_img_cp, cv::Scalar( 0, 150, 0 ),2); // B G R
//       imshow( "Line detector", raw_img_cp );
//       waitKey(); //9/13new
      
//       if (save_to_imgs)
//       {
//         std::string img_save_name = save_folder+"/saved_edges.jpg";
//         cv::imwrite(img_save_name,raw_img_cp);
//       }
      
      //10.22 kesita
      //  if (save_to_txts)
      //  {
      //    std::string txt_save_name = save_folder+"/saved_edges.txt";
      //    ofstream resultsFile;
      //    resultsFile.open(txt_save_name);
      //    for (int j=0;j<keylines_out.size();j++)
      //    {
      //      resultsFile <<keylines_out[j].startPointX <<"\t" <<keylines_out[j].startPointY  <<"\t"
      //              <<keylines_out[j].endPointX   <<"\t" <<keylines_out[j].endPointY    <<endl;
      //    }
      //    resultsFile.close();
      //  }
  
// }
