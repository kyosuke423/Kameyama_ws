#!/usr/bin/env python

import rospy
import tf2_ros
import geometry_msgs.msg

def broadcast_static_world_transform():
    rospy.init_node('world_transform_broadcaster')
    tf_broadcaster = tf2_ros.StaticTransformBroadcaster()

    # 初期のworld座標系の変換 (静的)
    world_transform = geometry_msgs.msg.TransformStamped()
    world_transform.header.stamp = rospy.Time.now()
    world_transform.header.frame_id = "world"  # world座標系のフレームID
    world_transform.child_frame_id = "world"  # world座標系の子フレームID

    # 初期位置 (x, y, z)
    world_transform.transform.translation.x = 0.0
    world_transform.transform.translation.y = 0.0
    world_transform.transform.translation.z = 0.0

    # 初期姿勢 (クォータニオン表現)
    world_transform.transform.rotation.x = 0.0
    world_transform.transform.rotation.y = 0.0
    world_transform.transform.rotation.z = 0.0
    world_transform.transform.rotation.w = 1.0

    tf_broadcaster.sendTransform([world_transform])

    rospy.spin()

if __name__ == '__main__':
    try:
        broadcast_static_world_transform()
    except rospy.ROSInterruptException:
        pass
