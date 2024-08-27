import rospy
from tutorial_python.srv import multiplier,multiplierResponse

def multiplier_client(x,y):
    rospy.init_node("client_node")
    rospy.wait_for_service("multiplier")
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        try:
            multiplier_two_ints = rospy.ServiceProxy("multiplier",multiplier)
            response = multiplier_two_ints(x,y)
            rospy.loginfo(response.result)
            rate.sleep()
        except rospy.ServiceException as e:
            print("Service call failed %s",e)

if __name__=='__main__':
    multiplier_client(7,2)