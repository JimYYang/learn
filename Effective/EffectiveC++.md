



### Effective c++

---

![image-20240627231228829](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627231228829.png)



---

![image-20240627232305794](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232305794.png)



编译器是位常量 编程希望是逻辑常量  static成员在const函数中可以变化 因为static成员根本不属于这个对象

----

![image-20240627232436165](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232436165.png)

mutable可以摆脱位常量的限制

![image-20240627232539678](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232539678.png)

![image-20240627232552112](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232552112.png)

![image-20240627232559309](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232559309.png)



![image-20240627232622475](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232622475.png)



![image-20240627232627093](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232627093.png)





![image-20240627232648891](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232648891.png)



![image-20240627232658659](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232658659.png)



其实这就是单例模式  在cpp11之后 这个写法是线程安全的 因为对于局部静态对象 编译器会自动加锁确保线程安全

![image-20240627232704857](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232704857.png)



![image-20240627232710409](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232710409.png)

会生成默认构造  拷贝构造 赋值  析构  但是不会生成移动构造和移动赋值

![image-20240627232716258](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232716258.png)



![image-20240627232723140](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232723140.png)

![image-20240627232729007](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232729007.png)

![image-20240627232745056](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232745056.png)



![image-20240627232749390](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232749390.png)

![image-20240627232755223](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232755223.png)



![image-20240627232800107](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232800107.png)



![image-20240627232817535](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232817535.png)



![image-20240627232822305](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232822305.png)



![image-20240627232832238](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232832238.png)

注意 这里必须为纯虚函数提供定义 不然会报链接错误





![image-20240627232837887](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232837887.png)



![image-20240627232843904](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232843904.png)



![image-20240627232848704](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627232848704.png)









![image-20240626210756499](/Users/jsyang/Library/Application Support/typora-user-images/image-20240626210928507.png)

![image-20240626211031866](/Users/jsyang/Library/Application Support/typora-user-images/image-20240626211031866.png)

----

#### Term9

![image-20240627101803154](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627101803154.png)

![image-20240627102304153](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627102304153.png)

对于析构函数同理  因为析构函数 先调用子类的析构  再调用父类析构  析构函数中调用虚函数  可能子类的相关成员已经被销毁  这时候调用虚函数  虚函数可能使用的是已经被销毁子类数据成员



![image-20240627103840003](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627103840003.png)

返回引用主要是可能前后缀++



![image-20240627104032683](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627104032683.png)



![image-20240627104939263](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627104939263.png)

不写 调用基类默认构造  基类没有默认构造就会报错  要手动调用基类相应的构造函数



不要忘记基类部分的拷贝

![image-20240627105223704](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627105223704.png)

![image-20240627105309876](/Users/jsyang/Library/Application Support/typora-user-images/image-20240627105309876.png)

---

![image-20240628143143594](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628143143594.png)

会调用三次析构  第一次是pInv1 = 这一行  因为是unique_ptr 强制赋值另一个 那么先析构他原来的



![image-20240628143316494](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628143316494.png)



![image-20240628144128446](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628144128446.png)

![image-20240628145710020](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628145710020.png)



![image-20240628145957874](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628145957874.png)



![image-20240628152110479](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628152110479.png)





![image-20240628152152289](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628152152289.png)

![image-20240628152613270](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628152613270.png)



![image-20240628152721649](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628152721649.png)

![image-20240628152808694](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628152808694.png)



![image-20240628153001644](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628153001644.png)

![image-20240628153026419](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628153026419.png)![image-20240628153137752](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628153137752.png) 











![image-20240628153443970](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628153443970.png)

类型转换运算符 将T1转换为T2

![image-20240628153623774](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628153623774.png)



![image-20240628163650256](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628163650256.png)



![image-20240628163758585](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628163758585.png)

只有按引用或者指针传递才有多态的效果



![image-20240628163842365](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628163842365.png)

内置类型 等 按照值传递即可

---

![image-20240628164136371](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628164136371.png)

不要随便返回引用



![image-20240628164304250](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628164304250.png)



![image-20240628164958984](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628164958984.png)

![image-20240628165644952](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628165644952.png)



![image-20240628170136976](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628170136976.png)

![image-20240628170150825](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628170150825.png)



![image-20240628170329428](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628170329428.png)



![image-20240628170351155](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628170351155.png)



![image-20240628171446100](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628171446100.png)

![image-20240628170912579](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628170912579.png)

这里只是把范围从T缩小到Widget<T>  只有改为int才符合标准

![image-20240628171128381](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628171128381.png)

这个和 swap(T, T)参数类型不同  是模板函数的重载



![image-20240628172338429](/Users/jsyang/Library/Application Support/typora-user-images/image-20240628172338429.png)



注意这里调用swap的名字查找顺序  先自己的名字空间 再全局  再其他的名字空间



![image-20240630142102072](/Users/jsyang/Library/Application Support/typora-user-images/image-20240630142102072.png)

![image-20240630142345122](/Users/jsyang/Library/Application Support/typora-user-images/image-20240630142345122.png)

![image-20240630142705387](/Users/jsyang/Library/Application Support/typora-user-images/image-20240630142705387.png)

![image-20240630142801647](/Users/jsyang/Library/Application Support/typora-user-images/image-20240630142801647.png)

![image-20240630142912513](/Users/jsyang/Library/Application Support/typora-user-images/image-20240630142912513.png)

![image-20240630143024225](/Users/jsyang/Library/Application Support/typora-user-images/image-20240630143024225.png)

![image-20240630143104744](/Users/jsyang/Library/Application Support/typora-user-images/image-20240630143104744.png)

![image-20240630143206859](/Users/jsyang/Library/Application Support/typora-user-images/image-20240630143206859.png)

![image-20240630143250163](/Users/jsyang/Library/Application Support/typora-user-images/image-20240630143250163.png)