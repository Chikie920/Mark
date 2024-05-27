# What Can I Say? Mybatis Out!

[^作者]: Chikie

[作者博客]: https://chikie920.github.io/



## 简介

使用传统JDBC进行数据库操作比较繁琐且代码复用性差，Mybatis就是用来简化数据库操作的，**MyBatis本质上就是对JDBC的封装**



## 第一个Mybatis程序-基于XML配置文件

### 准备工作

在Mysql中创建数据库

![image-20240527153006905](D:\Work\Mark\Java Basis\assets\image-20240527153006905.png)

### 引入依赖

创建项目，引入Maven依赖

```xml
<dependencies>
    <dependency>
        <groupId>org.mybatis</groupId>
        <artifactId>mybatis</artifactId>
        <version>3.5.16</version>
    </dependency>
    <!--Mybatis依赖-->

    <dependency>
        <groupId>com.mysql</groupId>
        <artifactId>mysql-connector-j</artifactId>
        <version>8.4.0</version>
    </dependency>
    <!--Mysql JDBC依赖 用于连接Mysql数据库-->
</dependencies>
```

### 配置文件编写

新建Mybatis的配置文件，在`resources`目录下新建文件`MybatisConfig.xml`

关于配置文件如何编写的问题，建议直接去Mybatis.org官网复制入门示例的配置文件内容

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN" "https://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <environments default="development">
        <environment id="development">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <property name="driver" value="com.mysql.cj.jdbc.Driver"/>
                <property name="url" value="jdbc:mysql://localhost:3306/mybatis_test"/> <!--这里使用我创建的mybatis_test数据库进行演示-->
                <property name="username" value="root"/>
                <property name="password" value="123456"/>
            </dataSource>
        </environment>
    </environments>
</configuration>
```

