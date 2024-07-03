### 一、C++基础深入

### 01深入C++需要的内功

#### 01-1 进程虚拟地址空间划分

![image-20231114212002058](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114212002058.png)

指令运行的时候放在`.text段`（or代码段）指令都放在`.text段`

还有`.rodata`只读数据段

`.data`存放`初始化且不为0的`

`.bss`存放`未初始化or初始化为0的`  但是`bss`中的数据会被强制初始化为0



加载共享库又叫`动态链接库`

`ZONE_DMA: 16MB`

`ZONE_NORMAL: 800多MB` `PCB块  内核线程   内核函数等`

---



![image-20231114212859012](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114212859012.png)

红色部分都对应指令 其他的都是数据 要么在`.data` 要么在`.bss`

静态变量在程序启动的时候不会初始化  只有在第一次运行的时候才会初始化

`a b c`这三行不会产生符号！！！  在编译的时候产生3个指令  放在`.text段`  然后程序运行的时候会给`main`开辟栈帧  然后指令运行的时候会在栈上开辟内存

---

每一个进程的用户空间是私有的  内核空间是共享的

![image-20231114213621190](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114213621190.png)

---

#### 01-2 从指令角度掌握函数调用堆栈详细过程

所有程序最后产生是：**指令和数据**

![image-20231114214149783](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114214149783.png)

![image-20231114214236466](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114214236466.png)

---

![image-20231114214540328](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114214540328.png)

`int a`对应的汇编指令

![image-20231114214646625](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114214646625.png)

![image-20231114214749299](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114214749299.png)

mov不是压栈指令

---

执行sum的时候进行`压栈` 从右往左压  在**调用处**开辟栈空间 **进行压栈**（esp往上提） 给形式参数开辟空间

![image-20231114215115935](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114215115935.png)

---

然后执行`call`指令

`call sum`做两件事：

1. 将下一行指令的地址压栈

![image-20231114215527811](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114215527811.png)

![image-20231114215647142](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114215647142.png)

2. 进入sum

   先处理左括号部分

   ![image-20231114220858720](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114220858720.png)

   `gcc/g++` 函数进来后 不会对栈帧初始化 `win `下的`vs`会执行红色部分汇编对栈帧区域全部初始化为`0xCCCCCCCC`

   ![image-20231114221039078](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114221039078.png)



​		然后进入函数体

![image-20231114221515675](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114221515675.png)

![image-20231114221537106](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114221537106.png)

  然后到右括号

![image-20231114222734999](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114222734999.png)

pop为出栈 并把栈顶赋值给ebp



![image-20231114223010974](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114223010974.png)

---

#### 01-3 从编译器角度理解C++的编译和链接

![image-20231114224315998](/Users/jsyang/Library/Application Support/typora-user-images/image-20231114224315998.png)



#### 编译

**符号表**

`global`符号其他文件才可见

静态变量和静态函数只能当前文件可见（`local`）

一个文件不管是定义还是声明的部分都产生符号（不是本文件定义的是`UND`）

![image-20231115080346917](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115080346917.png)

`objdumo`可以看`.o`文件和可执行文件的详细信息

`objdump -t main.o`查看符号表

![image-20231115081325539](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115081325539.png)

`.o`文件包含的段

![image-20231115081440574](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115081440574.png)

 `readelf -h main.o`查看文件头

![image-20231115081651735](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115081651735.png)

这里的入口地址为`0x0`是因为这不是可执行文件

---

`objdump -s main.o`打印常见的段

![image-20231115081853744](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115081853744.png)

---

`readelf -S main.o`打印所有段

![image-20231115082027031](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115082027031.png)

---

`g++ -c main.cpp -g`添加调试信息

`objdump -S main.o`查看

![image-20231115094548633](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115094548633.png)

---

#### 链接

---

**符号解析**

- 所有对符号的引用都要找到**符号定义**的地方

  `*UND*`到`.text（代码段）`or`.data/bss（数据段）`

  可能会出现符号未定义或者重定义的错误

符号解析完成后，才开始给所有的符号分配虚拟地址

可执行未见`.exe/.out`中也包含各种各样的段



**符号重定向**

![image-20231115095510967](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115095510967.png)

分配好虚拟地址后，在之前的0指令上写地址

---



![image-20231115095738508](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115095738508.png)

`objdump -S a.out`

![image-20231115095900344](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115095900344.png)

`sum`后面放的不是地址 而是偏移量

---

可执行文件也可以用`readelf objdump查看段表`

`readelf -h a.out`查看可执行文件文件头 可以看到已经从可重定位文件变成了可执行文件

![image-20231115100320036](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115100320036.png)

---

**可执行文件和可重定向文件的区别**

可执行文件多了一个段`program headers`

![image-20231115100742748](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115100742748.png)

运行的时候并不是所有的段都要加载  而是一部分需要加载  `program headers`说明了需要加载的部分

`align`是对齐的 一般一页面大小为对齐方式

比如上图：

- 加载代码段`.text`可读可执行
- 加载数据段`.data`可读可写

![image-20231115101014287](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115101014287.png)

---

**程序运行过程**

![image-20231115101800630](/Users/jsyang/Library/Application Support/typora-user-images/image-20231115101800630.png)



---

![image-20231228141118538](/Users/jsyang/Library/Application Support/typora-user-images/image-20231228141118538.png)

---

![image-20231228164801707](/Users/jsyang/Library/Application Support/typora-user-images/image-20231228164801707.png)

---

![image-20231228165007514](/Users/jsyang/Library/Application Support/typora-user-images/image-20231228165007514.png)