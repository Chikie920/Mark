# 致敬传奇SpringMVC

[^作者]: Chikie

[作者博客]: https://chikie920.github.io/

嗯，要开始写Web和Sql了......



## 基本概念

MVC是一种软件架构模式，是一种软件架构设计思想

●M：Model（模型），负责业务处理及数据的收集，负责**处理业务**、进行Sql操作进行**数据的处理**。
●V：View（视图），即前端页面。
●C：Controller（控制器），拦截前端请求并交给Model处理，将Model结果返回给前端展示。

分为三块而不是依托，可以降低代码耦合性，利于维护



### 三层模型与MVC架构

![image-20240524121041397](D:\Work\Mark\Java Basis\assets\image-20240524121041397.png)

#### 三层模型概念

三层是指**表示层-用户界面、应用层(业务逻辑层-负责处理数据)、数据层(数据访问层或持久层-进行数据库操作)**

![image-20240524121855834](D:\Work\Mark\Java Basis\assets\image-20240524121855834.png)

### 什么是SpringMVC

SpringMVC是一个实现了MVC架构模式的Web框架，底层基于Servlet实现。

使用SpringMVC可以帮助我们**简化WEB的开发**。



## 第一个SpringMVC程序

### 项目创建

新建项目结构如下

![image-20240524125709190](D:\Work\Mark\Java Basis\assets\image-20240524125709190.png)

项目右键选择添加框架支持，勾选并确定

![image-20240524125753030](D:\Work\Mark\Java Basis\assets\image-20240524125753030.png)

![image-20240524125815315](D:\Work\Mark\Java Basis\assets\image-20240524125815315.png)

或者在模块设置中选择添加也是一样的

![image-20240524125921740](D:\Work\Mark\Java Basis\assets\image-20240524125921740.png)

### 部署到TomCat并运行

IDEA中选择运行->编辑配置

![image-20240524130124899](D:\Work\Mark\Java Basis\assets\image-20240524130124899.png)

配置好后选择部署，添加工件

![image-20240524130457121](D:\Work\Mark\Java Basis\assets\image-20240524130457121.png)

可以将应用程序上下文改为`/`，这样网页访问时链接会更清爽，你想加也可以....

![image-20240524130723817](D:\Work\Mark\Java Basis\assets\image-20240524130723817.png)

![image-20240524130740484](D:\Work\Mark\Java Basis\assets\image-20240524130740484.png)

### Maven依赖

```java
<dependencies>
    <dependency>
        <groupId>org.junit.jupiter</groupId>
        <artifactId>junit-jupiter-api</artifactId>
        <version>5.10.2</version>
    </dependency>
    <!--Junit依赖-->
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-context</artifactId>
        <version>6.1.6</version>
    </dependency>
    <!--Spring核心依赖-->
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-webmvc</artifactId>
        <version>6.1.6</version>
    </dependency>
    <!--SpringMVC依赖-->
    <dependency>
        <groupId>jakarta.servlet</groupId>
        <artifactId>jakarta.servlet-api</artifactId>
        <version>6.1.0-M1</version>
    </dependency>
    <!--Servlet依赖-->
</dependencies>
```

前面说过，SpringMVC底层是由Servlet实现的，所以需要引入Servlet依赖



### 配置Servlet

严格来说，配置方法应该属于JavaWeb的内容，下面注释看不懂的请自行查阅

配置`WEB-INFO`目录下的`web.xml`文件如下

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet> <!--引入用于处理请求的servlet，让tomcat能够根据配置进行调用-->
        <servlet-name>SpringServlet</servlet-name> <!--定义servet的名称(别名)-->
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class> <!--servlet类的全类名, 用于tomcat进行调用-->
    </servlet>

    <servlet-mapping> <!--设置servlet的拦截请求-->
        <servlet-name>SpringServlet</servlet-name> <!--servlet名称，这里使用我们上面的-->
        <url-pattern>/</url-pattern> <!--拦截路径-->
    </servlet-mapping>

</web-app>
```

这里的`servlet`类为何使用**`DispatcherServlet`**？

Spring MVC框架是围绕`DispatcherServlet`来设计的，`DispatcherServlet`会把请求分发给各个处理器，并支持可配置的处理器映射、视图渲染、本地化、时区与主题渲染和文件上传等功能。



### SpringMVC配置

#### 默认方式配置

如果采用上面的`web.xml`文件配置，则为默认方式配置，**必须将SpringMVC配置文件放在`WEB-INF`文件夹下**，即`web.xml`同目录下，并且配置文件名必须为`web.xml`中配置的servlet的别名-servlet的形式，以上面的为例`SpringServlet-servlet.xml`

**位置或者名称不正确都会报错**



#### 自定义配置
