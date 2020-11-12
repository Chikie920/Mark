### c++允许main()函数括号内为空

即形参列表为空

目前的标准为C++11



### 程序源文件命名

程序后缀`.cc .cxx .cpp .cp .C`

不同的编译器可能会不同



### 命令行运行编译器

**编译**

**windows**

`CC 文件名.cc`

会在代码目录生成 `文件名.exe`

**UNIX**下为默认为`a.out`

都为可执行文件



**运行**

windows

`.\文件名`

UNIX

`./a.out`



.加/或\表示文件在当前目录下，不同系统表示不同



### GNU编译器编译

```shell
$ g++ -o 编译后指定的文件名 文件名.cc

-o 为编译器参数，指定可执行的文件名 
默认为a.out
```



### vs编译

```shell
cl /EHsc 文件名.cpp
```



### C++的输入输出



**标准IO库**  `<iostream>`头文件 与C的`<stdio.h>`类似

包含两个基础类型`istream`与`ostream` IO流 in stream 与 out stream

C++标准库内置的头文件不需要加后缀



**标准输入**

`cin`输入 读作(c-in 后面类推) `为istream`对象

**标准输出**

`cout`输出

另外两个 `ostream`对象

**标准错误**

`cerr` 

程序运行时的一般信息输出`clog`



### 使用标准IO库的程序

```c++
#include <iostream>

int main()
{
    int a = 0, b = 0;
    
    std::cin >> a >> b;
    std::cout<< "Hello World\n" << a << b << a+b << std::endl;
    
    return 0;
}
```





`<<`**输出运算符**

`>>`**输入运算符**

主要是判断箭头所指方向



`endl`结束当前行并刷新缓冲区



### 前缀`std::`

指出名字`cout`等是定义在名为`std`的命名空间的

而**作用域运算符**`::`用来指出

等于说`std`为主要目标，而`::`更细致的指明

标准库定义的所有名称都在此(命名空间)内，命名空间可避免不经意的名字定义错误

导致我们在使用标准库内的名字时须显示说明



### 注释

与C的一样，不细说



### `while`&`for`循环语句

与C的一样，同上



### 文件结束符

windows `ctrl+z`

unix mac ox x `ctrl+d`



### if语句



### 引入头文件

对与不是标准库内的头文件

我们使用`""`将其括住

`#include "first_head_of_cpp.h"`



### 重定向输入输出

```shell
$ 可执行文件名 <将要读取的文件名> 输出数据的文件名
```

其实与C的一样



### 类

即将数据结构定义为新的数据类型

和C的一样我们通过使用`.`符号来访问结构内的某一成员

即 **结构名.成员名()**





**作者：Chikie**  [Chikie920 · GitHub](https://github.com/Chikie920)

**Email: chikie920@foxmail.com or livewild0920@gmail.com**

**时间：2020/11/2**

**未经允许 禁止转载**

