#### Chapter 5

---

#### 基于范围的`for`循环

如果需要`读元素`   使用常量左值读  `const auto&`

如果需要`写元素` 使用万能引用`auto&&`写 

---

#### 循环展开

希望主要处理循环体部分（比如循环体只有一个语句） 而不是`for中的表达式`

![image-20231025220309761](/Users/jsyang/Library/Application Support/typora-user-images/image-20231025220309761.png)

![image-20231025220617615](/Users/jsyang/Library/Application Support/typora-user-images/image-20231025220617615.png)

 **改为下面这样的：**

![image-20231025220929766](/Users/jsyang/Library/Application Support/typora-user-images/image-20231025220929766.png)

![image-20231025220942762](/Users/jsyang/Library/Application Support/typora-user-images/image-20231025220942762.png)

**继续修改**：

![image-20231025221304706](/Users/jsyang/Library/Application Support/typora-user-images/image-20231025221304706.png)

![image-20231025221318378](/Users/jsyang/Library/Application Support/typora-user-images/image-20231025221318378.png)

----

#### 达夫设备

`switch`里面嵌套`for`循环

![image-20231025222230110](/Users/jsyang/Library/Application Support/typora-user-images/image-20231025222230110.png)

