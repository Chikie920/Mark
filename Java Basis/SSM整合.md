# SSM整合

[^作者]: Chikie

[作者博客]: https://chikie920.github.io/

## SSM整合-全注解形式

### 项目创建与依赖配置

![image-20240601164931280](D:\Work\Mark\Java Basis\assets\image-20240601164931280.png)

#### **项目结构**

![image-20240604144625475](D:\Work\Mark\Java Basis\assets\image-20240604144625475.png)

#### 数据库配置文件

```properties
driver=com.mysql.cj.jdbc.Driver
url=jdbc:mysql://localhost:3306/mybatis_test
user_name=root
password=123456
```

#### 数据库设计

![image-20240604152906829](D:\Work\Mark\Java Basis\assets\image-20240604152906829.png)

![image-20240604152914716](D:\Work\Mark\Java Basis\assets\image-20240604152914716.png)

#### **pom.xml**

```xml
<dependencies>
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
        <groupId>org.mybatis</groupId>
        <artifactId>mybatis</artifactId>
        <version>3.5.16</version>
    </dependency>
    <!--Mybatis依赖-->

    <dependency>
        <groupId>org.mybatis</groupId>
        <artifactId>mybatis-spring</artifactId>
        <version>3.0.3</version>
    </dependency>
    <!--Spring整合Mybatis依赖-->

    <dependency>
        <groupId>com.mysql</groupId>
        <artifactId>mysql-connector-j</artifactId>
        <version>8.4.0</version>
    </dependency>
    <!--Mysql数据库连接依赖-->

    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.17.1</version>
    </dependency>
    <!--SpringMVC Json数据处理依赖-->

    <dependency>
        <groupId>jakarta.servlet</groupId>
        <artifactId>jakarta.servlet-api</artifactId>
        <version>6.1.0-M1</version>
    </dependency>
    <!--SpringMVC Servlet依赖-->

    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-jdbc</artifactId>
        <version>6.1.0</version>
    </dependency>
    <!-- Spring操作jdbc依赖，这个不加会报错 -->

</dependencies>
```

### 配置类编写

#### **Spring配置类**

```java
package com.chikie.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;
import org.springframework.context.annotation.PropertySource;

@Configuration // 表示这是一个Spring配置文件，Spring会自动将该类加入到上下文中
@ComponentScan({"com.chikie.dao", "com.chikie.service"}) // dao层与service层由Spring来管理
@PropertySource("classpath:jdbc.properties") // 加载配置文件，全局可用
@Import(MybatisConfig.class) // 导入mybatis配置类，关于为什么要加我也不清楚，不加就会出现找不到mapper(dao)的现象
public class SpringConfig { // Spring配置类
}

```

#### **Spring整合SpringMVC**

**SpringMVC配置类**

```java
package com.chikie.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.DefaultServletHandlerConfigurer;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
@EnableWebMvc
@ComponentScan({"com.chikie.controller"})
public class SpringMvcConfig implements WebMvcConfigurer { // SpringMVC配置
    @Override
    public void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
        configurer.enable();
    } // 启用默认Servlet处理请求-放行静态资源
}

```

代替web.xml的配置类，用于进行Spring与SpringMVC整合

```java
package com.chikie.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.support.AbstractAnnotationConfigDispatcherServletInitializer;

public class WebConfig extends AbstractAnnotationConfigDispatcherServletInitializer { // 替代Web.xml配置文件，进行Spring与SpringMVC的整合

    @Override
    protected Class<?>[] getRootConfigClasses() {
        return new Class[] {SpringConfig.class};
    } // 配置根容器-Spring

    @Override
    protected Class<?>[] getServletConfigClasses() {
        return new Class[] {SpringMvcConfig.class};
    } // 配置WebMVC容器-SpringMVC

    @Override
    protected String[] getServletMappings() {
        return new String[] {"/"};
    } // 配置匹配路径
}

```

#### Spring整合SpringMVC原理

主要是通过配置类来实现`AbstractAnnotationConfigDispatcherServletInitializer`类，将Spring作为根容器，SpringMVC作为Web容器来实现的

#### Spring整合Mybatis

Jdbc配置类-配置数据库相关信息

```java
package com.chikie.config;

import com.mysql.cj.jdbc.MysqlDataSource;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;

import javax.sql.DataSource;

public class JdbcConfig { // 数据库配置类
    @Value("${url}")
    private String url;
    @Value("${user_name}")
    private String userName;
    @Value("${password}")
    private String passWord;

    @Bean
    public DataSource getDataSource() {
        MysqlDataSource mysqlDataSource = new MysqlDataSource();
        mysqlDataSource.setURL(url);
        mysqlDataSource.setUser(userName);
        mysqlDataSource.setPassword(passWord);
        return mysqlDataSource;
    }
}

```

Mybatis配置类

```java
package com.chikie.config;

import org.mybatis.spring.SqlSessionFactoryBean;
import org.mybatis.spring.mapper.MapperScannerConfigurer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;

import javax.sql.DataSource;

@Configuration
@Import(JdbcConfig.class)
public class MybatisConfig { // Mybatis配置类
    @Bean
    public SqlSessionFactoryBean getSqlSessionFactory(@Autowired DataSource dataSource) throws Exception {
        SqlSessionFactoryBean sqlSessionFactoryBean = new SqlSessionFactoryBean();
        sqlSessionFactoryBean.setDataSource(dataSource);
        return sqlSessionFactoryBean;
    } // 将SqlSessionFactory交给Spring管理

    @Bean
    public MapperScannerConfigurer mapperScannerConfigurer() {
        MapperScannerConfigurer mapperScannerConfigurer = new MapperScannerConfigurer();
        mapperScannerConfigurer.setBasePackage("com.chikie.dao");
        return mapperScannerConfigurer;
    } // 扫描mapper接口，采用动态代理的形式得到mapper实现类交给Spring管理
}

```

#### Spring整合Mybatis原理

如果单独使用Mybatis框架通常是这样的

```java
// 编写mybatis配置文件、mapper类-->使用SqlSessionFactoryBuilder获取SqlSessionFactory，再使用SqlSessionFactory获取SqlSession，通过传入mapper(dao)类获取mapper对象(dao对象)，通过调用mapper对象的方法执行sql语句
```

`SqlSessionFactoryBuilder`全局只需要创建一次，不需要Spring进行管理

`SqlSessionFactory`用于获取`SqlSession`，而`SqlSession`则每次请求都需要重新获取，处理完然后关闭(线程不共享)，所以`SqlSessionFactory`需要Spring进行管理

`SqlSession`，每次使用时创建，线程不共享，不需要Spring管理

对于`mapper`对象(dao对象)，在使用时由Mybatis动态生成代理对象，交给Spring管理

### 实体类编写

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

### 控制层编写

```java
package com.chikie.controller;

import com.chikie.entity.User;
import com.chikie.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class FirstController {
    @Autowired
    private UserService userService;

    @GetMapping("/hello")
    public String hello() {
        return "hello world";
    }

    @GetMapping("/user/{name}")
    public User dbTest(@PathVariable("name") String name) {
        System.out.println(name);
        return userService.selectByName(name);
    }
}

```

### 持久层编写

```java
package com.chikie.dao;

import com.chikie.entity.User;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.springframework.stereotype.Repository;

@Repository
public interface UserDao {
    @Select("SELECT * FROM users WHERE name = #{name}")
    User selectOne(@Param("name") String name);
}

```

### 业务层编写

`UserService`接口与其实现类

```java
package com.chikie.service;

import com.chikie.entity.User;

public interface UserService {
    User selectByName(String name);
}

```

```java
package com.chikie.service.impl;

import com.chikie.dao.UserDao;
import com.chikie.entity.User;
import com.chikie.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UserServiceImpl implements UserService {

    @Autowired
    private UserDao userDao; // 自动注入mapper

    @Override
    public User selectByName(String name) {
        return userDao.selectOne(name);
    }
}

```

