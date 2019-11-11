#!/usr/bin/env python
import sys
import rospy
from om_aiv_util.srv import *
def popupSimple_client(a, b , c, d):
    rospy.wait_for_service('popupSimple')
    try:
        add_two_ints = rospy.ServiceProxy('popupSimple', Service4)
        resp1 = add_two_ints(a, b, c, d)
        return resp1.device
    except rospy.ServiceException, error:
        print "Service call failed: %s"%error

def usage():
    return "%s <\"title\"> <\"message\"> <\"buttonLabel\"> <timeout>"%sys.argv[0]

if __name__ == "__main__":
    if len(sys.argv) == 5:
        a = str(sys.argv[1])
        b = str(sys.argv[2])
        c = str(sys.argv[3])
        d = str(sys.argv[4])

    else:
        print usage()
        sys.exit(1)
    print "running command"
    print popupSimple_client(a, b , c, d)