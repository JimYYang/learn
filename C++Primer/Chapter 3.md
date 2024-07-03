### Chapter 3

---

#### 数组

`类型`是编译器关心的问题  编译在运行前完成

**tricky**:exclamation:

```c++
int x;
cin >> x;
int a[x];
// 这个做法在C语言支持  在C++中不支持
// gcc和clang在缺省参数下支持
// 在--pedantic-errors参数下不支持
// 是gcc和clang对c++标准的扩展
```

不能使用`auto b = {1, 2, 3}`来推导类型

此时`b`的`类型`是`std::initializer_list<int>`

**数组不支持复制**

```c++
int b = {1, 2, 3};
auto a = b; // a是个指针 b作为右值会退化
auto& c = b; // 可以防止类型退化 c类型为int(&)[3]
```

---

#### 指针数组和数组的指针

`int* a[3]` `a`是一个数组 里面三个指针 类型是`int*[3]`

`int(*a)[3]` `a`是一个指针，指向一个数组 包含3个`int`

```c++
int b[3];
// 加括号后* 修饰的是对象a 不在和int 关联起来
int (*a)[3] = &b; // 正确 a的类型是int(*)[]
int (&c)[3] = b; //c是引用  类型是int(&)[3]

// 没有引用数组
int& a[3] = {x1, x2, x3}; // 错误 引用是别名  不是对象  但是数组中包含的元素一定是对象
```

---

#### 数组访问

`x[y]` 如果`x`和`y`都是内建数据类型 等价`*(x + y)` 也等价于`y[x]` `*((x) + (y))`

`int a[4]` `a[2] == *(a + 2 * 4(byte))`

---

#### 不能使用`extern`把数组声明成指针

`类型`是编译期概念

```c++
// 假如有两个文件s.cpp main.cpp
// s.cpp:
int array[5] = {1, 2, 3, 4, 5};
void fun() {
  std::cout << array << std::endl;
}

// main.cpp:
extern int* array; // 强行把数组声明成指针
extern void fun();

int main() {
  std::cout << array << std::endl;
}
// fun()打印出来的是array的首地址
// array中存的数（大端存储）
// 01 00 00 00
// 02 00 00 00
// 03 00 00 00
// 04 00 00 00
// main中强行把数组声明为指针
// 所以把数组中的前8个字节（前两个整数）强行解释为地址
```

如果不想改动数组大小  可以使用`extern int array[];` --> `Unknown Bounded Array` 

`Unknown Bounded Array` 在本单元中不能使用`begin end`（因为不知道具体元素个数）

`int array[]`属于`implicit type` 可以在声明时使用

---

#### 数组大小

`begin end`获取地址  运行期才能看到 数组大小编译期就可以得到

所以不用`end - begin`得到数组大小  会降低效率 

使用`std::size`最好（不会引起类型退化）

`strlen`会把字符数组转换为`指针` 

---

#### 高维数组

高维数组隐式转化为指针时  只有最高位的信息会丢弃

---

#### vector

