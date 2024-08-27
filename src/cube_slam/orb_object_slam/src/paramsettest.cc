#include <ros/ros.h>
#include <ar_track_alvar_msgs/AlvarMarker.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf2_msgs/TFMessage.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Transform.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>
#include <tf2_ros/transform_listener.h>

double x;

class ListenTest
{
public:
  ListenTest() : nh_(), tfBuffer_(), tfListener_(tfBuffer_)
  {
    timer_ = nh_.createTimer(ros::Duration(0.5), [&](const ros::TimerEvent& e) {
      geometry_msgs::TransformStamped transformStamped;
      try
      {
        transformStamped = tfBuffer_.lookupTransform("ar_marker_0","camera_color_optical_frame",ros::Time(0));
      }
      catch (tf2::TransformException& ex)
      {
        ROS_WARN("%s", ex.what());
        return;
      }
      auto& trans = transformStamped.transform.translation;
      auto& quat = transformStamped.transform.rotation;
      ROS_INFO("world->dynamic_tf: %f %f %f", trans.x, trans.y, trans.z);
      ROS_INFO("world->dynamic_tf_quat: %f %f %f %f", quat.x, quat.y, quat.z, quat.w);

      geometry_msgs::Pose object_d, object_w;
      object_d.position.z = 1.0;
      object_d.orientation.w = 1.0;
      tf2::doTransform(object_d, object_w, transformStamped);
      x = object_w.position.x;
      ROS_INFO("object_w x:%f, y:%f, z:%f", object_w.position.x, object_w.position.y, object_w.position.z);

      // nh_.setParam("/init_x", -object_w.position.x);
      // nh_.setParam("/init_y", -object_w.position.y);
      // nh_.setParam("/init_z", -object_w.position.z);
      nh_.setParam("/init_x", trans.x);
      nh_.setParam("/init_y", trans.y);
      nh_.setParam("/init_z", trans.z);
      nh_.setParam("/init_qx", quat.x);
      nh_.setParam("/init_qy", quat.y);
      nh_.setParam("/init_qz", quat.z);
      nh_.setParam("/init_qw", quat.w);
    });
  }

private:
  ros::NodeHandle nh_;
  ros::Timer timer_;
  tf2_ros::Buffer tfBuffer_;
  tf2_ros::TransformListener tfListener_;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "my_tf2_listener");
  ListenTest listen_test;
  ros::Rate loop_rate(10);
  while(x == 0)
  {
    std::cout << "set up..." << std::endl;
    ros::spinOnce();
    loop_rate.sleep();
  }
  // return 0;
};

// float x, y, z, qx, qy, qz, qw;

// void EulerAnglesToQuaternion(double roll, double pitch, double yaw,
//                             double& q0, double& q1, double& q2, double& q3)
// {
//     double cosRoll = cos(roll / 2.0);
//     double sinRoll = sin(roll / 2.0);
//     double cosPitch = cos(pitch / 2.0);
//     double sinPitch = sin(pitch / 2.0);
//     double cosYaw = cos(yaw / 2.0);
//     double sinYaw = sin(yaw / 2.0);

//     // q0 = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
//     // q1 = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
//     // q2 = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
//     // q3 = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
//     q0 = cosRoll * sinPitch * sinYaw + sinRoll * cosPitch * cosYaw;
//     q1 = -sinRoll * cosPitch * sinYaw + cosRoll * sinPitch * cosYaw;
//     q2 = cosRoll * cosPitch * sinYaw + sinRoll * sinPitch * cosYaw;
//     q3 = -sinRoll * sinPitch * sinYaw + cosRoll * cosPitch * cosYaw;
// }

// void geometry_quat_to_rpy(double& roll, double& pitch, double& yaw, geometry_msgs::Quaternion geometry_quat)
// {
// 	tf::Quaternion quat;
// 	quaternionMsgToTF(geometry_quat, quat);
// 	tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);  //rpy are Pass by Reference
// }

// geometry_msgs::Quaternion rpy_to_geometry_quat(double roll, double pitch, double yaw)
// {
// 	tf::Quaternion quat=tf::createQuaternionFromRPY(roll,pitch,yaw);
// 	geometry_msgs::Quaternion geometry_quat;
// 	quaternionTFToMsg(quat, geometry_quat);
// 	return geometry_quat;
// }

// tf2::Transform xyz_quat_to_tf2(double x, double y, double z, double qx, double qy, double qz, double qw){
//   tf2::Transform tf2(tf2::Quaternion(qx, qy, qz, qw), tf2::Vector3(x, y, z));
//   return tf2;
// }

// tf2::Transform tf2_invert(tf2::Transform tf2){
//   return tf2.inverse();
// }

// void showTF(tf2::Transform tf){
//   double lx=tf.getOrigin().x();
//   double ly=tf.getOrigin().y();
//   double lz=tf.getOrigin().z();

//   double scale = sqrt(1 - tf.getRotation().getW() * tf.getRotation().getW());
//   double rx=tf.getRotation().getAxis().x() * scale;
//   double ry=tf.getRotation().getAxis().y() * scale;
//   double rz=tf.getRotation().getAxis().z() * scale;
//   double rw=tf.getRotation().getW();
//   printf("pos(x,y,z):   %f, %f, %f\n", lx, ly, lz);
//   printf("ori(x,y,z,w): %f, %f, %f %f\n", rx, ry, rz, rw);

//   x = lx;
//   y = ly;
//   z = lz;
//   qx = rx;
//   qy = ry;
//   qz = rz;
//   qw = rw;
// }

// void init_pose(const tf2_msgs::TFMessage::ConstPtr & msg)
// {
//   geometry_msgs::TransformStamped pose_msg;
//   geometry_msgs::Transform camera_pose;
//   geometry_msgs::Quaternion camera_quat;
//   geometry_msgs::Quaternion set_camera;
//   tf2::Transform tf_ar, tf_camera;
//   double roll1, pitch1, yaw1;
//   double x1,y1,z1,qx1,qy1,qz1,qw1;
//   pose_msg = msg->transforms[0];

//   if(pose_msg.child_frame_id == "ar_marker_0")
//   {
//     camera_pose = pose_msg.transform;
//     x1 = camera_pose.translation.x;
//     y1 = camera_pose.translation.y;
//     z1 = camera_pose.translation.z;
//     qx1 = camera_pose.rotation.x;
//     qy1 = camera_pose.rotation.y;
//     qz1 = camera_pose.rotation.z;
//     qw1 = camera_pose.rotation.w;

//     tf_ar = xyz_quat_to_tf2(x1,y1,z1,qx1,qy1,qz1,qw1);
//     tf_camera = tf2_invert(tf_ar);
//     showTF(tf_camera);
//     // camera_quat.x = camera_pose.rotation.x;
//     // camera_quat.y = camera_pose.rotation.y;
//     // camera_quat.z = camera_pose.rotation.z;
//     // camera_quat.w = camera_pose.rotation.w;

//     // std::cout << "qx,qy,qz,qw : " << camera_quat.x << ", " << camera_quat.y << ", " << camera_quat.z << ", " << camera_quat.w<< std::endl;

//     // geometry_quat_to_rpy(roll1, pitch1, yaw1, camera_quat);
//     // std::cout << "roll, pitch, yaw : " << roll1 << ", " << pitch1 << ", " << yaw1 << std::endl;

//     // set_camera = rpy_to_geometry_quat(roll1 *-1, pitch1 , 0);

//     // qx = set_camera.x;
//     // qy = set_camera.y;
//     // qz = set_camera.z;
//     // qw = set_camera.w;

//     // EulerAnglesToQuaternion(roll1 *-1, pitch1, yaw1, x1, y1, z1, w1);
//     // std::cout << "x,y,z,w : " << x1 << ", " <<  y1 << ", " << z1 <<", " << w1 << std::endl;

//     // qx = x1;
//     // qy = y1;
//     // qz = z1;
//     // qw = w1;
//   }
// }

// int main(int argc, char** argv) {
//   ros::init(argc, argv, "rosparam");
//   ros::NodeHandle nh;

//   // ros::Subscriber init_sub = nh.subscribe("/ar_pose_marker", 10, init_pose);
//   ros::Subscriber init_sub = nh.subscribe("/tf", 10, init_pose);
//   // 取得したいパラメータの値に対応する型の変数を引数で渡す

//   ros::Rate loop_rate(1);
//   while(x == 0){
//     std::cout << "set up now..." << std::endl;
//     ros::spinOnce();
//     loop_rate.sleep();
//   }

//   nh.setParam("/init_x", x);
//   nh.setParam("/init_y", y);
//   nh.setParam("/init_z", z);
//   nh.setParam("/init_qx", qx);
//   nh.setParam("/init_qy", qy);
//   nh.setParam("/init_qz", qz);
//   nh.setParam("/init_qw", qw);

//   std::cout << "x : " << x << std::endl;
//   std::cout << "y : " << y << std::endl;
//   std::cout << "z : " << z << std::endl;
//   std::cout << "qx : " << qx << std::endl;
//   std::cout << "qy : " << qy << std::endl;
//   std::cout << "qz : " << qz << std::endl;
//   std::cout << "qw : " << qw << std::endl;

//   std::cout << "param set!" << std::endl;
// }