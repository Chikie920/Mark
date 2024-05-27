# 致敬传奇SpringMVC

[^作者]: Chikie

[作者博客]: https://chikie920.github.io/

**嗯，要开始做配置与写Web了......**



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



## 第一个SpringMVC程序-基于XML配置方式

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

#### 配置文件存放位置与名称设置

##### 默认方式配置

如果采用上面的`web.xml`文件配置，则为默认方式配置，**必须将SpringMVC配置文件放在`WEB-INF`文件夹下**，即`web.xml`同目录下，并且配置文件名必须为`web.xml`中配置的servlet的别名-servlet的形式，以上面的为例`SpringServlet-servlet.xml`

**位置或者名称不正确都会报错**



##### 自定义配置

自定义springmvc配置文件位置与文件名

在`servlet`标签中新增`<init-param>`标签如下

```xml
<servlet> <!--引入用于处理请求的servlet，让tomcat能够根据配置进行调用-->
    <servlet-name>springmvc</servlet-name> <!--定义servet的名称(别名)-->
    <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class> <!--servlet类的全类名-->
    <init-param>
        <param-name>contextConfigLocation</param-name>
        <param-value>classpath:springmvc-config.xml</param-value> <!--表示改配置文件位于main/resources目录下名为springmvc-config.xml-->
    </init-param>
</servlet>
```



##### 其他标签

**`load-on-startup`标签**

一般我们在开发web应用时，都会配置这个参数，有两个好处：

1. 如果初始化过程失败，则容器会提示启动失败，此时我们能够提前知道相关错误
2. 配置该参数相当于将初始化servlet的工作转移到容器启动过程，使得容器只要启动成功后，就可立即响应web请求，否则可能会等一小会进行加载

```xml
<servlet> <!--引入用于处理请求的servlet，让tomcat能够根据配置进行调用-->
    <servlet-name>springmvc</servlet-name> <!--定义servet的名称(别名)-->
    <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class> <!--servlet类的全类名-->
    <init-param>
        <param-name>contextConfigLocation</param-name>
        <param-value>classpath:springmvc-config.xml</param-value>
    </init-param>
    <load-on-startup>1</load-on-startup>
    <!--值大于或等于0时，在程序启动期间即加载这个servlet，默认或者小于0时，等到tomcat调用servlet时才被加载-->
</servlet>
```



#### SpringMVC配置文件编写

就使用IDEA新建spring的配置文件即可，第一个程序这里不用编写即可运行

```java
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="
       http://www.springframework.org/schema/beans
       http://www.springframework.org/schema/beans/spring-beans.xsd
       http://www.springframework.org/schema/context
       https://www.springframework.org/schema/context/spring-context.xsd">

	<!--	<mvc:annotation-driven />  后续如果要使用XML配置方式进行请求的拦截与处理，需要加上该标签表示启用SpringMVC功能 由于后面的例子都将采用注解的形式，只在这里进行说明 -->

</beans>
```



### 蜜汁404问题

初学者大概率会在运行第一个程序时出现404的错误，可能原因之一是Tomcat资源访问的问题(Servlet不知道要将静态资源交给哪个Servlet处理)

如果你使用.html后缀的页面文件(如index.html)就会404，而.jsp后缀的就不会，下面贴一下原因，这里引用知乎上面的回答

> Tomcat访问所有的资源，都是用Servlet来实现的。
>
> 在Tomcat看来，资源分3种
>
> 1. 静态资源，如css,html,js,jpg,png等
> 2. Servlet
> 3. JSP
>
> 对于静态资源，Tomcat最后会交由一个叫做DefaultServlet的类来处理
>
> 对于Servlet ，Tomcat最后会交由一个叫做 InvokerServlet的类来处理
>
> 对于JSP，Tomcat最后会交由一个叫做JspServlet的类来处理
>
> 所以Tomcat又叫Servlet容器嘛，什么都交给Servlet来处理。
>
> 那么什么时候调用哪个Servlet呢？ 有一个类叫做org.apache.tomcat.util.http.mapper.Mapper，它一共进行了7个大的规则判断，第7个，就是判断是否是该用DefaultServlet。
>
> 简单地说。。。先看是不是servlet,然后看是不是[jsp](https://www.zhihu.com/search?q=jsp&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A154753720})，如果都不是，那么就是你DefaultServlet的活儿了。

[知乎]: tomcat中对静态资源的访问也会用servlet来处理吗？-meepo的回答-知乎

所以我们需要在web.xml中配置默认的servlet--DefaultServlet来处理静态资源，更改后的代码如下

**web.xml**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet> <!--引入用于处理请求的servlet，让tomcat能够根据配置进行调用-->
        <servlet-name>springmvc</servlet-name> <!--定义servet的名称(别名)-->
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class> <!--servlet类的全类名-->
        <init-param>
            <param-name>contextConfigLocation</param-name>
            <param-value>classpath:springmvc-config.xml</param-value>
        </init-param>
        <load-on-startup>1</load-on-startup>
        <!--值大于或等于0时，在程序启动期间即加载这个servlet，默认或者小于0时，等到tomcat调用servlet时才被加载-->
    </servlet>

    <servlet-mapping>
        <servlet-name>default</servlet-name> <!--使用tomcat默认servlet拦截*.html请求-->
        <url-pattern>*.html</url-pattern> <!--处理html资源，如果需要处理如css、js等资源和这个一样继续添加-->
    </servlet-mapping>

    <servlet-mapping> <!--设置servlet的拦截请求-->
        <servlet-name>springmvc</servlet-name> <!--servlet名称，这里使用我们上面的-->
        <url-pattern>/</url-pattern> <!--匹配路径-->
    </servlet-mapping>

</web-app>
```

**当然还有其他方法比如静态资源映射等方法，请读者自行查阅并选择......**



## 第一个SpringMVC程序-基于全注解方式

### 目录结构

先不用管那个controller文件夹，这里删除了web.xml与springmvc的xml的配置文件，新建了两个类如下

![image-20240525144001783](D:\Work\Mark\Java Basis\assets\image-20240525144001783.png)

### 代替SpringMvc XML配置文件

新建`SpringMvcConfig`类

加上`@Configuration`注解表示这是一个配置Spring配置文件即可(包扫描现在可以不管，这还是初始项目)

```java
package com.chikie.config;

import org.springframework.context.annotation.Configuration;

@Configuration
public class SpringMvcConfig {
}
```



### ServletConfig代替web.xml

新建`ServletConfig`类，继承并实现抽象类`AbstractAnnotationConfigDispatcherServletInitializer`

```java
package com.chikie.config;

import org.springframework.web.servlet.support.AbstractAnnotationConfigDispatcherServletInitializer;

public class ServletConfig extends AbstractAnnotationConfigDispatcherServletInitializer {
    @Override
    protected Class<?>[] getRootConfigClasses() {
        return null;
    } // 加载Spring配置类，这里用不到所以return null

    @Override
    protected Class<?>[] getServletConfigClasses() {
        return new Class[] {SpringMvcConfig.class};
    } // 加载SpringMVC配置类

    @Override
    protected String[] getServletMappings() {
        return new String[] {"/"};
    } // 设置请求匹配路径(拦截路径)
}
```



#### AbstractAnnotationConfigDispatcherServletInitializer解析

这里引用CSDN上面的一篇文章(是不是原创不知道)

> ​	在Servlet3.0环境中，容器会在类路径中查找实现`javax.servlet.ServletContainerInitializer`接口的类，如果找到的话就用它来配置Servlet容器。
>  Spring提供了这个接口的实现，名为`SpringServletContainerInitializer`，这个类反过来又会查找实现`WebApplicationInitializer`的类并将配置的任务交给它们来完成。
>
> ​	Spring3.2引入了一个便利的`WebApplicationInitializer`基础实现，名为`AbstractAnnotationConfigDispatcherServletInitializer`，当我们的类实现了`AbstractAnnotationConfigDispatcherServletInitializer`并将其部署到Servlet3.0容器的时候，容器会自动发现它，并用它来配置Servlet上下文。

[CSDN]: https://blog.csdn.net/qq_41865229/article/details/121588209

![](D:\Work\Mark\Java Basis\assets\springmvc.png)

### 没想到吧还是我404

如果这里你还是采用的.html的页面，恭喜你还是404，那么采用全注解方式如何解决静态资源访问的问题呢？

还是按照官方的来

[Spring官方文档]: https://docs.spring.io/spring-framework/reference/web/webmvc/mvc-config/static-resources.html

这里还是将静态的html文件统一的丢进一个文件夹内，就叫`pages`吧

![image-20240525160414702](D:\Work\Mark\Java Basis\assets\image-20240525160414702.png)

有两种方案进行处理，任选其一即可。

#### **静态资源映射方法处理**

这里我们就不像官方那样再新建一个类了，我们直接在SpringMVC的配置类中写，实现`WebMvcConfigurer`类，并重写`addResourceHandlers`方法

**`SpringMvcConfig`配置类**

```java
package com.chikie.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.*;

@Configuration
public class SpringMvcConfig implements WebMvcConfigurer {
    @Override
    public void addResourceHandlers(ResourceHandlerRegistry registry) {
        registry.addResourceHandler("/pages/**").addResourceLocations("/pages/"); // 表示将URL路径中的/pages/**映射到/pages/文件夹中对应文件 这里**表示匹配/后多个目录，只有一个*表示匹配该级目录
        WebMvcConfigurer.super.addResourceHandlers(registry);
    }
}

```

#### 启用默认Servlet处理

当所有其他Servlet无法处理时交给该Servlet处理(默认最低优先级)-来自官方文档

依旧是实现`WebMvcConfigurer`接口，重写方法`configureDefaultServletHandling`，代码如下

```java
package com.chikie.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.*;

@Configuration
public class SpringMvcConfig implements WebMvcConfigurer {
    @Override
    public void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
        configurer.enable(); // 启用默认Servlet
   }
}

```



#### 关于WebMvcConfigurer和WebMvcConfigurationSupport

作者这里踩坑了，刚开始使用`WebMvcConfigurationSupport`做静态映射始终不生效，原因可参考下方链接

**WebMvcConfigurer**：主要用于添加或修改Spring MVC的配置，如添加拦截器，自定义消息转换器等（**推荐优先使用该类**）。
**WebMvcConfigurationSupport**：主要用于完全自定义Spring MVC的配置，如果我们需要对Spring MVC的配置进行大量的自定义，可以选择继承该类并重写其中的方法。但是需要注意的是，**继承该类会覆盖Spring MVC的部分默认配置导致WebMVC自动配置失效**。因此，**当我们只需要对部分配置进行自定义时，应该使用WebMvcConfigurer**。

[问题]: https://github.com/spring-projects/spring-boot/issues/32094



## 使用控制器进行访问拦截与处理

### **编写控制器类**

![image-20240525190000383](D:\Work\Mark\Java Basis\assets\image-20240525190000383.png)

**`MyController`类**

```java
package com.chikie.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller // 使用该注解表示该类为控制器类
public class MyController {
    @RequestMapping(value = "/", method = RequestMethod.GET) // 请求路径匹配 访问localhost:8080/ 匹配到/时由该函数进行处理
    public String indexDisplay() {
        return "/pages/index.html"; // 访问/pages/index.html文件
    }

    @RequestMapping(value = "/hello", method = RequestMethod.GET)
    public String helloDisplay() {
        return "/pages/hello.html";
    }
}

```

#### **`@RequestMapping`注解**

表示匹配请求进行处理，只能作用于类或方法上

- `value`值表示要匹配的路径

  **Ant风格的value**，value是可以用来匹配路径的，路径支持模糊匹配，我们把这种模糊匹配称之为Ant风格。关于路径中的通配符包括：

  1. `?`代表**任意一个字符**
  2. `*`代表**0到N个任意字符**
  3. `**`代表0到N个任意字符，并且路径中可以出现路径分隔符 /，** 通配符在使用时，左右不能出现字符，只能是 /

- `method`值表示匹配的请求方法GET、POST、PUT、DELETE、OPTIONS....，`method`值可以缺省经过测试默认是GET方法，不过还是强烈建议加上值



### **修改SpringMVC配置类**

**必须使用注解`@ComponentScan`开启包扫描并添加控制器类，必须使用注解`@EnableWebMvc`**

```java
package com.chikie.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.*;

@Configuration // 表明这是一个Spring配置类
@ComponentScan({"com.chikie.controller"}) // 开启包扫描，添加控制器的包
@EnableWebMvc // 开启SpringMVC功能
public class SpringMvcConfig implements WebMvcConfigurer {

//    @Override
//    public void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
//        configurer.enable(); // 开启默认Servlet
//    }

    @Override
    public void addResourceHandlers(ResourceHandlerRegistry registry) {
        registry.addResourceHandler("/pages/**").addResourceLocations("/pages/"); // 静态资源映射
        WebMvcConfigurer.super.addResourceHandlers(registry);
    }
}

```

**关于@EnableWebMvc`注解的作用**

如果不启用控制器将不会工作

- 启用SpringMVC
- 提供了SpringMVC的默认配置

- `@EnableWebMvc`相当于XML中的`<mvc:annotation-driven />`。它支持使用`@Controller`将传入请求映射到特定方法的`@RequestMapping`注释类



**测试结果**

![image-20240525194123903](D:\Work\Mark\Java Basis\assets\image-20240525194123903.png)



### 使用控制器获取URL参数以及返回原始内容

首先了解什么是RESTful风格API

#### RESTful风格API

##### URL设计规范

这里我直接引用别人写的(我觉得以及写的很好了，没有必要再写一遍，文章请见ref目录SpringMVC01)

![image-20240526121417553](D:\Work\Mark\Java Basis\assets\image-20240526121417553.png)

![image-20240526121515027](D:\Work\Mark\Java Basis\assets\image-20240526121515027.png)

##### 请求设计规范

按照不同的请求方式代表不同的操作类型

- 发送**GET**请求是用来做**查询**
- 发送**POST**请求是用来做**新增**发送
- **PUT**请求是用来做**修改**
- 发送**DELETE**请求是用来做**删除**

![image-20240526121717672](D:\Work\Mark\Java Basis\assets\image-20240526121717672.png)

##### 举个栗子

使用`GET`请求查询内容http://localhost:8080/users/chikie/21表示查询所有用户中名为chikie并且21岁的用户



#### @ResponseBody注解

`@RequestMapping`修饰方法只能返回`void`或者`String`类型，当返回`String`类型数据时，默认会定向到该返回值的目录下。如果我们想直接返回`String`数据而不是重定向呢？这就要使用该注解了。

`@ResponseBody`注解可以设置当前控制器方法响应内容为当前返回值，无需解析。



#### 如何获取RESTful风格请求的参数值

使用`{变量名(任取)}`的形式进行URL的占位，在处理函数参数列表中使用`@PathVariable`注解并传入要获取的对应变量名即可

更改后的`MyController`控制器类代码如下

```java
package com.chikie.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller // 使用该注解表示该类为控制器类
public class MyController {
    @RequestMapping(value = "/add/{a}/{b}", method = RequestMethod.GET) // RESTful风格的请求地址，并且采用占位符的方式获取值
    @ResponseBody // 返回原始内容
    public String add(@PathVariable("a") int num1, @PathVariable("b") int num2) { // 将获取的参数值传入处理函数
        return "{\"res\" : " + (num1+num2) + "}"; // 返回json数据
    }
}
```

**运行结果**

![image-20240526125323276](D:\Work\Mark\Java Basis\assets\image-20240526125323276.png)



#### 使用原始方式获取参数

##### 获取简单类型参数

即通过http://localhost:8080/add?key1=value2&key2=value2的形式进行参数传递

更改控制器代码如下

```java
package com.chikie.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller // 使用该注解表示该类为控制器类
public class MyController {
    @RequestMapping(value = "/add", method = RequestMethod.GET)
    @ResponseBody
    public String add(@RequestParam("num1") int num1, @RequestParam("num2") int num2) { // 使用RequestParam注解获取对应参数值
        return "{\"res\" : " + (num1+num2) + "}"; // 返回json数据
    }
}
```

**运行结果**

![image-20240526132122783](D:\Work\Mark\Java Basis\assets\image-20240526132122783.png)

##### 获取对象参数

创建实体类`Student`

```java
package com.chikie.entity;

public class Student {
    private String name;
    private int age;

    public Student() {
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
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
```

修改控制器类

```java
package com.chikie.controller;

import com.chikie.entity.Student;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller // 使用该注解表示该类为控制器类
public class MyController {
    @RequestMapping(value = "/students", method = RequestMethod.GET)
    @ResponseBody
    public String getStudent(Student student) {
        return student.toString();
    }
}
```

**运行结果**

![image-20240526132642897](D:\Work\Mark\Java Basis\assets\image-20240526132642897.png)

可见SpringMVC为我们自动装配了类

**注意点**

请求URL中的key值必须与实体类中对应属性的set方法名称对应(类似于Spring教程中使用配置文件进行**依赖注入**时一样)



#### 获取JSON格式的数据

`SpringMVC`默认使用Jackson来进行Json数据的解析操作，这里我们先使用maven导入依赖

```xml
<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.17.1</version>
</dependency>
<!--SpringMVC Json数据处理依赖-->
```

同时，你的SpringMVC配置类中必须有注解`@EnableWebMvc`，该注解会自动进行Json到实体类的转换(实际上没有这个注解，控制器都无法处理请求-servlet找不到控制器)



首先新建实体类`Student`

```java
package com.chikie.entity;

public class Student {
    private String name;
    private int age;

    public Student() {
    } // 必须包含无参方法

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
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
```

控制器类

```java
package com.chikie.controller;

import com.chikie.entity.Student;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller // 使用该注解表示该类为控制器类
public class MyController {
    @RequestMapping(value = "/students", method = RequestMethod.POST)
    @ResponseBody // 返回原始内容
    public String getStudent(@RequestBody Student student) {
        return student.toString();
    }
}
```



**运行测试**

由于需要传输`Json`数据，这里推荐使用`ApiFox`(垃圾PostMan)

![image-20240526210133769](D:\Work\Mark\Java Basis\assets\image-20240526210133769.png)



##### 一个逆天问题-HttpMessageNotReadableException: Required request body is missing或者是400、415代码

**问题描述**：在正确写完所有代码后（包括`@EnableWebMvc`注解），测试过程中**SpringMVC无法正常接收Json数据**，并且**控制器失效-无法进入控制器进行处理**，IDEA控制台出现`HttpMessageNotReadableException: Required request body is missing`问题。在多次更换注解如`@RestController`、`@PostMapping`，请求方法GET、POST都试过了....均无效，不断出现`400`、`415`代码(由于这里只进行了Json的测试，其他的如页面访问的没有测试，所以并不知道是不是`@EnableWebMvc`注解失效了)

**我是如何解决的**：我又重新新建了一个模块又写了一遍代码(和原来一样)结果能够正常运行，我又回到原来的代码模块中，打开模块设置将模块工件移除后又重新添加后，运行正常。耗费我五六个小时的问题这样解决了......

**我的建议：**如果你遇到类似的问题请以如下方式进行检查

- `@EnableWebMvc`注解是否添加到SpringMVC配置文件中
- `Jackson`依赖是否添加
- 最好使用POST方法进行Json数据的传入，Json数据格式要正确
- 尝试更换`@RequestMapping`注解到`@PostMapping`，更换`@Controller`注解到`@RestController`
- 重新配置IDEA工件

真tm无语的逆天问题.....



## 使用RESTful风格简化代码

**注解说明**

- `@RestController`，类注解，相当于`@Controller`+`@ResponseBody`
- `@GetMapping @PostMapping @PutMapping @DeleteMapping`，设置当前控制器方法请求访问路径与请求动作，相当于`@RequestMapping`的简化



**简化前的控制器代码**

```java
package com.chikie.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller
public class MyController {

    @RequestMapping(value = "/api/users", method = RequestMethod.GET)
    public String getUser() {
        return "返回user信息";
    }

    @RequestMapping(value = "/api/students", method = RequestMethod.POST)
    public String addStudent() {
        return "新增student信息";
    }
}
```

**简化后**

```java
package com.chikie.controller;

import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api") // 由于该控制器类中所有处理方法的匹配路径都有/api前缀，这里直接写在类上，表示该类所有方法都匹配/api前缀
public class MyController {

    @GetMapping("/users") // 匹配/users的GET请求
    public String getUser() {
        return "返回user信息";
    }

    @PostMapping("/students") // 匹配/students的POST请求
    public String addStudent() {
        return "新增student信息";
    }
}
```



## 拦截器

### 概念

这里我直接放别人写好的（已经写得很好了，请见ref目录下的SpringMVC02）

![image-20240527133034132](D:\Work\Mark\Java Basis\assets\image-20240527133034132.png)

![image-20240527133223659](D:\Work\Mark\Java Basis\assets\image-20240527133223659.png)

![](D:\Work\Mark\Java Basis\assets\springmvc01.png)

![](D:\Work\Mark\Java Basis\assets\springmvc02.png)

**总而言之**，拦截器就是在Controller处理之前对请求进行拦截处理



### 过滤器与拦截器的区别

来源于GPT回答

- **过滤器**：作用于所有的Web请求，包括静态资源。
- **拦截器**：只作用于Spring MVC的请求，不作用于静态资源
- **过滤器**：属于Servlet容器层次，早于Spring框架处理。
- **拦截器**：属于Spring MVC框架层次，在Controller方法调用之前和之后进行处理。
- **过滤器**：常用于编码设置、安全检查、日志记录等全局性任务。
- **拦截器**：常用于业务逻辑处理，如权限验证、数据预处理等。



### 自定义拦截器

SpringMVC中的拦截器需要实现`org.springframework.web.servlet.HandlerInterceptor`接口

这里我们创建一个拦截器类实现该接口

**MyInterceptor类**

```java
package com.chikie.config;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.HandlerInterceptor;
import org.springframework.web.servlet.ModelAndView;

@Component // 纳入Spring的管理
public class MyInterceptor implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        System.out.println("preHandle......");
        return true;
    } // 预处理

    @Override
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
        System.out.println("postHandle......");
    } // 后处理

    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
        System.out.println("afterCompletion......");
    } // 完成后的处理
}

```



**更改`SpringMVC`配置类**

```java
package com.chikie.config;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.*;

@Configuration
@ComponentScan({"com.chikie.controller", "com.chikie.config"}) // 将配置文件也纳入Spring包扫描中，以便Spring进行管理
@EnableWebMvc
public class SpringMvcConfig implements WebMvcConfigurer {

    @Autowired // 启用自动装配
    private MyInterceptor myInterceptor;

//    @Override
//    public void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
//        configurer.enable(); // 开启默认Servlet
//    }

    @Override
    public void addResourceHandlers(ResourceHandlerRegistry registry) {
        registry.addResourceHandler("/pages/**").addResourceLocations("/pages/"); // 静态资源映射
        WebMvcConfigurer.super.addResourceHandlers(registry);
    } // 静态资源管理

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(myInterceptor).addPathPatterns("/api/users"); // 添加我们的自定义拦截器类并配置拦截URL路径
        WebMvcConfigurer.super.addInterceptors(registry);
    } // 拦截器管理
}
```



**控制器代码**

```java
package com.chikie.controller;

import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api") // 由于该控制器类中所有处理方法的匹配路径都有/api前缀，这里直接写在类上，表示该类所有方法都匹配/api前缀
public class MyController {

    @GetMapping("/users") // 匹配/users的GET请求
    public String getUser() {
        return "返回user信息";
    }

    @PostMapping("/students") // 匹配/students的POST请求
    public String addStudent() {
        return "新增student信息";
    }
}
```



**运行测试**

使用GET方法请求`http://localhost:8080/api/users`

![image-20240527142552354](D:\Work\Mark\Java Basis\assets\image-20240527142552354.png)



### 注意

拦截器的拦截URL规则是从`根 /`开始匹配的

可以使用通配符`*`、`**`来进行匹配

例如使用`/api/**`可以匹配api后所有请求



### 关于重写的三个方法

●preHandle：处理器方法调用之前执行，**只有该方法有返回值，返回值是布尔类型，true放行，false拦截**。

​	若返回false则请求只会到`preHandle`这一步，直接被拦截了，后面的步骤均不会执行!控制器也不会执行!

●postHandle：处理器方法调用之后执行

●afterCompletion：渲染完成后执行

![image-20240527143321151](D:\Work\Mark\Java Basis\assets\image-20240527143321151.png)



这三个方法中，最常用的是**preHandle**,在这个方法中可以通过返回值来决定是否要进行放行，我们可以把业务逻辑放在该方法中，如果满足业务则返回true放行，不满足则返回false拦截。



### 拦截器链

这个自行了解吧，下面就放个图算了

![image-20240527143521320](D:\Work\Mark\Java Basis\assets\image-20240527143521320.png)

## SpringMVC执行流程

这里也贴个图吧

![](D:\Work\Mark\Java Basis\assets\springmvc03.png)



## 完结

SpringMVC基础教程就此告一段落，后面可能会出关于SpringMVC原理与实现的部分，马上到来的是Mybatis
