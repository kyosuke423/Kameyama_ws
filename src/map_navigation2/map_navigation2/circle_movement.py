import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import math

class CircleMovement(Node):
    def __init__(self):
        super().__init__('circle_movement')
        self.odom_subscription = self.create_subscription(
            Odometry,
            '/mecanum2/odom1',
            self.odom_callback,
            10
        )
        self.publisher_ = self.create_publisher(Twist, '/mecanum2/cmd_vel', 10)
        self.speed = 0.1  # 速度設定 (例: 0.1 m/s)
        self.target_direction = math.radians(90)  # 目標方向 (例: 90度をラジアンに変換)

        # P制御のゲイン設定
        self.Kp = 0.3

    def odom_callback(self, msg):
        # 自己位置情報を取得
        if msg.pose.pose.orientation:
            orientation = msg.pose.pose.orientation
            quaternion = (orientation.x, orientation.y, orientation.z, orientation.w)
            euler = self.quaternion_to_euler(quaternion)
            current_yaw = euler[2]  # z軸周りの角度 (ラジアン)

            # 目標角度と現在の角度の差を計算
            angle_diff = self.calculate_angle_difference(self.target_direction, current_yaw)

            # 速度制御用のTwistメッセージを生成
            twist = Twist()
            twist.linear.x = self.speed  # 前進方向の速度

            # P制御により角速度を計算
            angular_speed = self.Kp * angle_diff
            twist.angular.z = angular_speed  # 角速度

            # 制御した速度情報を発行
            self.publisher_.publish(twist)
        else:
            self.get_logger().warn("姿勢情報が見つかりませんでした。")

    def quaternion_to_euler(self, quaternion):
        x, y, z, w = quaternion
        t0 = +2.0 * (w * x + y * z)
        t1 = +1.0 - 2.0 * (x * x + y * y)
        roll = math.atan2(t0, t1)

        t2 = +2.0 * (w * y - z * x)
        t2 = +1.0 if t2 > +1.0 else t2
        t2 = -1.0 if t2 < -1.0 else t2
        pitch = math.asin(t2)

        t3 = +2.0 * (w * z + x * y)
        t4 = +1.0 - 2.0 * (y * y + z * z)
        yaw = math.atan2(t3, t4)

        return roll, pitch, yaw

    def calculate_angle_difference(self, target_angle, current_angle):
        # 角度の差を計算する関数（-πからπの範囲で正確な差を計算）
        diff = target_angle - current_angle
        while diff > math.pi:
            diff -= 2 * math.pi
        while diff < -math.pi:
            diff += 2 * math.pi
        return diff

def main(args=None):
    rclpy.init(args=args)
    circle_movement = CircleMovement()
    try:
        rclpy.spin(circle_movement)
    except KeyboardInterrupt:
        pass
    finally:
        circle_movement.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
