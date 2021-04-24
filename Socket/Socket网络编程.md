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
////////   注：MinGW并不支持该语句，需要在VsCode的task文件内添加链接库         ////////

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
                "-lws2_32"
            ],
```

注意不要链接`ws32`库，这个库较老，无法正常使用事件选择模型的函数



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



**函数介绍**



**WSACreateEvent函数**



**函数语法**

```c
WSAEVENT WSAAPI WSACreateEvent(); //WSAAPI为调用约定，与我们基本没关系，去掉没影响
```



**无参数**



**返回值**

没有错误返回事件**对象句柄**（相当于ID，每个事件独立），否则返回值为**WSA_INVALID_EVENT**，获取错误信息使用 `WSAGetLastError()`



句柄（事件对象）是一种**内核对象**，由操作系统在内核申请、访问，我们不能定位其内容也无法修改；不用了要用函数释放，不然会造成内核内存泄漏，与内存泄漏不同，内存泄漏只需关闭程序即可回收，而内核内存泄漏只能重启解决。Socket就是一种内核对象。



**WSACloseEvent函数**



**函数原型**

用于关闭事件对象，不用就要释放

```c
BOOL WSAAPI WSACloseEvent(
  WSAEVENT hEvent
);
```



**参数介绍**

需要关闭的事件对象名



**返回值**

成功为TRUE，失败为FALSE，获取错误信息使用 `WSAGetLastError()`



**WSAEventSelect函数**

给事件绑定SOCKET与操作码（用户操作事件），并投递给操作系统



**函数原型**

```c
int WSAAPI WSAEventSelect(
  SOCKET   s,
  WSAEVENT hEventObject,
  long     lNetworkEvents
);
```



**参数介绍**

**参数一**为被绑定的SOCKET，每个SOCKET都要被绑定事件

**参数二**为事件对象，与参一绑定

**参数三**为具体事件 `FD_ACCEPT等`，可以使用**位或**进行多个事件绑定，当有事件发生时，会产生信号



| **FD_ACCEPT**    | 与服务器SOCKET绑定，有客户端链接时有响应                     |
| ---------------- | ------------------------------------------------------------ |
| **FD_READ**      | **与客户端SOCKET绑定，有客户端消息时有响应**                 |
| **FD_CLOSE**     | **与客户端SOCKET绑定，有客户端下线(强制或正常)时有响应**     |
| **FD_WRITE**     | **与客户端SOCKET绑定，在accept后立即产生该信号，客户端链接成功即可发消息** |
| **FD_CONNECT**   | **用于客户端，服务器端用不到，给服务器SOCKET绑定**           |
| **0**            | **取消事件监视**                                             |
| **FD_OOB**       | **一般不使用**                                               |
| **FD_QOS**       | **套接字服务质量变化通知**                                   |
| **FD_GROUP_QOS** | **没有具体意义，保留词**                                     |

给原有事件对象再次绑定事件会覆盖原有事件



**返回值**

成功返回0，失败返回`SOCKET_ERROR`



**WSAWaitForMultipleEvents函数**

询问发生信号的事件



**函数原型**

```c
DWORD WSAAPI WSAWaitForMultipleEvents(
  DWORD          cEvents,
  const WSAEVENT *lphEvents,
  BOOL           fWaitAll,
  DWORD          dwTimeout,
  BOOL           fAlertable
);
```



`DWORD`为无符号长整型



**参数介绍**

**参数一**为事件个数

**参数二**为事件数组首地址

**参数三**为事件等待方式，TRUE-阻塞，等到所有事件都有信号才返回，FALSE，任何一个有信号立即返回

**参数四**为超时间隔，以毫秒为单位，一直等待宏 **WSA_INFINITE**

**参数五**为选择模型，TRUE为**重叠IO模型**使用的，FALSE为**事件选择模型**使用



**返回值**

参数三为TRUE返回，返回值指示已发出所有指定的事件对象的信号

参数三为FALSE返回，返回值减去**WSA_WAIT_EVENT_0**表示满足等待信号的事件对象的数组索引（下标）

参数五为TRUE返回，**WSA_WAIT_IO_COMPLETION**

超时返回，**WSA_WAIT_TIMEOUT**，`continue`即可

失败返回，**WSA_WAIT_FAILED**



**WSAEnumNetworkEvents函数**

列举事件，获取事件类型，并将信号重置



**函数原型**

```c
int WSAAPI WSAEnumNetworkEvents(
  SOCKET             s,
  WSAEVENT           hEventObject,
  LPWSANETWORKEVENTS lpNetworkEvents
);
```



**参数介绍**

**参数一**为SOCKET

**参数二**为对应事件

**参数三**装触发类型的事件，是一个结构体指针 `WSANETWORKEVENTS`

**结构体原型**

```c
typedef struct _WSANETWORKEVENTS {
  long lNetworkEvents;
  int  iErrorCode[FD_MAX_EVENTS];
} WSANETWORKEVENTS, *LPWSANETWORKEVENTS;
```

结构体成员一为**指示发生了哪些FD_XXX网络事件**

成员二为**错误码数组**，包含与对应于事件的比特中的位置的数组索引相关联的任何错误代码**lNetworkEvents**。诸如FD_READ_BIT和FD_WRITE_BIT之类的标识符可用于索引**iErrorCode**数组



**返回值**

成功返回0，失败返回 `SOCKET_ERROR`



### 代码实现

开始监听及以前代码与基本C\S模型相同

```c
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
//引用头文件与网络库

typedef struct event_socket_set {
    SOCKET socket_all[64];
    WSAEVENT event_all[64];
    unsigned int count;
} event_socket_set;

fd_set AllSockets;
//创建存放SOCKET与事件对象的容器，因为我们需要对每个SOCKET绑定相应的事件
event_socket_set es_set = {{0}, {0}, 0};


BOOL WINAPI Console_Shutdown(DWORD dwCtrlType)
{
    switch(dwCtrlType){
        case CTRL_CLOSE_EVENT: 
            for(int n = 0; n < es_set.count; ++n){
            closesocket(es_set.socket_all[n]);
            WSACloseEvent(es_set.event_all[n]);
        }
        WSACleanup();
        break;
    }

    return TRUE;
}

int main(void)
{

    SetConsoleCtrlHandler(Console_Shutdown, TRUE);

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
        printf("BIND ERROR! 错误代码: %d\n",WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    //绑定本地ip与端口
    
    int listen_return = listen(server_socket, SOMAXCONN);
    if(listen_return != 0){
        printf("LISETEN ERROR! 错误代码: %d\n",WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    printf("Listening...\n");
    //监听客户端链接


    //创建事件
    WSAEVENT EventServer = WSACreateEvent();
    //返回值处理
    if(EventServer == WSA_INVALID_EVENT){
        printf("CREATE EVENT ERROR! 错误代码: %d\n",WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 0;
    }

    //事件绑定与投递
    int EventSelect_return = WSAEventSelect(server_socket, EventServer, FD_ACCEPT | FD_WRITE | FD_READ);
    if(EventSelect_return == SOCKET_ERROR){
        printf("ERROR! 错误代码: %d\n",WSAGetLastError());
        WSACloseEvent(EventServer);
        closesocket(server_socket);
        WSACleanup();
        return 0;
    }

    es_set.socket_all[es_set.count] = server_socket;
    es_set.event_all[es_set.count] = EventServer;
    es_set.count++;
    //添加到容器中

    while(1){
        //操作系统监控事件与该函数是异步的，这个函数只是隔一段时间向系统获取事件的情况
        DWORD Wait_return = WSAWaitForMultipleEvents(es_set.count, es_set.event_all, FALSE, 200, FALSE);
        //函数错误
        if(Wait_return == WSA_WAIT_FAILED){
            printf("WAIT ERROR! 错误代码: %d\n",WSAGetLastError());
            break;
        }
        //超时
        if(Wait_return == WSA_WAIT_TIMEOUT){
            continue;
        }
        DWORD event_index = Wait_return - WSA_WAIT_EVENT_0;

        //得到下标对应事件
        WSANETWORKEVENTS NetworkEvents;
        int n_t_return = WSAEnumNetworkEvents(es_set.socket_all[event_index], es_set.event_all[event_index], &NetworkEvents);
        if(n_t_return == SOCKET_ERROR){
            printf("GETINDEX ERROR! 错误代码: %d\n",WSAGetLastError());
            break;
        }

        if(NetworkEvents.lNetworkEvents & FD_ACCEPT){
            if(NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0){ //等于0时为无错误码情况，正常处理
                SOCKET ClientSocket = accept(es_set.socket_all[event_index], NULL, NULL);
                if(ClientSocket == INVALID_SOCKET){
                    continue;
                }
                //给客户端SOCKET绑定事件
                WSAEVENT ClientEvent = WSACreateEvent();
                if(ClientEvent == WSA_INVALID_EVENT){
                    closesocket(ClientSocket);
                    continue;
                }
                //投递给系统监视
                if( WSAEventSelect(ClientSocket, ClientEvent, FD_READ | FD_CLOSE | FD_WRITE) == SOCKET_ERROR){
                    closesocket(ClientSocket);
                    WSACloseEvent(ClientEvent);
                    continue;
                }

                //将链接的客户端SOCKET装入数组集合进行后续监视
                es_set.socket_all[es_set.count] = ClientSocket;
                es_set.event_all[es_set.count] = ClientEvent;
                es_set.count++;
                printf("Client Connect Success\n");
            } else {
                continue;
            }
        }
        
        //根据客户端信号进行分类处理
        if(NetworkEvents.lNetworkEvents & FD_WRITE){
            if(NetworkEvents.iErrorCode[FD_WRITE_BIT] == 0){
                if(send(es_set.socket_all[event_index], "CONNECT SUCCESS", strlen("CONNECT SUCCESS"), 0) == SOCKET_ERROR){
                    printf("SEND ERROR! 错误代码: %d\n",WSAGetLastError());
                }
            } else {
                printf("CLIENT SOCKET ERROR! 错误代码: %d\n",NetworkEvents.iErrorCode[FD_WRITE_BIT]);
            }
        }

        if(NetworkEvents.lNetworkEvents & FD_READ){
            if(NetworkEvents.iErrorCode[FD_READ_BIT] == 0){
                char rec_msg[1500] = {0};
                if(recv(es_set.socket_all[event_index], rec_msg, 1499, 0) == SOCKET_ERROR){
                    printf("RECV ERROR! 错误代码: %d\n",WSAGetLastError());
                    continue;
                }
                printf("%s\n", rec_msg);
            } else {
                printf("CLIENT SOCKET ERROR! 错误代码: %d\n",NetworkEvents.iErrorCode[FD_READ_BIT]);
                continue;
            }
        }

        if(NetworkEvents.lNetworkEvents & FD_CLOSE){
            printf("Client ShutDown\n");
            //清理下线客户端SOCKET与事件
            closesocket(es_set.socket_all[event_index]);
            es_set.socket_all[event_index] = es_set.socket_all[es_set.count-1];
            //将已关闭SOCKET的位置用最后一个有效SOCKET替补，并将有效个数减一，避免移动后面所有SOCKET的情况，下同
            WSACloseEvent(es_set.event_all[event_index]);
            es_set.event_all[event_index] = es_set.event_all[es_set.count-1];
            es_set.count--;
        }

    }

	for(int n = 0; n < es_set.count; ++n){
		closesocket(es_set.socket_all[n]);
		WSACloseEvent(es_set.event_all[n]);
	}
    WSACleanup();
	//清理SOCKET、事件与网络库
    
    return 0;
}
```



**事件分类处理逻辑**

根据事件的响应的不同进行分类处理，下面展示的代码为`if`处理，现在讨论`switch`以及`if-else if`处理的问题，else-if本质上与switch相似，当有多个事件有信号时，else-if只能处理一个满足条件，即使后面的条件依然为真，switch则更严重



**else-if示例与解释**

```c
if(NetworkEvents.lNetworkEvents & FD_WRITE){
            if(NetworkEvents.iErrorCode[FD_WRITE_BIT] == 0){
                if(send(es_set.socket_all[event_index], "CONNECT SUCCESS", strlen("CONNECT SUCCESS"), 0) == SOCKET_ERROR){
                    printf("SEND ERROR! 错误代码: %d\n",WSAGetLastError());
                }
            } else {
                printf("CLIENT SOCKET ERROR! 错误代码: %d\n",NetworkEvents.iErrorCode[FD_WRITE_BIT]);
            }
        }

else if(NetworkEvents.lNetworkEvents & FD_READ){
    if(NetworkEvents.iErrorCode[FD_READ_BIT] == 0){
        char rec_msg[1500] = {0};
        if(recv(es_set.socket_all[event_index], rec_msg, 1499, 0) == SOCKET_ERROR){
            printf("RECV ERROR! 错误代码: %d\n",WSAGetLastError());
            continue;
        }
        printf("%s\n", rec_msg);
    } else {
        printf("CLIENT SOCKET ERROR! 错误代码: %d\n",NetworkEvents.iErrorCode[FD_READ_BIT]);
        continue;
    }
}

else if(NetworkEvents.lNetworkEvents & FD_CLOSE){
    printf("Client ShutDown\n");
    //清理下线客户端SOCKET与事件
    closesocket(es_set.socket_all[event_index]);
    es_set.socket_all[event_index] = es_set.socket_all[es_set.count-1];
    //将已关闭SOCKET的位置用最后一个有效SOCKET替补，并将有效个数减一，避免移动后面所有SOCKET的情况，下同
    WSACloseEvent(es_set.event_all[event_index]);
    es_set.event_all[event_index] = es_set.event_all[es_set.count-1];
    es_set.count--;
}
else {
    
}
```

当客户端链接并发送消息时，在`WSAEventSelect`函数内发生两个信号`READ`、`WRITE`，由`FD_XX`定义得，一个为01，一个为10，两个位和为11，即为3，NetworkEvents.lNetworkEvents值为3，else-if为多选一匹配，在后面匹配时先匹配`FD_WRITE`，然后就不执行后面判断了。有小问题，可以采用。



```c
switch (NetworkEvents.lNetworkEvents){
        case FD_ACCEPT:
        ...
        case FD_WRITE:
        ...
        case FD_READ:
        ...
        case FD_CLOSE:
        ...
}
```

对于`switch`，首先有客户端链接时，NetworkEvents.lNetworkEvents值为8，与FD_ACCEPT匹配，正常处理，当当有多个信号时，如`READ`、`WRITE`，NetworkEvents.lNetworkEvents值为3，不与任何信号匹配，出现错误。所以不建议使用switch方法分类处理信号。



### 有序优化之变态点击

解决`WSAWaitForMultipleEvents`按照我们放入es_set.event_all事件集合的事件顺序去依次遍历，而不是根据事件发生的顺序去遍历，查看有无事件被触发，而不管集合内事件发生的先后顺序，该函数一次只能处理一个事件信号，并返回下标最小事件下标，当其中一个信号一直发生时，后续事件将永远无法被处理的问题。

这里只解决只有一个事件被处理的问题。

```c
DWORD Wait_return = WSAWaitForMultipleEvents(es_set.count, es_set.event_all, FALSE, 0, FALSE);
        //函数错误
        if(Wait_return == WSA_WAIT_FAILED){
            printf("WAIT ERROR! 错误代码: %d\n",WSAGetLastError());
            break;
        }
        //超时
        if(Wait_return == WSA_WAIT_TIMEOUT){
            continue;
        }
DWORD event_index = Wait_return - WSA_WAIT_EVENT_0;
//因为WSAWaitForMultipleEvents函数返回的是最小的有响应的下标，从该下标往后遍历会更加高效

while(1){
    for(int nindex = event_index;nindex < es_set.count;++nindex){
        DWORD Wait_return = WSAWaitForMultipleEvents(1, es_set.event_all[nindex], FALSE, 0, FALSE);
        if(WSA_WAIT_FAILED == Wait_return){
            printf("ERROR! 错误代码: %d\n",WSAGetLastError());
            continue;
        }
        if(WSA_WAIT_TIMEOUT == Wait_return){
            continue;
        }

        //下面代码相同

        //得到下标对应事件
            WSANETWORKEVENTS NetworkEvents;
            int n_t_return = WSAEnumNetworkEvents(es_set.socket_all[event_index], es_set.event_all[event_index], &NetworkEvents);
            if(n_t_return == SOCKET_ERROR){
                printf("GETINDEX ERROR! 错误代码: %d\n",WSAGetLastError());
                break;
            }

            if(NetworkEvents.lNetworkEvents & FD_ACCEPT){
                if(NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0){ //等于0时为无错误码情况，正常处理
                    SOCKET ClientSocket = accept(es_set.socket_all[event_index], NULL, NULL);
                    if(ClientSocket == INVALID_SOCKET){
                        continue;
                    }
                    //给客户端SOCKET绑定事件
                    
                    /*
                    
                    省略
                    
                    */
}
```

还可以一组一组处理，使用结构体数组，和双重循环，还有一些细节的修改，由于字数原因，这里不做展示。

这里只介绍下 `memset`函数，用于将目标区域设置为指定字符

```c
void *memset(
   void *dest,
   int c,
   size_t count
);
```

例子

```c
struct event_socket_set es_set[20];
memset(es_set, 0, sizeof(event_socket_set)*20);
//将所有空间赋值为0
```



## 异步选择模型



**逻辑**

核心 - 消息队列，要使用消息队列先要创建窗口，操作系统为每个窗口创建一个消息队列并维护。

模型实现步骤：

1. 将SOCKET绑定在一个消息上并投递给系统，使用 `WSAAsyncSelect`函数
2. 取消息分类处理，有操作就会有对应的消息

**需要 `windows.h`头文件** ，**该模型只能用于windows**



**窗口的创建**

1. 创建窗口结构体 `WNDCLASSEX`
2. 注册窗口结构体 `RegisterClassEx`
3. 创建窗口 `CreateWindowEx`
4. 显示窗口 `ShowWindow`
5. 消息循环 `GetMessage、TranslateMessage、DispatchMessage`
6. 回调函数 `CALLBACK`



**WinMain应用程序入口点**

每个Windows程序都包含一个名为**WinMain**或**wWinMain**的入口点函数，相当于控制台程序的**Main**函数



**函数原型**

```c
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    return 0;
}
```

**WINAPI**是调用约定。一个*调用约定*定义了一个函数从主叫方接收参数。



**函数参数**

**参数一：** **HINSTANCE**为实例句柄(ID)，就是该程序的ID或名字

**参数二：**已不再使用，仅作兼容，之前用来跟踪应用程序的前一个实例，即程序的父亲的程序实例

**参数三：** **PWSTR**为命令行参数，用于传递数据

**参数四：** 指示是否将主应用程序窗口最小化，最大化或正常显示



**WNDCLASSEX结构体**

用于装窗口属性，这里带了后缀Ex为扩展版本



**结构体声明**

```c
typedef struct tagWNDCLASSEXA {
  UINT      cbSize;
  UINT      style;
  WNDPROC   lpfnWndProc;
  int       cbClsExtra;
  int       cbWndExtra;
  HINSTANCE hInstance;
  HICON     hIcon;
  HCURSOR   hCursor;
  HBRUSH    hbrBackground;
  LPCSTR    lpszMenuName;
  LPCSTR    lpszClassName;
  HICON     hIconSm;
} WNDCLASSEXA, *PWNDCLASSEXA, *NPWNDCLASSEXA, *LPWNDCLASSEXA;
```



**窗口结构体设置**

```c
    WNDCLASSEX SW; //创建窗口结构体
    SW.cbClsExtra = 0; //根据窗口类结构分配的额外字节数。系统将字节初始化为零。一般用不到，填0
    SW.cbSize = sizeof(WNDCLASSEX); //窗口结构体大小
    SW.cbWndExtra = 0; //窗口实例后要分配的额外字节数。系统将字节初始化为零.一般不用，填0。
    SW.hbrBackground = NULL; //窗口颜色，默认为白
    SW.hCursor = NULL; //设置光标形态
    SW.hIcon = NULL; //左上角图标
    SW.hIconSm = NULL; //最小化图标
    SW.hInstance = hInstance; //实例句柄，填参数一 
    SW.lpfnWndProc = xxxx; //填回调函数名字 
    SW.lpszClassName = "SynSelect"; //当前窗口类的名字，随便起一个
    SW.lpszMenuName =  NULL; //菜单
    SW.style = CS_HREDRAW | CS_VREDRAW; //窗口风格
    /*
    CS_HREDRAW 水平刷新  CS_VREDRAW 垂直刷新
    窗口改变时，需要重新绘制，不然窗口就无法正常显示
    */
```



**RegisterClassEx函数**

窗口结构体带Ex这里就要带

用于注册结构体

**参数：**窗口结构体地址



**CreateWindowEx函数**

用于创建窗口



**函数原型**

```c
HWND CreateWindowExW(
  DWORD     dwExStyle,
  LPCWSTR   lpClassName,
  LPCWSTR   lpWindowName,
  DWORD     dwStyle,
  int       X,
  int       Y,
  int       nWidth,
  int       nHeight,
  HWND      hWndParent,
  HMENU     hMenu,
  HINSTANCE hInstance,
  LPVOID    lpParam
);
```



**参数一：** 窗口风格，这里用 `WS_EX_OVERLAPPEDWINDOW` 正常风格

**参数二：** 窗口类名

**参数三：** 窗口名字，自定

**参数四：** 为窗口表面样式，这里用 ``WS_OVERLAPPEDWINDOW``，多个样式使用位或

**参数五与六：**为窗口起始坐标

**参数七与八：** 为窗口宽与高

**参数九：**副(子)窗口，我们这里没有，填`NULL`

**参数十：** 为菜单句柄，这里没有，填`NULL`

**参数十一：** 窗口句柄，填 `hInstance`

**参数十二：** 给回调函数传数据的参数，这里不需要，填`NULL`



**返回值**

返回值是新窗口的句柄



**创建窗口**

```c
CreateWindow(WS_EX_OVERLAPPEDWINDOW, "SynSelect", "SynSelect_Test", WS_OVERLAPPEDWINDOW, 200, 600, 400, NULL, NULL, hInstance, NULL);
```



**ShowWindow函数**

**参数一：** 要显示的窗口ID

**参数二：** 显示方式，填`1`为正常显示，填 `0`为最小化显示，可以填主函数参数四，它默认为`1`



**GetMessage函数**

用于从消息队列中取消息

**参数一：** 消息结构体地址

**参数二：** 窗口句柄或`NULL`，填句柄，则只从指定窗口(ID)获取消息，一个应用程序可能会有多个窗口，填 `NULL`为从整个程序窗口获取消息

**参数三与四：** 为消息范围，消息本质为宏是整数，都填0，为接收所有消息



**TranslateMessage函数**

翻译消息，对消息分类

**参数为窗口结构体地址**



**DispatchMessage函数**

分类处理，调用回调函数

**参数为窗口结构体地址**



**回调函数**

由系统调用

```c
LRESULT CALLBACK WinBack(HWND hwnd, UINT msgID, WPARAM wparam, LPARAM lparap)
{
    
}
```

**LRESULT**为返回类型，本质为long型

**CALLBACK**为调用约定

**参数一：** 为窗口句柄

**参数二：** 为消息ID

**参数三：** 装SOCKET

**参数四：** 装SOCKET具体事件与错误信息



### 窗口实现

```c
#include <stdio.h>
#include <Windows.h>

LRESULT CALLBACK WinBack(HWND hwnd, UINT msgID, WPARAM wparam, LPARAM lparap);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX WS; //创建窗口结构体
    WS.cbClsExtra = 0; //根据窗口类结构分配的额外字节数。系统将字节初始化为零。一般用不到，填0
    WS.cbSize = sizeof(WNDCLASSEX); //窗口结构体大小
    WS.cbWndExtra = 0; //窗口实例后要分配的额外字节数。系统将字节初始化为零.一般不用，填0。
    WS.hbrBackground = NULL; //窗口颜色，默认为白
    WS.hCursor = NULL; //设置光标形态
    WS.hIcon = NULL; //左上角图标
    WS.hIconSm = NULL; //最小化图标
    WS.hInstance = hInstance; //实例句柄，填参数一 
    WS.lpfnWndProc = WinBack; //填回调函数名字 
    WS.lpszClassName = "SynSelect"; //当前窗口类的名字，随便起一个
    WS.lpszMenuName =  NULL; //菜单
    WS.style = CS_HREDRAW | CS_VREDRAW; //窗口风格
    /*
    CS_HREDRAW 水平刷新  CS_VREDRAW 垂直刷新
    窗口改变时，需要重新绘制，不然窗口就无法正常显示
    */

   //注册窗口
   RegisterClassEx(&WS);

   //创建窗口
   HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "SynSelect", "SynSelect_Test", WS_OVERLAPPEDWINDOW, 200, 200, 600, 400, NULL, NULL, hInstance, NULL);

    //显示窗口
    ShowWindow(hwnd, 1);

    //重绘（刷新）窗口
    UpdateWindow(hwnd);

    //消息循环
    MSG msg; //创建消息结构体
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WinBack(HWND hwnd, UINT msgID, WPARAM wparam, LPARAM lparap)
{
    switch(msgID){
        case WM_CREATE: //窗口 初始化产生，只产生一次，可以放用于初始化的代码
            break;
        case WM_DESTROY: //这里WM_XX就是消息
            PostQuitMessage(0); //传递退出消息，没有的话窗口关闭不了
            break;
    }

    return DefWindowProc(hwnd, msgID, wparam, lparap); //对没有处理的消息默认处理
}
```



开始监听及以前代码与基本C\S模型相同



核心函数 `WSAAsyncSelect`，作用是给SOCEKT绑定消息，并投递给系统

**函数原型**

```c
int WSAAsyncSelect(
  SOCKET s,
  HWND   hWnd,
  u_int  wMsg,
  long   lEvent
);
```



**参数介绍**

**参数一：** SOCKET

**参数二：** 窗口句柄

**参数三：** 网络事件发生时要接收的消息，消息本身就是一个数，消息对应的数是唯一的

为防止与系统已定义的消息冲突，使用宏 `WM_USER`，这个宏以下的数为系统消息所占用，以上的我们可以自己使用

自定义消息，可以使用 `#define` 创建宏

```c
#define UM_ASYNSELECT WM_USER+1
//自定义消息一般以U开头
```

**参数四：** 给SOCKET绑定操作，与事件选择模型一样



如果SOCKET填的是服务器SOCKET，将其与消息绑定，有客户端链接时，消息就会被触发，然后我们捕获与处理



**返回值**

出错返回`SOCKET_ERROR`，成功返回`0`



**MessageBox函数**

显示一个模式对话框



**函数原型**

```c
int MessageBox(
  HWND    hWnd,
  LPCTSTR lpText,
  LPCTSTR lpCaption,
  UINT    uType
);
```



**参数介绍**

**参数一：** 要创建的消息框的所有者窗口的句柄。填句柄，则为该窗口的子窗口。如果此参数为**NULL**，则消息框为独立窗口

**参数二：** 要显示的消息

**参数三：** 窗口标题

**参数四：** 窗口风格



**TextOut函数**

在窗口上输出文本



**函数原型**

```c
BOOL TextOutA(
  HDC    hdc,
  int    x,
  int    y,
  LPCSTR lpString,
  int    c
);
```



**参数介绍**

**参数一：** 窗口显示区（去掉窗口名字显示的那个头部框的部分）的句柄

使用 `GetDC函数`得到该句柄，参数为窗口句柄，`HDC`类型

**参数二与三：** 显示字符串的位置

**参数四：** 要输出的字符串

**参数五：** 字符串长度



### 代码实现

```c
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <string.h>

#define UM_ASYNSELECT WM_USER+1
#define SOCKET_SIZE 1024

LRESULT CALLBACK WinBack(HWND hwnd, UINT msgID, WPARAM wparam, LPARAM lparap);

struct AllSockets {
    SOCKET sockets[SOCKET_SIZE];
    int count;
}; //存放所有SOCKET的结构体

struct AllSockets all_sockets;
int x = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX WS; //创建窗口结构体
    WS.cbClsExtra = 0; //根据窗口类结构分配的额外字节数。系统将字节初始化为零。一般用不到，填0
    WS.cbSize = sizeof(WNDCLASSEX); //窗口结构体大小
    WS.cbWndExtra = 0; //窗口实例后要分配的额外字节数。系统将字节初始化为零.一般不用，填0。
    WS.hbrBackground = NULL; //窗口颜色，默认为白
    WS.hCursor = NULL; //设置光标形态
    WS.hIcon = NULL; //左上角图标
    WS.hIconSm = NULL; //最小化图标
    WS.hInstance = hInstance; //实例句柄，填参数一 
    WS.lpfnWndProc = WinBack; //填回调函数名字 
    WS.lpszClassName = "SynSelect"; //当前窗口类的名字，随便起一个
    WS.lpszMenuName =  NULL; //菜单
    WS.style = CS_HREDRAW | CS_VREDRAW; //窗口风格
    /*
    CS_HREDRAW 水平刷新  CS_VREDRAW 垂直刷新
    窗口改变时，需要重新绘制，不然窗口就无法正常显示
    */

   //注册窗口
   RegisterClassEx(&WS);

   //创建窗口
   HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "SynSelect", "SynSelect_Test", WS_OVERLAPPEDWINDOW, 200, 200, 600, 400, NULL, NULL, hInstance, NULL);
	if (NULL == hwnd)
	{
		return 0;
	}

    //显示窗口
    ShowWindow(hwnd, 1);

    //重绘（刷新）窗口
    UpdateWindow(hwnd);

    WORD WSversion = MAKEWORD(2,2);  //版本号
    WSADATA ServerSocket;
    int return_WASA = WSAStartup(WSversion,&ServerSocket);
    if(return_WASA!=0){
        printf("初始化网络库失败!");
        WSACleanup();  //清理网络库
        return 0;
    }
    //启动网络库

    SOCKET Socket_Server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //创建服务端SOCKET Socket_Server
    if(Socket_Server == INVALID_SOCKET){
        //INVALID_SOCKET为socket函数返回失败值
        printf("创建SOCKET失败!");
        WSACleanup();
        return 0;
    }
    //创建SOCKDET

    all_sockets.count = 0;
    all_sockets.sockets[all_sockets.count] = Socket_Server;
    all_sockets.count++;
    //将服务端SOCKET装入数组

    struct sockaddr_in bind_info;
    bind_info.sin_family = AF_INET;
    bind_info.sin_port = htons(2333);
    bind_info.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //配置协议端口与IP地址

    int bind_return = bind(Socket_Server,(const struct sockaddr *)&bind_info,sizeof(bind_info));
    if(bind_return == SOCKET_ERROR){
        printf("绑定地址与端口失败!");
        closesocket(Socket_Server);  //关闭SOCKET
        WSACleanup();
        return 0;
    }

    int listen_return = listen(Socket_Server,10);
    //开始监听客户端连接
    if(listen_return == SOCKET_ERROR){
        printf("监听失败!");
        closesocket(Socket_Server);
        WSACleanup();
        return 0;
    } else {
        printf("Listening...\n");
    }

    //给SOCEKT绑定消息，并投递给系统
    if(WSAAsyncSelect(Socket_Server, hwnd, UM_ASYNSELECT, FD_ACCEPT) == SOCKET_ERROR){
        closesocket(Socket_Server);
        WSACleanup();
        return 0;
    }

    //消息循环
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    for(int n = 0; n<all_sockets.count; ++n){
        closesocket(all_sockets.sockets[n]);
        WSACleanup();
    } //关闭全部SOCKET与清理网络库

    return 0;
}

LRESULT CALLBACK WinBack(HWND hwnd, UINT msgID, WPARAM wparam, LPARAM lparam)
{
    SOCKET socket;
    HDC hdc = GetDC(hwnd); //获取窗口显示区句柄

    switch(msgID){
        case WM_CREATE: //窗口 初始化产生，只产生一次，可以放用于初始化的代码
            break;
        case WM_DESTROY: //这里WM_XX就是消息
            PostQuitMessage(0); //传递退出消息，没有的话窗口关闭不了
            break;
        case UM_ASYNSELECT:
            socket = (SOCKET)wparam; //获取SOCKET
            if(HIWORD(lparam) != 0){ //判断消息是否出错
                if(WSAECONNABORTED == HIWORD(lparam)){ //客户端关闭
                    WSAAsyncSelect(socket, hwnd, UM_ASYNSELECT, 0); //取消SOCKET上的消息
                    closesocket(socket);
                    for(int n =0; n<all_sockets.count; ++n){
                        if(socket == all_sockets.sockets[n]){
                            all_sockets.sockets[n] = all_sockets.sockets[all_sockets.count-1];
                            all_sockets.count--;
                            break;
                        }
                    }
                    TextOut(hdc, 0, x, "Client Close", strlen("Client Close"));
                    x+=15;
                }
                break;
            }

            //具体消息
            switch(LOWORD(lparam)){
                case FD_ACCEPT:
                    TextOut(hdc, 0, x, "Client Connect", strlen("Client Connect")); //输出字符
                    x+=15;
                    SOCKET Socket_Client = accept(socket, NULL, NULL);
                    if(Socket_Client == INVALID_SOCKET){
                        break;
                    }
                    MessageBox(NULL, "Client Connect!", "Prompt", MB_OK); //弹出窗口
                    //将客户端SOCKET绑定消息并投递给消息队列
                    if(WSAAsyncSelect(Socket_Client, hwnd, UM_ASYNSELECT, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR){
                        printf("ACCEPT ERROR! 错误代码: %d\n",WSAGetLastError());
                        closesocket(Socket_Client);
                        break;
                    }
                    all_sockets.sockets[all_sockets.count] = Socket_Client;
                    all_sockets.count++;
                    break;
                case FD_READ:
                {
					char recv_msg[1024] = { 0 };
					if (SOCKET_ERROR == recv(socket, recv_msg, 1023, 0))
					{
						break;
					}
					TextOut(hdc, 30, x, recv_msg, strlen(recv_msg));
					x += 15;
                }
                    break;
                case FD_WRITE:
                    TextOut(hdc, 0, x, "write", strlen("write"));
                    x+=15;
                    break;
                case FD_CLOSE:
                    WSAAsyncSelect(socket, hwnd, UM_ASYNSELECT, 0); //取消SOCKET上的消息
                    closesocket(socket);
                    for(int n =0; n<all_sockets.count; ++n){
                        if(socket == all_sockets.sockets[n]){
                            all_sockets.sockets[n] = all_sockets.sockets[all_sockets.count-1];
                            all_sockets.count--;
                            break;
                        }
                    }
                    TextOut(hdc, 0, x, "Client Close", strlen("Client Close"));
                    x+=15;

                    break;
            }

            break;
    }

    return DefWindowProc(hwnd, msgID, wparam, lparam); //对没有处理的消息默认处理
}
```



**优化：** 每个窗口维护一定的SOCKET，当SOCKET过多时，延迟会增大，我们可以创建多个线程，每个线程管理一个窗口，每个窗口投递一定数量的客户端。当然线程不是万能的，也有最大处理效率。

**问题：** 在一次处理过程中，客户端产生多次send，服务端会产生多次接收的消息，第一次接收消息会收完所有信息。



## 重叠IO模型



### 介绍

**意义：** 重叠IO是windows提供的一种异步读写文件的机制，SOCKET本质是文件操作，如`recv`，是阻塞的，等协议缓冲区的数据全部复制进buffer(缓冲区)里，函数才结束并返回复制的个数，写也一样，同一时间只能执行一个，也就是执行阻塞。

**作用：** 系统多开线程，同时处理(异步)

**实现：**将`accept、recv、send`优化为异步处理过程，用`AcceptEx、WSARecv、WSASend`函数代替它们，是对基本C/S模型的直接优化

**本质：** 结构体(重叠结构) `WSAOVERLAPPED`，定义一个该结构体的变量与SOCKET绑定

**使用：** 重叠IO模型把重叠结构与SOCKET绑定在一起并投递给系统，然后系统以重叠机制处理反馈

重叠IO反馈的两种方式：**事件通知** - 调用AcceptEx等函数并投递被完成的操作，事件信号被置为有信号，调用WSAWaitForMultipleEvents获取事件信号、**完成历程** - 回调函数。可以单独或者配合使用。

**性能：** 来源网络，普通电脑链接2w个SOCKET，同时请求send，CPU占用上涨40%(重叠IO模型)；完成端口CPU占用上涨2%左右



### 事件通知

**实现逻辑**

1. 创建重叠IO模型使用的SOCKET 使用 `WSAScoekt`创建
2. 投递-AcceptEx
   - 立即完成，系统空闲且正好有链接
     - 对客户端套接字投递 `WSARecv`
       1. 立即完成-处理信息，对客户端套接字投递 `WSARecv`
       2. 延迟完成-去循环等信号
     - 根据需求对客户端套接字投递 `WSASend`
       1. 立即完成-处理信息，根据需求投递 `WSASend`
       2. 延迟完成-去循环等信号
     - 对服务器套接字继续投递 `AcceptEx`,重复上述
   - 延迟完成，系统开线程等待链接(异步)，去循环里等信号，有就分类处理
3. 循环等信号
   - 等信号- `WSAWaitForMultipleEvents`函数
   - 有信号
     - 获取重叠结构上的信息 `WSAGetOverlappedResult`函数
     - 客户端退出，删除服务端的信息
     - 接收链接 - 投递  `AcceptEx`
     - 接收信息 - 处理消息，对客户端套接字投递 `WSARecv`
     - 发送消息，根据需求投递 `WSASend`



**WSASocket函数**

创建用于异步操作的SOCKET

`WSA`前缀的函数是windows专用的函数

**函数原型**

```c
SOCKET WSAAPI WSASocket(
  int                 af,
  int                 type,
  int                 protocol,
  LPWSAPROTOCOL_INFOW lpProtocolInfo,
  GROUP               g,
  DWORD               dwFlags
);
```

**参数介绍**

与原 `socket`函数参数不同的参数：

**参数四：** 定义了要创建的套接字的特性，不使用填 `NULL`，这里用不到

**参数五：** 保留参数，暂时无用，填`0`

**参数六：** 指定套接字属性，填 **`WSA_FLAG_OVERLAPPED`** - 创建一个支持重叠IO操作的套接字



**返回值**

成功，返回可用套接字，失败返回 `INVALID_SOCKET`



**AcceptEx函数**

投递服务器SOCKET，让操作系统开一根线程监视，随时接收客户端链接



**函数原型**

```C
BOOL AcceptEx(
  SOCKET       sListenSocket,
  SOCKET       sAcceptSocket,
  PVOID        lpOutputBuffer,
  DWORD        dwReceiveDataLength,
  DWORD        dwLocalAddressLength,
  DWORD        dwRemoteAddressLength,
  LPDWORD      lpdwBytesReceived,
  LPOVERLAPPED lpOverlapped
);
```

**参数介绍**

**参数一：** 服务器SOCKET

**参数二：** 自定义SOCKET，有客户端链接时，IP与端口号绑定在此

**参数三：** 指向缓冲区的指针，客户端发来的第一组数据由该参数(字符数组)接收，第二次以后由`recv`接收，不能设置为`NULL`

**参数四：** 参数三数组大小，设置`0`，取消参数三的功能，一般用不到三，所以我们填0

**参数五：** 为本地地址信息保留的字节数，该值必须比使用的传输协议的最大地址长度至少多16个字节，不能为0，**存储客户端IP与端口号**

**参数六：** 为远程地址信息保留的字节数，该值必须比使用的传输协议的最大地址长度至少多16个字节。不能为零。与参数五填一样就行。

**参数七：** 填NULL

**参数八：** 服务器SOCKET的重叠结构



**返回值**

立即完成返回 `TRUE`，出错返回 `FALSE`

使用 `WSAGetLastError`函数得到错误代码，若为 `ERROR_IO_PENDING`表示延时处理需要单独处理，其他错误码为错误



**WSARecv函数**

投递异步接收信息

**函数原型**

```c
int WSAAPI WSARecv(
  SOCKET                             s,
  LPWSABUF                           lpBuffers,
  DWORD                              dwBufferCount,
  LPDWORD                            lpNumberOfBytesRecvd,
  LPDWORD                            lpFlags,
  LPWSAOVERLAPPED                    lpOverlapped,
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
```

**函数参数**

**参数一：** 客户端SOCKET

**参数二：** 接收后信息储存的缓冲区 `WSABUF`型结构体

**WSABUF**：成员一为缓冲区的长度，以字节为单位，成员二为指向缓冲区的指针

使用示例

```c
WSABUF wsabuf;
char str[1024] = {0};
wsabuf.buf = str;
wsabuf.len = 1024;
```

**参数三：** 是`WSABUF`的个数

**参数四：** 接收成功装成功接收到的字符数。参数六为NULL时，不能为NULL

**参数五：** 指向用于修改**WSARecv**函数调用行为的标志的指针 ，填 **`MSG_PUSH_IMMEDIATE`**-该标志允许使用流套接字的应用程序告诉传输提供者不要延迟部分填充的未决接收请求的完成。处理小信息好。

**参数六：** 对应SOCKET的重叠结构

**参数七：** 回调函数，完成例程时使用，这里填 `NULL`



**返回值**

立即发生返回0， 错误返回`SOCKET_ERROR`，使用`WSAGetLastError`函数得到错误代码，若为 `ERROR_IO_PENDING`表示延时处理需要单独处理



**WSAGetOverlappedResult函数**

获取对应SOCKET上的具体情况：客户端链接、消息等

**函数原型**

```c
BOOL WSAAPI WSAGetOverlappedResult(
  SOCKET          s,
  LPWSAOVERLAPPED lpOverlapped,
  LPDWORD         lpcbTransfer,
  BOOL            fWait,
  LPDWORD         lpdwFlags
);
```

**参数介绍**

**参数一：** 有信号的SOCKET

**参数二：** 对应的重叠结构

**参数三：** 发送或者接收到的实际字节数，不能为`NULL`,参数为0表示客户端下线

**参数四：** 选择事件通知模型填`TRUE`

**参数五：** 装`WSARecv`的参数五，不能是`NULL`，如果重叠操作是通过`WSARecv`或 `WSARecvFrom`启动的 ，则此参数将包含`lpFlags`参数的结果值。此参数不能为`NULL`指针。



**返回值**

成功返回 `TRUE`， 错误返回 `FALSE`，获得错误码，如果为`10054`则为客户端强制退出



**WSASend函数**

**函数原型**

```c
int WSAAPI WSASend(
  SOCKET                             s,
  LPWSABUF                           lpBuffers,
  DWORD                              dwBufferCount,
  LPDWORD                            lpNumberOfBytesSent,
  DWORD                              dwFlags,
  LPWSAOVERLAPPED                    lpOverlapped,
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
```

**参数介绍**

**参数一：** 客户端SOCKET

**参数二：** 接收信息储存的buffer

**参数三：** WSABUF的个数

**参数四：** 接收成功，装发送成功的字节数

**参数五：** 函数调用行为标志

**参数六：** 重叠结构

**参数七：** 回调函数



**返回值**

立即发生：`0    失败` `SOCKET_ERROR` 获取错误代码若为 `ERROR_IO_PENDING`表示延时处理需要单独处理





### 事件通知代码实现

```c
#include <stdio.h>
#include <winsock2.h>
#include <mswsock.h>

#define MAXSIZE_SOCKET 1024
#define MAXSIZE_BUF 1024

SOCKET allsocket[MAXSIZE_SOCKET]; //创建SOCKET数组
OVERLAPPED alloverlapp[MAXSIZE_SOCKET]; //创建重叠结构体数组
int count;
char str[MAXSIZE_BUF] = {0}; // 接收缓冲区

int PostAccept();
int PostRecv(int);
int PostSend(int);
void Clear(); //清理函数

int main(void)
{
    WORD WSversion = MAKEWORD(2,2);  //版本号
    WSADATA ServerSocket;
    int return_WASA = WSAStartup(WSversion,&ServerSocket);
    if(return_WASA!=0){
        printf("初始化网络库失败!");
        WSACleanup();  //清理网络库
        return 0;
    }
    //启动网络库

    SOCKET Socket_Server = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    //创建服务端SOCKET Socket_Server
    if(Socket_Server == INVALID_SOCKET){
        //INVALID_SOCKET为socket函数返回失败值
        printf("创建SOCKET失败!");
        WSACleanup();
        return 0;
    }
    //创建SOCKDET

    struct sockaddr_in bind_info;
    bind_info.sin_family = AF_INET;
    bind_info.sin_port = htons(2333);
    bind_info.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //配置协议端口与IP地址

    int bind_return = bind(Socket_Server,(const struct sockaddr *)&bind_info,sizeof(bind_info));
    if(bind_return == SOCKET_ERROR){
        printf("绑定地址与端口失败!");
        closesocket(Socket_Server);  //关闭SOCKET
        WSACleanup();
        return 0;
    }

    int listen_return = listen(Socket_Server,10);
    //开始监听客户端连接
    if(listen_return == SOCKET_ERROR){
        printf("监听失败!");
        closesocket(Socket_Server);
        WSACleanup();
        return 0;
    } else {
        printf("Listening...\n");
    }

    allsocket[count] = Socket_Server;
    alloverlapp[count].hEvent = WSACreateEvent(); //给重叠结构的事件成员赋值一个合法的事件
    count++;

    if(PostAccept() != 0){
        Clear();
        return 0;
    } //函数的调用逻辑比较复杂，我们封装成一个函数

    while(1){ //循环等待事件
        for(int n = 0;n < count;++n){
            int wait_return = WSAWaitForMultipleEvents(1, &alloverlapp[n].hEvent, FALSE, 0, FALSE);
            if(wait_return == WSA_WAIT_TIMEOUT || wait_return == WSA_WAIT_FAILED){ //超时或错误
                continue;
            }
            DWORD dwstate;
            DWORD dwflag;
            BOOL get_return = WSAGetOverlappedResult(allsocket[n], &alloverlapp[n], &dwstate, TRUE, &dwflag);

            WSAResetEvent(alloverlapp[n].hEvent); //信号制空

            if(get_return == FALSE){
                if(GetLastError() == 10054){
                    printf("Client Close\n");
                    closesocket(allsocket[n]);
                    WSACloseEvent(alloverlapp[n].hEvent);
                    allsocket[n] = allsocket[count-1];
                    alloverlapp[n] = alloverlapp[count-1];
                    n--; //循环控制变量减一
                    count--; //个数减一
                }
                continue;
            }
            if(n == 0){ //接受链接完成
                printf("Client Connect\n");
                PostRecv(count);
                count++;
                PostAccept();
                continue;
            }
            if(dwstate == 0){ //客户端下线
                printf("Client Close\n");
                closesocket(allsocket[n]);
                WSACloseEvent(alloverlapp[n].hEvent);
                allsocket[n] = allsocket[count-1];
                alloverlapp[n] = alloverlapp[count-1];
                n--; //循环控制变量减一
                count--; //个数减一
                continue;
            }
            if(dwstate != 0){ //发送或者接收成功
                if(str[0] != 0){ //接收成功
                    printf("Client: %s\n", str);
                    memset(str, 0, MAXSIZE_BUF); //打印信息与清空缓冲区
                    PostRecv(n); //递归，继续投递recv
                } else { //发送成功
                    printf("Send Success\n");
                }
            }
        }
    }

    Clear();
    return 0;
}

int PostAccept()
{
    allsocket[count] =  WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED); //使用socket函数也可以，但该函数更好
    alloverlapp[count].hEvent = WSACreateEvent();
    char str[1024] = {0};
    BOOL Acp_return = AcceptEx(allsocket[0], allsocket[count], str, 0, sizeof(struct sockaddr_in)+16, sizeof(struct sockaddr_in)+16, NULL, &alloverlapp[0]); //基本地址长度为sizeof(struct sockaddr_in)
    if(Acp_return == FALSE){ //错误处理
    int error = WSAGetLastError();
        if(error == ERROR_IO_PENDING){
            return 0; //延时处理
        } else {
            return error; //出错
        }
    } else {
        //立即完成
        PostRecv(count); //投递recv
        count++;
        PostAccept(); //立即完成就递归
    }

    return 0;
}

int PostRecv(int index)
{
    WSABUF wsabuf;
    wsabuf.buf = str;
    wsabuf.len = MAXSIZE_BUF;
    DWORD buffcount;
    DWORD dwflag = 0;
    int recv_return = WSARecv(allsocket[index], &wsabuf, 1, &buffcount, &dwflag, &alloverlapp[index], NULL);
    if(recv_return == 0){
        //立即完成
        if(str[0] != 0){
            printf("Client: %s", str);
            memset(str, 0, MAXSIZE_BUF); //打印信息与清空缓冲区
        }
        PostRecv(index); //递归，继续投递recv
        return 0;
    } else {
        int error = WSAGetLastError();
        if(error == WSA_IO_PENDING){
            return 0; //延迟处理
        }
        return error;
    }

}

int PostSend(int index)
{
    WSABUF wsabuf;
    wsabuf.buf = "Hello";
    wsabuf.len = MAXSIZE_BUF;
    DWORD dwSendCount;
	DWORD dwFlag = 0;
	int nRes = WSASend(allsocket[index], &wsabuf, 1, &dwSendCount, dwFlag, &alloverlapp[index], NULL);

	if (0 == nRes)
	{
		//立即完成的
		//打印信息
		printf("send成功\n");
		
		return 0;
	}
	else
	{
		int a = WSAGetLastError();
		if (ERROR_IO_PENDING == a)
		{
			//延迟处理
			return 0;
		}
		else
		{
			return a;
		}
	}
}

void Clear()
{
    for(int n = 0;n < count; ++n){
        closesocket(allsocket[n]);
        WSACloseEvent(alloverlapp[n].hEvent);
    }
    WSACleanup();
}
```



### 完成例程

**本质：** 为我们的SOCKET，重叠结构绑定一个函数，当异步操作完成时，系统异步自动调用这个函数 ， `send`绑一个 `recv`绑一个，完成就调用各自的函数，然后我们在函数内做相应的操作。在分类方式上，完成例程性能更好，系统自动调用处理

**逻辑：** 与事件通知基本相同，延时处理变成了回调函数处理

**不同：** 在函数 `WSARecv WSASend` 最后一个参数上填上回调函数



**回调函数介绍**

**LPWSAOVERLAPPED_COMPLETION_ROUTINE回调函数**



**函数原型**

```c
void CALLBACK LpwsaoverlappedCompletionRoutine(
  DWORD dwError,
  DWORD cbTransferred,
  LPWSAOVERLAPPED lpOverlapped,
  DWORD dwFlags
);
```

**参数介绍**

**参数一：** 错误码

**参数二：** 发送或接收到的字节数

**参数三：** 重叠结构

**参数四：** 函数的执行方式

与 `WSAGetOverlappedResult`函数对比，参数基本相同

**处理流程**

`dwError=10054`-强行退出，删除客户端

`cbTransferred=0`，正常退出；不等于0，接收成功

都不是，得到或发送完数据，继续投递接收请求



**完成例程事件分类处理**

由于所有的客户端的响应都在回调函数中做了，在 `WSAWaitForMultipleEvents`等待循环中就不用再处理了，只用处理服务器`SOCKET`对应事件就行了，`WSAWaitForMultipleEvents`函数参数五设置 `WSA_INFINITE`一直等待，参数六填 `TRUE`，将事件等待与完成例程机制结合在一起，实现等待事件函数与完成例程函数异步执行，完成例程函数执行完并给等待事件函数信号，事件函数返回  `WSA_WAIT_IO_COMPLETION`，被等待函数接收。此时返回值判断需要修改。



### **完成例程代码实现**

```c
#include <stdio.h>
#include <winsock2.h>
#include <mswsock.h>

#define MAXSIZE_SOCKET 1024
#define MAXSIZE_BUF 1024

SOCKET allsocket[MAXSIZE_SOCKET]; //创建SOCKET数组
OVERLAPPED alloverlapp[MAXSIZE_SOCKET]; //创建重叠结构体数组
int count;
char str[MAXSIZE_BUF] = {0}; // 接收缓冲区

int PostAccept();
int PostRecv(int);
int PostSend(int);
void CALLBACK Recv_call(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
void CALLBACK Send_call(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
void Clear(); //清理函数

int main(void)
{
    WORD WSversion = MAKEWORD(2,2);  //版本号
    WSADATA ServerSocket;
    int return_WASA = WSAStartup(WSversion,&ServerSocket);
    if(return_WASA!=0){
        printf("初始化网络库失败!");
        WSACleanup();  //清理网络库
        return 0;
    }
    //启动网络库

    SOCKET Socket_Server = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    //创建服务端SOCKET Socket_Server
    if(Socket_Server == INVALID_SOCKET){
        //INVALID_SOCKET为socket函数返回失败值
        printf("创建SOCKET失败!");
        WSACleanup();
        return 0;
    }
    //创建SOCKDET

    struct sockaddr_in bind_info;
    bind_info.sin_family = AF_INET;
    bind_info.sin_port = htons(2333);
    bind_info.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //配置协议端口与IP地址

    int bind_return = bind(Socket_Server,(const struct sockaddr *)&bind_info,sizeof(bind_info));
    if(bind_return == SOCKET_ERROR){
        printf("绑定地址与端口失败!");
        closesocket(Socket_Server);  //关闭SOCKET
        WSACleanup();
        return 0;
    }

    int listen_return = listen(Socket_Server,10);
    //开始监听客户端连接
    if(listen_return == SOCKET_ERROR){
        printf("监听失败!");
        closesocket(Socket_Server);
        WSACleanup();
        return 0;
    } else {
        printf("Listening...\n");
    }

    allsocket[count] = Socket_Server;
    alloverlapp[count].hEvent = WSACreateEvent(); //给重叠结构的事件成员赋值一个合法的事件
    count++;

    if(PostAccept() != 0){
        Clear();
        return 0;
    } //函数的调用逻辑比较复杂，我们封装成一个函数

    while(1){ //循环等待事件
        int wait_return = WSAWaitForMultipleEvents(1, &(alloverlapp[0].hEvent), FALSE, WSA_INFINITE, TRUE);
        if(wait_return == WSA_WAIT_IO_COMPLETION || wait_return == WSA_WAIT_FAILED){ //完成例程执行完或错误
            continue;
        }

        WSAResetEvent(alloverlapp[0].hEvent); //信号制空
        printf("Client Connect\n");
        PostRecv(count);
        count++;
        PostAccept();
    }

    Clear();
    return 0;
}

int PostAccept()
{
    allsocket[count] =  WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED); //使用socket函数也可以，但该函数更好
    alloverlapp[count].hEvent = WSACreateEvent();
    char str[1024] = {0};
    BOOL Acp_return = AcceptEx(allsocket[0], allsocket[count], str, 0, sizeof(struct sockaddr_in)+16, sizeof(struct sockaddr_in)+16, NULL, &alloverlapp[0]); //基本地址长度为sizeof(struct sockaddr_in)
    if(Acp_return == FALSE){ //错误处理
    int error = WSAGetLastError();
        if(error == ERROR_IO_PENDING){
            return 0; //延时处理
        } else {
            return error; //出错
        }
    } else {
        //立即完成
        PostRecv(count); //投递recv
        count++;
        PostAccept(); //立即完成就递归
    }

    return 0;
}

int PostRecv(int index)
{
    WSABUF wsabuf;
    wsabuf.buf = str;
    wsabuf.len = MAXSIZE_BUF;
    DWORD buffcount;
    DWORD dwflag = 0;
    int recv_return = WSARecv(allsocket[index], &wsabuf, 1, &buffcount, &dwflag, &alloverlapp[index], Recv_call);
    if(recv_return == 0){
        //立即完成
        if(str[0] != 0){
            printf("Client: %s", str);
            memset(str, 0, MAXSIZE_BUF); //打印信息与清空缓冲区
        }
        PostRecv(index); //递归，继续投递recv
        return 0;
    } else {
        int error = WSAGetLastError();
        if(error == WSA_IO_PENDING){
            return 0; //延迟处理
        }
        return error;
    }

}

int PostSend(int index)
{
    WSABUF wsabuf;
    wsabuf.buf = "Hello";
    wsabuf.len = MAXSIZE_BUF;
    DWORD dwSendCount;
	DWORD dwFlag = 0;
	int nRes = WSASend(allsocket[index], &wsabuf, 1, &dwSendCount, dwFlag, &alloverlapp[index], Send_call);

	if (0 == nRes)
	{
		//立即完成的
		//打印信息
		printf("send成功\n");

		return 0;
	}
	else
	{
		int a = WSAGetLastError();
		if (ERROR_IO_PENDING == a)
		{
			//延迟处理
			return 0;
		}
		else
		{
			return a;
		}
	}
}

void Clear()
{
    for(int n = 0;n < count; ++n){
        closesocket(allsocket[n]);
        WSACloseEvent(alloverlapp[n].hEvent);
    }
    WSACleanup();
}

void CALLBACK Recv_call(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
    int index = lpOverlapped - &alloverlapp[0];
    if(dwError == 10054 || cbTransferred == 0){ //客户端退出
        printf("Client Close\n");
        int index = lpOverlapped - &alloverlapp[0];
        closesocket(allsocket[index]);
        WSACloseEvent(alloverlapp[index].hEvent);
        allsocket[index] = allsocket[count-1];
        alloverlapp[index] = alloverlapp[count-1];
        count--;
    } else {
        if(str[0] != 0){
            printf("Client: %s\n", str);
            memset(str, MAXSIZE_BUF, 0);
        }
        PostRecv(index);
    }
}

void CALLBACK Send_call(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
    printf("Send Success\n");
}
```



**简单总结**

事件通知是我们自己分配任务，顺序不能保证，循环次数多，下标越大客户端延迟越大

完成例程是客户端根据具体事件自动调用代码，自动分类处理问题与异步选择相似



## 完成端口模型



# 完结

本教程到此结束，你学废了吗？有问题的小伙伴们欢迎在评论区友好交流。

