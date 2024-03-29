---
title: PcNetwork_ChapterFour
coments: true
date: 2021-10-29 11:19:15
tags: [Network]
---

# 第四章-网络层: 数据平面



## 4.1-网络层概述

每台路由器的**数据平面**的主要作用是从其输入链路向其输出链路转发数据报

**控制平面**的主要作用是协调这些本地的每路由器转发动作，使得数据报沿着源和目的地主机之间的路由器路径最终进行端到端传送



### 4.1.1-转发和路由选择：数据平面和控制平面

**转发：**是数据平面实现的唯一功能，是指将分组从一个输人链路接口转移到适当的输出链路接口的路由器本地动作，使用硬件实现，时间尺度小

**路由选择：**是指确定分组从源到目的地所采取的端到端路径的网络范围处理过程，使用软件实现，时间尺度大

**转发表：**路由器检查到达分组首部的一个或多个字段值，进而使用这些首部值在其转发表中索引，将分组转发到合适的出链路

**路由选择算法**决定了插入转发表的内容



#### 控制平面：SDN方法

下图是路由选择厂商在其产品中采用的传统方法，至少最近还是如此

![network_4_1](/images/network_4_1.png)



将路由的数据平面与控制平面分离的方法，路由选择设备仅执行转发，而远程控制器计算并分发转发表，被称为**软件定义网络SDN**



![network_4-2](/images/network_4-2.png)



### 4.1.2-网络服务模型

因特网的网络层仅提供**尽力而为服务**，但也能服务的足够好





## 4.2-路由器工作原理



![network_4_3](/images/network_4_3.png)

**输入端口：**最边缘执行物理层功能，中间执行数据链路层功能，而最内层执行查找功能-查询转发表决定输出端口，即转发决策功能在输入端实现

**交换结构：**将路由器的输入端口连接到输出端口

**输出端口：**存储交换结构接收的分组

**路由选择处理器：**执行控制平面功能。传统路由器中执行路由选择协议，维护路由选择表与关联链路状态信息，并为该路由器计算转发表；SDN路由器中负责与远程控制器通信，目的是接收由远程控制器计算的转发表项，并在该路由器的输入端口安装这些表项

以上都为硬件实现



### 4.2.1-输入端口处理和基于目的地转发

转发表是由路由选择处理器计算和更新的，转发表从路由选择处理器经过独立总线复制到线路卡，输入端口使用转发表的副本进行索引



转发表不能表示出每一种IP与其对应的转发决策，只能使用一定数量的前缀提供匹配

![network_4_4](/images/network_4_4.png)

路由器用分组目的地址的**前缀**与该表中的表项进行匹配

当有多个匹配时，该路由器使用**最长前缀匹配规则**，使用最长的匹配项



### 4.2.2-交换

![network_4_5](/images/network_4_5.png)

**经内存交换：**最简单、最早的路由器是传统的计算机，需要经过两次内存读写，在输入端口与输出端口之间的交换是在CPU的直接控制下完成的，系统总线一次仅能执行一个内存读写，不能同时处理两个分组，许多现代路由器也使用这种交换

**经总线交换：**输入端口经一根共享总线将分组直接传送到输出端口． 不需要CPU的干预，但总线一次也仅允许一个分组的传输

**经互联网络交换：**也称纵横式交换，有多个总线，能够并行转发多个分组，只要输入或输出端口不是一样的



### 4.2.3-输出端口处理

取出输出缓存分组并传送



### 4.2.4-何处出现排队

输入端口与输出端口都有可能出现排队



### 4.2.5-分组调度



#### 1 . 先进先出

FIFO，先到达的分组先传送



#### 2. 优先权排队

可将分组分为具有更高优先级类别，优先传输，同优先级按照FIFO

**非抢占式优先权排队：**一旦分组开始传输就不能打断



#### 3. 循环和加权公平排队



**循环排队规则**

分组被分为几类，传输一类的一个分组后传输下一个类别的分组，如果展示没有分组到达，则传输下一个类别，循环往复



**加权公平排队WFQ**

到达的分组被分类并在合适的每个类的等待区域排队

![network_4_6](/images/network_4_6.png)

如循环一样每次服务一个类，类别为空则服务下一个类，与循环排队不同的是，每次对类的服务可能不止服务一个分组，每个类都被分配一个权w_i，第i类能确保收到的服务部分为`w_i/∑w_n`



## 4.3-网际协议：IPv4 、寻址、IPv6 及其他



### 4.3.1-IPv4 数据报格式

![network_4_7](/images/network_4_7.png)

**版本字段：**规定IP协议版本，不同的版本有不同的数据报格式

**首部长度：**数据报首部长度，由于选项字段可选，长度不是一定的，需要该字段确定数据载荷位置

**服务类型：**提供特定等级服务

**数据报长度：**IP数据报总长度(字节)

**标识、标志、偏移：**与IP分片有关

**寿命：**TTL，用来确保数据报不会永远在网络中循环，每当一台路由器处理数据报时，该字段的值减1 ，若TTL字段减为0, 则该数据报必须丢弃

**协议：**表明要交付给特定的运输层协议，6-TCP，17-UDP

**首部检验和：**将首部中的每2 个字节当作一个数，用反码算术对这些数求和，类似于UDP检验和

**源和目的IP 地址：**4字节

**选项：**选项字段允许IP 首部被扩展，IPV6已移除

**数据：**有效载荷



### 4.3.2-IPv4 数据报分片

- 并不是所有链路层协议都能承载相同长度的网络层分组

- 一个链路层帧能承载的最大数据量叫作**最大传送单元MTU**，MTU 严格地限制着IP数据报的长度

- 当链路层帧无法容纳数据报时，会将数据报分片成两个或多个较小的数据报，用单独的链路层帧封装，称为**片**

- 片在其到达目的地运输层以前需要重新组装，IPv4 的设计者将数据报的重新组装工作放到端系统中

- 当生成一个数据报时，发送主机在为该数据报设置源和目的地址的同时贴上标识号, 发送主机通常将它发送的每个数据报的标识号加1当某路由器需要对一个数据报分片时， 形成的每个数据报（即片）具有初始数据报的源地址、目的地址与标识号

- 最后一个片的标志比特被设为0 、而所有其他片的标志比特被设为1

- 使用偏移字段指定该片应放在初始IP数据报的哪个位置



### 4.3.3 IPv4 编址

主机与物理链路之间的边界叫作**接口**

路由器与它的任意一条链路之间的边界也叫作接口。一台路由器因此有多个接口．每个接口有其链路

**一个IP地址与一个接口相关联，而不是与包括该接口的主机或路由器相关联**

每个IP 地址长度为32 比特（等价为4 字节），采用**点分十进制记法**，每八位用句点隔开，每个字节用十进制表示

地址不能随意地自由选择。一个接口的IP 地址的一部分需要由其连接的子网来决定





![network_4_8](/images/network_4_8.png)

上图有三个子网，每个子网都有相同的前缀，形如223.1.1.x

其前24位是相同的，该子网可表示为223.1.1.0/24，/24称为**子网掩码**，指示32 比特中的最左侧24 比特定义了子网地址

任何其他要连到223.1.1.0/24网络的主机都要求其地址具有223.1.1. XXX 的形式

**确定子网的方法**：

分开主机和路由器的每个接口，产生几个隔离的网络岛，使用接口端接这些隔离的网络的端点这些隔离的网络中的每一个都叫作一个**子网**

因特网的地址分配策略被称为**无类别域间路由选择**

形式为a. b. c. d/x的地址的元最高比特构成了IP 地址的网络部分，并且经常被称为该地址的**前缀**

一个组织可使用一段具有相同前缀的IP，路由器仅需查询前缀即可确定路径，节约了转发表项

一个地址的剩余32 - x． 比特可认为是用于区分该组织内部设备的，当该组织内部的路巾器转发分组时，才会考虑这些比特

**IP 广播地址255.255.255.255**

当一台主机发出一个目的地址为255.255.255. 255 的数据报时，该报文会交付给同一个网络中的所有主机。路由器也会有选择地向邻近的子网转发该报文



#### 1 . 获取一块地址

**组织**从ISP获取一块连续地址



#### 2. 获取主机地址：动态主机配置协议

- 主机想从当前组织获取地址使用**动态主机配置协议DHCP**
- DHCP 允许主机自动获取一个IP 地址
- 网络管理员能够配置DHCP, 以使某给定主机每次与网络连接时能得到一个相同的IP 地址， 或者某主机将被分配一个临时的IP 地址

- 由于DHCP 具有将主机连接进一个网络的网络相关方面的自动能力，故它又常被称为即插即用协议或零配置协议

- 每个子网将具有一台DHCP服务器，如果在某子网中没有服务器，则需要一个DHCP 中继代理（通
  常是一台路由器），这个代理知晓用于该网络的DHCP服务器的地址

![network_4_9](/images/network_4_9.png)



**DHCP协议是一个4个步骤的过程**

- **DHCP 服务器发现：**新到达的主机要获取IP需要使用UDP协议向所在网络广播**DHCP发现报文**，该报文使用源地址为0.0.0.0，目的主机地址为广播地址，目的端口号为67
- **DHCP 服务器提供：**DHCP 服务器收到一个DHCP 发现报文时，用**DHCP提供报文**响应，也是使用广播，该报文包含发现报文的事务ID 、向客户推荐的IP 地址、网络掩码以及IP 地址租用期等，一个子网中可能有多个DHCP服务器
- **DHCP 请求：**新到达的客户从一个或多个服务器提供中选择一个，并向选中的服务器提供用DHCP请求报文进行响应，回显配置的
  参数
- **DHCP ACK：**服务器用DHCP ACK 报文对DHCP 请求报文进行响应， 证实所要求的参数。

客户收到ACK即完成



### 4.3.4-网络地址转换

**网络地址转换-NAT**

NAT使能的路由器有一个接口，与设备构成一个子网

**专用网络或具有专用地址的地域：**具有专用地址的地域是指其地址仅对该网络中的设备有意义的网络，该地址仅在其子网内有意义

NAT 路由器对外界的行为就如同一个具有单一IP地址的单一设备，所有离开家庭路由器流向更大因特网的报文都拥有一个源IP 地址138. 76.29.7, 且所有进入家庭的报文都拥有同一个目的IP 地址138. 76.29.7 ，对外界隐藏了家庭网络的细节



![network_4_10](/images/network_4_10.png)

NAT 路由器使用一张NAT转换表，在表项中包含了端口号及其IP 地址

NAT 已成为因特网的一个重要组件，成为所谓**中间盒**

中间盒并不执行传统的数据报转发，而是执行诸如NAT 、流蜇流的负载均衡、流量防火墙（参见下面的插入框内容）等功能



### 4.3.5-IPv6



#### 1. IPv6数据报格式

特点：

- IP地址长度扩展到128比特(16字节)
- 简化高效的40字节首部
- 流标签

![network_4_11](/images/network_4_11.png)

**版本：**IPV6使用6作为版本号

**流量类型：**提供优先权服务

**下一个首部：**段标识数据报中的内容（数据字段）需要交付给哪个协议，使用与IPv4 首部中协议字段相同的值



IPv6 不允许在中间路由器上进行分片与重新组装，如果路由器收到的IPv6 数据报因太大而不能转发到出链路上的话，则路由器只需丢掉该数据报，并向发送方发回一个“分组太大”的ICMP差错报文即可

因为冗余去除了检验和字段



#### 2. 从IPv4 到IPv6 的迁移

虽然新型IP面使能系统可做成向后兼容，即能发送、路由和接收lPv4 数据报、但已部署的具有IPv4 能力的系统却不能够处理IPv6 数据报

目前使用的是**建隧道**技术

两个IPv6 节点要使用IPv6 数据报进行交互但它们是经由中间IPv4 路由器互联的。我们将两台IPv6 路巾器之间的中间IPv4 路由器的集合称为一个隧道

隧道接收端的lPv6 节点最终收到该IPv4 数据报，并确定该IPv4 数据报含有一个IPv6 数据报（通过观察在IPv4 数据报中的协议号字段是41），从中取出IPv6 数据报，然后再为该IPv6 数据报提供路由

![network_4_12](/images/network_4_12.png)



## 4.4-通用转发和SON



在基于目的地转发中，通过“匹配”加“动作”来实现功能，对应SDN，这种“匹配”加“动作”变得更为通用，不仅匹配IP和执行转发



![network_4_13](/images/network_4_13.png)

每台分组交换机中的一张匹配加动作表，由远程控制器计算、安装和更新。



**OpenFlow**是一个得到高度认可和成功的标准，它已经成为匹配加动作转发抽象、控制器以及更为一般的SDN 革命等概念的先驱

匹配加动作转发表在OpenFlow 中称为**流表**

- **首部宇段值的集合:**入分组将与之匹配，匹配不上流表项的分组将被丢弃或发送到远程控制器做更多处理
- **计数器集合:**当分组与流表项匹配时更新计数器
- **采取的动作集合:**丢弃、复制、转发等



### 4.4.1-匹配

OpenFlow 的匹配抽象允许对来自三个层次的协议首部所选择的字段进行匹配

![network_4_14](/images/network_4_14.png)



### 4.4.2-动作

重要的动作：转发、丢弃、修改首部字段



### 4.4.3-匹配加动作操作中的OpenFlow例子(看书)

