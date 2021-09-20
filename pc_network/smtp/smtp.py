'''
author: chikie
date: 2021/9/20
project_name: SMTP Client
description: computer network homework
'''

import socket

smtpIP = 'smtp.qq.com'
smtpPort = 587

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket.connect((smtpIP, smtpPort))
smtp_resp = clientSocket.recv(1024).decode()
if int(smtp_resp[:3]) != 220:
    print('The SMTP server is not ready, please try again.')
    exit(0)
else:
    print(smtp_resp)


def msg_send(msg, code):
    clientSocket.send(msg.encode())
    smtp_resp = clientSocket.recv(1024).decode()
    print(smtp_resp)
    if int(smtp_resp[:3]) != code:
        print('Code: %s,Try again' % smtp_resp[:3])
        to_try(msg, code)


def to_try(msg, code):
    while True:
        result = input('Try again? Y/N')
        if result == 'Y' or result == 'y':
            msg_send(msg, code)
        elif result == 'N' or result == 'n':
            exit(0)
        else:
            print('Fk U')
            exit(0)


smtpMsg = 'HELO qq.com\r\n'
msg_send(smtpMsg, 250)
#
smtpMsg = 'AUTH LOGIN\r\n'
msg_send(smtpMsg, 334)
#
userName = '2225827828@qq.com'
userName_base64 = 'MjIyNTgyNzgyOEBxcS5jb20='
msg_send(userName_base64+'\r\n', 334)
#
authorization_code = 'irhrxhsfcvuwdiii'
authorization_code_base64 = 'aXJocnhoc2ZjdnV3ZGlpaQ=='
msg_send(authorization_code_base64+'\r\n', 235)
#FUCK QQ
smtpMsg = 'MAIL FROM:<%s>\r\n' % userName
msg_send(smtpMsg, 250)
#
target = 'chikie920@foxmail.com'
smtpMsg = 'RCPT TO:<%s>\r\n' % target
msg_send(smtpMsg, 250)
#
smtpMsg = 'DATA\r\n'
msg_send(smtpMsg, 354)
#

message = 'FROM:<2225827828@qq.com>\r\nTo:<1597784057@qq.com>\r\nSubject: Test mail\r\n\r\nChikie, you will be a good coder in the future!'
clientSocket.send(message.encode())
clientSocket.send('\r\n.\r\n'.encode())
clientSocket.send('quit\r\n'.encode())
print(clientSocket.recv(1024).decode())
clientSocket.close()