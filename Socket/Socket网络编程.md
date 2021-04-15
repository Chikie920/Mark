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

**参数一**为服务端socket即server_socket

**参数二**为sockaddr类型的结构体指针，用于储存一个客户端信息，我们还是使用sockaddr_in类型更便捷

**参数三**为结构体大小的整型指针

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

**特点**：select模型用于服务端，客户端代码不变，解决基本C/S模型中，accept()与recv()函数傻等的问题(select本身是执行阻塞的)，实现与多个客户端链接与多个客户端同时通信。

**原理**：将所有SOCKET装如一个数组，通过select函数遍历数组，将所有有响应的SOCKET返回。**当有客户端链接**时**服务端监听套接字**会有响应，我们调用accept函数处理；**当有响应的SOCKET为客户端的**，则说明有客户端通信，调用send或recv函数。



**fd_set结构体**

为什么使用它--因为select函数的参数需要该结构体，所以我们使用它的成员来储存SOCKET

```c
typedef struct fd_set {
  u_int  fd_count;
  SOCKET fd_array[FD_SETSIZE];
} fd_set, FD_SET, *PFD_SET, *LPFD_SET;
```

**成员一**为无符号整型，用来记录集合中有响应的SOCKET数量

**成员二**为储存SOCKET的集合，`FD_SETSIZE`为宏，值为64，我们可以通过在套接字头文件前使用 `define`重新定义大小



**四个操作fd_set结构体的参数宏**

`FD_ZERO`：参数为fd_set结构体地址，将结构体内数组初始化(其实就是将fd_count初始化为0)

示例： `FD_ZERO(&AllSockets);`

`FD_SET`：向集合中添加一个SOCKET

示例：`FD_SET(Socket, &AllSockets);`

`FD_CLR`：集合中删除指定SOCKET

示例：`FD_CLR(Socket, &AllSockets);`

**注意：**在从集合中删除SOCKET后要记得释放掉SOCKET，不然会**内存泄漏**

```c
SOCKET Temp_Socket;
Temp_Socket = AllSockets.fd_array[n];
FD_CLR(AllSockets.fd_array[n], &AllSockets);
closesocket(Temp_Socket);
//现在看不懂没关系，后续学习中会明白
```

`FD_ISSET`：判断SOCKET是否在集合中，不在返回0，在返回非0

示例：`FD_ISSET(Socket, &AllSockets);`



**select函数原型**

```c
int WSAAPI select(
  int           nfds,
  fd_set        *readfds,
  fd_set        *writefds,
  fd_set        *exceptfds,
  const timeval *timeout
);
```

**参数一**仅用作兼容，我们不需要管它，填0即可

**参数二**传入fd_set结构体，select函数将检查是否有可读SOCKET，并返回

**原理**：我们将含SOCKET集合的结构体作为参数，select将其投放给系统，系统将有响应的SOCKET返回到原数组，只剩下有响应的SOCKET，然后我们可以根据SOCKET的不同，进行不同处理

**参数三**传入类型相同，用于检查是否有可写SOCKET，系统将可以被发送消息的SOCKET返回到原数组，一般正常链接了我们随时可以发送消息，而不是需要等到有响应才可以发送，所以我们用的不是特别多

**参数四**传入类型相同，用于检查 SOCKET的异常错误，返回有异常的

```c
getsockopt(socket, SOL_SOCKET, SO_ERROR, buf, buflen); //得到错误码
```

**参数五**为最大等待时间，select为执行阻塞，需要设置等待时间，当客户端SOCKET集合无响应时会等待

两个都赋值0，则此时select为非阻塞，无函数等待时间，两个都赋值NULL则完全阻塞成为傻等



**timeval结构体**

```c
typedef struct timeval {
  long tv_sec;
  long tv_usec;
} TIMEVAL, *PTIMEVAL, *LPTIMEVAL;
```

**成员一**以秒单位

**成员二**以毫秒为单位

```c
struct timeval secondtime;
secondtime.tv_sec = 3;
secondtime.tv_usec = 4;
//等待时间为3秒4微秒
```



**select函数返回值**

- `0`，客户端SOCKET无反应，我们continue就行
- `大于0`，有客户端响应
- `SOCKET_ERROR`，错误，使用 `WSAGetLastError()`函数得到错误代码



### 代码实现

```c
//上方代码与C/S模型相同
fd_set AllSockets;
FD_ZERO(&AllSockets); //创建并初始化结构体
FD_SET(ServerSocket, &AllSockets); //将服务端监听SOCKET放入数组

struct timeval seconds;
seconds.tv_sec = 3;
seconds.tv_usec = 0; //设置select函数等待时间

while(1){
	fd_set ReadSockets = AllSockets; //因为select函数会改变传入的结构体，不能改变原来的SOCKET集合
        int select_return = select(0, &ReadSockets, NULL, NULL, &seconds);

        if(select_return == 0){ //无客户端响应
            continue;
        } else if(select_return > 0){ //有客户端响应
            
            for(int n = 0; n < ReadSockets.fd_count; ++n){
                
                if(ReadSockets.fd_array[n] == server_socket){ //检查是否为服务端SOCKET
                    SOCKET SocketClient = accept(server_socket, NULL, NULL); //接受客户端链接
                    if(SocketClient == INVALID_SOCKET){ //错误处理
                        continue;
                    }
                    FD_SET(SocketClient, &AllSockets); //将建立连接的客户端SOCKET装入结构体数组成员中，用于后续的响应监测
                    
                } else {
                    char Msg[1500] = {0};
                    int recv_return = recv(ReadSockets.fd_array[n], Msg, 1499, 0); //接收客户端消息
                    if(recv_return == 0){
                        printf("客户端下线\n");
                    } else if(recv_return > 0){
                        printf("%s\n", Msg);
                    } else {
                        printf("ERROR 客户端强制下线\n");
                        SOCKET socketTemp = ReadSockets.fd_array[n];
                        FD_CLR(ReadSockets.fd_array[n],&AllSockets); //移除下线SOCKET
                        closesocket(socketTemp);
                    }
                    
                } // else
                
            } // for
            
        } else { // 发生错误
            printf("发生错误! 错误代码: %d\n", WSAGetLastError());
        }
        
    } // while

    for(int n = 0; n < AllSockets.fd_count; ++n){
        SOCKET socketTemp = AllSockets.fd_array[n];
        closesocket(socketTemp);
    } //最后千万别忘了释放SOCKET集合，不然会内存泄漏
    WSACleanup();
    //清理网络库

	return 0;
```



**关于一些代码的解释**

刚开始定义 `fd_set`结构体，我们装入监听客户端链接的服务端SOCKET，并将结构体作为参数传入`select`函数，**若有客户端链接时，服务端监听的SOCKET会有响应**，被返回出来，此时`fd_set`结构体的`fd_count`成员值为`1`，表明有一个有响应的SOCKET。此时我们可以使用`accept`函数进行与客户端的链接并创建存储客户端信息的SOCKET，并将其装入原SOCKET集合中，以此来用`select`监听其是否会有后续的响应，若有响应则表明有该客户端发来的消息，我们使用`recv`来接收。

若客户端下线则我们需要将其从原SOCKET集合中移除，并使用`closesocket()`释放



**关于参数三**，只要与客户端链接了，那该客户端SOCKET就是可写的，不一定需要该参数决定。如果我们向参数三传入AllSockets的副本，其中的ServerSocket不会对返回的数组成员造成影响，并且，只要有客户端链接成功，参数三返就一直是有响应的，select函数的返回值就**永远大于0**



**参数四** 用于处理异常SOCKET，异常条件较苛刻，我们一般不会遇到所以用不上



### 模型总结

1. 创建SOCKET集合
2. select()遍历
3. 处理
   1. 返回0 - 无响应，继续遍历
   2. 大于0 - 分类处理
   3. SOCKET_ERROR



select函数是阻塞的

1. 不等待 - 执行阻塞（原因：select函数遍历SOCKET集合需要时间）
2. 半等待 - 执行阻塞+软阻塞
3. 全等待 - 执行阻塞+硬阻塞（傻等）



### 控制台关闭事件

当我们直接关闭Server程序窗口时，很可能不会释放所有SOCKET与关闭网络库，我们可以请求操作系统监视我们的窗口，当我们点`×`关闭窗口时，系统可以调用我们的函数释放数组与关闭网络库。(钩子事件)



**SetConsoleCtrlHandler 函数**

**函数原型**

```c
BOOL WINAPI SetConsoleCtrlHandler(
  _In_opt_ PHANDLER_ROUTINE HandlerRoutine,
  _In_     BOOL             Add
);
```



**函数使用**

```c
SetConsoleCtrlHandler(function_name, TRUE);
```

**参数一**为我们需要调用的自定义的函数名-**回调函数名**，回调函数需要在该函数使用前定义

**参数二**可填**TRUE**和**FALSE**，当收到事件的时候，**HandlerRoutine-回调函数**可以选择处理，或者简单的忽略。如果回调函数选择忽略，函数返回FALSE，系统将处理下一个钩子程序。如果处理消息，程序在处理完消息后应该返回TRUE。即填TRUE会调用我们的函数，FALSE不会



**HandlerRoutine 回调函数**

回调函数为被系统调用的函数



**函数原型**

```c
BOOL WINAPI HandlerRoutine(
  _In_ DWORD dwCtrlType // _In_ 只起说明作用表明为传入，填入参数时可去掉
);
```



**实际使用演示**

```c
fd_set AllSockets; //定义为全局对象

bool Console_Shutdown(DWORD dwCtrlType)
{
    switch(dwCtrlType){
        case CTRL_CLOSE_EVENT: 
            for(int n = 0; n < AllSockets.fd_count; ++n){
                SOCKET socketTemp = AllSockets.fd_array[n];
                closesocket(socketTemp);
            }
            WSACleanup();
            break;
        	//关闭窗口时，释放SOCKET与清理网络库处理
        default:
            break;
    }

    return TRUE;
} //回调函数定义

int main(void)
{
    SetConsoleCtrlHandler(Console_Shutdown, TRUE); //系统监视
    ...
    return 0;
}
```



## 事件选择模型



**Windows消息机制与事件机制**

**消息机制**：核心 - 消息队列（按操作顺序先入先出队列），用户操作产生消息，由计算机放入队列，然后被我们依次处理。消息队列由计算机创建与维护，我们无法干涉和改变，只能做调用，根据消息做分类处理。异步选择模型基于消息机制。



**事件机制**：核心 - 事件集合（无顺序），事件由我们自己调用API创建，需要多少创建多少，给每个操作绑定事件（相当于给每个事件绑定ID），每个事件的检测顺序由程序员决定（事件集合由我们自己创建，我们可以将事件装入数组等），并将事件投递给系统监视，系统会根据我们创建集合的事件顺序依次检测，不能无限创建，太多系统处理不来。



**事件选择模型的处理逻辑**

整体逻辑与select模型差不多，核心函数为**`WSAEventSelect()`**



1. 创建一个事件对象 **`WSACreateEvent()`**
2. 给每个事件对象绑定SOCKET以及对应操作 `accept、read、close等`并投递给操作系统，然后就不用管了，系统自动监管 **`WSAEventSelect()`**-绑定加投递功能
3. 查看事件是否有信号 **`WSAWaitForMultipleEvents()`**
4. 有信号就分类处理 **`WSAEnumNetworkEvents()`**



### 代码实现

开始监听及以前代码与基本C\S模型相同





## 异步选择模型



## 重叠IO模型



## 完成端口模型



# 完结

本教程到此结束，你学废了吗？有问题的小伙伴们欢迎在评论区友好交流。

