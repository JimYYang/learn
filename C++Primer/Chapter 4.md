### Chapter 4

---

#### 左值和右值

![image-20231019194920134](/Users/jsyang/Library/Application Support/typora-user-images/image-20231019194920134.png)

![image-20231019192027974](/Users/jsyang/Library/Application Support/typora-user-images/image-20231019192027974.png)

```c++
int x = 3; // 这个等号是拷贝初始化
x = 4; // 这个等号才是赋值运算符

const int x = 3; // x是glvalue 并且不是xvalue 所以是lvalue
x = 4; // x是左值 不能放在等号左边

int x = int(); // int()是纯右值
Str() = Str(); // 纯右值也可能放在等号左边 进行初始化
```



**左值可以转化为右值**

```c++
int x = 3;
int y = x;
x + y
```



**Temporary Materialization（临时具体化）**

```c++
struct str{
  int x;
}

str().x; // str()为纯右值 可以转化为xvalue


void fun(const int& a);
fun(3); // 3为纯右值 转换为将亡值
```



**再探decltype**

![image-20231019195653670](/Users/jsyang/Library/Application Support/typora-user-images/image-20231019195653670.png)



---

#### 类型转换

 位运算可能引起`integral promotion`

---

#### 位运算

计算机都是对`补码`进行操作的

- 如`1`的原码（补码）：`00000001`

  `~1`: 由于符号位为`0`所以计算机认为是正数的`补码`  直接对`00000001`按位取反

  得到：`11111110` 由于此时符号位为`1` 计算机认为是负数的补码

  `11111110`-->原码：先减1 ：`11111101` 再把非符号位取反:`10000010` 为`-1



- 如`-1`的原码：`10000001` 补码为`11111111`

  `~1`: 由于符号位为`1`所以计算机认为是负数的`补码`  直接对`11111111`按位取反

  得到：`00000000` 由于此时符号位为`0` 计算机认为是正数的补码

  为`0`

负数`补码`左移补0   右移补1

![38841697768080_.pic_hd](/Users/jsyang/Library/Containers/com.tencent.xinWeChat/Data/Library/Application Support/com.tencent.xinWeChat/2.0b4.0.9/64e781ec46db4312a069d5cb1baebd22/Message/MessageTemp/9e20f478899dc29eb19741386f9343c8/Image/38841697768080_.pic_hd.jpg)

---

```c++
short x;
x = {0x80000003}; // 加上大括号  如果出现收缩转换编译时直接报错
x = {3}; // 不会报错

int y = 3;
short x;
x = {y}; // 会报错  因为y是变量  编译期间不能确定y是否会超过short y的值可能变 可能会超出short的范围
```

`x^=y^=x^=y` 交换`x y`

`x++`后缀只能返回右值  前缀可以返回左值（返回操作数即可）

`++(++x) == ++++x` 因为`++`是右结合的

`(x++)++`不合法 因为后缀返回的是右值

---

![image-20231020141831535](/Users/jsyang/Library/Application Support/typora-user-images/image-20231020141831535.png)

```c++
// 注意decltype(exp) exp是实体 变量名或者无括号的类成员访问表达式 都会推导得到原类型
struct str{
  int a;
};
str a;
decltype(a.x) y; //  == int y;

decltype(str().x) y = std::move(a.x); // .左操作数是将亡值 返回右值引用
```



![image-20231020143859053](/Users/jsyang/Library/Application Support/typora-user-images/image-20231020143859053.png)

---

```c++
// sizeof 表达式
int x = 3;
int * p = nullptr;
// 一般情况下解引用空指针*p是违法的  但是sizeof 的操作对象若是表达式，是假装对其求值
sizeof(*p); // 合法
```

---

![image-20231020145303208](/Users/jsyang/Library/Application Support/typora-user-images/image-20231020145303208.png)

