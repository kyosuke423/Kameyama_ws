// std c
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

// opencv
#include <opencv2/opencv.hpp> //opencv/cv.hからopencv2/opencv.hppに
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/features2d.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <fstream>
#include <ctime>

// ros
#include <ros/ros.h>
#include <ros/package.h>

// Eigen
#include <Eigen/Dense>
#include <Eigen/Core>

// ours
#include "detect_3d_cuboid/detect_3d_cuboid.h"
#include "tictoc_profiler/profiler.hpp"

#include<std_msgs/Float32MultiArray.h>
#include<line_msg/LinePoint.h>
// #include<darknet_ros_msgs/BoundingBoxes.h>
// #include<darknet_ros_msgs/BoundingBox.h>
#include<yolov5_ros/yolov5_data.h>
#include <sensor_msgs/Imu.h>
#include <math.h>

#include "line_lbd/line_lbd_allclass.h"


using namespace std;
using namespace Eigen;
using namespace cv;

static const std::string COBOID_WINDOW = "Image window";

//line parameter
bool use_LSD_algorithm;
int numOfOctave_ = 1;
float Octave_ratio = 2.0;

class Imageimport
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void saveObjectCuboidsToCSV(const std::string& filename, const std::vector<ObjectSet>& object_cuboids) {
        std::ofstream outputFile(filename, std::ios::app); // 追記モードでファイルをオープン

        if (outputFile.is_open()) {
            // オブジェクトごとに直方体情報を書き込む
            for (int object_id = 0; object_id < object_cuboids.size(); object_id++) {
                for (int cube_id = 0; cube_id < object_cuboids[object_id].size(); cube_id++) {
                    double height = object_cuboids[object_id][cube_id]->scale(2);
                    double width = object_cuboids[object_id][cube_id]->scale(0);
                    double depth = object_cuboids[object_id][cube_id]->scale(1);

                    // CSVファイルにデータを書き込む
                    outputFile << object_id << "," << cube_id << "," << height << "," << width << ","<< depth << "," << "\n";
                }
            }

            ROS_INFO("Object cuboids data appended to %s", filename.c_str());
        } else {
            ROS_ERROR("Unable to open file %s", filename.c_str());
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // void saveObjectCuboidsToCSV(const std::string& filename, const std::vector<ObjectSet>& object_cuboids) {
    //     time_t currentTime;
    //     struct tm* timeinfo;
    //     char buffer[80];

    //     time(&currentTime);                   // 現在の時間を取得
    //     timeinfo = localtime(&currentTime);   // 構造体 tm に変換

    //     strftime(buffer, sizeof(buffer), "object_cuboids_%Y%m%d_%H%M%S.csv", timeinfo); // ファイル名を生成

    //     std::ofstream outputFile(buffer); // ファイルを書き込みモードでオープン

    //     if (outputFile.is_open()) {
    //         // タイトル行を書き込む（オブジェクトID、直方体ID、各寸法のヘッダ）
    //         outputFile << "Object ID,Cuboid ID,Height,Width,Depth\n";

    //         // オブジェクトごとに直方体情報を書き込む
    //         for (int object_id = 0; object_id < object_cuboids.size(); object_id++) {
    //             for (int cube_id = 0; cube_id < object_cuboids[object_id].size(); cube_id++) {
    //                 double height = object_cuboids[object_id][cube_id]->scale(2);
    //                 double width = object_cuboids[object_id][cube_id]->scale(0);
    //                 double depth = object_cuboids[object_id][cube_id]->scale(1);

    //                 // CSVファイルにデータを書き込む
    //                 outputFile << object_id << "," << cube_id << "," << height << "," << width << "," << depth << "\n";
    //             }
    //         }

    //         outputFile.close(); // ファイルをクローズ
    //         ROS_INFO("Object cuboids data saved to %s", buffer);
    //     } else {
    //         ROS_ERROR("Unable to open file %s", buffer);
    //     }
    // }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 追加: CSVファイルに直方体情報を保存するメソッド
    // void saveObjectCuboidsToCSV(const std::string& filename, const std::vector<ObjectSet>& object_cuboids) {
    //     std::ofstream outputFile(filename); // ファイルを書き込みモードでオープン

    //     if (outputFile.is_open()) {
    //         // タイトル行を書き込む（オブジェクトID、直方体ID、各寸法のヘッダ）
    //         outputFile << "Object ID,Cuboid ID,Height,Width,Depth\n";

    //         // オブジェクトごとに直方体情報を書き込む
    //         for (int object_id = 0; object_id < object_cuboids.size(); object_id++) {
    //             for (int cube_id = 0; cube_id < object_cuboids[object_id].size(); cube_id++) {
    //                 double height = object_cuboids[object_id][cube_id]->scale(2);
    //                 double width = object_cuboids[object_id][cube_id]->scale(0);
    //                 double depth = object_cuboids[object_id][cube_id]->scale(1);

    //                 // CSVファイルにデータを書き込む
    //                 outputFile << object_id << "," << cube_id << "," << height << "," << width << "," << depth << "\n";
    //             }
    //         }

    //         outputFile.close(); // ファイルをクローズ
    //         ROS_INFO("Object cuboids data saved to %s", filename.c_str());
    //     } else {
    //         ROS_ERROR("Unable to open file %s", filename.c_str());
    //     }
    // }
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ros::NodeHandle nh;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    //image_transport::Publisher image_pub_;
    ros::Subscriber yolo_sub;
    // ros::Subscriber point_sub;
    ros::Subscriber imu_sub;
    
private:
    Eigen::MatrixXd all_lines_raw;   
    MatrixXd obj_bbox_coors;
    // line_msg::LinePoint pointdata;
    yolov5_ros::yolov5_data yolodata;
    //darknet_ros_msgs::BoundingBoxes yolodata;
    sensor_msgs::Imu imudata;
    std::vector<string> object_classes;
    int n;
    Matrix3d R;
    Matrix4d transToWolrd;
    Matrix3d center; //亀山追加
    double x,y,z;

public:
    void pointCallback(const line_msg::LinePoint::ConstPtr& pointdata)
    {
        //ROS_INFO("point ok");
        int xyz;
        xyz = pointdata->startx.data.size();
        all_lines_raw.resize(xyz, 4);
        //Eigen::MatrixXd all_lines_raw(100,4);
        for (int j=0;j<pointdata->startx.data.size();j++)
        {
            all_lines_raw(j,0) = pointdata->startx.data[j];
            all_lines_raw(j,1) = pointdata->starty.data[j];
            all_lines_raw(j,2) = pointdata->endx.data[j];
            all_lines_raw(j,3) = pointdata->endy.data[j];
        }
    }

//yolov5
    void yoloCallback(const yolov5_ros::yolov5_data::ConstPtr& yolodata)
    {
        int s = yolodata->yolo_box_data.data.size();
        n = (s+1)/7;
        // object_classes.resize(n);
        obj_bbox_coors.resize(n,7); 
        for(int b=0;b<n;b++)
        {
            // object_classes.push_back("bottle");
            //単眼用
            // obj_bbox_coors(b,0) = yolodata.data[6*b+1] - (yolodata.data[6*b+3]/2);
            // obj_bbox_coors(b,1) = yolodata.data[6*b+2] - (yolodata.data[6*b+4]/2);
            //複眼用
            obj_bbox_coors(b,0) = yolodata->yolo_box_data.data[7*b+1]; //xmin
            obj_bbox_coors(b,1) = yolodata->yolo_box_data.data[7*b+2]; //ymin

            obj_bbox_coors(b,2) = yolodata->yolo_box_data.data[7*b+3]; //width
            obj_bbox_coors(b,3) = yolodata->yolo_box_data.data[7*b+4]; //height
            obj_bbox_coors(b,4) = yolodata->yolo_box_data.data[7*b+5]; //conf
            obj_bbox_coors(b,5) = yolodata->yolo_box_data.data[7*b]; //class
            // obj_bbox_coors(b,6) = yolodata->object_depth_data.data[b]; //depth
            obj_bbox_coors(b,6) = yolodata->yolo_box_data.data[7*b+6]; //depth kari; //kari

            //2024.7.18 亀山追加
            double xmin = obj_bbox_coors(b,0);
            double ymin = obj_bbox_coors(b,1);
            double depth = obj_bbox_coors(b,6);

            Matrix3d Kalib;
            Kalib << 611.1965, 0, 318.3764,
            0, 611.2900, 234.5255,
            0, 0, 1.0000;
            double hypotenuse = sqrt(abs((center(b,0)*center(b,0))+(center(b,1)*center(b,1))));

            //centerY = ymin + height / 2.0　をピクセル座標系からカメラ座標系へ
            //centerX = xmin + width / 2.0　をピクセル座標系からカメラ座標系へ
            center(b,0) = ((xmin + obj_bbox_coors(b,2) / 2.0) - Kalib(0,2)) * center(b,2) / Kalib(0,0);
            center(b,1) = ((ymin + obj_bbox_coors(b,3) / 2.0) - Kalib(1,2)) * center(b,2) / Kalib(1,1);
            center(b,2) = sqrt(abs((depth*depth)-(hypotenuse*hypotenuse)));

            //std::cout << "x: " << center(b,0) << std::endl;
            //std::cout << "y: " << center(b,1) << std::endl;
            //std::cout << "z: " << center(b,2) << std::endl;

            x = center(b,0);
            y = center(b,1);
            z = center(b,2);
        }
        obj_bbox_coors.leftCols<2>().array() -= 1;    // change matlab coordinate to c++, minus 1
    }
    

//imu
    void imucallback(const sensor_msgs::Imu::ConstPtr& imudata)
    {
        //参考：https://qiita.com/shrimp-f/items/6c6820b88f162731dd94
        double g = 10.0; //重力加速度
        double r,p; //それぞれroll,pitch。下は、それぞれトピックの値から計算
        
        r = abs(atan(imudata->linear_acceleration.y/imudata->linear_acceleration.z));
        p = abs(atan(-imudata->linear_acceleration.x/(sqrt(pow(imudata->linear_acceleration.y,2)+pow(imudata->linear_acceleration.z,2)))));
        //r = atan2(imudata->linear_acceleration.y, imudata->linear_acceleration.z);
        //p = atan2(-imudata->linear_acceleration.x, sqrt(pow(imudata->linear_acceleration.y, 2) + pow(imudata->linear_acceleration.z, 2)));

        // std::cout << "roll: " << r << std::endl;
        // std::cout << "pitch: " << p << std::endl;

        R << cos(p)*cos(0), (sin(r)*sin(p)*cos(0)) - (cos(r)*sin(0)), (cos(r)*sin(p)*cos(0)) +  (sin(r)*sin(0)),
            cos(p)*sin(0), (sin(r)*sin(p)*sin(0)) + (cos(r)*cos(0)), (cos(r)*sin(p)*sin(0)) - (sin(r)*cos(0)),
            -sin(p), sin(r)*cos(p), cos(r)*cos(p);
        
        
        transToWolrd << cos(p)*cos(0), (sin(r)*sin(p)*cos(0)) - (cos(r)*sin(0)), (cos(r)*sin(p)*cos(0)) +  (sin(r)*sin(0)), x ,
           cos(p)*sin(0), (sin(r)*sin(p)*sin(0)) + (cos(r)*cos(0)), (cos(r)*sin(p)*sin(0)) - (sin(r)*cos(0)), y ,
           -sin(p), sin(r)*cos(p), cos(r)*cos(p), z,
           0, 0, 0, 1;

        //std::cout << "x: " << x << std::endl;
        //std::cout << "y: " << y << std::endl;
        //std::cout << "z: " << z << std::endl;

        
        double rad_to_deg = 180.0 / M_PI; // ラジアンから度への変換係数
        // ラジアンを度に変換
        double roll_deg = r * rad_to_deg;
        double pitch_deg = p * rad_to_deg;
        // 出力（デバッグ用)
        std::cout << "roll: " << roll_deg << " degrees" << std::endl;
        std::cout << "pitch: " << pitch_deg << " degrees" << std::endl;
        
    }


//datknet_ros
    // void yoloCallback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& yolodata)
    // {
    //     n = yolodata->bounding_boxes.size();
    //     object_classes.resize(n);
    //     obj_bbox_coors.resize(n,5);                // hard coded
    //     for(int b=0;b<n;b++)
    //     {
    //         obj_bbox_coors(b,0) = yolodata->bounding_boxes[b].xmin;
    //         obj_bbox_coors(b,1) = yolodata->bounding_boxes[b].ymin;
    //         obj_bbox_coors(b,2) = yolodata->bounding_boxes[b].xmax - yolodata->bounding_boxes[b].xmin;
    //         obj_bbox_coors(b,3) = yolodata->bounding_boxes[b].ymax - yolodata->bounding_boxes[b].ymin;
    //         obj_bbox_coors(b,4) = yolodata->bounding_boxes[b].probability;
    //     }

    //     for(int s=0;s<n;s++)
    //     {
    //         object_classes.push_back(yolodata->bounding_boxes[s].Class);
    //     }
    //     // object_classes2 = yolodata->bounding_boxes[1].Class;
    //     obj_bbox_coors.leftCols<2>().array() -= 1;    // change matlab coordinate to c++, minus 1
    //     //std::cout << yolodata->bounding_boxes[0].Class << std::endl;
    // }

    Imageimport()
        : it_(nh)
    {
        // point_sub = nh.subscribe("/point_msg", 10, &Imageimport::pointCallback, this);
        yolo_sub = nh.subscribe("mecanum2/multi_box_command", 10, &Imageimport::yoloCallback, this);
        //yolo_sub = nh.subscribe("/darknet_ros/bounding_boxes", 10, &Imageimport::yoloCallback, this);
        image_sub_ = it_.subscribe("mecanum2/camera/color/image_raw", 1, &Imageimport::imageCuboid, this);
        //image_pub_ = it_.advertise("/image_converter/output_video", 1);
        imu_sub = nh.subscribe("mecanum2/camera/imu", 1, &Imageimport::imucallback, this);
    }

    ~Imageimport()
    {
        cv::destroyWindow("frame_all_cubes_img");
    }

   


    void imageCuboid(const sensor_msgs::ImageConstPtr& msg)
    {
        cv_bridge::CvImagePtr rgb_img;
        try
        {
            rgb_img = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch(cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        Matrix3d Kalib;
        //realsense
        Kalib << 611.1965, 0, 318.3764,
        0, 611.2900, 234.5255,
        0, 0, 1.0000;
        //motomoto
        // Kalib << 771.3686, 0, 410.0889,
        //     0, 770.9415, 223.0994,
        //     0, 0, 1.0000;

        //Matrix4d transToWolrd;
        //transToWolrd << 1, 0.0011, 0.0004, 0, // hard coded  NOTE if accurate camera roll/pitch, could sample it!
        //    0, -0.3376, 0.9413, 0,
        //    0.0011, -0.9413, -0.3376, 1.35,
        //    0, 0, 0, 1;

        //line start
        nh.param<bool>("use_LSD_algorithm",use_LSD_algorithm,true);

        line_lbd_detect* line_lbd_ptr = new line_lbd_detect(numOfOctave_,Octave_ratio); 
        line_lbd_ptr->use_LSD = use_LSD_algorithm;
        line_lbd_ptr->line_length_thres = 15;  // remove short edges

        // using my line detector class, could select LSD or edline.
        cv::Mat out_edges;
        std::vector< KeyLine> keylines_raw,keylines_out;
        line_lbd_ptr->detect_raw_lines(rgb_img->image,keylines_raw);
        line_lbd_ptr->filter_lines(keylines_raw,keylines_out);  // remove short lines

        int xyz;
        xyz = keylines_out.size();
        all_lines_raw.resize(xyz, 4);

        for (int j=0;j<xyz;j++)
        {
            all_lines_raw(j,0) = keylines_out[j].startPointX;
            all_lines_raw(j,1) = keylines_out[j].startPointY;
            all_lines_raw(j,2) = keylines_out[j].endPointX;
            all_lines_raw(j,3) = keylines_out[j].endPointY;
            // resultsFile <<keylines_out[j].startPointX <<"\t" <<keylines_out[j].startPointY  <<"\t"
            //         <<keylines_out[j].endPointX   <<"\t" <<keylines_out[j].endPointY    <<endl;
        }

        ////////堀江追加↓
        // all_lines_rawのデータを画面に表示
        // std::cout << "all_lines_raw data:" << std::endl;
        // std::cout << all_lines_raw << std::endl;
        /////////////////////////////////////////////////////////////////////////////堀江
        //line finish

        ca::Profiler::enable();

        int frame_index = 0;
        char frame_index_c[256];
        sprintf(frame_index_c, "%04d", frame_index); // format into 4 digit

        // point_sub = nh.subscribe("/point_msg", 10, &Imageimport::pointCallback, this);
        // yolo_sub = nh.subscribe("/darknet_ros/bounding_boxes", 10, &Imageimport::yoloCallback, this);

        //obj_bbox_coors << 188, 189, 201, 311, 0.8800; // [x y w h prob]
        //read_all_number_txt(base_folder + "edge_detection/LSD/" + frame_index_c + "_yolo.txt", obj_bbox_coors);
        // obj_bbox_coors.leftCols<2>().array() -= 1;    // change matlab coordinate to c++, minus 1

        //std::cout << all_lines_raw << std::endl;

        //std::cout << obj_bbox_coors << std::endl;

        // ROS_INFO("yolodata");
		// std::cout << obj_bbox_coors << std::endl;

        detect_3d_cuboid detect_cuboid_obj;
        detect_cuboid_obj.whether_plot_detail_images = false;//new　これはいらんなんかグレーの
        detect_cuboid_obj.whether_plot_final_images = true;
        detect_cuboid_obj.print_details = false; // false  true new
        detect_cuboid_obj.set_calibration(Kalib);
        //detect_cuboid_obj.set_cam_pose(transToWolrd);
        detect_cuboid_obj.whether_sample_bbox_height = true; //2.2new trueにした
        detect_cuboid_obj.whether_sample_cam_roll_pitch = true;

        std::vector<ObjectSet> all_object_cuboids; //直方体描画に超重要なパラメータ
        detect_cuboid_obj.detect_cuboid(rgb_img->image, transToWolrd, obj_bbox_coors, all_lines_raw, all_object_cuboids);

        ///堀江追加/////////12.28//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////これ大事
        // all_object_cuboids の内容を表示
        for (int object_id = 0; object_id < all_object_cuboids.size(); object_id++) {
            std::cout << "Object ID: " << object_id << std::endl;

            for (int cube_id = 0; cube_id < all_object_cuboids[object_id].size(); cube_id++) {
                std::cout << "Cuboid ID: " << cube_id << std::endl;
                std::cout << *(all_object_cuboids[object_id][cube_id]) << std::endl; // cuboid の情報を表示

                  // 追加: 直方体の寸法を表示
                double height = all_object_cuboids[object_id][cube_id]->scale(2);
                double width = all_object_cuboids[object_id][cube_id]->scale(0);
                double depth = all_object_cuboids[object_id][cube_id]->scale(1);

                // cuboidオブジェクトにサイズ情報をセット　試す
                all_object_cuboids[object_id][cube_id]->scale << width, depth, height;

                std::cout << "Detected Dimensions:" << std::endl;
                std::cout << "Height: " << height << std::endl;
                std::cout << "Width: " << width << std::endl;
                std::cout << "Depth: " << depth << std::endl;

            }
        }
        ////////////////
        /////////////堀江検証2↓/////
        // detect_3d_cuboidクラスのdetect_cuboidメソッド内の直方体サイズ推定部分///////////////////////////////////////////////////
            // all_object_cuboidsの情報をCSVファイルに保存
        std::string filename = "3object_cuboids_data.csv"; // ファイル名を適切なものに変更
        saveObjectCuboidsToCSV(filename, all_object_cuboids);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




        //std::cout << all_object_cuboids << std::endl;
        
        // for(string &a: object_classes)
        // {
        //     cout << a << endl;
        //     //std::cout << object_classes2 << std::endl;
        // }

        //image_pub_.publish(rgb_img->toImageMsg());
        ca::Profiler::print_aggregated(std::cout);
        cv::waitKey(3);
    }

};

//////csv

/////
int main(int argc, char **argv)
{
    ros::init(argc, argv, "detect_3d_cuboid");

    Imageimport ic;
    //cv::Mat rgb_img = cv::imread(base_folder + frame_index_c + "_rgb_raw.jpg", 1);

    ros::spin();
    return 0;
}
