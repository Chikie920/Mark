# Java入门到跑路



## 草履虫基础



### 基本数据类型

```java
public static void main(String[] args) {
    // 基本数据类型

    // 整型
    byte a = 1; // 占1字节，下面以此类推
    short b = 2;
    int c = 4;
    long d = 8;

    // 浮点型
    float e_1 = 4.0f;
    float e_2 = 4.0F;
    double f = 8.0;
    // 对于浮点型赋值，若为float，必须在后面加f或F，否则默认为double类型

    // 字符型
    char g = 'a'; // 2B Unicode字符

    // 布尔型
    boolean h = true; // 1B

}
```

**注意：**在Java中条件判断时整型无法转换为布尔类型（与C不同）

![image-20240423183747020](D:\Work\Mark\Java Basis\assets\image-20240423183747020.png)



### 命名规则

**变量或者方法命名规则--**开头小写的驼峰命名

**类命名规则--**开头大写的驼峰命名



### Scanner类

其属于Java.util包下

```java
Scanner scanner = new Scanner(System.in);
// 创建scanner对象，System.in是固定写法，表示从控制台获取输入

String inputStr = scanner.next();
while (!inputStr.equals("-1")) {
    System.out.println(inputStr);
    inputStr = scanner.nextLine();
}
```

**next()方法读取一个有效字符串，其前的空白字符会被处理，读取到空白字符为止(并不处理)**

**nextLine()方法读取一行字符串，遇到换行符结束，不保存末尾换行符**

![image-20240423190436338](D:\Work\Mark\Java Basis\assets\image-20240423190436338.png)



## Jvav入门



### 数组

首先要明确，Java中数组是一种**引用类型**

```java
public static void main(String[] args) {
    int[] a; // 数组声明 表明变量的存在
    a = new int[5]; // 数组定义 为变量开辟存储空间
    System.out.println(a[4]); // 输出0
}
```



**数组初始化方式**

```java
int[] b = new int[] {1, 2, 3}; // 方式一
int[] c = {0, 1, 2}; // 方式二
```

**多维数组同理**



**数组引用**

```java
int[] b = new int[] {1, 2, 3}; // 方式一
int[] c = {0, 1, 2, 3}; // 方式二
b = c;
System.out.println(b[0]);
```

**输出0，**数组变量b存储了数组c的地址



**使用for-each遍历数组**

```java
for (int item : b) {
    System.out.println(item);
}
```



## Java核心之面向对象也干了

**属性(成员变量)、方法、构造器就不写了**



### this与super关键字

- this在类中指代当前实例对象
- this()表示调用本类的无参构造器



- super在类中表示父类对象
- super()表示父类无参构造器



#### 注意

对于在构造器中调用本类或者父类的构造器-this()或者super()，必须写在构造器首行



### 多态

```java
package com.chikie.basis;

public class DuoTai {
    public static void main(String[] args) {
        Animal dog = new Dog();
        Animal cat = new Cat();

        dog.shout();
        cat.shout();
        /**
       		输出：
       		狗叫....
            哈人....
        **/
    }
}

class Animal {
    public void shout() {

    }
}

class Dog extends Animal {
    @Override
    public void shout() {
        System.out.println("狗叫....");
    }

    public void eat() {
        System.out.println("eat shit....");
    }
}

class Cat extends Animal {
    @Override
    public void shout() {
        System.out.println("哈人....");
    }

    public void need() {
        System.out.println("键帽欠爱了....");
    }
}
```



#### 多态运行特点

调用成员变量时：编译看左边，运行看左边

调用成员方法时：编译看左边，运行看右边

```java
package com.chikie.basis;

public class DuoTai {
    public static void main(String[] args) {
        Animal dog = new Dog();
        Animal cat = new Cat();

        System.out.println(dog.str);
        System.out.println(cat.str);
        // 结果均为Animal

        // dog.eat(); 不能调用特殊(特有)方法，编译不通过
    }
}

class Animal {
    public static String str = "Animal";
}

class Dog extends Animal {
    public static String str = "Dog";

    public void eat() {
        System.out.println("eat shit....");
    }
}

class Cat extends Animal {
    public static String str = "Cat";

    public void need() {
        System.out.println("键帽欠爱了....");
    }
}
```



### 权限修饰符

|                  | public | protected | 默认 | private |
| ---------------- | ------ | --------- | ---- | ------- |
| 同一类中         | √      | √         | √    | √       |
| 同一包中的类     | √      | √         | √    |         |
| 不同包的子类     | √      | √         |      |         |
| 不同包中的无关类 | √      |           |      |         |



### 抽象类

**继承抽象类的子类必须实现所有抽象方法，否则必须也声明为抽象类**

```java
package com.chikie.basis;

public class AbstractClass {

}

abstract class Person {
    public abstract void talk();
    public abstract void job();
    public Person() {
        System.out.println("构造方法被调用");
    } // 抽象类中可以存在构造方法，但是不允许调用(抽象类不允许实例化)
}

abstract class Doctor extends Person {
    @Override
    public void talk() {
        System.out.println("苹果远离我!");
    }

    // 没有实现全部的抽象方法，必须声明为抽象类
}

class Teachor extends Person {

    @Override
    public void talk() {
        System.out.println("来我办公室喝茶");
    }

    @Override
    public void job() {
        System.out.println("教师");
    }
}
```



### 接口

比抽象类更抽象，接口中不允许有构造方法

```java
package com.chikie.basis;

public class InterfaceTest {
}

interface Fruit {
    public static final String str = "水果"; // 对于接口的成员变量，默认有public static final三个关键字修饰，可以省略

    public abstract void type(); // 接口的方法默认使用public abstract修饰，可以省略，且方法不允许有方法体

    void color();
}

class Banana implements Fruit {
    @Override
    public void type() {
        System.out.println("大香蕉，一个大香蕉，嘿！你的感觉真的很奇妙...");
    }

    @Override
    public void color() {
        System.out.println("Yellow....");
    }
}


abstract class Apple implements Fruit {
    @Override
    public void type() {
        System.out.println("医生远离我");
    }
    // 对于没有实现完接口的类，必须声明为抽象方法
}

```



### 内部类





### lambda表达式

