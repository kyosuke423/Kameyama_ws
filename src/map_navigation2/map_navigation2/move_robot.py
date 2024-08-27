import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry

class MoveRobot(Node):

    def __init__(self):
        super().__init__('move_robot')
        self.subscription = self.create_subscription(
            Odometry,
            '/mecanum2/odom1',
            self.odom_callback,
            10)
        self.publisher_ = self.create_publisher(Twist, '/mecanum2/cmd_vel', 10)
        self.odom_data = None
        self.start_time = None
        self.move_duration = 15.0  # Duration for movement in seconds
        #10秒だと約４５度、4秒くらい？？
        # self.linear_speed = -0.1  # Adjust the linear velocity as needed
        self.shutdown_timer = None  # Timer to shutdown the node

    def odom_callback(self, msg):
        self.odom_data = msg
        self.move_x()  # Call move_x() whenever new odometry data is received

    def move_x(self):
        if self.start_time is None:
            self.start_time = self.get_clock().now().to_msg()

        if self.odom_data:
            twist = Twist()
            #twist.linear.y = 0.1
            #twist.angular.z = -0.1
            #もともと
            twist.linear.y = 0.03
            twist.angular.z = -0.03

            # Calculate the time elapsed
            current_time = self.get_clock().now().to_msg()
            elapsed_time = (current_time.sec - self.start_time.sec) + (current_time.nanosec - self.start_time.nanosec) / 1e9

            # Move for specified duration
            if elapsed_time <= self.move_duration:
                self.publisher_.publish(twist)
                self.get_logger().info('Moving...')
            else:
                # Stop after specified duration
                stop_twist = Twist()
                self.publisher_.publish(stop_twist)
                self.get_logger().info('Stopped moving')
                # Shutdown the node after the movement
                self.shutdown_node()

    def shutdown_node(self):
        self.get_logger().info('Shutting down node...')
        self.destroy_node()
        rclpy.shutdown()




#####mainのプログラム###########################################
def main(args=None):
    rclpy.init(args=args)
    move_robot = MoveRobot()
    try:
        rclpy.spin(move_robot)
    except KeyboardInterrupt:
        pass
    finally:
        move_robot.shutdown_node()

if __name__ == '__main__':
    main()
