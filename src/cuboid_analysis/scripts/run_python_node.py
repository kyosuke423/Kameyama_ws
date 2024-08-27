#!/usr/bin/env python3
import rospy
import time
import os

def main():
    rospy.init_node('run_python_node', anonymous=True)
    delay = rospy.get_param('~delay', 10)  # デフォルトの遅延時間（秒）
    time.sleep(delay)
    os.system('python3 /home/dars/kameyama_ws/src/cuboid_analysis/scripts/d-op.py')  # Pythonスクリプトのパス

if __name__ == '__main__':
    main()
