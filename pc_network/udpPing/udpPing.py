'''
author: chikie
date: 2021/9/20
project_name: UdpPing Client
description: computer network homework
'''

import socket
import time

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
clientSocket.settimeout(1)
serverIP = '127.0.0.1'
serverPort = 2333

for n in range(1, 11):
    sendTime = time.time()
    pingMsg = 'Ping '+str(n)+' '+str(sendTime)
    clientSocket.sendto(pingMsg.encode(), (serverIP, serverPort))
    try:
        serverMsg, address = clientSocket.recvfrom(1024)
        print('来自 %s 的回复: RTT=%.5f'%(address, time.time()-sendTime))
    except Exception as error:
        print('Time is out ')

clientSocket.close()

