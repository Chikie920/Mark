## 3.1 命名空间的using声明

我们用到的库函数基本上都属于命名空间std，std::cin表示从标准输入中读取内容

作用域操作符(::) 的含义是：编译器应从操作符左侧名字所示的作用域中寻找右侧那个名字。

我们也可以使用更简单的途径使用到命名空间中的成员-**using声明**

`using namespace: : name; `



**每个名字都需要独立的using声明**

按照规定，每个using声明引入命名空间中的一个成员。

`using std::cin;`就只能引入cin

我们可以使用

```c++
using namespace std;
```

来引入命名空间std的所有成员



## 3.2 标准库类型string

标准库类型string表示可变长的字符序列，使用string类型必须首先包含string头文件。