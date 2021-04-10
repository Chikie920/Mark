# IO库



- C++语言不直接处理输入输出，而是通过标准库中的一组类来处理IO

- 这些IO类型可从设备读写数据，设备可以是文件、控制台窗口等。还有一些类型允许内存IO，即读写字符串

- 1.2节介绍的IO库：
  - `istream`（输入流）类型，提供输入
  - `ostream`（输出流）类型，提供输出
  - `cin`，是istream对象，从标准输入读取数据
  - `cout`，是ostream对象，向标准输出写数据
  - `cerr`，是ostream对象，用于输出错误信息，写到标准错误
  - `>>`运算符，从istream对象读输入
  - `<<`运算符，向ostream对象写输出
  - `getline`函数，从给定的istream读取一行数据，存入string对象



## 8.1-IO类

- 到目前为止， 我们已经使用过的l0类型和对象都是操纵char 数据的，实际程序不仅要从控制台窗口进行IO操作，还需要读写文件，而且用IO操作处理字符串也很方便。另外，程序可能需要读写宽字符文本

- 三个标准库头文件

![8.1](C:\Users\Mirai\Desktop\Work\Mark\Sources\images\8.1.png)

- 支持宽字符的语言，标准库定义了一组类型和对象来操作wchar_t，宽字符版本的类型和函数的名字以一个w开始

- wcin、wcout 和wcerr是分别对应cin、cout 和cerr的宽字符版对象

- 宽字符版本的类型和对象与其对应的普通char 版本的类型定义在同一个头文件中，如：fstream定义了ifstream和wifstream类型



- 设备类型和字符宽度不会影响IO操作，例如`>>`运算符对控制台窗口、文件、字符串都可用，对char和wchar_t也可用

- 标准库使我们能忽略这些不同类型的流之间的差异， 这是通过**继承机制**实现的

- 继承机制使我们可以声明一个特定的类继承自另一个类。我们通常可以将一个**派生类**（继承类）对象当作其**基类**（所继承的类）对象来使用，类型ifstream和istringstream都继承自istream，因此我们可以将用在iostream上的操作用在ifstream和istringstream对象上，派生类会继承基类的所有操作



### 8.1.1-IO对象无拷贝和赋值

- 我们不能拷贝或对IO对象赋值

```c++
ofstream outl, out2;
outl = out2; //错误:不能对流对象赋值
ofstream print(ofstream); //错误:不能初始化ofstream参数
out2 = print(out2); //错误:不能拷贝流对象
```

- 由千不能拷贝IO对象， 因此我们也不能将形参或返回类型设置为流类型
- 进行IO操作的函数通常以引用方式传递和返回流，读写一个IO对象会改变其状态， 因此传递和返回的引用不能是const的



### 8.1.2-条件状态

访问与操作流的状态



![8.2](C:\Users\Mirai\Desktop\Work\Mark\Sources\images\8.2.png)



- 一个流一旦发生错误，其上后续的IO操作都会失败

- 确定一个流对象的状态的最简单的方法是将它当作一个条件来使用 `while(cin >> word)`



**查询流的状态**

- lO库定义了一个与机器无关的`iostate` 类型，它提供了表达流状态的完整功能，这个类型应作为一个**位集合**来使用

- IO库定义了4个iostate 类型的constexpr值，表示特定的位模式。这些值用来表示特定类型的IO条件， 可以与位运算符，一起使用来一次性检测或设置多个标志位
  - `badbit`表示系统级错误，不可恢复。一旦它被置位，流就无法使用
  - `failbit`在发生可恢复错误时被置位，如读取类型错误
  - 读到EOF处，`eofbit`和`failbit`都被置位
  - `goodbit`的值为0表示无错误

- badbit、failbit、eofbit中的任一个被置位，则检测流状态的条件都会失败

- 标准库定义了一组函数来查询这些iostate标志位的状态，
  - `good()`在所有错误位均未置位时返回true
  - `bad()`、`fail()`、`eof()`均在对应错误位被置位时返回true
  - `badbit`被置位时，`fail()`也会返回true



**管理条件状态**

- 流对象的rdstate成员返回一个iostate值，对应流的当前状态

- setstate操作将给定条件位置位，表示发生了对应错误

- clear成员是一个重载的成员它有一个不接受参数的版本， 而另一个版本接受一个iostate 类型的参数

- clear不接受参数的版本清除（复位）所有错误标志位

```c++
//记住cin的当前状态
auto old_state = cin.rdstate(); //记住cin的当前状态
cin.clear(); //使cin有效
process_input(cin); //使用cin
cin.setstate(old_state); //将cin置为原有状态
```

- 带参数的clear 版本接受一个iostate值，表示流的新状态

```c++
auto old_state=cin.rdstate();                           //保存cin的状态
cin.clear();                                            //清除错误位，使之有效
process_input(cin);                                     //使用cin
cin.setstate(old_state);                                //将cin置为原来的状态
cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);  //复位failbit和badbit，其他位不变
```



### 8.1.3-管理输出缓冲

- 每个输出流都管理一个缓冲区，用来保存程序读写的数据

- 输出段文本串可能立即打印出来，但也有可能被操作系统保存在缓冲区中， 随后再打印

- **缓冲机制**，操作系统就可以将程序的多个输出操作组合成单一的系统级写操作。由千设备的写操作可能很耗时，允许操作系统将多个输出操作组合为单一的设备写操作可以带来很大的性能提升。

- 导致**缓冲刷新**（即数据真正写到设备/文件）的原因：
  - 程序`正常结束`，缓冲刷新作为main的return的一部分
  - `缓冲区满`时刷新
  - 用操纵符如`endl`、`flush`、`ends`显式刷新
  - 输出操作之后可用操纵符`unitbuf`设置流的内部状态，使其在每次输出都刷新缓冲。默认时cerr时unitbuf的，即cerr的内容立即刷新
  - 一个输出流可能被`关联`到另一个流。读写被关联的流时，关联到的流的缓冲被刷新。例如，cin和cerr关联到cout，故读cin或写cerr都将使cout刷新



**刷新缓冲区**

三种操纵符可以刷新缓冲区： `endl`插入一个换行符再刷新缓冲区、 `flush`直接刷新缓冲区、 `ends`插入一个空字符再刷新缓冲区



**unitbuf操纵符**

- 使用`unitbuf`操纵符使流在每次输出操作后都刷新缓冲区
- 而nounitbuf操纵符则重置流，使其恢复使用正常的系统管理的缓冲区刷新机制

```c++
std::cout << unitbuf;
std::cout << nounitbuf;
```

- 如果程序崩溃输出缓冲区不会刷新



**关联输入和输出流**

- 当一个输入流被关联到一个输出流时，任何试图从输入流读取数据的操作都会先刷新关联的输出流

-  `cin >> ival;`会导致cout的缓冲区被刷新

- 使用 `tie`函数将流绑定到一起
  - 不带参数的版本返回指向输出流的指针，如果本对象当前关联到一个输出流， 则返回的就是指向这个流的指针， 如果
    对象未关联到流，则返回空指针
  - 二个版本接受一个指向ostream 的指针， 将自己关联到此ostream。即， x.tie(&o)将流x关联到输出流

```c++
cin.tie(&cout);                     //将cin关联到cout
ostream *old_tie=cin.tie(nullptr);  //使cin不再关联到任何流
cin.tie(&cerr);                     //将cin关联到cerr
cin.tie(&old_tie);                  //重建cin和cout间的正常关联
```

- 每个流同时最多关联到一个流，但多个流可以同时关联到同一个ostream



## 8.2-文件输入输出

- 头文件`fstream`定义了三个类型来支持文件IO: **ifstream**从一个给定文件读取数据，**ofstream**向一个给定文件写入数据， 以及**fstream**可以读写给定文件

- fstream继承了iostream类型的操作，还增加了一些新的成员来管理与流关联的文件

![8.3](C:\Users\Mirai\Desktop\Work\Mark\Sources\images\8.3.png)



### 8.2.1-使用文件流对象

- 使用文件流操作文件，文件名即可是string对象也可以是C风格的字符串

- 创建文件流对象时，我们可以提供文件名（可选的）。如果提供了一个文件名，则open会自动被调用

```c++
ifstream in(file); //定义输入流in，读取file文件的内容
ofstream out; //定义未与任何文件关联的输出流
```

- 在要求`基类`对象的地方，可用`派生类`对象代替。例如，接受iostream引用/指针的函数，可用对应的fstream/sstream引用/指针来调用

- 如果定义了一个空文件流对象，可以随后调用open来将它与文件关联起来

```c++
ifstream in(ifile);         //初始化时关联到文件
ofstream out;               //默认初始化
out.open(ifile+".copy");    //打开文件
if (out){/*使用out*/}       //先检查是否成功关联到文件，再使用流
in.close();                 //一个文件流打开另一个文件前，必须关闭当前文件
in.open(ifile+"2");         //打开另一个文件
```

- 对已经关联到文件的流再次调用`open`会失败，并将`failbit`置位，随后的试图使用文件流的操作都会失败

- 为了将文件流关联到另外一个文件， 必须首先关闭已经关联的文件



**自动构造和析构**

- 当fstream被正确析构时（例如离开作用域），`close`会被自动调用，关联文件自动关闭



### 8.2.2-文件模式



![8.4](C:\Users\Mirai\Desktop\Work\Mark\Sources\images\8.4.png)

- 无论用哪种方式打开文件， 我们都可以指定文件模式

- 文件模式有如下限制：
  - 只可对ofstream或fstream对象设定`out`模式
  - 只可对ifstream或fstream对象设定`in`模式
  - 只有当out也被设定时才可设定`trunc`模式
  - 只要trunc未被设定，就可设定app模式。在`app`模式下，文件总以out模式被打开
  - 默认情况下，即使未指定trunc，以out模式打开的文件也会被截断，即默认用out即用了trunc。为`避免截断`，可指定app模式，使数据追加到文件末尾；或指定in模式，同时读写。
  - `ate`和`binary`模式可用于任何文件流对象，且可与其他任何模式组合

- 每个文件流类型都定义了默认的文件模式：
  - `ifstream`关联的文件默认以in模式打开
  - `ofstream`关联的文件默认以out模式打开
  - `fstream`关联的文件默认以in和out模式打开



**以out模式打开文件会丢弃已有数据**

```c++
//在这几条语句中． filel都被截断
ofstream out("filel"); //隐含以捡出才莫式打开文件并截断文件
ofs tream out2 ("filel", ofstream::out); //隐含地截断文件
ofstream out3("filel", ofstream::out | ofstream::trunc);
//为了保留文件内容， 我们必须显式指定app模式
ofstream app("file2", ofstream::app); //隐含为轮出模式
ofstream app2("file2", ofstream:: out | ofstream::app);
```

**保留被ofstream打开的文件中已有数据的唯一方法是显式指定app或in模式**



**每次调用open时都会确定文件模式**

- 对于一个给定流，每当打开文件时，都可以改变其文件模式

```c++
ofstream out; //未指定文件打开模式
out.open("scratchpad"); //模式隐含设置为徐出和截断
out.close(); //关闭out,以便我们将其用于其他文件
out. open ("precious", of stream: : app); //模式为榆出和追加
out.close();
```

- 在每次打开文件时，都要设置文件模式，可能是显式地设置，也可能是隐式地设置。当程序未指定模式时，就使用默认值-隐式使用out模式



## 8.3-string流

头文件`sstream`包含三个类型 `istringstream`、 `ostringstream`、 `stringstream`

![8.5](C:\Users\Mirai\Desktop\Work\Mark\Sources\images\8.5.png)



### 8.3.1-使用istringstream

- 用`getline`逐行读取，每次读到的整行文本用`istringstream`读取单词



### 8.3.2-使用ostringstream

- 用`ostringstream`逐步构造输出，最后一起打印