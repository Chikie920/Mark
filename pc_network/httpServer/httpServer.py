'''
author: chikie
date: 2021/9/19
project_name: httpServer
description: computer network homework
'''

import socket
import re

fileList = ['index.html', '404.html']

welcomeSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#服务器使用IPV4和Tcp协议

welcomeSocket.bind(('127.0.0.1', 2333))
#绑定ip与端口

welcomeSocket.listen(1)
print('listing...')

def create_responsed(target):
    file = open(target)
    content = file.read()
    responsed = 'HTTP/1.1 200 OK\nConnection: keep-alive\nContent-Length: %d\nContent-Type: text/html\n\n%s' % (len(content), content)
    return responsed

while(True):
    mesg = ''
    newSocket, clientAddress = welcomeSocket.accept()
    print('New client address: ', clientAddress)
    mesg = newSocket.recv(2048).decode()
    # print('client: ', mesg)
    requestTarget = re.search(r'GET /(.*)? ', mesg)
    requestTarget = requestTarget.group(1)
    if requestTarget in fileList:
        responsed = create_responsed(requestTarget)
    else:
        responsed = 'HTTP/1.1 404 Found'
    newSocket.send(responsed.encode())

