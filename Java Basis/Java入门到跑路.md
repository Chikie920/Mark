# Java入门到跑路

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
while (!inputStr.equals("-1")) {
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



#### **补充知识点：**

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





## 番外



### Maven



