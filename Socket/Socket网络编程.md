---
title: Socket网络编程
date: 2021-01-23 21:37:02
tags: [Socket网络编程,C]
comments: true
---

# 前言

-本教程一方面是作为个人学习笔记另一方面也是本着一种助人为乐的态度写的，参考了[C3程序员](https://study.163.com/course/courseMain.htm?courseId=1006358018&share=1&shareId=1141882478)的视频同时也包含了我自己遇到问题时的经验而写成，我尽量将本笔记写的简洁并且易懂的同时囊括大部分的内容以节约大家的时间与耐心，没有时间观看视频的小伙伴们可以看我的笔记，要是觉得本笔记不适合的话推荐去观看原视频，这个老师讲的很好，内容也浅显易懂，希望大家能够支持他。如果本文章存在侵权行为，请联系我删除。如有错误，欢迎大家批评指正!

-作者使用Visual Studio Code搭配GCC编译器进行代码编写与运行，这里不介绍如何安装，如果你使用的其他环境，具体实践可能会与本文章的内容有所出入，请自行解决

-文章刚发布内容可能会不完善，后续将会慢慢补齐

-转载请注明链接，请尊重我的劳动成果！

# 什么是SOCKET



## SOCKET简介与简单的网络通信原理

SOCKET又称套接字，现代的网络通信就是通过SOCKET进行的，SOCKET编程也叫网络编程

Socket相当于一个电话，只需要知道另一个电话号码(另一端的信息)即可通信，我们并不需要了解手机是如何做成的，对与socket编程也一样，我们只需要了解简单的通信协议与函数即可编写出简单的通信模型出来，所以不要惧怕它。同时，我们需要善用[MSDN](https://docs.microsoft.com/zh-cn/)来学习有关函数的调用。

# 基于TCP/IP的C/S通信模型



## TCP/IP协议的简单介绍



## SOCKET通信步骤



## Windows网络库与头文件

**WinSock2.h**头文件，名称即为Windows下的socket简写，2指第二版的网络库(主版本)，我们使用新版的网络库不使用1版的，引入该头文件即可使用网络库的函数

**ws2_32.lib**为windows网络库，需要有网络库并且成功初始化，WinSock2.h头文件内的函数才能成功的调用

头文件与库的名字都不区分大小写

```c
#include <WinSock2.h>
//引入头文件
#pragma comment(lib, "ws2_32.lib")
//引入网络库

/*
引入windows库的模板写法
#pragma comment(lib, "库名字")
不用过多纠结
*/
```



## 初始化网络库-WSAStartup()函数与返回值

**函数介绍**

我们使用WSAStartup()函数来初始化网络库，以便网络函数能成功调用

W指windows 

S指socket 

A指Asynchronous异步，同步则阻塞，卡死，而异步则指多线程，同时的意思

Startup启动

**函数原型**

我们可以使用[MSDN](https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup)来查看相关函数，与其使用实例

```c
int WSAStartup(
  WORD      wVersionRequired,
  LPWSADATA lpWSAData
);
```

**参数解析**

这个函数的返回值为int类型，有两个参数

一个为WORD类型，它并不是一个浮点型。变量名为wVersionRequired，变量名实际使用可以自定，指网络库的具体版本，目前最新为2.2版本(副版本)，对于详细版本可以在MSDN中搜索WSAStartup下翻查看

另一个为LPWSADATA类型，是一个指针类型，它指向WSADATA结构体，一般名称中有LP的基本都为指针类型

**函数返回值**

如果WSAStartup()调用成功则返回0，失败则返回其他值

若初始化网络库失败，则其他网络函数将无法正常使用

**使用函数**

```c
WORD WSVersion = (2, 2);//选择版本
/*
官方提供这种方法来进行版本号的赋值
*/
WSADATA wsadata;

int wsas_return = WSAStartup(WSVersion, &wsadata);
if(wsas_return != 0){
    printf("初始化网络库失败! 请检查网络库，或者重启电脑\n");
}
```



## VScode配置

需配置项目目录内的`.vscode`内的`tasks.json`文件内tasks->args，将库包含进工程，才能正常使用网络库函数

```json
"args": [
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-lwsock32"
            ],
```



## 创建套接字-socket()函数与返回值



**函数介绍**

该函数用于创建进行通信的Socket

**函数原型**

```c
SOCKET WSAAPI socket(
  int af,
  int type,
  int protocol
);
```

**参数解析**

第一个参数为地址的类型，填**AF_INET**，为使用IPV4地址为现在常用的地址类型，若填**AF_INET6**则为IPV6地址类型但尚未普及，可以选择不同的协议进行通信，但前提是知道对方的地址，并使用对应的地址类型，这里我们使用IPV4

第二个参数为套接字的类型，填**SOCK_STREAM**，即使用TCP进行通信

第三个为使用的协议类型，我们使用的是TCP/IP协议，所以填**IPPROTO_TCP**

这里我们只是简单了解会使用即可，关于协议的解释，感兴趣的可以查找MSDN的Socket函数或者网上查阅大佬的文章

**函数返回值**

函数使用成功返回一个可用的Socket，否则返回**INVALID_SOCKET**

**使用函数**

```c
SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if(server_socket == INVALID_SOCKET){
    printf("创建socket失败! 错误代码:");
    int error = WSAGetLastError();//可以使用该函数进行查看上个最近网络函数失败后的错误代码
    printf("%d\n",error);
    WSACleanup();//清理网络库
    return 1;//结束程序
}
/*
无法成功创建socket我们就无法通信，这是非常重要的环节之一，所以程序无法也没有必要再继续运行
在结束运行之前要关闭socket与清理网络库，由于这里创建socket失败所以我们无需关闭，只需要清理网络库即可
*/
```



## 绑定本地socket-bind()函数与返回值

**函数介绍**

该函数用于给socket绑定具体地址与端口号用于通信

**地址与端口号的简单解释**

地址是唯一的，可以通过地址找到对应的计算机设备

计算机内的软件通过端口与外界通信，端口范围为0-65535，端口有我们所熟知的如22(SSH服务)、80(HTTP服务)等，我们也可以自己申请一个端口使用，后面的通信模型中我们会进行实践，一个软件可能只占用一个端口也可能是多个，端口号是唯一的，不能是多个软件拥有同一个端口，这样信息的传递是混乱的，同时计算机也不允许这样

**函数原型**

```c
int WSAAPI bind(
  SOCKET         s,
  const sockaddr *name,
  int            namelen
);
```

**函数参数**

参数一为SOCKET类型，使用我们上面创建并配置好协议的**server_socket**，来进行端口号与地址的绑定

参数二为一个结构体指针，我们需要sockaddr类型的结构体内存放要绑定的地址与端口

参数三为结构体的大小，使用sizeof()函数得到

**sockaddr与sockaddr_in结构体的定义与选择**

```c
struct sockaddr {
        ushort  sa_family;
        char    sa_data[14];
};

struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};
```

同为IPV4协议使用的结构体，sockaddr第一个成员为地址协议，也就是我们创建socket时的协议类型(协议族)，指为AF_INET

第二个成员为一个数组，用于存放地址与端口，由于MSDN没有sockaddr成员二的存储方法，我们不能得知该以何种方式去赋值。

官方使用的是第二个结构体sockaddr_in，因为这两个结构体内存排布相同，我们在使用sockaddr_in进行配置后可以强转为sockaddr类型。

再让我们来看sockaddr_in，第一个成员与上一个相同，第二个成员可以看出是用来存放端口号的，第三个成员为一个in_addr类型的结构体，我在编译器内查看它的定义如下

```c
typedef struct in_addr {
  union {
    struct { u_char  s_b1, s_b2, s_b3, s_b4; } S_un_b;
    struct { u_short s_w1, s_w2; } S_un_w;
    u_long S_addr;
  } S_un;
} IN_ADDR, *PIN_ADDR, *LPIN_ADDR;
```

结构体内为一个S_un联合，我们有三种方式去储存地址，这里为了方便我们使用第三种u_long型(无符号long型)进行存储。我们在进行本地通信模型时使用本机地址(**127.0.0.1**)进行数据通信，但是该地址并不是一个无符号long型，需要使用**inet_addr()**这个宏去将地址转换为u_long型。

这里可能会比较复杂，想了解更多可以去MSDN搜索sockaddr

第四个成员为sockaddr结构体的大小，同样使用sizeof()得出

**函数返回值**

成功返回0，失败返回SOCKET_ERROR宏，同样我们可以使用WSAGetLastError()来得到具体的错误代码

**函数使用**

```c
struct sockaddr_in bind_info;
bind_info.sin_family = AF_INET;
bind_info.sin_port = htons(2333);//下面解释该代码
bind_info.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

int bind_return = bind(server_socket, (const struct *)&bind_info, sizeof(bind_info));
if(bind_return != 0){
    printf("ERROR! 错误代码: %d\n",WSAGetLastError());
    closesocket(server_socket);//关闭socket
    WSACleanup();//清理网络库
    return 1;
    /*
    closesocket()为网络库函数，所以要先关闭socket再清理网络库
    */
}
/*
与socket函数相同，bind()函数也是重要的一环，当该函数没有正确的返回时，该程序也就失败了，没有必要再运行了
后面的一些函数使用例子也是如此，将不再赘述
*/
```

**使用本地地址并开启本地端口用于通信与htons宏的使用**

这里我们只经行本地通信，使用本机地址，在进行通信时，既作为服务端传递信息也作为客户端接收信息，当然，需要使用不同的程序

上面我们简单介绍过端口，其中0~1023为系统保留端口，是系统所占用的，我们无法申请使用

剩下的1024~65535为我们可以支配的，但是其中有些已经被我们所安装的软件所使用，我们不能再占用这些端口，比如我们想使用2333端口，那么如何去查看该端口是否被占用呢？

`netstat -ano|findstr "端口号"`查看某个端口号是否被占用，如果没有任何信息则没有被占用

`netstat -ano`查看所有被使用的端口号与信息

由于bind_info.sin_port为一个u_short类型(无符号short类型)，而我们输入的端口号为int类型，所以使用htons()函数经行转化，更加规范



## 监听链接-listen()函数与返回值

**函数介绍**

开启服务端对客户端的socket通信监听

**函数原型**

```c
int WSAAPI listen(
  SOCKET s,
  int    backlog
);
```

**函数参数**

WSAAP为调用约定，可以忽略，于我们无关

第一个参数为服务端socket，也就是上面我们创建于配置的server_socket

第二个参数为开始挂起客户端链接的最大长度，实际在通信时，一个服务端可能会接收到许多客户端的链接，由于服务端的性能有限，无法同时处理全部的链接，所以需要设置最大的处理个数，多出来的请求进行排队等待处理。我们可以自行设置个数，自己的电脑建议2~20个左右，也可以使用`SOMAXCONN`宏让系统根据自身性能自动设置。

**函数返回值**

成功返回0，失败返回SOCKET_ERROR

**函数使用**

```c
int listen_return = listen(server_socket, SOMAXCONN);
if(listen_return != 0){
    printf("ERROR! 错误代码: %d\n",WSAGetLastError());
    closesocket(server_socket);
    WSACleanup();
    return 1;
}
```



## 与服务端链接-connect()函数与返回值

**函数介绍**

该函数用于客户端与服务端链接

**函数原型**

```c
int WSAAPI connect(
  SOCKET         s,
  const sockaddr *name,
  int            namelen
);
```

**函数参数**

参数一为服务端socket

参数二为服务端的协议与ip和端口信息

参数三为结构体大小

**函数返回值**

如果未发生错误，则 connect返回零。否则，它将返回SOCKET_ERROR

**函数使用**

与bind()相似

```c
struct sockaddr_in server_info;
server_info.sin_family = AF_INET;
server_info.sin_port = htons(2333);
server_info.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
int connect_return = connect(server_socket, (const struct sockaddr *)&server_info, sizeof(server_info));
if(connect_return != 0){
    printf("与服务端链接错误! 错误代码: %d\n",WSAGetLastError());
    closesocket(server_socket);
    WSACleanup();
    return 1;
} else {
    printf("链接成功!\n");
}
```



## 接受链接-accept()函数与返回值

**函数介绍**

创建客户端socket，储存客户端信息

这里要弄清楚，客户端与服务器进行通信使用储存服务端信息的socket，而服务端与客户端通信使用储存客户端信息的socket

相当于我们需要知道对方的电话号码才能通信

listen()通过监听客户端的链接，accept()将一个客户端信息绑定到一个socket上，多个客户端则调用多次

该函数是**阻塞**的，当没有客户端链接时会一直等待，相当于进入卡死状态，当客户端链接时继续运行

**函数原型**

```c
SOCKET WSAAPI accept(
  SOCKET   s,
  sockaddr *addr,
  int      *addrlen
);
```

**函数参数**

参数一为服务端socket即server_socket

参数二为sockaddr类型的结构体指针，用于储存一个客户端信息，我们还是使用sockaddr_in类型更便捷

参数三为结构体大小的整型指针

该函数是通过从服务端socket获取客户端信息进行储存，储存到我们所填的参数二与三的变量中。

所以参数二与三不需要给出具体值，实际上参数二我们也不清楚

参数二与三我们也可以不写，直接设置为NULL，选择不存储客户端的信息，当然返回的socket内是有储存的，但是下一次就被覆盖了

想储存可以使用链表，这里就不写了

**函数返回值**

成功则返回**SOCKET**类型的值，也就是一个socket，错误返回**INVALID_SOCKET**

**函数使用**

```c
SOCKET client_socket = accept(server_socket, NULL, NULL);
if(client_socket == INVALID_SOCKET){
    printf("ERROR! 错误代码: %d\n",WSAGetLastError());
    closesocket(server_socket);
    WSACleanup();
    return 1;
}
printf("客户端链接成功!\n");
```



## 接收信息-recv()函数与返回值

**函数原型**

```c
int WSAAPI recv(
  SOCKET s,
  char   *buf,
  int    len,
  int    flags
);
```

**函数参数**

参数一为目标的socket

参数二为消息的储存空间(字符数组)，一般为1500(网络传输的最大单元)，不要超过它，超过了会分次发送

参数三为从缓冲区读取的字节数(读取后会被存储在数组中)

参数四为数据的读取方式，写0就行

当另一端发送消息时，数据由SOCKET底层协议进行储存在一个缓冲区中，而recv()则是从该缓冲区进行信息的读取放在数组中

**函数返回值**

未发生错误则返回接收到的字符数，如果正常关闭链接则返回0，错误则返回SOCKET_ERROR

**函数使用**

```c
char rec_msg[1500] = {0};
int recv_return = recv(client_socket, rec_msg, 1499, 0);
if(recv_return == 0){
    printf("客户端下线\n");
} else if(recv_return > 0){
    printf("%s\n", rec_msg);
} else {
    printf("ERROR! 错误代码: %d\n",WSAGetLastError());
}
```



## 发送信息-send()函数与返回值

**函数原型**

```c
int WSAAPI send(
  SOCKET     s,
  const char *buf,
  int        len,
  int        flags
);
```

**函数参数**

参数一为目标的socket

参数二为用来发送信息的字符串指针

参数三为字符串数组长度

参数四为发送的方式，同样我们填0就行

**函数返回值**

成功则返回发送的字节总数，否则返回SOCKET_ERROR

**函数使用**

```c
char send_msg[1500] = {0};
int send_return = send(server_socket, send_msg, sizeof(send_msg), 0);
if(send_return == SOCKET_ERROR){
    printf("ERROR! 错误代码: %d\n",WSAGetLastError());
}
```



## Server端完整编写

```c
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(void)
{
    WORD WSVersion = (2, 2);
	WSADATA wsadata;
    int wsas_return = WSAStartup(WSVersion, &wsadata);
    if(wsas_return != 0){
        printf("初始化网络库失败! 请检查网络库，或者重启电脑\n");
    }
    //初始化网络库
    
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(server_socket == INVALID_SOCKET){
        printf("创建socket失败! 错误代码:");
        int error = WSAGetLastError();
        printf("%d\n",error);
        WSACleanup();
        return 1;
    }
    //创建本地socket
    
    struct sockaddr_in bind_info;
    bind_info.sin_family = AF_INET;
    bind_info.sin_port = htons(2333);
    bind_info.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    int bind_return = bind(server_socket, (const struct sockaddr *)&bind_info, sizeof(bind_info));
    if(bind_return != 0){
        printf("ERROR! 错误代码: %d\n",WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    //绑定本地ip与端口
    
    int listen_return = listen(server_socket, SOMAXCONN);
    if(listen_return != 0){
        printf("ERROR! 错误代码: %d\n",WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    printf("Listening...\n");
    //监听客户端链接
    
    SOCKET client_socket = accept(server_socket, NULL, NULL);
    if(client_socket == INVALID_SOCKET){
        printf("ERROR! 错误代码: %d\n",WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    printf("客户端链接成功!\n");
    //创建客户端socket
    
    while(1){ //死循环使服务端能持续接收消息
        char rec_msg[1500] = {0};
        char send_msg[1500] = {0};
        int recv_return = recv(client_socket, rec_msg, 1499, 0);
        if(recv_return == 0||recv_return == -1){
            printf("客户端下线\n");
            closesocket(client_socket);
        } else if(recv_return > 0){
            printf("%s\n", rec_msg);
        } else {
            printf("ERROR! 错误代码: %d\n",WSAGetLastError());
        }
        //接收客户端信息
        scanf("%s",send_msg);
        send(client_socket, send_msg, sizeof(send_msg), 0);//与客户端发消息
    }
    
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    //关闭socket与清理网络库
    
    return 0;
}
```



## Client端完整编写

```c
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
//socket头文件网络库

int main(void)
{
    WORD WSVersion = (2, 2);
    WSADATA wsadata;
    int wsas_return = WSAStartup(WSVersion, &wsadata);
    if(wsas_return != 0){
        printf("初始化网络库失败! 请检查网络库，或者重启电脑\n");
    }
    //初始化网络库
    
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_socket == INVALID_SOCKET){
        printf("创建socket失败! 错误代码:");
        int error = WSAGetLastError();
        printf("%d\n",error);
        WSACleanup();
        return 1;
    }
    //创建服务端socket
    
    struct sockaddr_in server_info;
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(2333);
    server_info.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    int connect_return = connect(server_socket, (const struct sockaddr *)&server_info, sizeof(server_info));
    if(connect_return != 0){
        printf("与服务端链接错误! 错误代码: %d\n",WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    } else {
        printf("链接成功!\n");
        while(1){
            char recv_msg[1500] = {0};
            char send_msg[1500] = {0};
            scanf("%s",send_msg);
            send(server_socket, send_msg, sizeof(send_msg), 0);

            int recv_return = recv(server_socket, recv_msg, 1499, 0);
            if(recv_return == 0){
                printf("服务端中断!\n");
            } else if(recv_return == SOCKET_ERROR){
                printf("ERROR! 错误代码: %d\n",WSAGetLastError());
            } else {
                printf("%s\n", recv_msg);
            }
        }
    }
    //与服务端链接
    
    closesocket(server_socket);
    WSACleanup();
    //关闭socket与清理网络库
    
    return 0;
}
```



## 运行

![](/images/2021_1_23_1.png)

![](/images/2021_1_23_2.png)

![](/images/2021_1_23_3.png)



## 问题

如果你试着写出了C/S模型，你会发现我们上面所写的模型server端不能与多个client端通信，并且当与一个client端通信时只能以一种“回合制”模式进行。因为listen()与accept()函数只接收了一个client_socket，只能与一个client通信，而我们的recv()函数是阻塞的，当没有另一端的信息时会一直等待，无法执行后续的代码(accept函数也是如此)。这样的通讯无疑是没有实际用处的。

# C/S模型优化





## select()模型

### 特点与原理

解决基本C/S模型中，accept()与recv()函数傻等的问题，与多个客户端同时通信。



## 事件选择模型



## 异步选择模型



## 重叠IO模型



## 完成端口模型



# 完结

本教程到此结束，你学废了吗？有问题的小伙伴们欢迎在评论区友好交流。