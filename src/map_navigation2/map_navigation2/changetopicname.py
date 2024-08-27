import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped

#これはトピックの名前を変えるやつ
class TFRemapper(Node):
    def __init__(self):
        super().__init__('tf_remapper')
        self.publisher = self.create_publisher(TransformStamped, '/tf_static', 10)
        self.subscription = self.create_subscription(TransformStamped, '/mecanum2/tf_static', self.tf_callback, 10)

    def tf_callback(self, msg):
        try:
            # フレームIDを変更して /tf にパブリッシュします
            msg.header.frame_id = '/tf'
            self.publisher.publish(msg)
        except Exception as e:
            self.get_logger().error(f"Error in tf_callback: {str(e)}")

def main(args=None):
    rclpy.init(args=args)
    try:
        tf_remapper = TFRemapper()
        rclpy.spin(tf_remapper)
    except Exception as e:
        print(f"Error in main: {str(e)}")
    finally:
        if tf_remapper:
            tf_remapper.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
