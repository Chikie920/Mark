# Java之Spring也干了



**本文档基于Spring6，其要求JDK17及以上**



## 第一个Spring程序

首先用IDEA创建一个Java项目，使用maven引入spring框架(版本看情况选择)

![image-20240502154408747](D:\Work\Mark\Java Basis\assets\image-20240502154408747.png)

![image-20240502155348199](D:\Work\Mark\Java Basis\assets\image-20240502155348199.png)

### **项目结构**

![image-20240502161429868](D:\Work\Mark\Java Basis\assets\image-20240502161429868.png)

Spring配置文件在res目录下创建，可以使用IDEA自带的创建或者自己创建xml文件，不过IDEA创建会带部分代码（Spring配置相关），自己创建需要粘贴一下

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

</beans>
```



### **Dog类**

```java
package com.chikie.Entity;

public class Dog {
    private String name;
    private int age;

    public Dog() {
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
        return "Dog{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
```



### **配置文件编写**

通过编写配置文件将类交给Spring管理，**配置文件名任意**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
       http://www.springframework.org/schema/beans/spring-beans.xsd">

    <bean id="dog1" name="myDog" class="com.chikie.Entity.Dog"></bean>
        

</beans>
```

**类似于html的写法，使用bean标签并添加一些属性将类交给Spring管理**

`id属性`，Spring管理的bean的**唯一**标识，不可重复

`name属性`，bean的别名

`class属性`，纳入管理类的全类名



- **当id重复时**

```xml
<bean id="dog1" name="myDog" class="com.chikie.Entity.Dog"></bean>
<bean id="dog1" class="com.chikie.Entity.Dog"></bean>
```

**错误**

`org.springframework.beans.factory.parsing.BeanDefinitionParsingException: Configuration problem: Bean name 'dog1' is already used in this <beans> element
Offending resource: class path resource [SpringConfig.xml]`



- **当name重复时**

```xml
<bean id="dog1" name="myDog" class="com.chikie.Entity.Dog"></bean>
<bean id="dog2" name="myDog" class="com.chikie.Entity.Dog"></bean>
```

**错误**

`org.springframework.beans.factory.parsing.BeanDefinitionParsingException: Configuration problem: Bean name 'myDog' is already used in this <beans> element`
`Offending resource: class path resource [SpringConfig.xml]`



**由此可知，id于name均唯一，不可重复**



### **测试类**

```java
package com.chikie.Entity;

import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringTest {
    @Test
    public void firstDemoTest() {
        ApplicationContext applicationContext = new ClassPathXmlApplicationContext("SpringConfig.xml"); // 读取Spring配置文件，创建Spring容器
        Object dog1 = applicationContext.getBean("dog1"); // 根据id从容器中获取bean
        Object dog1_2 = applicationContext.getBean("myDog"); // 根据name从容器中获取bean
        System.out.println((Dog) dog1);
        System.out.println((Dog) dog1_2);
    }
}

// 输出结果
Dog{name='null', age=0}
Dog{name='null', age=0}
```



### 探究

#### **Spring是如何创建bean的？**

我们在Dog类的无参构造中加入输出语句

<img src="D:\Work\Mark\Java Basis\assets\image-20240502171911746.png" alt="image-20240502171911746" style="zoom: 80%;" />

再次运行结果如下

**结果：**

`无参构造被调用
Dog{name='null', age=0}`

`Dog{name='null', age=0}`





如果我们去除无参，仅包含有参方法呢？

**结果：**` Failed to instantiate [com.chikie.Entity.Dog]: No default constructor found`



**可见Spring通过类的无参构造方法创建对象（bean）**





## 依赖注入DI

简而言之就是给bean的成员变量(属性)赋值



### set方法注入

类需要提供相应属性的set方法，否则无法注入



#### 值注入



**Dog类跟上面的第一个例子一样，无改动**

```java
package com.chikie.Entity;

public class Dog {
    private String name;
    private int age;

    public Dog() {
        System.out.println("无参构造被调用");
    }

    public Dog(String name, int age) {
        this.name = name;
        this.age = age;
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
        return "Dog{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}

```



**SpringConfig.xml**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
    <bean id="dog1" name="myDog" class="com.chikie.Entity.Dog">
        <property name="name" value="布鲁斯"></property>
        <property name="age" value="1" />
        <!--两种写法均可-->
    </bean>
</beans>
```

使用`property`标签，`name`参数与要注入属性的**set方法相关**（如下会有解释），`value`表示要注入的值



**Test类**

```java
package com.chikie.Entity;

import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringTest {
    @Test
    public void firstDemoTest() {
        ApplicationContext applicationContext = new ClassPathXmlApplicationContext("SpringConfig.xml"); // 读取Spring配置文件，创建Spring容器
        Object dog1 = applicationContext.getBean("dog1"); // 根据id从容器中获取bean
        System.out.println((Dog) dog1);
    }
}
```

**结果：**

`无参构造被调用
Dog{name='布鲁斯', age=1}`



##### 值注入与类中set方法的联系

我们修改Dog类如下

```java
package com.chikie.Entity;

public class Dog {
    private String name;
    private int age;

    public Dog() {
        System.out.println("无参构造被调用");
    }

    public Dog(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setAaa(String name) {
        this.name = name;
    } // 设置name的set方法名称改动

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Dog{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}

```



**SpringConfig.xml**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
    <bean id="dog1" name="myDog" class="com.chikie.Entity.Dog">
        <property name="aaa" value="布鲁斯"></property>
        <!--name参数的值改为了aaa，对应于setAaa-->
        <property name="age" value="1" />
    </bean>
</beans>
```



**运行测试类，结果如下**

`无参构造被调用
Dog{name='布鲁斯', age=1}`

可见类的name属性被正常赋值了



**结论：**`property`参数的`name`属性值与类中要注入属性的**set方法的名称**对应，与注入属性名称无关

上例中，类中要注入属性的名称为name，set方法名称为setAaa，`property`参数的name属性值为aaa

**可见set方法名称setXyz其对应`property`参数的name属性值为xyz**，**xyz为任意字符**

即

- setName对应name
- setAge对应age



#### 引用注入

值注入为基本数据类型的数据注入，而引用注入则是对于对象的注入



新建类`Student`如下

```java
package com.chikie.Entity;

public class Student {
    private String name;
    private int age;
    private Dog dog; // 有一个类成员变量(类属性)

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

    public Dog getDog() {
        return dog;
    }

    public void setDog(Dog dog) {
        this.dog = dog;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", dog=" + dog +
                '}';
    }
}

```



**SpringConfig.xml**

```java
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
    <bean id="dog1" name="myDog" class="com.chikie.Entity.Dog">
        <property name="name" value="布鲁斯"></property>
        <property name="age" value="1" />
    </bean>

    <bean id="student" name="student" class="com.chikie.Entity.Student">
        <property name="name" value="chikie"></property>
        <property name="age" value="21"></property>
        <!--值注入-->
        <property name="dog" ref="dog1"></property>
        <!--引用注入，使用已经被Spring管理的bean进行注入-->
     </bean>
</beans>
```



**测试类**

```java
package com.chikie.Entity;

import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringTest {
    @Test
    public void firstDemoTest() {
        ApplicationContext applicationContext = new ClassPathXmlApplicationContext("SpringConfig.xml"); // 读取Spring配置文件，创建Spring容器
        Object dog1 = applicationContext.getBean("dog1"); // 根据id从容器中获取bean
        System.out.println((Dog) dog1);

        Student student = applicationContext.getBean("student", Student.class); // 这种方法获取bean就不用强制转型了
        System.out.println(student);
    }
}

```

**结果：**

`无参构造被调用
Dog{name='布鲁斯', age=1}
Student{name='chikie', age=21, dog=Dog{name='布鲁斯', age=1}}`



**引用注入即将`value`属性换为了`ref`属性**



### 构造方法注入

使用构造方法给类的属性赋值，使用该种方法，对象实例化与赋值是**同时**进行的，不像set注入，对象先被实例化再进行赋值



为Student类加上有参构造方法

```java
package com.chikie.Entity;

public class Student {
    private String name;
    private int age;
    private Dog dog;

    public Student() {
    }

    public Student(String name, int age, Dog dog) {
        this.name = name;
        this.age = age;
        this.dog = dog;
    } // 新增代码

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

    public Dog getDog() {
        return dog;
    }

    public void setDog(Dog dog) {
        this.dog = dog;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", dog=" + dog +
                '}';
    }
}

```



**SpringConfig.xml**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
    <bean id="dog1" name="myDog" class="com.chikie.Entity.Dog">
        <property name="name" value="布鲁斯"></property>
        <property name="age" value="1" />
    </bean>

    <bean id="student" name="student" class="com.chikie.Entity.Student">
        <constructor-arg name="name" value="chikie"></constructor-arg>
        <constructor-arg name="age" value="21"></constructor-arg>
        <constructor-arg name="dog" ref="dog1"></constructor-arg>
        <!--使用构造方法注入-->
     </bean>
</beans>
```

**测试类代码同上**

**结果为**

`无参构造被调用
Dog{name='布鲁斯', age=1}
Student{name='chikie', age=21, dog=Dog{name='布鲁斯', age=1}}`



**总结：**使用构造方法注入参数，使用`constructor-arg`标签，通过设置`name`属性（还可以使用index等，不过都没有name属性直观）、`value`属性-值注入、以及`ref`属性



### 自动装配

即Spring自动进行属性的注入（**引用注入**）

更改**SpringConfig.xml**代码如下，其他代码均相同

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
    <bean id="dog1" name="myDog" class="com.chikie.Entity.Dog">
        <property name="name" value="布鲁斯"></property>
        <property name="age" value="1" />
    </bean>

    <bean id="student" name="student" class="com.chikie.Entity.Student" autowire="byType">
        <property name="name" value="chikie"></property>
        <property name="age" value="21"></property>
        <!--没有显式编写dog参数的注入-->
     </bean>
</beans>
```

通过在需要自动装配的bean标签中加入`autowire`参数，并设置`byType`或`byName`来实现自动注入

推荐使用`byType`根据所需要的类别进行自动装配，而`byName`的名称规则与bean标签`name`属性的值规则相同，比如要注入的属性的set方法为setDog，那么要自动装配的bean的id或name其中之一需要为dog，否则自动装配后的值为null



#### 探究

**当使用`byType`进行自动装配时，如果有两个级以上的满足要求的类别时，结果会怎样？**

![image-20240503144731212](D:\Work\Mark\Java Basis\assets\image-20240503144731212.png)

**结论为无法注入**



### 引用配置文件

首先要了解Spring XML配置文件中的**命名空间**的概念 [链接](https://zhuanlan.zhihu.com/p/194263065)

简要概括一下，命名空间是来自XML文件的概念，主要是用来引入标签的。



要引入配置文件需要修改XML如下

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
                           http://www.springframework.org/schema/context http://www.springframework.org/schema/context/spring-context.xsd">

</beans>
```



**新建DataSource类**

```java
package com.chikie.Entity;

public class DataSource {
    private String url;
    private String userName;
    private String password;

    public DataSource() {
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "DataSource{" +
                "url='" + url + '\'' +
                ", userName='" + userName + '\'' +
                ", password='" + password + '\'' +
                '}';
    }
}

```



**jdbc.properties文件**

在resource目录下

```properties
url=jdbc:mysql://localhost:3306/test
username=root
password=123456
```



修改后的配置文件如下

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
                            http://www.springframework.org/schema/context http://www.springframework.org/schema/context/spring-context.xsd">
    <context:property-placeholder location="jdbc.properties"></context:property-placeholder>

    <bean name="dataSource" class="com.chikie.Entity.DataSource">
        <property name="url" value="${url}"></property>
        <property name="userName" value="${username}"></property>
        <property name="password" value="${password}"></property>
    </bean>
</beans>
```



测试类如下

```java
package com.chikie.Entity;

import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringTest {
    @Test
    public void firstDemoTest() {
        ApplicationContext applicationContext = new ClassPathXmlApplicationContext("SpringConfig.xml"); // 读取Spring配置文件，创建Spring容器
        DataSource dataSource = applicationContext.getBean("dataSource", DataSource.class);
        System.out.println(dataSource);
    }
}

```

运行结果为：

`DataSource{url='jdbc:mysql://localhost:3306/test', userName='Mirai', password='123456'}`

但是仔细一看，发现userName的值并不是root，而是本机的用户名，是因为**spring默认会优先加载系统环境变量，此时获取到的username的值实际上指的是当前计算机的用户名。而不是properties配置文件中指定的username的值。**

这里我们修改名称即可，注意${}内大小写不敏感，修改为user_name即可



#### **结论**

**引入配置文件的步骤：**

1. **xml配置文件中加入context命名空间**
2. **<context:property-placeholder location="配置文件名"></context:property-placeholder>**
3. **在bean的`value`属性中(冒号内)使用`${参数名}`来引用配置文件中的参数**



## 全注解开发

不采用XML配置文件，使用配置类来进行Spring的配置



### **常用注解**

- `@Component`，作用与类上，将该类交给Spring管理(作为bean)，相当于

```xml
<bean id="xxx" class="com.chikie.entity.xxx"></bean>
```

​		其中xxx可以作为`@Component参数`进行设置

- `@Configuration`，表示本类为Spring配置类，用于取代XML配置文件
- `@ComponentScan`，开启包扫描
- `@Controller`，功能同上，相当于别名，通常用于SpringMVC中，标识将**控制类**作为bean交给Spring管理
- `@Service`，同上，标识将**服务类**作为bean交给Spring管理
- `@Repository`，同上，标识将**实体类**作为bean交给Spring管理

- `@Value`，用于进行**基本数据类型**的数据**注入**
- `@Autowired`，表示开启自动装配(按照类别进行注入)，在需要进行**bean对象自动注入**的位置使用，不可直接修饰类
- `@Qualifier`，通常与`@Autowired`注解一同使用，自动装配默认按照类别进行注入，当同一类有多个实现时需要使用`@Qualifier`注解进行区分
- `@Resource`，该注解属于JDK，功能与`@Autowired`类似，不过它默认根据提供的名称进行注入



### 全注解配置、构造方法注入与属性注入示例



**项目结构**

![image-20240507192045476](D:\Work\Mark\Java Basis\assets\image-20240507192045476.png)

**SpringConfig类**

```java
package com.chikie.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration // Spring配置类注解，加上这个才会被作为配置类
@ComponentScan({"com.chikie.entity"}) // 开启包扫描，扫描包下的Spring注解，并进行处理
public class SpringConfig {
}

```

**Student类**

```java
package com.chikie.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Repository;

@Repository // 没有指定名称则默认为类名开头小写
public class Student {
    private String name;
    private int age;
    private Dog dog;

    public Student(@Value("chikie") String name, @Value("21") int age, @Autowired Dog dog) { // 构造方法注入
        System.out.println("有参方法被调用");
        this.name = name;
        this.age = age;
        this.dog = dog;
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

    public Dog getDog() {
        return dog;
    }

    public void setDog(Dog dog) {
        this.dog = dog;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", dog=" + dog +
                '}';
    }
}

```

**Dog类**

```java
package com.chikie.entity;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component("myDog")
public class Dog {
    @Value("布鲁斯") // 属性注入
    private String name;
    @Value("1") // 属性注入
    private int age;

    public Dog() {
        System.out.println("无参构造被调用");
    }

    public Dog(String name, int age) {
        this.name = name;
        this.age = age;
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
        return "Dog{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}

```

**SpringTest类**

```java
package com.chikie.test;

import com.chikie.config.SpringConfig;
import com.chikie.entity.Dog;
import com.chikie.entity.Student;
import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class SpringTest {
    @Test
    public void methodOne() {
        ApplicationContext applicationContext = new AnnotationConfigApplicationContext(SpringConfig.class);
        Dog myDog = applicationContext.getBean("myDog", Dog.class);
        System.out.println(myDog);
        Student student = applicationContext.getBean("student", Student.class);
        System.out.println(student);
    }
}

```

**运行结果：**

`无参构造被调用
有参方法被调用
Dog{name='布鲁斯', age=1}
Student{name='chikie', age=21, dog=Dog{name='布鲁斯', age=1}}`



#### 注意

**更改后的Student类-加上了无参构造方法**

```java
package com.chikie.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Repository;

@Repository // 没有指定名称则默认为类名开头小写
public class Student {
    private String name;
    private int age;
    private Dog dog;

    public Student() {
        System.out.println("Student无参构造方法被调用");
    } // 加上了无参构造方法

    public Student(@Value("chikie") String name, @Value("21") int age, @Autowired Dog dog) { // 构造方法注入
        System.out.println("有参方法被调用");
        this.name = name;
        this.age = age;
        this.dog = dog;
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

    public Dog getDog() {
        return dog;
    }

    public void setDog(Dog dog) {
        this.dog = dog;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", dog=" + dog +
                '}';
    }
}

```

**运行结果：**

`无参构造被调用
Student无参构造方法被调用
Dog{name='布鲁斯', age=1}
Student{name='null', age=0, dog=null}`

**可见，当无参与有参同时存在时，Spring优先使用无参构造方法生成对象**



### **set注入**

注意SET注入不能作用于参数，必须作用于SET函数

**Student类**

```java
package com.chikie.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Repository;

@Repository // 没有指定名称则默认为类名开头小写
public class Student {
    private String name;
    private int age;
    private Dog dog;

    public Student() {
        System.out.println("Student无参构造方法被调用");
    }

    public String getName() {
        return name;
    }

    @Value("chikie") // set方法注入
    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    @Value("21")
    public void setAge(int age) {
        this.age = age;
    }


    public Dog getDog() {
        return dog;
    }

    @Autowired
    public void setDog(Dog dog) {
        this.dog = dog;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", dog=" + dog +
                '}';
    }
}

```

**运行结果：**

`无参构造被调用
Student无参构造方法被调用
Dog{name='布鲁斯', age=1}
Student{name='chikie', age=21, dog=Dog{name='布鲁斯', age=1}}`
