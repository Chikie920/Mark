# Java急速上手



## 草履虫基础



### 基本数据类型

```java
public static void main(String[] args) {
    // 基本数据类型

    // 整型
    byte a = 1;
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