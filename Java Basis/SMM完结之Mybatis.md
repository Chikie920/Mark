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

关于配置文件如何编写的问题，建议直接去Mybatis.org官网复制入门示例的配置文件内容，复制下面我写好的也是一样的

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

​	MyBatis 的映射文件通常是一个 XML 文件，主要用于描述SQL查询、插入、更新和删除操作，以及这些操作与Java对象之间的映射关系。它可以包括SQL语句和相应的映射规则。

​	在传统的JDBC编程中，开发者需要手动编写大量的SQL语句和代码来处理数据库的连接、关闭、结果集的处理等。这不仅繁琐，而且容易出错。MyBatis通过Mapper文件简化了这些工作，使得数据库操作更加直观和便捷。

​	这里依旧使用官网提供的模板进行修改

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

### 代码解释

#### XML配置文件

`configuration`标签，Mybatis配置根标签

`environment`标签，用于配置数据库连接池和事务管理器的相关配置

`environments`标签，用于定义多个数据库运行环境的集合。它包含一个或多个`<environment>`标签，并且通过默认属性来指定哪个环境是默认使用的。

`transactionManager` 标签用于配置事务管理器。事务管理器负责管理数据库事务的提交和回滚操作。它有一个type属性，指定事务管理器具体使用什么方式。一种是`JDBC`直接使用JDBC的提交和回滚功能。一种是`MANAGED` 这个配置几乎什么都不做。它从不提交或回滚连接。

`dataSource` 标签通常出现在 `environment` 标签内部，用于配置与特定环境相关的数据源设置。`type`属性：用来指定具体使用的数据库连接池的策略，可选值包括三个：

- **UNPOOLED**，采用传统的获取连接的方式，无连接池的数据源，每次请求都会打开和关闭数据库连接，适用于简单的小型应用。
- **POOLED**，使用连接池的数据源，管理数据库连接的创建和释放，提高性能，适用于大多数应用程序。
- **JNDI，**通过 Java 命名和目录接口（JNDI）查找数据源，适用于在 Java EE 环境中配置数据源。

`property`标签用于配置参数，`name`属性值：

- `driver` 这是 JDBC 驱动的 Java 类全限定名。
- `url` 这是数据库的 JDBC URL 地址。
- `username` 登录数据库的用户名。
- `password` 登录数据库的密码。
- `defaultTransactionIsolationLevel` 默认的连接事务隔离级别。
- `defaultNetworkTimeout` 等待数据库操作完成的默认网络超时时间（单位：毫秒）

`mapper` 标签用于配置某个sql映射文件的路径

- `resource`属性：使用相对于类路径的资源引用方式
- `url`属性：使用完全限定资源定位符（URL）方式

`mappers` 标签可以包含多个 `mapper` 子标签进行注册

#### XML映射文件

在 MyBatis 的 XML 映射文件中，`<mapper>` 标签是整个文件的根元素，它定义了映射文件的命名空间，并将该文件中的所有 SQL 语句、结果映射、参数映射等组织起来。

`<mapper>` 标签通过 `namespace` 属性定义一个唯一的命名空间。这个命名空间通常与对应的 Mapper 接口相关联，确保 SQL 语句与相应的 Mapper 方法匹配。

`<mapper>` 标签内包含多个子元素，这些子元素定义了具体的 SQL 语句、结果映射、参数映射等内容。常见的子元素包括 `<select>`, `<insert>`, `<update>`, `<delete>`, 和 `<resultMap>` 等。

#### 测试代码解析

`SqlSession` 是 MyBatis 中的一个核心接口，它提供了执行 SQL 命令的方法(增删改查)和管理事务(提交、回滚)以及获取mapper的方法。`SqlSession` 是与数据库进行交互的主要手段，它的实例可以通过 `SqlSessionFactory` 来创建，而 `SqlSessionFactory` 需要`SqlSessionFactoryBuilder`类来获取。

**注意**

- `SqlSession` 是非线程安全的，每个线程应该有它自己的 `SqlSession` 实例，即每次操作都需要重新获取`SqlSession`
- `SqlSession` 使用完毕后一定要关闭

### 编写工具类获取SqlSession

​	实际上`SqlSessionFactoryBuilder`读取配置文件并且获取`SqlSessionFactory` 在整个应用中只需要进行一次即可，而`SqlSession`则需要每次进行数据库操作时获取。

​	`SqlSessionFactoryBuilder` 是一个用于创建 `SqlSessionFactory` 实例的构建器。通常在应用程序启动时**只需要创建一次** `SqlSessionFactory` 实例。`SqlSessionFactoryBuilder` 一旦创建了 `SqlSessionFactory`，它就不再需要了，通常也不会被重用。

​	`SqlSessionFactory` 是一个用于创建 `SqlSession` 的工厂，它包含了数据库连接池和配置文件的信息。在整个应用程序的生命周期中，通常只需要一个 `SqlSessionFactory` 实例。这个实例是线程安全的，**可以被多个线程共享**。

​	`SqlSession` 是 MyBatis 与数据库交互的核心接口，用于执行 SQL 语句、获取映射器和管理事务。每次进行数据库操作时，都需要从 `SqlSessionFactory` 获取一个新的 `SqlSession` 实例。`SqlSession` 不是线程安全的，不能在线程之间共享。

在com.chikie.utils下创建**类`SqlSessionUtil`**代码如下

```java
package com.chikie.utils;

import com.chikie.test.MybatisTest;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class SqlSessionUtil {
    private static SqlSessionFactory sqlSessionFactory; // 全局只存在一个

    static {
        SqlSessionFactoryBuilder sqlSessionFactoryBuilder = new SqlSessionFactoryBuilder(); // 获取SqlSessionFactoryBuilder对象
        String configPath = MybatisTest.class.getResource("/MybatisConfig.xml").getPath(); // 获取配置文件路径
        FileInputStream fileInputStream = null;
        try {
            fileInputStream = new FileInputStream(configPath); // 读取配置文件
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        sqlSessionFactory = sqlSessionFactoryBuilder.build(fileInputStream);
    } // 类被加载的时候仅执行一次

    public static SqlSession getSqlSession() {
        return sqlSessionFactory.openSession();
    } // 获取SqlSession

}
```



## 使用Mybatis进行CURD-基于XML配置文件形式

### 参数占位符

在编写SQL语句时，有时候会需要传入参数例如select条件语句等

**mybatis提供了两种参数占位符：**

- `#{}` ：执行SQL时，会将 #{} 占位符替换为？，将来自动设置参数值。从上述例子可以看出使用#{} 底层使用的是`PreparedStatement`，会将数据加上`''`号。
- `${}` ：拼接SQL。底层使用的是 Statement ，会存在SQL注入问题。直接将数据放入SQL语句中，不会加`''`号。

### insert标签

#### 使用Map进行传参

编写mapper配置文件

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "https://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="user">

    <insert id="addUser">
        INSERT INTO users(name, age) VALUES (#{name}, #{age})
    </insert>


</mapper>
```

编写测试类

```java
package com.chikie.test;

import com.chikie.utils.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;

import java.util.HashMap;
import java.util.Map;

public class MybatisTest {
    public static void main(String[] args) {
        SqlSession sqlSession = SqlSessionUtil.getSqlSession(); // 获取SqlSession对象
        Map<String, Object> paramMap = new HashMap<>(); // 使用map传递参数
        paramMap.put("name", "jack");
        paramMap.put("age", 18);
        int res = sqlSession.insert("addUser", paramMap); // 执行sql
        System.out.println(res);
        sqlSession.commit(); // 提交
        sqlSession.close(); // 最后一定要关闭SqlSeesion
    }
}

// 返回1
```

对于单个参数可以直接传递，多个需要使用Map或类进行参数传递

**对于map传参，map中的key值一定要与SQL中#{}的变量名一样否则无法传入**



#### 使用类进行传参

测试类

```java
package com.chikie.test;

import com.chikie.entity.User;
import com.chikie.utils.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;

public class MybatisTest {
    public static void main(String[] args) {
        SqlSession sqlSession = SqlSessionUtil.getSqlSession(); // 获取SqlSession对象
        User user = new User();
        user.setName("marven");
        user.setAge(23);
        int res = sqlSession.insert("addUser", user); // 执行sql
        System.out.println(res);
        sqlSession.commit(); // 提交
        sqlSession.close(); // 最后一定要关闭SqlSeesion
    }
}
```

##### 注意

SQL中#{}内变量名一定要与实体类中属性的get方法名称对应

如#{name}对应getName，如下为示例

**User类**

```java
package com.chikie.entity;

public class User {
    private String name;
    private int age;

    public User() {
    }

    public String getA() { // 只是改了get方法，属性名称未变
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

**mapper配置文件**

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "https://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="user"> <!--mapper标签表明这是一个sql映射 namespace为命名空间-->

    <insert id="addUser">
        INSERT INTO users(name, age) VALUES (#{a}, #{age})
    </insert>


</mapper>
```

成功运行

### delete标签

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "https://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="user"> <!--mapper标签表明这是一个sql映射 namespace为命名空间-->

    <delete id="deleteUser">
        DELETE FROM users WHERE name = #{name}
    </delete>

</mapper>
```

```java
package com.chikie.test;

import com.chikie.utils.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;

public class MybatisTest {
    public static void main(String[] args) {
        SqlSession sqlSession = SqlSessionUtil.getSqlSession(); // 获取SqlSession对象
        int res = sqlSession.delete("deleteUser", "marven"); // 执行sql
        System.out.println(res);
        sqlSession.commit(); // 提交
        sqlSession.close(); // 最后一定要关闭SqlSeesion
    }
}

```

### update标签

![image-20240529145727343](D:\Work\Mark\Java Basis\assets\image-20240529145727343.png)

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "https://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="user"> <!--mapper标签表明这是一个sql映射 namespace为命名空间-->

    <update id="updateUser">
        UPDATE users SET age = #{age} WHERE name = #{name}
    </update>

</mapper>
```

```java
package com.chikie.test;

import com.chikie.utils.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;

import java.util.HashMap;
import java.util.Map;

public class MybatisTest {
    public static void main(String[] args) {
        SqlSession sqlSession = SqlSessionUtil.getSqlSession(); // 获取SqlSession对象
        Map<String, Object> paramMap = new HashMap<>();
        paramMap.put("age", 22);
        paramMap.put("name", "jack");
        int res = sqlSession.update("updateUser", paramMap); // 执行sql
        System.out.println(res);
        sqlSession.commit(); // 提交
        sqlSession.close(); // 最后一定要关闭SqlSeesion
    }
}

```

执行后

![image-20240529145849916](D:\Work\Mark\Java Basis\assets\image-20240529145849916.png)

这里同样采用了map传递参数

### select标签

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "https://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="user"> <!--mapper标签表明这是一个sql映射 namespace为命名空间-->

    <select id="selectOne">
        SELECT * FROM users WHERE name = #{name}
    </select>

    <select id="selectAll">
        SELECT * FROM users
    </select>

</mapper>
```

```java
package com.chikie.test;

import com.chikie.utils.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;

public class MybatisTest {
    public static void main(String[] args) {
        SqlSession sqlSession = SqlSessionUtil.getSqlSession(); // 获取SqlSession对象
        Object res = sqlSession.selectOne("selectOne", "chikie"); // 查询一个结果
        System.out.println(res);
        sqlSession.close(); // 最后一定要关闭SqlSeesion
    }
}

```

运行结果报错了

![image-20240529152913452](D:\Work\Mark\Java Basis\assets\image-20240529152913452.png)

意思是Mybatis不知道以何种方式返回数据，需要在`select`标签中添加`resultType`属性指定返回类型，更改后的mapper代码如下所示

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "https://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="user"> <!--mapper标签表明这是一个sql映射 namespace为命名空间-->

    <select id="selectOne" resultType="com.chikie.entity.User">
        SELECT * FROM users WHERE name = #{name}
    </select>

    <select id="selectAll" resultType="com.chikie.entity.User">
        SELECT * FROM users
    </select>

</mapper>
```

测试代码

```java
package com.chikie.test;

import com.chikie.entity.User;
import com.chikie.utils.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;

import java.util.List;

public class MybatisTest {
    public static void main(String[] args) {
        SqlSession sqlSession = SqlSessionUtil.getSqlSession(); // 获取SqlSession对象
        User res = sqlSession.selectOne("selectOne", "chikie"); // 查询一个结果
        System.out.println("查询单个");
        System.out.println(res);
        System.out.println("查询所有");
        List<User> resList = sqlSession.selectList("selectAll");
        resList.forEach(user -> System.out.println(user));
        sqlSession.close(); // 最后一定要关闭SqlSeesion
    }
}

```

运行结果

![image-20240529153314391](D:\Work\Mark\Java Basis\assets\image-20240529153314391.png)
