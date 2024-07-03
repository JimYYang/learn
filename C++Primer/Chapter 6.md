### Chapter 6

---

形参会`拷贝初始化`给实参

`c++17`会强制省略复制临时对象 

```c++
struct Str
{
  Str() = default;
  Str(const Str&)
  {
    std::cout << "Copy constructor is called.\n";
  }
}

void fun(Str par)
{
  
}

int main() 
{
  Str a;
  fun(a); // 会调用拷贝初始化
  fun(Str{}); // Str()是临时对象  不会调用拷贝初始化
}
```

---

#### 参数传递引起的类型退化

```c++
fun(int *a);
fun(int a[]);
fun(int a[3]);
// 这三种方式都会使得数组退化为指针

fun(int (&p)[3]); // 可以防止类型退化
```

---

#### 变长参数

```c++
// initializer_list
void fun(std::initializer_list<int> par);

fun({1, 2, 3, 4});

// initialize_list的实现开销很小 内部包含两个指针 只会涉及指针的拷贝 一般不需要传引用
// 右值可以传常量引用
void fun(const std::initializer_list& par);
fun({1, 2, 3}); // {1, 2, 3}的生命周期在fun结束后才销毁

// 下面的代码非常危险
std::initializer_list<int> fun()
{
 return {1, 2, 3}; 
}
auto res = fun(); // {1, 2, 3}在函数结束后被销毁  但是实际上initializer_list维护两个指针 现在已经指向了无效的地址
```

---

#### 缺省实参

在`一个翻译单元`中，每个形参的缺省实参只能定义一次(不同翻译单元可以定义不同的缺省实参，可以通过函数声明实现)

```c++
void fun(int x, int y, int z);
void fun(int x, int y, int z)
{
  
}
// 二者只能有一处定义缺省实参


// 但是可以引入多个声明  分别定义缺省实参 但是顺序一定要从左到右
void fun(int x, int y, int z = 3);
void fun(int x, int y = 2, int z);
```

不重要的参数可以放在后面

可以定义缺省值

缺省实参为对象时  实参的缺省值随着对象值的变化而变化

```c++
int x = 3;
void fun(int y = x);
fun(); // --> fun(x);
```

---

#### main函数

```c++
int main(int argc, char *argv[]); // 注意argv是和[]关联的  不是和*关联的 因为要使*和argv关联需要加()
// argv是一个指针 指向一个数组 大小为argc + 1  数组内元素类型为char*  数组的末元素一定是个空指针
```

![image-20231027173416731](/Users/jsyang/Library/Application Support/typora-user-images/image-20231027173416731.png)

---

#### 返回值优化（RVO）

去掉返回值优化`-fno-elide-constructors`

`c++17`对返回`临时对象`的强制优化

```c++
struct Str
{
  Str() = default;
  Str(const Str&)
  {
    std::cout << "Copy constructor is called.\n";
  }
}

Str fun()
{
  // 返回具名返回值
  Str x;
  return x;
}

int main() {
  Str res = fun(); // 如果没有优化 将会调用两次拷贝构造函数 第一次是return x时 用x来构造一个Str对象来作为返回值 第二次是res = fun()
  // 如果引入优化 那么将省去两次拷贝构造 编译器将引入优化 传入函数的时候传入res的地址 函数内部的一系列改变在res地址内进行
}
```

---

### 函数重载和重载解析

![image-20231028151150698](/Users/jsyang/Library/Application Support/typora-user-images/image-20231028151150698.png)

```c++
// 注意是 名称隐藏  不是函数隐藏
void fun(int x);
namespace my{
  int fun = 3;
  void g(){
    fun(3); // 错误 因为会认为fun是int
  }
}

// 第三条 不适用函数模板 模板函数处理分两步 第一步先检查语法错误（从上到下） 第二步实例化 此时可能已经看到了模板函数下面的东西

template <typename T>
void fun(T x) {
  g(x);
}

namespace my{
  struct Str{};
  void g(Str x) {
    
  }
}

int main() {
  my::Str obj;
	fun(obj); // 正确 因为函数模板在实例化的时候能够看到g
}
```



![image-20231028164012351](/Users/jsyang/Library/Application Support/typora-user-images/image-20231028164012351.png)

左值引用不能绑定到右值

---

#### 内联函数

函数展开的时候在`编译期`进行 `编译期`每个翻译单元单独处理

`inline`把函数只能在同一个程序（可能包含多个翻译单元）中定义转化为只能在同一个翻译单元内定义

在头文件中用`inline`时，最好直接给出函数定义 而不是声明  否则：

假设`main.cpp`包含该头文件 会报`warning` 是该函数未定义的警告

---

`constexpr`修饰函数

和`inline`一样 因为常量是编译期概念  所以要在单个翻译单元给出完整函数的定义

---

#### 函数指针

函数指针类型`int(*)(int)` 

```c++
using K = int(int);
K* fun; // 和int(* fun)(int)一致


int inc(int x);
void Demo(K fun);
Demo(inc); // 和Demo(&inc)等价 因为直接传入函数会退化为函数指针  void Demo(K* fun) 和void Demo(K fun)也一致
```

**most vexing parse**

`{}`中一定是对象 不能是类型