# Java入门到跑路

[^作者]: Chikie

[作者博客]: https://chikie920.github.io/

阅读建议：本教程并不完善一些语法与细节没有包括（个人认为网上其它资源已经足够全面，请自行学习），建议有编程基础（稍微学过一点Java基础），比如计算机专业的混子大学生。



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
while (!inputStr.equals("-1")) { // scanner对象读取结束时会返回"-1"
    System.out.println(inputStr);
    inputStr = scanner.nextLine();
}
```

**next()方法读取一个有效字符串，其前的空白字符会被处理，读取到空白字符为止(并不丢弃)**

**nextLine()方法读取一行字符串，遇到换行符结束，不保存末尾换行符(并不丢弃)**

![image-20240423190436338](D:\Work\Mark\Java Basis\assets\image-20240423190436338.png)



## Jvav入门



### 数组

首先要明确，Java中数组是一种**引用类型**

```java
public static void main(String[] args) {
    int[] a; // 数组声明 表明变量的存在
    a = new int[5]; // 数组定义 为变量开辟存储空间
    System.out.println(a[4]); // 输出0，默认初始化值为0
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

调用成员变量时：**编译看左边，运行看左边**

调用成员方法时：**编译看左边，运行看右边**

```java
package com.chikie.basis;

public class DuoTai {
    public static void main(String[] args) {
        Animal dog = new Dog();
        Animal cat = new Cat();

        System.out.println(dog.str);
        System.out.println(cat.str);
        // 结果均为Animal

        // *******************************************
        // dog.eat(); 不能调用子类特殊(特有)方法，编译不通过
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

**内部类分为如下四种**

```java
package com.chikie.basis;

public class ExternalClass {
    public class InnerClassA {
        // 成员内部类，作为ExternalClass的成员变量 通过 new ExternalClass(). new InnerClassA()创建
    }

    static public class InnerClassB {
        // 静态成员内部类，外部类可直接调用该类
    }

    public void methodA() {
        class InnerClassC {
            // 方法局部内部类，只在方法内部使用
        }
    }

    public void methodB() {
        InnerClassC innerClassC = new InnerClassC() {
            @Override
            public void method() {
                // 实现方法
            }
        }; // 匿名内部类，只使用一次
    }
}

interface InnerClassC {
    void method();
}

```



### 枚举

枚举本质为类



### lambda表达式

本质是避免为了实现接口或者抽象类而再声明一个类再来创建该类的对象



#### 语法



**语法注意点**

1. **参数类型可以省略**
2. **假如只有一个参数，()括号可以省略**
3. **如果方法体只有一条语句，{}大括号可以省略**
4. **如果方法体中唯一的语句是return返回语句，那省略大括号的同时return也要省略**

```java
package com.chikie.basis;

public class LambdaTest {
    public static void main(String[] args) {
        ClassOne classOne = new ClassOne() {
            @Override
            public void method() {
                System.out.println("Hello Lambda");
            }
        }; // 完整写法

        ClassOne classOne1 = ()->{
            System.out.println("Hello Lambda");
        }; // 精简写法

        ClassOne classOne2 = ()->System.out.println("Hello Lambda"); // 更精简写法，方法体内只有一条语句时可以去掉大括号
        /****测试****/
        classOne1.method();
        classOne1.method();
        classOne2.method();

        ClassTwo classTwo = (a)->{return a;}; // 有返回值写法
        ClassTwo classTwo1 = (a)->a; // 有返回值写法，精简版
        ClassTwo classTwo2 = a->a; // 一个参数时，小括号也可以去掉
        /****测试****/
        System.out.println(classTwo.method(1));
        System.out.println(classTwo1.method(1));
        // 结果 1 1 1

        ClassThree classThree = (a, b)->a+b;
        /****测试****/
        System.out.println(classThree.method(1, 2));
        // 结果为3

    }
}

interface ClassOne {
    void method();
}

interface ClassTwo {
    int method(int a);
}

interface ClassThree {
    int method(int a, int b);
}
```



#### 方法引用

**原理：利用已有函数实现lambda表达式中的接口或者抽象类的方法**

```java
package com.chikie.basis;

public class MehodRefer {
    public int add_method(int a, int b) {
        return a+b;
    }

    public static int add_method_2(int a, int b) {
        return a+b;
    }

    public static void main(String[] args) {
        /****方法引用****/
        MehodRefer mehodRefer = new MehodRefer();
        Cal cal = mehodRefer::add_method; // 引用对象方法
        System.out.println(cal.add(1, 3));
        // 结果为4

        Cal cal1 = MehodRefer::add_method_2;
        System.out.println(cal1.add(1, 2)); // 引用类方法
        // 结果为3

        ClassFour classFour = System.out::println;
        /*
        这里，ClassFour接口的method方法没有返回值，接收String类型参数
        而System.out的println方法也是如此，可以引用
         */
        classFour.method("Hello Lambda");
        // 输出内容

        /****构造方法引用****/
        Student student = Human::new; // 有参构造方法
        student.method("chikie", 21);
        // 输出有参构造

        Worker worker = Human::new; // 无参构造方法
        worker.method();
        // 输出无参构造
    }
}

interface Cal {
    int add(int a, int b);
}

interface ClassFour {
    void method(String str);
}

class Human {
    public String name;
    public int age;

    public Human() {
        System.out.println("无参构造");
    }

    public Human(String name, int age) {
        this.name = name;
        this.age = age;
        System.out.println("有参构造");
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
        return "Kid{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}

interface Student {
    void method(String name, int age);
}

interface Worker {
    void method();
}

```



### IO

![image-20240426204641046](D:\Work\Mark\Java Basis\assets\image-20240426204641046.png)



#### **补充知识点-获取resource文件夹内文件方法：**

**class.getResource()方法**

```java
// getResource("")不带"/“时候是从当前类所在包路径去获取资源
// getResource("/")带”/"时候是从classpath的根路径获取
```



#### 字节流

**FileInputStream与FileOutputStream**

```java
package com.chikie.basis;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class IOTest {
    public static void main(String[] args) {
        System.out.println(IOTest.class.getResource(""));
        System.out.println(IOTest.class.getResource("/"));

        File file = new File(IOTest.class.getResource("/").getPath() + "content.txt");

        // 字节流
        try {
            FileInputStream fileInputStream = new FileInputStream(file); // 获取输出流
            long length = file.length(); // 获取文件字节数
            int res; // 存储字符
            for (int i = 0; i < length; ++i) { // 按字节数循环读取
                res = fileInputStream.read(); // 每次读取一个字符
                System.out.print((char) res);
            } // 根据结果可以看出按字节读取中文字符会乱码，因为中文字符不只占一字节
            System.out.println("\n");
            fileInputStream.close(); // 关闭流

            /********/

            fileInputStream = new FileInputStream(file); // 重新打开文件
            byte[] bytes = new byte[2]; // 两字节存储
            while (fileInputStream.read(bytes)!=-1) {
                System.out.println(new String(bytes)); // String接收字节数组创建字符串
            }

            fileInputStream.close();

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}

```

**结果**

![image-20240426215626601](D:\Work\Mark\Java Basis\assets\image-20240426215626601.png)



#### 字符流

以字符为单位进行读取

**FileReader**

```java
package com.chikie.basis;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class IOTest2 {
    public static void main(String[] args) {
        try {
            FileReader fileReader = new FileReader(IOTest2.class.getResource("/").getPath()+"content.txt");
            int res;
            while((res = fileReader.read())!=-1) {
                System.out.print((char)res);
            }

            fileReader.close();
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

```

![image-20240501172450550](D:\Work\Mark\Java Basis\assets\image-20240501172450550.png)

**FileWriter**

```java
package com.chikie.basis;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class IOTest2 {
    public static void main(String[] args) {
        try {
            FileWriter fileWriter = new FileWriter(IOTest2.class.getResource("/").getPath() + "content.txt", true); // 第二个参数表示文件追加
            fileWriter.write("\nJvav之父是张浩扬");
            fileWriter.close(); // 刷新流然后关闭
            FileReader fileReader = new FileReader(IOTest2.class.getResource("/").getPath()+"content.txt");
            int res;
            while ((res = fileReader.read()) != -1) {
                System.out.print((char) res);
            }
            fileReader.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
```

![image-20240501172629291](D:\Work\Mark\Java Basis\assets\image-20240501172629291.png)





### 反射

- **java文件：就是我们自己编写的java代码。**

- **字节码文件：就是通过java文件编译之后的class文件（是在硬盘上真实存在的，用眼睛能看到的）**

- **字节码文件对象：当class文件加载到内存之后，虚拟机自动创建出来的对象。这个对象里面至少包含了：构造方法，成员变量，成员方法。**



#### 获取字节码文件对象

**反射第一步首先是获取字节码文件对象**

在`com.chikie.Entity`包下新建类`Student`

```java
package com.chikie.Entity;

public class Student {
    public String name;
    private int age;
    private String gender;

    public Student() {
    }

    public Student(String name, int age, String gender) {
        this.name = name;
        this.age = age;
        this.gender = gender;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    private void privateMethod() {
        System.out.println("private method");
    }
}

```



**测试类**

```java
package com.chikie.basis;

import com.chikie.Entity.Student;

public class InflectTest {
    public static void main(String[] args) {
        try {
            Class aClass = Class.forName("com.chikie.Entity.Student");
            // 方法一 使用Class.forName传入全类名获取
            System.out.println(aClass);
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

        Class bClass = Student.class;
        // 方法二 使用类名.class获取
        System.out.println(bClass);

        Student student = new Student();
        Class cClass = student.getClass();
        // 方法三 创建对象获取
        System.out.println(cClass);

    }
}

```

**结果：**

`class com.chikie.Entity.Student
class com.chikie.Entity.Student
class com.chikie.Entity.Student`



**这里推荐第二种方法获取**



#### 获取类属性

| 方法名                              | 说明                                         |
| ----------------------------------- | -------------------------------------------- |
| Field[] getFields()                 | 返回所有成员变量对象的数组（只能拿public的） |
| Field[] getDeclaredFields()         | 返回所有成员变量对象的数组，存在就能拿到     |
| Field getField(String name)         | 返回单个成员变量对象（只能拿public的）       |
| Field getDeclaredField(String name) | 返回单个成员变量对象，存在就能拿到           |



获得Field对象后

| 方法                                | 说明               |
| ----------------------------------- | ------------------ |
| void set(Object obj, Object value） | 给对象对应属性赋值 |
| Object get(Object obj)              | 获取对象对应属性值 |



```java
package com.chikie.basis;

import com.chikie.Entity.Student;

import java.lang.reflect.Field;

public class InflectFieldTest {
    public static void main(String[] args) throws NoSuchFieldException, IllegalAccessException {
        Student student = new Student("chikie", 21, "male");

        Class studentClass = Student.class;


        Field[] fields = studentClass.getFields(); // 获取类的所有公共属性
        System.out.println(fields.length); // Student类中只有一个public属性，故长度为1
        Field name_field = fields[0]; // 获取这唯一的属性
        System.out.println(name_field.getName()); // 获取属性名称
        System.out.println("***********************");
        System.out.println(name_field.get(student)); // 获取对象对应属性值
        name_field.set(student, "john"); // 设置对象对应属性值
        System.out.println(name_field.get(student)); // 修改后结果
        System.out.println("***********************");

        Field[] declaredFields = studentClass.getDeclaredFields(); // 获取类的所有属性
        System.out.println(declaredFields.length); // 获取Student类的所有属性 有3个
        for(Field field : declaredFields) {
            System.out.println(field.getName());
        }
        System.out.println("***********************");
        Field age_declaredField = declaredFields[1]; // 获取age属性
        age_declaredField.setAccessible(true); // 修改属性的访问权限，如果属性是私有的，则无法直接访问
        System.out.println(age_declaredField.get(student)); // 获取student对象的age属性值
        age_declaredField.set(student, 22);
        System.out.println(age_declaredField.get(student)); // 修改后结果

        Field name_field_b = studentClass.getField("name"); // 根据属性名称获取，只能获取public修饰的属性
        Field age_field = studentClass.getDeclaredField("age"); // 根据属性名称获取，所有属性均可获取


    }
}

```

**结果：**

![image-20240504131649716](D:\Work\Mark\Java Basis\assets\image-20240504131649716.png)



##### 注意

对于`private`修饰的属性，要获取对象的相应属性或者设置相应值需要修改属性的访问权限，使用`setAccessible`方法



#### 获取类方法

| 方法名                                                       | 说明                                         |
| ------------------------------------------------------------ | -------------------------------------------- |
| Method[] getMethods()                                        | 返回所有成员方法对象的数组（只能拿public的） |
| Method[] getDeclaredMethods()                                | 返回所有成员方法对象的数组，存在就能拿到     |
| Method getMethod(String name, Class<?>... parameterTypes)    | 返回单个成员方法对象（只能拿public的）       |
| Method getDeclaredMethod(String name, Class<?>... parameterTypes) | 返回单个成员方法对象，存在就能拿到           |



**如何获取方法并运行？**

```java
package com.chikie.basis;

import com.chikie.Entity.Student;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class InflectMethodTest {
    public static void main(String[] args) throws InvocationTargetException, IllegalAccessException, NoSuchMethodException {
        Student student = new Student("chikie", 21, "male");

        Class studentClass = Student.class;

        Method[] methods = studentClass.getMethods(); // 获取类的所有public修饰的方法
        System.out.println(methods.length); // 类的所有public修饰的方法数量，包括父类的方法
        for(Method method : methods) {
            System.out.println(method.getName());
        } // 遍历

        Method gender_method = studentClass.getMethod("getGender"); // 获取getGender方法
        System.out.println("**********************");
        System.out.println(gender_method.getName()); // 获取方法名
        String res = (String) gender_method.invoke(student);// 运行该方法
        System.out.println(res); // 输出结果
        System.out.println("**********************");

        Method privateMethod = studentClass.getDeclaredMethod("privateMethod"); // 获取指定私有方法
        privateMethod.setAccessible(true); // 私有方法必须开启访问权限才能使用，否则报错
        privateMethod.invoke(student); // 执行
    }
}

```

**运行结果**

![image-20240504132439105](D:\Work\Mark\Java Basis\assets\image-20240504132439105.png)



##### 注意

使用`getMethods()`方法获取类的方法的顺序每次可能不一样（**不固定**），而`getDeclaredFields()`方法获取属性的顺序貌似和类中的顺序是一样的（**固定的**）



对于`getMethod`与`getDeclaredMethod`这两个获取指定method的方法，若类的method参数不为空，则在使用这两个方法时加上类中method对应参数的类型，否则会出现找不到方法的错误。



#### 获取类构造方法

| 方法名                                                       | 说明                              |
| ------------------------------------------------------------ | --------------------------------- |
| Constructor<?>[] getConstructors()                           | 获得所有的构造（只能public修饰）  |
| Constructor<?>[] getDeclaredConstructors()                   | 获得所有的构造（包含private修饰） |
| Constructor<T> getConstructor(Class<?>... parameterTypes)    | 获取指定构造（只能public修饰）    |
| Constructor<T> getDeclaredConstructor(Class<?>... parameterTypes) | 获取指定构造（包含private修饰）   |



**获取构造方法来创建对象**

使用`newInstance`方法

```java
package com.chikie.basis;

import com.chikie.Entity.Student;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

public class InflectConstructorTest {
    public static void main(String[] args) throws InvocationTargetException, InstantiationException, IllegalAccessException {
        Class studentClass = Student.class;

        Constructor[] constructors = studentClass.getConstructors(); // 获取所有public构造方法，这里就不用私有构造方法来演示了，都差不多的
        System.out.println(constructors.length);
        for(Constructor constructor : constructors) {
            System.out.println(constructor.getName());
        }
        System.out.println("***********************");

        Constructor noParam_constructor = constructors[0]; // 获取无参构造方法
        Constructor param_constructor = constructors[1]; // 获取有参构造方法

        Student student1 = (Student) noParam_constructor.newInstance(); // 使用无参构造方法创建对象
        Student student2 = (Student) param_constructor.newInstance("chikie", 21, "male"); // 使用有参构造方法创建对象

        System.out.println(student1);
        System.out.println(student2);

    }
}

```

**结果**

![image-20240504133333787](D:\Work\Mark\Java Basis\assets\image-20240504133333787.png)



### 注解

注解的格式

```java
元注解
public @interface 自定义注解名 {}
```

**关于注解**

- 注解本质上就是一个**接口**，该接口继承`java.lang.annotation.Annotation`接口
- 注解类中的抽象方法称为**注解的属性**
- 注解的属性（抽象方法）的返回值类型必须为：**基本数据类型、String、枚举类、注解类、以上的数组**（普通类、void不能作为返回值）
- 在使用注解时，需要给注解的属性**赋值**

**对于注解的属性**

- 使用`default 默认值`的形式设置默认值
- 对于只有一个属性的注解，若其属性的名称为value，则在使用注解时，`@注解名(value = 值)`可简化为`@注解名(值)`
- 数组赋值时使用{}包裹

**AnnotationTest类**

```java
package com.chikie.basis;

public class AnnotationTest {
    @MyAnnotation("chikie")
    public void method() {
        System.out.println("....");
    }
}

```

**MyAnnotation类**

```java
package com.chikie.basis;

public @interface MyAnnotation {
    String value();
    int age() default 21; // 使用default value的形式设定默认值，这样使用注解的时候可以不用设置值
}

```



**元注解**

用于描述注解的注解

-  `@Target`，指定注解可以使用的位置（可以修饰的对象）
-  `@Retention`，注解可以被保留的阶段
-  `@Documented`，在使用 javadoc 工具为类生成帮助文档时是否要保留其注解信息
-  `@Inherited`，使被它修饰的注解具有继承性（如果某个类使用了被@Inherited修饰的注解，则其子类将自动具有该注解）

```java
package com.chikie.basis;

import java.lang.annotation.*;

@Target({ElementType.TYPE, ElementType.METHOD}) // 表示注解作用于类、方法上
@Retention(RetentionPolicy.RUNTIME) // 注解保留到运行阶段被运行，RetentionPolicy.SOURCE表示仅保留在源代码阶段，RetentionPolicy.CLASS表示保留到字节码文件阶段
@Documented
@Inherited
public @interface MyAnnotation {
    String value();
    int age() default 21; // 使用default value的形式设定默认值，这样使用注解的时候可以不用设置值
}
```



## 番外



### Maven篇







### 日志篇

**参考文献：**https://www.yuque.com/xinblog/javalog

Java日志框架编年史

<img src="D:\Work\Mark\Java Basis\assets\javalogbls.jpg" style="zoom:50%;" />

#### 日志框架与日志门面

日志框架技术 JUL、Logback、Log4j、Log4j2

日志门面技术 JCL、SLF4j

每一种日志框架都有自己单独的API，要使用对应的框架就要使用对应的API，这就大大的增加了应用程序代码对于日志框架的耦合性。

我们使用了日志门面技术之后，对于应用程序来说，无论底层的日志框架如何改变，应用程序不需要修改任意一行代码，就可以直接上线了。

**日志门面屏蔽日志框架的底层实现**



#### JUL

JUL 全称 Java Util Logging，它是java原生的日志框架，在java.util.logging包下，主要是使用在小型应用中。

**JUL组件**

<img src="D:\Work\Mark\Java Basis\assets\jul_module.jpg" style="zoom: 50%;" />

- **Logger：**记录器，应用程序通过**获取 Logger 对象**，**调用其 API 来发布日志信息。**Logger通常被认为是访问日志系统的入口程序。
- **Handler：**处理器，每个 Logger 都会关联一个或者是一组 Handler，**Logger 会将日志交给关联的Handler 去做处理**，由 Handler 负责将日志做记录。Handler 具体实现了日志的输出位置，比如可以输出到控制台或者是文件中等等。
- **Filter：**过滤器，根据需要定制哪些信息会被记录，哪些信息会被略过。**过滤日志信息**。
- **Formatter：**格式化组件，它负责**对日志**中的数据和信息进行转换和**格式化**，所以它决定了我们输出日志最终的形式。
- **Level：** **日志的输出级别**，每条日志消息都有一个关联的级别。我们根据输出级别的设置，用来展现最终所呈现的日志信息。根据不同的需求，设置不同的级别。



**示例代码**

```java
package com.chikie.basis;

import java.util.logging.Logger; // 引入类

public class JULTest {
    public static void main(String[] args) {
        Logger logger = Logger.getLogger("com.chikie.basis.JCLTest");
        // 使用Logger.getLogger()方法传入本类的全类名获得Logger对象，即可进行本类的日志管理

        logger.severe("严重信息......");
        logger.warning("警告信息......");
        logger.info("普通(默认)信息......");
        logger.config("配置信息......");
        logger.fine("详细信息(少)......");
        logger.finer("详细信息(中)......");
        logger.finest("详细信息(多)......");
        // 使用Logger对象与相应级别的日志方法可以输出对应日志信息
    }
}

```

**输出结果：**

`5月 05, 2024 12:24:22 下午 com.chikie.basis.JCLTest main
严重: 严重信息......
5月 05, 2024 12:24:22 下午 com.chikie.basis.JCLTest main
警告: 警告信息......
5月 05, 2024 12:24:22 下午 com.chikie.basis.JCLTest main
信息: 普通(默认)信息......`

**可以看到日志信息只输出到了info级别（默认日志信息级别），比该级别更低的日志信息不会输出，我们可以设置日志信息级别**

```java
package com.chikie.basis;

import java.util.logging.ConsoleHandler;
import java.util.logging.Level;
import java.util.logging.Logger; // 引入类
import java.util.logging.SimpleFormatter;

public class JULTest {
    public static void main(String[] args) {
        Logger logger = Logger.getLogger("com.chikie.basis.JCLTest");
        // 使用Logger.getLogger()方法传入本类的全类名获得Logger对象，即可进行本类的日志管理

        // 将默认的日志打印方式关掉
        // 参数设置为false ，打印日志时就不会按照默认的方式去打印了
        logger.setUseParentHandlers(false);
        // 日志处理器：日志处理器有控制台处理器、文件日志处理器等等，这里演示控制台日志处理器
        ConsoleHandler consoleHandler = new ConsoleHandler();
        // 设置输出格式
        SimpleFormatter simpleFormatter = new SimpleFormatter();
        consoleHandler.setFormatter(simpleFormatter);
        // 将处理器添加到日志记录器
        logger.addHandler(consoleHandler);
        // 设置日志的打印级别
        // 日志记录器和处理器的级别均需要进行统一的设置，才可以达到日志级别自定义设置的需求
        consoleHandler.setLevel(Level.FINE);
        logger.setLevel(Level.FINE); // 不进行上述操作只设置该代码不会起任何作用

        logger.severe("严重信息......");
        logger.warning("警告信息......");
        logger.info("普通(默认)信息......");
        logger.config("配置信息......");
        logger.fine("详细信息(少)......");
        logger.finer("详细信息(中)......");
        logger.finest("详细信息(多)......");
        // 使用Logger对象与相应级别的日志方法可以输出对应日志信息
    }
}

```

**结果：**

`5月 05, 2024 12:49:07 下午 com.chikie.basis.JCLTest main
严重: 严重信息......
5月 05, 2024 12:49:07 下午 com.chikie.basis.JCLTest main
警告: 警告信息......
5月 05, 2024 12:49:07 下午 com.chikie.basis.JCLTest main
信息: 普通(默认)信息......
5月 05, 2024 12:49:07 下午 com.chikie.basis.JCLTest main
配置: 配置信息......
5月 05, 2024 12:49:07 下午 com.chikie.basis.JCLTest main
详细: 详细信息(少)......`

**个人感觉这样做有点麻烦......**



**将日志信息输出到文件**

创建`FileHandler`对象，大部分代码相同

```java
public void JULFileTest() throws IOException {
    Logger logger = Logger.getLogger("com.chikie.basis.JULTest");
    logger.setUseParentHandlers(false);
    FileHandler fileHandler = new FileHandler("./Log.txt");
    // 创建FileHandler对象，传入存储日志信息文件位置
    SimpleFormatter simpleFormatter = new SimpleFormatter(); // 创建格式类
    fileHandler.setFormatter(simpleFormatter); // 给handler设置格式
    logger.addHandler(fileHandler); // 给logger对象设置handler
    fileHandler.setLevel(Level.FINE);
    logger.setLevel(Level.FINE); // 设置日志级别

    logger.severe("严重信息......");
    logger.warning("警告信息......");
    logger.info("普通(默认)信息......");
    logger.config("配置信息......");
    logger.fine("详细信息(少)......");
    logger.finer("详细信息(中)......");
    logger.finest("详细信息(多)......");
}
```

![image-20240505133121037](D:\Work\Mark\Java Basis\assets\image-20240505133121037.png)





### XML篇

#### Dom4J

[官方文档](https://dom4j.github.io/)

[官方示例](https://github.com/dom4j/dom4j/wiki/Cookbook)

这里只介绍读取与查询

**resources/config.xml**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<root>
    <student id="astudent">
        <property name="name" value="chikie"></property>
        <property name="age" value="21"></property>
    </student>
    <student id="bstudent"></student>
</root>
```

**XMLTest**

```java
package com.chikie.basis;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;

import java.util.List;

public class XMLTest {
    public static void main(String[] args) throws DocumentException {
        SAXReader saxReader = new SAXReader();
        Document document = saxReader.read(XMLTest.class.getClassLoader().getResource("config.xml").getPath()); // 读取并解析xml配置文件
        List<Node> nodes = document.selectNodes("//student"); // 使用xpath获取匹配结点
        for (Node node : nodes) {
            System.out.println(node.getName()); // 获取结点名称
            System.out.println(node.valueOf("@id")); // 获取结点给定属性值，属性名称前要加@符号
        }
        System.out.println("********************");
        Node studentA = nodes.get(0); // 获取第一个student结点
        Node node = studentA.selectSingleNode("property");// 该方法获取第一个匹配的结点
        System.out.println(node.getName());
        System.out.println(node.valueOf("@value"));

    }
}
```

**运行结果：**

`student
astudent
student
bstudent`

`property
chikie`
