#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped
import tf2_ros
from builtin_interfaces.msg import Time  # 追加

class TFListener(Node):
    def __init__(self):
        super().__init__('tf_listener')
        self.tf_buffer = tf2_ros.Buffer()
        self.tf_listener = tf2_ros.TransformListener(self.tf_buffer, self)

    def run(self):
        rate = self.create_rate(10.0)
        while rclpy.ok():
            try:
                # TFを取得したいフレーム間の座標変換情報を指定
                transform_stamped = self.tf_buffer.lookup_transform("mecanum2/odom", "mecanum2/base_link", Time())
            except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException) as e:
                self.get_logger().warn(f"Failed to lookup transform: {str(e)}")
                continue

            # 取得した座標変換情報を使って処理を行う
            # ここでは単に画面に表示するだけです
            trans = transform_stamped.transform.translation
            rot = transform_stamped.transform.rotation
            self.get_logger().info(f"Translation: {trans}, Rotation: {rot}")

            rate.sleep()

def main(args=None):
    rclpy.init(args=args)
    tf_listener = TFListener()

    try:
        tf_listener.run()
    except KeyboardInterrupt:
        pass

    tf_listener.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
