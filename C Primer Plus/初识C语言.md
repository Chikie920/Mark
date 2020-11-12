### 简单的C语言程序

```c
#include <stdio.h> //引用头文件
    
int main(void) //main函数(主函数)
{
	printf("Hello World!"); //printf()函数
    
    return 0; //回传数据
}
//主函数结束


输出结果
Hello World!
```

如果你是初学者，现在只需要了解基本结构即可，后续将会深入理解



### 程序解释



**#include为C语言预处理指令**

```c
#include <stdio.h> //在标准系统目录内查找文件 如我的是在gcc解释器文件内查找
```

指包含`stdio.h`这一文件(C标准I/O输出库），引用后即可在本程序中使用该文件内的函数

如`printf() scanf()`等等

(后续将会讲更多的C的头文件)



我们还可以这样写

```c
#include "a.h" //查找当前目录
#include "C:/Users/chikie/a.h" //查找指定目录
```



```c
int main(void)
{
    retrun 0;
}
/*
main为主函数，总是第一个被调用，无论它在程序的哪个位置
一个C语言程序，以main函数开始与结束
int 为该函数的返回数据类型——与函数结尾的return回传的数据类型对应，这里表示回传一个整数类型的数据，即0
void 为该函数的接收数据类型(因为是main函数—第一个函数，我们并不需要接收什么数据，当然后面会介绍一个特殊情况)
void 代表没有参数，代表空的意思

我们因养成在主函数内使用return的好习惯，会避免我们在其他应有返回数据的函数中忽略
*/

/*
注意：
如果你是学生你或许会发现你的同学这样写
int main(){
	retrun 0;
}
或许他正在使用的编译器不会报错
但是所有的标准都未认定这种写法，请使用标准形式
*/
```





作业:

读附录

了解C的历史，与C的标准

创建C的环境，使用IDE创建一个C的程序文件





**作者：Chikie**  [Chikie920 · GitHub](https://github.com/Chikie920)

**Email: 1597784057@qq.com or livewild0920@gmail.com**

**时间：2020/10/30**

**未经允许 禁止转载**