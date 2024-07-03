### C++面向对象

---

```c++
class S{
    inline static int a = 0;
};
```

1. **`inline` 关键字**：当用于类成员（如方法或静态成员变量）时，`inline` 关键字指示编译器尝试在每个调用点内联该成员。内联的目的是减少函数调用的开销，但它并不总是保证成员会被内联。对于静态成员变量，`inline` 的一个重要作用是允许在类定义中直接初始化该变量。在没有 `inline` 关键字的情况下，静态成员变量需要在类定义外部进行单独的定义和初始化。
2. **`static` 关键字**：在类中使用 `static` 关键字声明的成员变量或函数表明它们属于类本身，而不是类的任何特定对象。这意味着无论创建了多少个类的实例，静态成员都只有一个副本。在您的代码中，`a` 是一个静态成员变量，所以它属于 `S` 类，而不是 `S` 类的任何特定实例。

在上述代码中，`inline static int a = 0;` 声明了一个属于类 `S` 的静态整数成员 `a`，并在类定义中直接对其进行了初始化。这种做法在`C++17`及更高版本中有效，因为它们允许静态成员在类定义中被声明为 `inline` 并直接初始化。这样做的好处包括简化代码（无需在类外部定义和初始化静态成员）以及确保静态成员的初始化在程序启动时只进行一次。

![image-20231119221317536](/Users/jsyang/Library/Application Support/typora-user-images/image-20231119221317536.png)

![image-20231119221506650](/Users/jsyang/Library/Application Support/typora-user-images/image-20231119221506650.png)



![image-20231121104410823](/Users/jsyang/Library/Application Support/typora-user-images/image-20231121104410823.png)

`new`相当于`mallloc`开辟内存加对象构造两个操作

---

#### 深拷贝和浅拷贝

`memcpy`和`realloc`都是`浅拷贝` 只是内存拷贝

![image-20231121163351086](/Users/jsyang/Library/Application Support/typora-user-images/image-20231121163351086.png)

---

![image-20231121163502212](/Users/jsyang/Library/Application Support/typora-user-images/image-20231121163502212.png)

---

赋值重载返回引用的原因：可能要连续赋值 返回值会构造临时对象