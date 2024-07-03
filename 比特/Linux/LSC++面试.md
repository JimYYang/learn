## LSC++面试

![image-20240322205815738](/Users/jsyang/Library/Application Support/typora-user-images/image-20240322205815738.png)

const 可以减少内存分呗  用define内存会被分配两次

const还有类型检查 作用域检查  define只是替换



const修饰函数返回值

![image-20240322210228170](/Users/jsyang/Library/Application Support/typora-user-images/image-20240322210228170.png)



const 修饰成员函数  当定义常对象的时候  这个对象（or指针 or引用）只能访问常成员函数



![image-20240322210757466](/Users/jsyang/Library/Application Support/typora-user-images/image-20240322210757466.png)

还可以用来函数重载

---

### static

![image-20240322211856734](/Users/jsyang/Library/Application Support/typora-user-images/image-20240322211856734.png)

---

new操作符从**自由存储区（free store）**上为对象动态分配内存空间，而malloc函数从**堆**上动态分配内存。自由存储区是C++基于new操作符的一个抽象概念，凡是通过new操作符进行内存申请，该内存即为自由存储区。而堆是操作系统中的术语，是操作系统所维护的一块特殊内存，用于程序的内存动态分配，C语言使用malloc从堆上分配内存，使用free释放已分配的对应内存。

那么自由存储区是否能够是堆（问题等价于new是否能在堆上动态分配内存），这取决于operator new 的实现细节。自由存储区不仅可以是堆，还可以是静态存储区，这都看operator new在哪里为对象分配内存。

特别的，new甚至可以不为对象分配内存！**定位new**的功能可以办到这一点：

new (place_address) type

place_address为一个指针，代表一块内存的地址。当使用上面这种仅以一个地址调用new操作符时，new操作符调用特殊的operator new，也就是下面这个版本：

void * operator new (size_t,void *) //不允许重定义这个版本的operator new

这个operator new**不分配任何的内存**，它只是简单地返回指针实参，然后右new表达式负责在place_address指定的地址进行对象的初始化工作。

![image-20240322224051150](/Users/jsyang/Library/Application Support/typora-user-images/image-20240322224051150.png)

---

问题：对c++初学者来说存在一个误区，如果类没有定义任何[构造函数](https://so.csdn.net/so/search?q=构造函数&spm=1001.2101.3001.7020)，编译器会自动生成默认的构造函数。 

**注意：这种说法是错误的。**

正确的说法：惟有默认构造函数**”被需要“**的时候[编译器](https://so.csdn.net/so/search?q=编译器&spm=1001.2101.3001.7020)才会合成默认构造函数。

那什么情况下是“被需要”的时候？

以下有四种情况编译器会自动合成默认构造函数

**情况1** **含有类对象数据成员，该类对象类型有默认构造函数**

即：一个class含有[类对象](https://so.csdn.net/so/search?q=类对象&spm=1001.2101.3001.7020)数据成员，该类对象类型有默认构造函数sA包含了一个对象成员objectB，而这个对象成员定义了（classB的）默认构造函数，那么编译器会为classB合成一个默认构造函数。

```

```

原因：因为类成员对象有默认构造函数,那么编译器就需要显式的来调用这个类成员对象的构造函数。而编译器想显式的调用类成员对象的默认构造函数,就需要自己来合成一些代码来调用。但是记住,编译器合成的默认构造函数**仅仅调用类成员对象的默认构造函数,而不对我们类里面的其它变量做任何初始化操作****。**

 

**情形2 基类带有默认构造函数的派生类**

 当一个类派生自一个含有默认构造函数的基类时，该类也符合编译器需要合成默认构造函数的条件。编译器合成的默认构造函数将根据基类声明顺序调用上层的基类默认构造函数。

 原因：因为派生类被合成时需要显式调用基类的默认构造函数。

```cpp

```

**情形3 带有虚函数的类**

​     类带有虚函数可以分为两种情况：

 

1. (1)类本身定义了自己的虚函数

​      (2)类从继承体系中继承了虚函数（成员函数一旦被声明为虚函数，继承不会改变虚函数的”虚性质“）。

 

​    这两种情况都使一个类成为带有虚函数的类。这样的类也满足编译器需要合成默认构造函数的类，原因是含有虚函数的类对象都含有**一个虚表指针vptr**，编译器需要对vptr设置初值以满足虚函数机制的正确运行，**编译器会把这个设置初值的操作放在默认构造函数中**。如果设计者没有定义任何一个默认构造函数，则编译器会合成一个默认构造函数完成上述操作，否则，编译器将在每一个构造函数中插入代码来完成相同的事情。

 

**情形4 带有虚基类的类**

   虚继承也会在子类对象中被合成一个指向虚基类的指针，因此也要被初始化，所以必须要构造函数，虚基类或者虚继承保证子类对象中只有一份虚基类的对象。

 

 总结一下： 不符合以上4种情形的而且没有声明任何构造函数的，编译器并不会合成默认的构造函数；

​          并且合成的默认构造函数并不会初始化类的内置类型复合类型的数据成员。

![image-20240323101149763](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323101149763.png) 













需要默认拷贝构造函数原因：如果不提供默认拷贝构造函数，编译器会按照位拷贝进行拷贝（位拷贝指的是按字节进行拷贝，有些时候位拷贝出现的不是我们预期的行为，会取消一些特性）

以下是需要默认拷贝构造函数的必要条件：

1：类成员也是一个类，该成员类有拷贝构造函数 。为了让成员类的拷贝构造函数能够被调用到，不得不为类生成默认拷贝构造函数。

2：类继承自基类，基类有拷贝构造函数。子类执行拷贝构造函数时，先调用父类的拷贝构造函数，为了能够调用到父类的拷贝构造，不得不生成默认的拷贝构造函数。

3：类成员当中包含一个或多个虚函数。为了实现多态机制，需要为类维护一个虚函数表，类所有对象需要保存指向该虚函数的指针。如果不提供默认拷贝构造函数，会进行位拷贝，那么虚函数表指针会丢失。因此，不得不位类生成默认拷贝构造函数，完成虚函数表指针的拷贝。

4：类继承自基类，基类有一个或多个虚函数。如果不提供默认拷贝构造函数，会进行位拷贝，那么基类拷贝构造函数不能调用，从而虚函数表指针会丢失。因此，不得不为类生成默认拷贝构造函数，完成基类拷贝构造函数的调用，从而完成虚函数表指针的拷贝。

---

   当`std::vector`中存储的元素是指针时，容器负责管理这些指针的生命周期，但不负责管理指针所指向对象的生命周期。这意味着，当`vector`被销毁或从中删除元素时，它会自动销毁存储的指针，但不会自动删除指针所指向的对象。如果没有手动删除这些对象，就可能会导致内存泄漏。

这种设计反映了C++标准库容器的一般原则：容器管理其包含的元素的生命周期，但不管理指针所指对象的生命周期。对于非指针类型的元素，当元素被移除或容器被销毁时，元素的析构函数会被自动调用。然而，对于指针类型的元素，析构函数仅负责释放指针本身的内存，而不是指针所指向的对象的内存。

```c++
#include <iostream>
#include <vector>

class MyClass {
public:
    MyClass() { std::cout << "MyClass constructed\n"; }
    ~MyClass() { std::cout << "MyClass destructed\n"; }
};

int main() {
    std::vector<MyClass*> vec;
    
    vec.push_back(new MyClass()); // 构造函数被调用
    vec.push_back(new MyClass()); // 构造函数被调用

    // 此时vector被销毁，但只释放了指针的内存，并没有调用MyClass的析构函数
}
```

![image-20240323150507981](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323150507981.png)

![image-20240323164010714](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323164010714.png)

![image-20240323170307688](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323170307688.png)

![image-20240323171414722](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323171414722.png)

模版参数的类型推导规则和auto一致

---

## function lambda bind

![image-20240323182709869](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323182709869.png)

![image-20240323182920454](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323182920454.png)

![image-20240323182745810](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323182745810.png) 







![image-20240323184701859](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323184701859.png)

![image-20240323184805870](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323184805870.png)

![image-20240323185824828](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323185824828.png)

![image-20240323193350641](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323193350641.png)

![image-20240323193724309](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323193724309.png)

![image-20240323195603072](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323195603072.png)

![image-20240323200954738](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323200954738.png)

![image-20240323202204860](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323202204860.png)

![image-20240323204935077](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323204935077.png)

![image-20240323205532518](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323205532518.png)

![image-20240323210206834](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323210206834.png)

![image-20240323210512628](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323210512628.png)

![image-20240323225213149](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323225213149.png)

![image-20240323230805689](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323230805689.png)

![image-20240323230842197](/Users/jsyang/Library/Application Support/typora-user-images/image-20240323230842197.png)

![image-20240324103425750](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324103425750.png)

![image-20240324103457722](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324103457722.png)

![image-20240324103631748](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324103631748.png)

![image-20240324115645665](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324115645665.png)

![image-20240324115857686](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324115857686.png)



![image-20240326120509705](/Users/jsyang/Library/Application Support/typora-user-images/image-20240326120509705.png)

![image-20240326120544687](/Users/jsyang/Library/Application Support/typora-user-images/image-20240326120544687.png)



![image-20240324123725634](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324123725634.png)

![image-20240324124322921](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324124322921.png)

![image-20240324124546993](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324124546993.png)

![image-20240324192317112](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324192317112.png)

![image-20240324192617682](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324192617682.png)

![image-20240324192828231](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324192828231.png)

![image-20240324194227611](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324194227611.png)

![image-20240324195007030](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324195007030.png)

![image-20240324195137154](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324195137154.png)

![image-20240324204226955](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324204226955.png)

![image-20240324204917120](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324204917120.png)

![image-20240324205155847](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324205155847.png)

![image-20240324205339665](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324205339665.png)

![image-20240324205426528](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324205426528.png)

![image-20240324210131007](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324210131007.png)

![image-20240324210229482](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324210229482.png)

![image-20240324211205708](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324211205708.png)

![image-20240324211405835](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324211405835.png)

![image-20240324211653222](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324211653222.png)

![image-20240324211712774](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324211712774.png)

![image-20240324220623380](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324220623380.png)

![image-20240324220847724](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324220847724.png)

![image-20240324221339974](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324221339974.png)

![image-20240324221932477](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324221932477.png)

![image-20240324222037555](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324222037555.png)

![image-20240324222130003](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324222130003.png)

---

写数据流程

![image-20240324222538958](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324222538958.png)

![image-20240324222856155](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324222856155.png)

![image-20240324224752819](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324224752819.png)

![image-20240324224943149](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324224943149.png)

![image-20240324225155694](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324225155694.png)

![image-20240324225408529](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324225408529.png)

![image-20240324225455222](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324225455222.png)

![image-20240324225742456](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324225742456.png)

![image-20240324225836614](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324225836614.png)

![image-20240324230552665](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324230552665.png)

![image-20240324230855241](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324230855241.png)

![image-20240324231033967](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324231033967.png)

![image-20240324231159388](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324231159388.png)

![image-20240324231627365](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324231627365.png)

![image-20240324232552321](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324232552321.png)

![image-20240324233415581](/Users/jsyang/Library/Application Support/typora-user-images/image-20240324233415581.png)

![image-20240325084018551](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325084018551.png)

![image-20240325084254846](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325084254846.png)

![image-20240325084704157](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325084704157.png)

![image-20240325084717918](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325084717918.png)

![image-20240325084934528](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325084934528.png)

![image-20240325085859765](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325085859765.png)

![image-20240325090355148](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325090355148.png)

![image-20240325090957926](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325090957926.png)

![image-20240325091105562](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325091105562.png)

![image-20240325104817903](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325104817903.png)

![image-20240325131606215](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325131606215.png)

![image-20240325132028642](/Users/jsyang/Library/Application Support/typora-user-images/image-20240325132028642.png)

![image-20240326140052114](/Users/jsyang/Library/Application Support/typora-user-images/image-20240326140052114.png)

![image-20240412131035517](/Users/jsyang/Library/Application Support/typora-user-images/image-20240412131035517.png)