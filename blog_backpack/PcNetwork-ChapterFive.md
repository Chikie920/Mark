---
title: PcNetwork_ChapterFive
coments: true
date: 2021-11-01 11:28:00
tags: [Network]
---

# 第五章-网络层：控制平面



## 5.1-概述



- **每路由器控制：**每台路由器有一个路由选择组件，用于与其他路由器中的路由选择组件通信，以计算其转发表的值，在因特网中已经使用了几十年
- **逻辑集中式控制：**逻辑集中式控制器计算并分发转发表以供每台路由器使用



在逻辑集中式控制中，每台路由器有一个**控制代理CA**与控制器交互，并按控制器命令行事

![network_5_1](/images/network_5_1.png)

<img src="/images/network_5_2.png" alt="network_5_2"  />



SDN 采用了逻辑集中式控制器的概念



## 5.2-路由选择算法

**路由选择算法**, 其目的是从发送方到接收方的过程中确定一条通过路由器网络的好的路径(最低开销路径)

计算机网络可以被抽象成图，图的边的值代表开销(链路长度、速度、花费、拥塞程度等)

当路径的开销相同时，选择最短路径



**路由选择算法**根据是集中式还是分散式划分：

- **集中式路由选择算法：**该算法以所有节点之间的连通性及所有链路的开销为输入，拥有全局状态信息(链路的连通性与开销)的算法常被称为**链路状态算法LS**

- **分散式路由选择算法：**路由器以迭代、分布式的方式计算出最低开销路径，每个节点仅有与其直接相连链路的开销知识即可开始工作，**距离向量算法DV**



根据静态还是动态划分：

- **静态路由选择算法：**路由随时间的变化非常缓慢，通常是人工进行调整
- **动态路由选择算法：**随着网络流量负载或拓扑发生变化而改变路由选择路径



根据负载敏感的还是负载迟钝划分：

- **负载敏感算法：**链路开销会动态地变化以反映出底层链路的当前拥塞水平
- 当今因特网使用**负载迟钝算法**



### 5.2.1-链路状态路由选择算法





### 5.2.2-距离向量路由选择算法





## 5.3-因特网中自治系统内部的路由选择：OSPF

- **规模：**路由器数目很大，涉及路由选择信息的通信、计算和存储的开销将高得不可实现

- **管理自治：**每个ISP 都有它自己的路由器网络，ISP 通常希望按自己的意愿运行路由器(选择路由选择算法)



**自治系统AS**，每个AS 由一组通常处在相同管理控制下的路由器组成，通常在一个ISP 中的路由器以及互联它们的链路构成一个AS，ISP也可以将其网络划分为多个AS

在相同AS 中的路由器都运行相同的路由选择算法并且有彼此的信息，在一个自治系统内运行的路由选择算法叫作**自治系统内部路由选择协议**



#### 开放最短路优先(OSPF)

OSPF 是一种链路状态协议，它使用洪泛链路状态信息和Dijkstra最低开销路径算法，各条链路开销是由网络管理员配置的

使用OSPF 时，路由器向自治系统内所有其他路由器广播路由选择信息，每当一条链路的状态发生变化时），路由器就会广播链路状态信息。即使链路状态未发生变化，它也要周期性地（ 至少每隔30 min 一次）广播链路状态

OSPF报文直接由IP承载，对OSPF 其上层协议的值为89



OSPF 的优点：

- **安全：**使用鉴别，仅有受信任的路由器能参与一个AS 内的OSPF 协议

- **多条相同开销的路径：**多条路径具有相同的开销时， OSPF 允许使用多条路径

- **对单播与多播路由选择的综合支持**

- **支持在单个AS 中的层次结构：**OSPF 自治系统能够层次化地配置多个区域每个区域都运行自己的OSPF 链路状态路由选择算法，在每个区域内， 一台或多台区域边界路由器负责为流向该区域以外的分组提供路由选择，在AS 中只有一个OSPF区域配置成主干区域，主干区域的主要作用是为该AS 中其他区域之间的流量提供路由选择。在AS 中的区域间的路由选择要求分组先路由到一个区域边界路由器（区域内路由选择），然后通过主干路由到位于目的区域的区域边界路由器进而再路由到最终目的地



## 5.4-ISP之间的路由选择：BGP

OSPF 是一个AS 内部路由选择协议，当分组跨越多个AS 进行路由时，需要一个**自治系统间路由选择协议**

AS 间路由选择协议涉及多个AS 之间的协调，所以AS 通信必须运行相同的AS 间路由选择协议

在因特网中，所有的AS 运行相同的AS 间路由选择协议，称为**边界网关协议BGP**



### 5.4.1-BGP的作用

在BCP 中，分组并不是路由到一个特定的目的地址，相反是路由到CIDR 化的前缀，其中每个前缀表示一个子网或一个子网的集合



- **从邻居AS 荻得前缀的可达性信息：**BGP 允许每个子网向因特网的其余部分通告它的存在，BGP 确保在因特网中的所有AS 知道该子网

- **确定到该前缀的“最好的“路由：**路由器将本地运行一个BGP 路由选择过程



### 5.4.2-通告BGP 路由信息

**网关路由器:**是一台位于AS 边缘的路由器，它直接连接到在其他AS 中的一台或多台路由器

**内部路由器:**内部路由器仅连接在它自己AS中的主机和路由器



在BGP 中，每对路由器通过使用179 端口的半永久TCP连接交换路由选择信息，跨越两个AS 的BGP连接称为外部BGP(eBGP) 连接，而在相同AS中的两台路由器之间的BGP 会话称为内部BGP (iBGP) 连接



### 5.4.3-确定最好的路由

两个较为重要的**BGP属性**-**AS-PATH**、**NEXT-HOP**

AS-PATH 属性包含了通告已经通过的AS 的列表，当一个前缀通过某AS 时，该AS 将其ASN 加入AS-PATH 中的现有列表

BGP 路由器还使用AS-PATH 属性来检测和防止通告环路，如果一台路由器在路径列表中看到包含了它自己的AS, 它将拒绝该通告

NEXT-HOP 是AS-PATH 起始的路由器接口的IP 地址



#### 1. 热土豆路由选择

![network_5_3](/images/network_5_3.png)

**热土豆路由选择依据的思想是:**尽可能快地将分组送出其AS，，而不担心其AS 外部到目的地的余下部分的开销



#### 2.路由器选择算法

进入BGP 的路由选择算法的输入是到某前缀的所有路由的集合，如果仅有一条这样的路由， BGP 则显然选择该路
由。如果到相同的前缀有两条或多条路由，则顺序地调用下列消除规则直到余下一条路由：

- **本地偏好：**取决于该AS 的网络管理员
- 选择具有最短AS-PATH的路由，BGP 将使用距离向量算法决定路径，其中距离测度使用AS 跳的跳数而不是路由器跳的跳数
- 使用热土豆路由选择
- 使用BGP标识符来选择路由



### 5.4.4-IP任播

- 在许多分散的不同地理位置，替换不同服务器上的相同内容
- 让每个用户从最靠近的服务器访问内容。

当该客户想向那个IP 地址发送一个请求时，因特网路由器则向那个“最近的＂服务器转发该请求分组，最近的服务器是由BGP 路由选择算法所定义的



### 5.4.5-路由选择策略

商业运行的ISP 们都遵从的一个经验法则是：任何穿越某ISP 主干网的流量必须是其源或目的（ 或两者）位于该ISP 的某个客户网络中



## 5.5-SDN控制平面

SDN关键特征：

- **基于流的转发：**基于流表的转发
- **数据平面与控制平面分离**
- **网络控制功能：**控制平面自身由两个组件组成：一个SDN 控制器(网络操作系统)，若干网络控制应用程序；控制器维护准确的网络状态信息

- **可编程的网络：**应用程序有不同的功能



![network_5_4](/images/network_5_4.png)



### 5.5.1-SDN控制平面：SDN控制器和SDN网络控制应用程序

SDN 控制平面大体划分为两个部分，即SDN控制器和SDN网络控制应用程序



SDN控制器结构(自底向上方式)：

- **通信层：**SDN 控制器和受控网络设备之间的通信,控制器和受控设备之间的通信跨越了一个接口，它现在被称为控制器的“南向“接口。OpenFlow, 它是一种提供这种通信功能的特定协议
- **网络范围状态管理层：**维护网络状态信息和流表
- **对于网络控制应用程序层的接口：**控制器通过它的“北向“接口与网络控制应用程序交互。该API 允许网络控制应用程序在状态管理层之间读／写网络状态和流表。



![network_5_5](/images/network_5_5.png)



### 5.5.2-OpenFlow协议

OpenFlow协议运行在SDN控制器和SDN控制的交换机或其他实现OpenFlow API 的设备之间

协议运行在TCP 之上，使用6653 的默认端口号

![network_5_6](/images/network_5_6.png)



## 5.6-ICMP: 因特网控制报文协议

因特网控制报文协议( ICMP ),，被主机和路由器用来彼此沟通网络层的信息，ICMP 最典型的用途是差错报告

ICMP 报文有一个类型字段和一个编码字段，并且包含引起该ICMP 报文首次生成的IP 数据报的首部和前8 个字节

ping 程序发送一个ICMP 类型8 编码0 的报文到指定主机

![network_5_7](/images/network_5_7.png)



## 5.7-网络管理和SNMP(看书)
