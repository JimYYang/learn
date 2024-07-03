### Chapter 2 

`cout`和`clog`不会刷新缓冲区  `cerr`会刷新缓冲区

所谓刷新缓冲区就是把缓冲区的内容输出  然后清空缓冲区

---

```c++
// 如果函数中不用pValue 但是又想保留这个接口（2个参数） 可以使用下面的形式
void func(const char* pInfo, int /*pValue balabalabal*/) {
};
```

---

```c++
int a;
int *p = &a;
// p + 1 向前移动了4个字节
void *b;
// b + 1 是非法的  不知道要移动多少单位
```

---

指针的「复制成本」低，但是「读写成本」高

因为要进行「解引用」

需要进行**两次内存访问**：一次是**访问指针本身**得到地址；第二次是**根据地址访问对象**

----

 引用属于**编译期概念**，底层还是通过**指针**实现

不存在**空引用**，但是存在**非法引用**

不存在**引用的引用**（因为引用不是对象）

```c++
int& fun() {
	int x;
	return x;
	// return x 等价:
	// int& ref = x;
	// return ref;
}

int main() {
  // 非法引用 x生命周期在fun()结束后已经结束
 	// 引用绑定了一个已经销毁的对象
  int& r = fun();
  
  int x = 3;
  int& ref = x;
  // 没有引用的引用
  int& & ref2 = ref;
  // &&代表右值引用
  int&& ref3 = ref; // 错误 ref不是对象
}
```

---

变量是由底层硬件支持的（可以修改对应内存上的值），常量是**编译期概念**（不存在说某一个内存只读 ）

```c++
const int* ptr 和 int const* ptr等价
// 可以在*画一条竖线 看看const 出现在哪里
// 指向常量的指针可以指向变量(反过来不行)
int x = 3;
const int* ptr = &x; // *x 的类型为int* 在初始化的时候进行了隐式类型转换int* --> const int*

// 常量引用
void fun(const int& param);
// 这种写法是没有必要的
// 如果我们想修改参数的值  使用int& 即可
// 如果我们不想修改参数的值  使用int即可
// 		 这时候使用const int& 会拷贝指针的值给形式参数（8个字节）并且在fun内部读取x时需要解引用 降低了效率
// 只有结构体或者类的时候才有必要使用常量引用

// 常量引用可以绑定字面值
```

---

#### 常量表达式

`const int a = 3`  a在**编译期**确定（编译时将会进行性能优化）

`const int a = x`  a在**运行期**确定

**编译期常量**使用`constexpr`

**注意**:exclamation::exclamation::exclamation: 

- `constexpr int a = 3;`  `a`的类型还是`const int`只不过告诉编译器是编译期常量

**常量表达式指针**

- `constexpr const int* ptr = nullptr` 

   `constptr`是修饰`ptr`的(`constexpr`并不是类型修饰部分，不是类型)  

  `ptr`的类型是`const int* const`

---

#### 别名

注意别名**不是**简单的替换

```c++
using IntPtr = int*;

int x = 3;
const int* a = &x; // 底层const 指向常量的指针
const IntPtr b = &x; // 顶层const  const 修饰整个IntPtr(即int*) 常量指针
```

---

#### 自动推导 

`int&`作为右值会退化为`int`

`const int&` --> `int`

```c++
int x = 3;
int& r1 = x;
auto r2 = r1; // r2退化为int

const int x = 3;
const auto y = x; // const int作为右值会退化为int 但是左边写的是const auto 编译器会自动推断出一个最合适的类型 即const int

auto& // 能够推导出引用类型 可以避免类型退化
const int x = 3;
auto& y = x; // 首先 y 一定是引用类型  然后auto匹配为const int 所以y为const int&

const int& x = 3;
auto& y = x; // y还是const int&

decltype // 不会产生类型退化
decltype(exp)
// 如果exp为右值 和exp一样
// 如果exp为左值 返回的是 左值类型+引用
int x = 3;
int* p = &x;
*p -> int
decltype(x) -> int // 如果exp是变量名称 一定就是exp的类型
decltype(*p) -> int& // exp为变量名加操作符 左值加引用
decltype((x)) -> int& // 如果想得到引用类型 最简单的方法是变量名加括号
  
decltype(auto) x = exp; // auto会自动变成exp
```

---

#### 域与对象的生命周期

域其中的**名称**有唯一的含义（注意不是`对象`或`变量`） 

