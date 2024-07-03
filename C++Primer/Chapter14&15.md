#### Chatper 14&15

### 运算符重载和虚函数

---

友元函数如果直接定义在类内部（实际上是定义在全局域内）

如果参数列表为空  如果类之前没有声明  那么直接使用会出现`undeclared`的错误

如果参数列表中有类的对象  则不需要声明  在名称查找的时候会根据参数类型在类内查找

![image-20231107085829522](/Users/jsyang/Library/Application Support/typora-user-images/image-20231107085829522.png)

---

**注意**

`Str x = ....`是类的构造 不是赋值

`[], *`运算符在重载的时候通常要重载成`const`（返回值）和非`const`（返回引用）两种形式



单参数的构造函数实际上引入了一个类型转换函数

---

### 继承

编译器只看静态类型

**注意** 构造函数的初始化在初始化列表完成 函数体内是赋值部分



基类的指针可以转换为派生类  使用`dynamic`强制转化 如果该指针不是指向派生类的  那么强制转化会返回一个空指针

基类的引用可以转换为派生类  使用`dynamic`强制转化 如果该引用不是指向派生类的  那么会抛出异常



没有虚函数 所以得调用绑定在编译期被绑定起来

通过动态类型实现运行期的多态

虚函数的缺省实参只会考虑静态类型（因为编译期的时候只知道静态类型）



如果不使用指针或引用来实现多态，就只能使用静态绑定，这意味着函数调用在编译时就已经确定，这将不能利用到多态性带来的灵活性和扩展性



在C++中，在构造函数中调用虚函数要小心以下事项：

1. **对象的构造过程中**，如果在构造函数中调用虚函数，将不会发生通常所期望的动态绑定。也就是说，即使是通过派生类的构造函数，在基类构造函数中的虚函数调用仍然只会调用基类中的版本，而不是派生类中可能重写的版本。
2. **未完全构造的对象**：当基类构造函数执行时，派生类部分尚未初始化，这意味着如果虚函数使用了派生类中的任何数据成员，这些成员可能还没有被初始化，从而可能导致不可预知的行为或者程序错误。

因此，最佳实践是避免在构造函数和析构函数中调用虚函数。如果需要在构造过程中调用某些可重写的行为，应该考虑使用非虚成员函数或者在构造完成后的初始化函数中进行。

```c++
class Base {
public:
    Base() {
        virtualFunction(); // 调用虚函数
    }

    virtual void virtualFunction() {
        cout << "Base version of virtualFunction" << endl;
    }
};

class Derived : public Base {
public:
    Derived() : Base() {}

    void virtualFunction() override {
        cout << "Derived version of virtualFunction" << endl;
    }
};

Derived obj;
```

你可能期望 `Derived` 类的 `virtualFunction` 被调用，但实际上，因为这个调用发生在 `Base` 类的构造函数中，所以调用的是 `Base` 类的 `virtualFunction`，即使是在 `Derived` 类的对象构造过程中。

这样做可能会导致问题，因为 `Derived` 类可能已经重写了 `virtualFunction` 来使用它自己的数据成员，但在 `Base` 的构造函数中，这些数据成员还没有被初始化，所以使用它们可能会导致未定义行为。



**派生类的析构函数会隐式调用基类的析构函数**



通常将基类的析构函数声明为`virtual`是为了确保派生类的对象可以通过基类的指针或引用被正确地析构。如果基类的析构函数不是虚函数，那么通过基类指针或引用删除派生类对象时，只会调用基类的析构函数，而不会调用派生类的析构函数。这可能导致派生类分配的资源没有被正确释放，从而造成资源泄漏。声明基类析构函数为`virtual`确保了派生类的析构函数将被调用，这是多态删除(polymorphic deletion)的重要组成部分。



在派生类中修改虚函数的访问权限

```c++
class Base {
public:
    virtual void func() {
        // 基类中的实现
    }
};

class Derived : public Base {
private:
    void func() override {
        // 在派生类中改变了访问权限
    }
};

int main() {
    Derived d;
    Base *b = &d;
    b->func();  // 有效：Base::func() 是公有的
    // d.func();  // 无效：Derived::func() 是私有的，不能从类的外部访问
}
```

在这个例子中，即使`Derived::func`是私有的，仍然可以通过基类`Base`的指针来调用它，因为在多态中，动态绑定会在运行时找到正确的函数版本，而不受访问权限的影响。然而，不能直接通过`Derived`的对象来调用`func`，因为它在`Derived`类中是私有的



![image-20231108160127182](/Users/jsyang/Library/Application Support/typora-user-images/image-20231108160127182.png)



无论是什么派生（继承） 子类都可以看见父类内部的`public/protected`成员 



构造函数使用`using`无法改变访问权限

![image-20231108163130320](/Users/jsyang/Library/Application Support/typora-user-images/image-20231108163130320.png)

上面代码可以运行的原因是：

不是使用using 改变了权限  而是编译器先处理Derive之后发现没有构造函数 然后生成缺省的构造函数->会隐式调用基类构造函数



友元不能继承

![image-20231108163517940](/Users/jsyang/Library/Application Support/typora-user-images/image-20231108163517940.png)

这个代码的友元函数无论改为Base& 还是Derive&都是错的（认为子类能够访问x 所以定义的友元函数也能 这个想法是错误的）



![image-20231108163848020](/Users/jsyang/Library/Application Support/typora-user-images/image-20231108163848020.png)

这样定义的友元函数只能访问Derive中隶属于Base的那部分



![image-20240325171647241](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325171647241.png)