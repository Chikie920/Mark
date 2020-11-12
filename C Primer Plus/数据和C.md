### 一个C语言程序

```c
#include <stdio.h>

int main(void)
{
    int old;
    float weight;
    
    scanf("%d",&old);
    scanf("%f",&weight);
    /*
    当然也可以这样写 scanf("%d %f",&old,&weight); 用逗号将两个变量分开
    试试在编译器中运行这个程序
    */
    printf("I'm %d years old and I'm weight %fkg",old,weight);
    
    return 0;
}
```



### 程序解释

该代码声明了一个`int`(整型)型的变量名为old和一个`float`(浮点型)的变量weight

`scanf()`函数用于获取用户键盘输入,和`printf()`一样在" "内都有转换说明符%加一个字母,与要输入的数据类型匹配

后面另一个数据如&old,表示赋值给old变量，&符是取地址符，当`scanf()`要操作变量的值时，需要得到该变量的地址，因为数据在C中都是储存在电脑内存中的

当我们输入一个值时按下回车键，`scanf`将会将值赋给变量

现在只对输入输出函数做简单了解



`printf()`函数原型 `printf("内容或转换说明",变量或值或计算表达式或多个变量);`

如`printf("打字好累%d %d %d",2-1,a,b);`

其中多个变量或值 用`,`分隔开



**特别注意转换说明与值或变量一一对应，不能多或少**



`scanf()`为`scanf("转换说明",地址);`

与上面类似



#### 对与`scanf()`的输入

```c
scanf("%d %d",&a,&b);
你可以在终端输入一个空一格输入另一个值再回车
或输入一个值回车再输入再回车
```

`scanf()`遇到空格符或回车会终止读取，如有剩余数据会留在缓冲区，等待下次读取



使用交互式输入输出使程序更加人性化



### 试一试

试下这个代码看有何不同

```c
scanf("%d,%d",&a,&b);


scanf("%d %d",&a,&b) //与scanf("%d%d"...)一样
    
    
    //此为简化代码
```



我们发现在" "内加入的除转换说明外的其他字符都要按原样输入才行

当然我个人认为这样做有点多此一举



### C的数据类型关键字

| K&R给出的关键字 | C90标准 | C99标准    |
| --------------- | ------- | ---------- |
| int             | signed  | _Bool      |
| long            | void    | _Complex   |
| short           |         | _Imaginary |
| unsigned        |         |            |
| char            |         |            |
| float           |         |            |
| double          |         |            |



### 数据类型



**`int`型**

表示整型，整数的意思，变量的值可为正整数负整数或0

可表示数范围-32768~32767 无需记忆



**float型**

表示(单精度)浮点数

如果我们使用float声明变量最终变量会被**自动转换为double（双精度浮点型）类型储存**



我们可以使用e或E计数法表示浮点数

如3.1*10的7次方可表示为3.1e7   (e E都可)

不能这样写3.1 e7

不常用



### 其他整数类型

范围大小比较

`short int < int < long int <long long int`



**unsigned前缀**

`unsigned int`类型表示储存无符号整型因为只储存非负整数，所以他的非负范围会翻倍

是`int`型非负数范围的两倍









### 如何选择类型？

![](C:\Users\Mirai\Desktop\Work\C Primer Plus\附加内容\82612@1598791624@2.png)

即正常使用`int`即可,在储存不够时使用大的类型





### 打印short,long, long long,unsgined类型

short int

unsigned int

long int (int可省略，下同上)

long long int

`printf()`内对应的转换说明为

%d或%hd 计算机会自动转换shot类型为int类型，一般都是往高阶(精度)转换

%u

%ld

%lld





### char类型

char类型储存字符（字母或标点符号）

只储存一个**字**

```c
#include <stdio.h>

int main(void)
{
    char a;
    a = 'a';
    printf("%c",a);
    retrun 0;
}

/*
输出: a
*/
```



**解释**

char 类型会将变量值自动转换为整数储存在内存中

a的值为a对应的ASCII码的值，我们不必背下ASCII码

需要知道时用单引号`''`将字母或字符括起来会将其转换为对应的码值

使用

`printf("%d",a);`输出码值即可



### _Bool类型

C99添加了布尔类型即true false

用一位储存1 0



### 浮点值的上溢与下溢

```c
float too_big = 3.14e40;
printf("%f",too_big);

这是上溢的示例
    too_big超过了float的范围
    我们会得到INF或INFINITY的输出，表示无限大
    

float a = 0.1234e-10;
a = a/10;
printf("%f",a);

这是下溢的示例
    得到0.0123e-10
    损失了精度

    了解即可
```



## 小结:基本数据类型

```c
int 系统给定的基本整数类型 int类型不小于16位
short或short int 小于等于int 至少占16位
long或long int 大于等于最大的int整数 至少占32位
long long或long long int 大于等于最大的long整数 至少占64位
    
    
    
float 基本浮点类型 可精确表示至少6位有效数字
double 储存浮点数的范围比float大精度高
```



### 数据类型大小与sizeof()函数



```c
printf("当前系统int类型的大小为%zd",sizeof(int));

sizeof用于获取数据类型的大小，单位是位
    c99 c11提供%zd转换说明匹配sizeof的返回类型
```





**本节理论性的内容较多对新手可能有点晦涩难懂，有不懂的地方建议谷歌或百度**



任务:

1.了解进制(8、16、32进制)等

2.了解C的转义字符

3.编写一个程序输入一个ASCII码值，输出该字符

4.编写一个程序，要求输入圆的半径，输出圆的面积





**作者：Chikie**  [Chikie920 · GitHub](https://github.com/Chikie920)

**Email: 1597784057@qq.com or livewild0920@gmail.com**

**时间：2020/10/31**

**未经允许 禁止转载**

