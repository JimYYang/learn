### Chapter 9

### 容器

---

#### array

`array`的`复制`和`swap`都很慢

---

#### vector

`vector`的`复制`慢 `swap`快 直接交换指针  和数组长度无关

`emplace_back`会减少对象的拷贝与移动  效率更高

函数重载不能通过返回类型重载

---

#### set

`set`迭代器所指的对象是const的 不能通过迭代器修改元素

---

#### map

用`at`访问内存如果越界直接抛出异常

**`[]`不能用于常量对象**

````c++
void fun(const map<int, int>& m){
  m[3];
}

int main() {
	map<int, int> m{{3, 100}};
  fun(m); //错误  因为函数声明为常量对象m 因为编译期不确定3是否存在 如果不存在 运行期会改变m（插入3这个键）
}
````

---

#### 适配器

`string_view`消耗很低 其内部维护指针  函数传参时不需要传引用  因为解引用可能更耗时

一般都是作为函数参数（和`initializer_list`类似）  不作为返回值

下面这样是可以的

![image-20231102223241594](/Users/jsyang/Library/Application Support/typora-user-images/image-20231102223241594.png)



`ranges`不会立即求值 `缓式求值`  不会构造新的容器