### STL

---

![image-20231125155238178](/Users/jsyang/Library/Application Support/typora-user-images/image-20231125155238178.png)

#### vector

![image-20231124082649488](/Users/jsyang/Library/Application Support/typora-user-images/image-20231124082649488.png)

resize()和reserve()是两回事，前者影响容器中元素个数，后者影响容器预留空间。

> 假设vector vec; size() = 50 capacity() = 100 那么：
>
> 1. resize(10);//size() == 10 10–49下标的元素被删除,capacity()=100不变，没有内存重分配。
> 2. resize(60);//size()==60 50–59下标用默认构造函数填充,capacity()=100不变，没有内存重分配。
> 3. resize(60,999);//size()==60 50–59下标用999填充,capacity()=100不变，没有内存重分配。
> 4. resize(200);//size()==200 50–199下标用默认构造函数填充,capacity()=200,自动扩容，内存重分配。
> 5. reserve(10);//size()==50 不变，没有元素被删除，capacity()=100，不变，即reserve调用不起作用。
> 6. reserve(60);//size()==50 元素不变，capacity()=100，不变，即reserve调用不起作用。
> 7. reserve(200);//size()==50 元素不变，capacity()=200，扩容，内存重分配。

![image-20231124085147393](/Users/jsyang/Library/Application Support/typora-user-images/image-20231124085147393.png)

---

#### deque

![image-20231124090616844](/Users/jsyang/Library/Application Support/typora-user-images/image-20231124090616844.png)

![image-20231124090305141](/Users/jsyang/Library/Application Support/typora-user-images/image-20231124090305141.png)

![image-20231124090451227](/Users/jsyang/Library/Application Support/typora-user-images/image-20231124090451227.png)

---

#### list

![image-20231124092203104](/Users/jsyang/Library/Application Support/typora-user-images/image-20231124092203104.png)

---

#### 简单对比

![image-20231125154139098](/Users/jsyang/Library/Application Support/typora-user-images/image-20231125154139098.png)

`vector`的效率更好 因为内存是连续的 底层移动的指令更少

---

#### 容器适配器

![image-20231125160029149](/Users/jsyang/Library/Application Support/typora-user-images/image-20231125160029149.png)

![image-20231125160443227](/Users/jsyang/Library/Application Support/typora-user-images/image-20231125160443227.png)

`vector`开始的容量为0 需要不断扩容 而`deque`开始时包含很多空间
在 C++ 标准库中，容器适配器是一种使用基本容器类（如 `vector`, `deque`, `list` 等）的封装，以提供不同的接口或行为。`queue`, `stack`, 和 `priority_queue` 是常见的容器适配器。它们各自选择了不同的底层容器，主要基于它们的特定用途和性能需求。

1. **`queue` 和 `stack` 使用 `deque`**:
   - `queue` 和 `stack` 的主要操作是在一端添加元素，在另一端移除元素。
   - `deque`（双端队列）支持在两端高效地添加和移除元素。
   - 使用 `deque` 作为底层容器允许 `queue` 和 `stack` 在不需要重新分配或移动整个容器内容的情况下，快速地在两端进行操作。
2. **`priority_queue` 使用 `vector`**:
   - `priority_queue` 的主要功能是确保最高（或最低）优先级元素总是可访问。
   - 在 `priority_queue` 中，元素通常按照堆排序，使得队列的头部总是最高优先级的元素。
   - `vector` 提供了快速的随机访问，这对于维护堆结构是重要的，因为堆操作（如 `push_heap` 和 `pop_heap`）需要访问和比较内部元素。
   - 相比于 `deque`，`vector` 通常拥有更紧凑的内存布局，这有助于优化堆操作。

---

#### unordered_map

for-each需要使用常引用const auto&

---

#### 迭代器

![image-20231125170449946](/Users/jsyang/Library/Application Support/typora-user-images/image-20231125170449946.png)



![image-20231125165912032](/Users/jsyang/Library/Application Support/typora-user-images/image-20231125165912032.png)

---

#### 函数对象（仿函数）

=>C中的函数指针

![image-20231126080146516](/Users/jsyang/Library/Application Support/typora-user-images/image-20231126080146516.png)

![image-20231126080227060](/Users/jsyang/Library/Application Support/typora-user-images/image-20231126080227060.png)

![image-20231126080352557](/Users/jsyang/Library/Application Support/typora-user-images/image-20231126080352557.png)

`内联`发生在编译阶段

即使`greater less`前面加上`inline`也不行  因为`compare`里，在编译阶段根本不知道调用了谁

**函数对象实现**

![image-20231126080639723](/Users/jsyang/Library/Application Support/typora-user-images/image-20231126080639723.png)

这样传入的是对象  调用的是谁非常明确  可以达到内联的效果

![image-20231126080849854](/Users/jsyang/Library/Application Support/typora-user-images/image-20231126080849854.png)

---

#### 泛型算法

![image-20231126091616564](/Users/jsyang/Library/Application Support/typora-user-images/image-20231126091616564.png)

![image-20231126091716260](/Users/jsyang/Library/Application Support/typora-user-images/image-20231126091716260.png)

![image-20231126091742356](/Users/jsyang/Library/Application Support/typora-user-images/image-20231126091742356.png)

![image-20231126091946079](/Users/jsyang/Library/Application Support/typora-user-images/image-20231126091946079.png)