### 二、C++基础深入

---

**01掌握形参带默认值的函数**

带默认形参的函数执行效率可能会更高

```c++
int sum(int a, int b);

int res = sum(10, 20);
/*
mov eax, dword ptr[ebp - 8]
push eax
mov ecx, dword ptr[ebp - 4]
push ecx
call sum
*/
// 如果传字面值 而不是变量 也会少一次mov  比如sum(a, 20)

int sum(int a = 10, int b);

int res = sum(20);
/*
少了一次mov
push eax
mov ecx, dword ptr[ebp - 4]
push ecx
call sum
*/
```

---

![image-20231117220447322](/Users/jsyang/Library/Application Support/typora-user-images/image-20231117220447322.png)

---

#### 引用

---

![image-20231117222002234](/Users/jsyang/Library/Application Support/typora-user-images/image-20231117222002234.png)

---

#### 右值引用

![image-20231118085258179](/Users/jsyang/Library/Application Support/typora-user-images/image-20231118085258179.png)

和`const`引用类似

![image-20231118085356793](/Users/jsyang/Library/Application Support/typora-user-images/image-20231118085356793.png)

如果用变量初始化const

`int b; const int a = b;` a也将退化为常变量（因为初始值不是立即数，是一个变量） 在替换的时候都用b替换 运行期才能确定 



---

一个右值引用变量，本身是一个左值

![image-20231118090332959](/Users/jsyang/Library/Application Support/typora-user-images/image-20231118090332959.png)

---

#### const

![image-20231118091202895](/Users/jsyang/Library/Application Support/typora-user-images/image-20231118091202895.png)

编译阶段 出现`a`的地方都将被替换为20， `*(&a)`将会被编译器优化 不会真正地解引用

**但是！** `a`对应的地址的值确实被修改为30了！！！

`c`中  局部`const`（在栈上分配内存的）可以被修改  全局不行 会发生段错误

![image-20231118091311962](/Users/jsyang/Library/Application Support/typora-user-images/image-20231118091311962.png)

c中的`const`不是常量

![image-20231118091518347](/Users/jsyang/Library/Application Support/typora-user-images/image-20231118091518347.png)

---

#### const和指针的结合

![image-20231118102016643](/Users/jsyang/Library/Application Support/typora-user-images/image-20231118102016643.png)

![image-20231118102632550](/Users/jsyang/Library/Application Support/typora-user-images/image-20231118102632550.png)

![image-20231118103034589](/Users/jsyang/Library/Application Support/typora-user-images/image-20231118103034589.png)

`q2`的类型是`int*`而不是`int*const`

---

#### const与二级指针的结合

基本的三种情况

```c++
const int** q; // == int const **q;所以const修饰**q
int*const* q; // const修饰*q
int ** const q; // const修饰q
```

![image-20231119100418891](/Users/jsyang/Library/Application Support/typora-user-images/image-20231119100418891.png)

`const`只看右边的类型

```c++
int a;
int *p = &a;
int ** const q = &p; 
// 相当于int **const <= int** == int ** <= int **是正确的
```



- `int*const*` `const`修饰右边的`*` 其实这里是一级指针的转换  

  即`* <= const *`是错误的

- `int *const *` `const`修饰一级指针

  即`const *<= *`是正确的

---

```c++
int a;
int *p = &a;
const int** q = &p;
/*
是错误的  错误的原因为：
如果成立
*q等价于p
*q的类型为const int *
那么如果const int b;
*q = &b; 是正确的
但是p类型为int* 所以这样就允许了把常量指针赋给非常量指针(普通的指针里面，有了常量的地址) 是错误的
其实没有多级指针
const int** p; 
这两个*含义不同  右边的表示p为指针变量  左边的和const int一起组成类型  即*p的类型为const int *
*/

// 解决办法1
// 把p改为指向常量的指针
const int * p = &a; // 上述错误的原因是：可能会把常量地址赋给普通指针  那么现在把p变成指向常量的指针即可

// 解决办法1
// 不允许修改*q
const int*const* q = &p;
```

---

常量的值是可以传递给别人的

```c++
int a;
int *const p = &a;
int ** q = &p;  // &p => int *const*
// 相当于int ** <= int*cosnt* == * <= const*是错误的
```

```c++
int a;
const int *p = &a;
int *const* q = &p; 
// 相当于int *const* <= const int** == int **
// 两个const分别来看
// 左边的：相当于const* <= int* 可以
// 结合后去掉一个 方便看右边的const
// int * <= const int* 是错误的
// 所以整个转化是错误的
```

---

#### const 指针 引用

```c++
int a;
int *p = &a;
const int*& q = p;
// 错误 还原为指针 const int** q = &p;
// const int** <= int ** 错误
```

```c++
int a;
int *const p = &a; // p是一个常量
int*& q = p;
// 错误 把常量的地址泄漏给普通引用变量
// int** <= int *const * 显然错误
```

---

### 函数重载

---

调用的时候有函数声明就足够了

函数重载需要在同一个作用域

![image-20231119152947485](/Users/jsyang/Library/Application Support/typora-user-images/image-20231119152947485.png)

---

#### new/delete free/malloc

![image-20231119160937794](/Users/jsyang/Library/Application Support/typora-user-images/image-20231119160937794.png)

![image-20231119160953825](/Users/jsyang/Library/Application Support/typora-user-images/image-20231119160953825.png)

new delete[]混用问题

https://www.foxzzz.com/cpp-array-delete/