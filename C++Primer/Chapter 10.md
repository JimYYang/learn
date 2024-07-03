### Chapter 10

### 泛型算法

---

`类别`和`类型`是不同的概念

---

![image-20231103135951580](/Users/jsyang/Library/Application Support/typora-user-images/image-20231103135951580.png)



只有`局部自动对象`需要捕获 静态或全局对象不需要捕获

---

使用auto避免复制（c++14）

下面的代码虽然使用`const&`但是还是会复制

因为`map`解引用的对象类型是`pair<const Key, T>`

使用`const auto&`可以避免这个问题

![image-20231103154852259](/Users/jsyang/Library/Application Support/typora-user-images/image-20231103154852259.png)

---

局部自动对象在语句结束后销毁（在`auto`那一句结束后销毁）

![image-20231103163037311](/Users/jsyang/Library/Application Support/typora-user-images/image-20231103163037311.png)