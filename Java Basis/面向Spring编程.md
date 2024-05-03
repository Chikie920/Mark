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



#### 如何设置bean的属性(成员变量)?

