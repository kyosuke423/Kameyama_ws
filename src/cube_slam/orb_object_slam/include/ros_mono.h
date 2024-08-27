#include <Eigen/Dense>
#include <Eigen/Core>

#include<std_msgs/Float32MultiArray.h>
#include<line_msg/LinePoint.h>
// #include<darknet_ros_msgs/BoundingBoxes.h>
// #include<darknet_ros_msgs/BoundingBox.h>

#include <ros/ros.h>
#include <ros/package.h>

using namespace Eigen;

//10.22 line subscribe用
//Eigen::MatrixXd all_lines_raw(100, 4);   

Eigen::MatrixXd raw_all_obj2d_bbox;