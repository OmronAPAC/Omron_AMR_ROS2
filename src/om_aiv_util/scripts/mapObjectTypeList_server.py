#!/usr/bin/env python
from socketconnection_class import ConnectSocket, connecttcp
s = connecttcp.sock
import socket
import threading
import time
import re
import sys
from std_msgs.msg import String
BUFFER_SIZE = 1024
# ip_address = rospy.get_param("ip_address")
# port = rospy.get_param("port")
ip_address = "172.21.5.125"
port = 7171
connecttcp.connect(str(ip_address), port)

from om_aiv_util.srv import Service,ServiceResponse
import rospy

def handle_mapObjectTypeList(req):
    global fault
    fault = req.a
    mapObjectTypeList()
    # return ServiceResponse(req.a)
    return rcv

def mapObjectTypeList_server():
    rospy.init_node('mapObjectTypeList_server')
    s = rospy.Service('mapObjectTypeList', Service, handle_mapObjectTypeList)
    rospy.spin()

def mapObjectTypeList():
    global rcv
    pub = rospy.Publisher('arcl_mapObjectTypeList', String, queue_size=10)
    # rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    command = "mapObjectTypeList"
    print "Running command: ", command
    command = command.encode('ascii')
    s.send(command+b"\r\n")
    try:
        data = s.recv(BUFFER_SIZE)
        rcv = data.encode('ascii', 'ignore')
        while not rospy.is_shutdown():
            #check for required data
            if "End of MapObjectTypeList" in rcv:
                print rcv
                return rcv
                break
            else:
                data = s.recv(BUFFER_SIZE)
                rcv = rcv + data.encode('ascii', 'ignore')

    except socket.error as e:
        print("Connection  failed")
        return e

if __name__ == "__main__":
    mapObjectTypeList_server()