# What Can I Say? Mybatis Out!

[^作者]: Chikie

[作者博客]: https://chikie920.github.io/



## 简介

使用传统JDBC进行数据库操作比较繁琐且代码复用性差，Mybatis就是用来简化数据库操作的，**MyBatis本质上就是对JDBC的封装**



## 第一个Mybatis程序-基于XML配置文件

### 准备工作

在Mysql中创建数据库

![image-20240527153006905](D:\Work\Mark\Java Basis\assets\image-20240527153006905.png)

**项目结构**

![image-20240527221558909](D:\Work\Mark\Java Basis\assets\image-20240527221558909.png)

编写**实体类User**

```java
package com.chikie.entity;

public class User {
    private String name;
    private int age;

    public User() {
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "User{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}

```

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

### 编写Mapper映射文件

​	在MyBatis中，Mapper（映射文件）是一种配置文件，用于定义Java方法与SQL语句之间的映射关系。它的主要目的是告诉MyBatis，某个Java接口的方法应该执行哪条SQL语句，以及如何处理SQL执行结果。

​	在传统的JDBC编程中，开发者需要手动编写大量的SQL语句和代码来处理数据库的连接、关闭、结果集的处理等。这不仅繁琐，而且容易出错。MyBatis通过Mapper文件简化了这些工作，使得数据库操作更加直观和便捷。

 	这里依旧使用官网提供的模板进行修改

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "https://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="user"> <!--mapper标签表明这是一个sql映射 namespace为命名空间-->
    <select id="selectAllUsers" resultType="com.chikie.entity.User"> <!--id唯一标识该标签(sql语句) resultType指定返回类型-->
        select * from users
    </select> <!--使用select标签编写select语句-->
</mapper>
```

编写完mapper不要忘记在Mybatis配置文件中注册，否则不会生效。更改后的Mybatis配置文件如下

**`MybatisConfig.xml`**

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN" "https://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <environments default="development">
        <environment id="development">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <property name="driver" value="com.mysql.cj.jdbc.Driver"/>
                <property name="url" value="jdbc:mysql://localhost:3306/mybatis_test"/>
                <property name="username" value="root"/>
                <property name="password" value="123456"/>
            </dataSource>
        </environment>
    </environments>

    <mappers>
        <mapper resource="UserMapper.xml"></mapper>
    </mappers> <!--注册该sql映射文件-->

</configuration>
```

### 测试类编写

```java
package com.chikie.test;

import com.chikie.entity.User;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.*;
import java.util.List;

public class MybatisTest {
    public static void main(String[] args) {
        SqlSessionFactoryBuilder sqlSessionFactoryBuilder = new SqlSessionFactoryBuilder(); // 获取SqlSessionFactoryBuilder对象
        String configPath = MybatisTest.class.getResource("/MybatisConfig.xml").getPath(); // 获取配置文件路径
        FileInputStream fileInputStream = null;
        try {
            fileInputStream = new FileInputStream(configPath); // 读取配置文件
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        SqlSessionFactory sqlSessionFactory = sqlSessionFactoryBuilder.build(fileInputStream); // 获取SqlSessionFactory对象
        SqlSession sqlSession = sqlSessionFactory.openSession(); // 获取SqlSession对象
        List<User> users = sqlSession.selectList("selectAllUsers"); // 执行sql语句
        users.forEach(user -> System.out.println(user));

    }
}
```

**运行结果如下**

![image-20240527224429642](D:\Work\Mark\Java Basis\assets\image-20240527224429642.png)
