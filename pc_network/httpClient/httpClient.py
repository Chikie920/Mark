'''
author: chikie
date: 2021/9/19
project_name: httpClient
description: computer network homework
'''

import socket

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip = '127.0.0.1'
port = 2333
mesg = ''
clientSocket.connect((ip, port))
print('connect successful')
clientSocket.send('hello server'.encode())
mesg = clientSocket.recv(1024)
print('server: ', mesg.decode())
clientSocket.close()