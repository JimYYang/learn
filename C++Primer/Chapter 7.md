### Chapter 7

### 类

---

不完全类型可以定义指针

```c++
struct str; // 声明
str* p; // 正确 因为指针的大小是固定的
```

结构的一处定义原则：**翻译单元级别定义**



```c++
struct Str{
  int x = 3;
  int y;
};
// 上述代买表示结构体Str的定义 结构体中的数据成员只是声明
// 只有在真正定义对象的时候 数据成员才得到定义
Str s; // 定义了Str的对象 也隐式定义了内部包含的数据成员
```

结构体中的数据成员定义可以使用`decltype` 不能使用`auto`

---

#### 静态数据成员

```c++
struct Str{
  static int x; // 声明
  int y;
};

int Str::x; // 这才是定义
```

`c++98`可以用`const`静态成员的初始化

`const static int arr_size = 100`  注意 常量是编译期概念 

```c++
struct Str{
  const static int x = 3; // 编译时会用3替换x 但是此时还没有分配x对应的内存
  int a[x];
};

// 若想真正使用x 需要给出定义
const int Str::x;
```

`c++17`可以使用内联静态数据成员

```c++
struct Str{
  inline static int x = 3;
  // 也可以使用auto inline static auto x = 3;
  static Str x; // 不加static会报错
  int y;
};
// 不需要再使用一个cpp文件定义int Str::x;
// 但是结构体内定义Str对象需要单独加上定义; inline static Str x是错误的; 原因是编译器从上到下解析 到这一行时  要对x定义 此时需要对Str有全面的了解 但是此时还没有全面的了解
Str Str::x;

// 编译器在计算str对象所占的内存时不会考虑静态成员
Str m1;
Str m2;

// 可以这么做
struct Str{
  Str x;
};
inline Str Str::x;
```

`static`表示这个数据成员被所有对象共享

---

#### 成员函数

在类内部定义：成员函数都是隐形内联的

在类内部声明，外部定义：成员函数不是内联的

类在编译时会两遍处理（第一遍只是不会处理成员函数内部的逻辑）

可以使用trail returning type(`c++11`)

`auto Str::fun() -> MyRe`



成员函数的第一个隐含参数是`Str* this`



**静态成员函数**

被所有的对象共享

`static` 不会传入隐含的`this`指针

可以返回静态数据成员



---

#### 友元

`void ::fun();`不是函数声明

友元函数可以在类内定义 但是要注意 **隐藏友元**

![image-20231106100000452](/Users/jsyang/Library/Application Support/typora-user-images/image-20231106100000452.png)

---

#### 构造函数

构造函数函数体内的内容都是赋值（成员数据已经提前被构造出来了）  使用初始化列表区分初始化和赋值 提升性能

**注意most vexing parse**

假设`Str`是一个类

`Str m();` 这样写编译器会理解为函数声明



单一构造函数可以视为类型转换函数



`c++17`会强制去掉移动初始化（传参的时候）