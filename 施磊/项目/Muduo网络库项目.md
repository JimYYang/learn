## Muduo网络库项目

![image-20240227161722091](/Users/jsyang/Library/Application Support/typora-user-images/image-20240227161722091.png)

![image-20240227161819929](/Users/jsyang/Library/Application Support/typora-user-images/image-20240227161819929.png)

![image-20240227162318648](/Users/jsyang/Library/Application Support/typora-user-images/image-20240227162318648.png)

![image-20240227162934507](/Users/jsyang/Library/Application Support/typora-user-images/image-20240227162934507.png)

![image-20240227203221992](/Users/jsyang/Library/Application Support/typora-user-images/image-20240227203221992.png)

![image-20240228215746408](/Users/jsyang/Library/Application Support/typora-user-images/image-20240228215746408.png)

![image-20240302164227863](/Users/jsyang/Library/Application Support/typora-user-images/image-20240302164227863.png)

![image-20240303100841711](/Users/jsyang/Library/Application Support/typora-user-images/image-20240303100841711.png)

![image-20240303101646567](/Users/jsyang/Library/Application Support/typora-user-images/image-20240303101646567.png)

![image-20240303101953678](/Users/jsyang/Library/Application Support/typora-user-images/image-20240303101953678.png)

![image-20240303112038936](/Users/jsyang/Library/Application Support/typora-user-images/image-20240303112038936.png)

---

一个`EventLoop`管理一个`Poller`和多个`Channel`  还有`wakeFd`（每个loop都有一个wakeFd 可以通过向这个fd写内容来唤醒阻塞在epoll_wait的loop）

![image-20240310095020199](/Users/jsyang/Library/Application Support/typora-user-images/image-20240310095020199.png)