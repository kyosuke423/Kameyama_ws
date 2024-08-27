#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile
from tf2_ros import TransformListener, Buffer, TransformStamped, LookupException, ExtrapolationException, ConnectivityException
from geometry_msgs.msg import Twist, TransformStamped as GeometryTransformStamped
import math

class TF2TwistNode(Node):

    def __init__(self):
        super().__init__('tf2twist')
        qos_profile = QoSProfile(depth=10)
        self.tfBuffer = Buffer()
        self.listener = TransformListener(self.tfBuffer, self)
        self.twist_data = Twist()
        self.pub_cmd_vel = self.create_publisher(Twist, "/mecanum2/cmd_vel", qos_profile)

    def quaternion_to_euler(self, q0, q1, q2, q3):
        q0q0 = q0 * q0
        q0q1 = q0 * q1
        q0q2 = q0 * q2
        q0q3 = q0 * q3
        q1q1 = q1 * q1
        q1q2 = q1 * q2
        q1q3 = q1 * q3
        q2q2 = q2 * q2
        q2q3 = q2 * q3
        q3q3 = q3 * q3

        a = math.atan2(2.0 * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3)
        b = math.asin(2.0 * (q0q2 - q1q3))
        c = math.atan2(2.0 * (q2q3 + q0q1), q0q0 - q1q1 - q2q2 + q3q3)

        return a, b, c

    def run(self):
        while rclpy.ok():
            try:
                now = self.get_clock().now() - rclpy.duration.Duration(seconds=0,nanoseconds=1000000)
                trans = self.tfBuffer.lookup_transform('odom', 'base_link', now, rclpy.duration.Duration(seconds=0, nanoseconds= 0))
                roll, pitch, yaw = self.quaternion_to_euler(trans.transform.rotation.x, trans.transform.rotation.y, trans.transform.rotation.z, trans.transform.rotation.w)

                if yaw > 0.3:
                    self.twist_data.angular.z = 70.0
                elif yaw < -0.3:
                    self.twist_data.angular.z = -70.0
                else:
                    self.twist_data.angular.z = 0.0
                self.pub_cmd_vel.publish(self.twist_data)
            except (LookupException, ExtrapolationException, ConnectivityException) as e:
                self.get_logger().error(f"Error: {str(e)}")

def main(args=None):
    rclpy.init(args=args)
    tf2twist = TF2TwistNode()
    try:
        tf2twist.run()
    except KeyboardInterrupt:
        pass

    tf2twist.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
