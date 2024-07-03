### Chapter 12

### 动态内存

---

#### 智能指针

下面的例子  使用了自定义的`deleter`函数 来正确处理了`static`对象的销毁

默认是`delete(x.get())`

![image-20231101164141974](/Users/jsyang/Library/Application Support/typora-user-images/image-20231101164141974.png)



推荐使用`make_shared`

因为`shared_ptr`中包含对象本身的地址 也包含一个`引用计数`地址

这两个地址的距离可能很远  如果减少引用计数时发现减为0 这时候需要到很远的地方（对象的地址）去销毁对象  这样可以会引入一次`cache`读取

`make_shared`会引入优化 将这两个地址尽量安排的近 

```c++
shared_prt<int> x = new int(3);
shared_ptr<int> x = make_shared<int>(3); // 更好
```

**小心重复删除**

下面的代码会重复`delete`同一块内存

![image-20231101165621243](/Users/jsyang/Library/Application Support/typora-user-images/image-20231101165621243.png)

`unique_ptr`可以使用移动语义

```c++
unique_ptr<int> x(new int(3));
unique_ptr<int> y = move(x);
```



---

#### sizeof 不能返回动态内存的大小

`sizeof`在编译期完成  动态内存分配在编译期完成 

---

#### allcotate、mallco/free不会构造对象（不会调用构造函数）

#### new会完成内存分配和对象构造

---

#### 动态内存和异常安全

```c++
int fun() {
  int *p = new int(3);
  // ... 若这里有处理异常的代码  那么发生异常时将会直接跳出程序 导致内存泄漏
  delete p;
}

int fun() {
  // 可以解决这个问题
  shared_ptr<int> p(new int(3));
  // ...
}
```

