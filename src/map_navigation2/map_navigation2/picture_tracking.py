import rclpy
from rclpy.node import Node
from nav_msgs.msg import Path, OccupancyGrid, Odometry
from std_msgs.msg import Float64
import math
import time
import os
from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist

class PictureTracking(Node):
    def __init__(self):
        super().__init__('picture_tracking')
        # subscribeの宣言
        # self.tracking_subscription = self.create_subscription(
        #     Image,
        #     '/mecanum2/yolo/image',
        #     self.tracking_callback,
        #     10
        # )
        self.odom_subscription = self.create_subscription(
            Odometry,
            '/mecanum2/odom1',
            self.tracking_callback,
            10
        )
        self.publisher_ = self.create_publisher(Twist, '/mecanum2/cmd_vel', 10)

    def tracking_callback(self, odom):
        # if not self.occupancy_grid_:
        #     self.get_logger().warn('Occupancy Grid Map not received')
        #     return

        # total_entropy = 0.0
        # for pose in path.poses:
        #     cell_index = self.get_cell_index_from_pose(pose)
        #     if cell_index != -1:
        #         time.sleep(0.4)
        #         occupancy_prob = self.get_occupancy_probability(cell_index)
        #         cell_entropy = self.calculate_cell_entropy(occupancy_prob)
        #         total_entropy += cell_entropy

        # self.get_logger().info('Calculation finishe and total entropy publish')
        land = odom.pose.pose.position.x
        tracking_msg = Twist()
        if (land > 1.0):
            tracking_msg.linear.x = 0.0
            tracking_msg.angular.z = 0.0
            self.get_logger().info('stop')

        elif (land <= 1.0):
            tracking_msg.linear.x = 0.1
            self.get_logger().info('move')

        self.publisher_.publish(tracking_msg)

    # def get_cell_index_from_pose(self, pose):
    #     if not self.occupancy_grid_:
    #         return -1
    #     resolution = self.occupancy_grid_.info.resolution
    #     origin_x = self.occupancy_grid_.info.origin.position.x
    #     origin_y = self.occupancy_grid_.info.origin.position.y

    #     map_x = int((pose.pose.position.x - origin_x) / resolution)
    #     map_y = int((pose.pose.position.y - origin_y) / resolution)

    #     map_width = self.occupancy_grid_.info.width
    #     map_height = self.occupancy_grid_.info.height

    #     self.get_logger().info('OGM Initialize')

    #     if (
    #         map_x < 0 or map_x >= map_width or
    #         map_y < 0 or map_y >= map_height
    #     ):
    #         self.get_logger().info('Out of map range')
    #         return -1

    #     cell_index = map_y * map_width + map_x 
    #     return cell_index

    # def get_occupancy_probability(self, cell_index):
    #     occupancy_value = self.occupancy_grid_.data[cell_index]

    #     if occupancy_value == -1:
    #         self.get_logger().info('Arranging Map Costs Unknown')
    #         occupancy_prob = 0.5
    #         return occupancy_prob
        
    #     # elif 100 >= occupancy_value >= 99:
    #     #     self.get_logger().info('Arranging Map High Costs')
    #     #     occupancy_prob = 0.99
    #     #     return occupancy_prob
        
    #     # elif 0 <= occupancy_value <= 1:
    #     #     self.get_logger().info('Arranging Map Low Costs')
    #     #     occupancy_prob = 0.01
    #     #     return occupancy_prob
        
    #     else:
    #         self.get_logger().info('Arranging Map Normal Costs')
    #         occupancy_prob = float(occupancy_value) / 100
    #         return occupancy_prob

    # def calculate_cell_entropy(self, occupancy_prob):
    #     if occupancy_prob == 0.0 or occupancy_prob == 1.0:
    #         cell_entropy = 0.0
    #         return cell_entropy
        
    #     self.get_logger().info('Entropy calculation')

    #     cell_b_entropy = -occupancy_prob * math.log2(occupancy_prob) - (1.0 - occupancy_prob) * math.log2(1.0 - occupancy_prob)
    #     cell_entropy = cell_b_entropy / 2
    #     return cell_entropy


def main(args=None):
    rclpy.init(args=args)
    
    picture_tracking = PictureTracking()
    rclpy.spin(picture_tracking)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
