# Interview

##### java基础面试知识点

- java中==和equals和hashCode的区别
- int、char、long各占多少字节数
- int与integer的区别
- 探探对java多态的理解
- String、StringBuffer、StringBuilder区别
- 什么是内部类？内部类的作用
- 抽象类和接口区别
- 抽象类的意义
- 抽象类与接口的应用场景
- 抽象类是否可以没有方法和属性？
- 接口的意义
- 泛型中extends和super的区别
- 父类的静态方法能否被子类重写
- 进程和线程的区别
- final，finally，finalize的区别
- 序列化的方式
- Serializable 和Parcelable 的区别
- 静态属性和静态方法是否可以被继承？是否可以被重写？以及原因？
- 静态内部类的设计意图
- 成员内部类、静态内部类、局部内部类和匿名内部类的理解，以及项目中的应用
- 谈谈对kotlin的理解
- 闭包和局部内部类的区别
- string 转换成 integer的方式及原理

##### java深入源码级的面试题

- 哪些情况下的对象会被垃圾回收机制处理掉？
- 讲一下常见编码方式？
- utf-8编码中的中文占几个字节；int型几个字节？
- 静态代理和动态代理的区别，什么场景使用？
- Java的异常体系
- 谈谈你对解析与分派的认识。
- 修改对象A的equals方法的签名，那么使用HashMap存放这个对象实例的时候，会调用哪个equals方法？
- Java中实现多态的机制是什么？
- 如何将一个Java对象序列化到文件里？
- 说说你对Java反射的理解
- 说说你对Java注解的理解
- 说说你对依赖注入的理解
- 说一下泛型原理，并举例说明
- Java中String的了解
- String为什么要设计成不可变的？
- Object类的equal和hashCode方法重写，为什么？

##### 数据结构

- 常用数据结构简介
- 并发集合了解哪些？
- 列举java的集合以及集合之间的继承关系
- 集合类以及集合框架
- 容器类介绍以及之间的区别（容器类估计很多人没听这个词，Java容器主要可以划分为4个部分：List列表、Set集合、Map映射、工具类（Iterator迭代器、Enumeration枚举类、Arrays和Collections），具体的可以看看这篇博文 [Java容器类](https://link.jianshu.com?t=http%3A%2F%2Falexyyek.github.io%2F2015%2F04%2F06%2FCollection%2F)）
- List,Set,Map的区别
- List和Map的实现方式以及存储方式
- HashMap的实现原理
- HashMap数据结构？
- HashMap源码理解
- HashMap如何put数据（从HashMap源码角度讲解）？
- HashMap怎么手写实现？
- ConcurrentHashMap的实现原理
- ArrayMap和HashMap的对比
- HashTable实现原理
- TreeMap具体实现
- HashMap和HashTable的区别
- HashMap与HashSet的区别
- HashSet与HashMap怎么判断集合元素重复？
- 集合Set实现Hash怎么防止碰撞
- ArrayList和LinkedList的区别，以及应用场景
- 数组和链表的区别
- 二叉树的深度优先遍历和广度优先遍历的具体实现
- 堆的结构
- 堆和树的区别
- 堆和栈在内存中的区别是什么(解答提示：可以从数据结构方面以及实际实现方面两个方面去回答)？
- 什么是深拷贝和浅拷贝
- 手写链表逆序代码
- 讲一下对树，B+树的理解
- 讲一下对图的理解
- 判断单链表成环与否？
- 链表翻转（即：翻转一个单项链表）
- 合并多个单有序链表（假设都是递增的）

##### 线程、多线程和线程池

- 开启线程的三种方式？
- 线程和进程的区别？
- 为什么要有线程，而不是仅仅用进程？
- run()和start()方法区别
- 如何控制某个方法允许并发访问线程的个数？
- 在Java中wait和seelp方法的不同；
- 谈谈wait/notify关键字的理解
- 什么导致线程阻塞？
- 线程如何关闭？
- 讲一下java中的同步的方法
- 数据一致性如何保证？
- 如何保证线程安全？
- 如何实现线程同步？
- 两个进程同时要求写或者读，能不能实现？如何防止进程的同步？
- 线程间操作List
- Java中对象的生命周期
- Synchronized用法
- synchronize的原理
- 谈谈对Synchronized关键字，类锁，方法锁，重入锁的理解
- static synchronized 方法的多线程访问和作用
- 同一个类里面两个synchronized方法，两个线程同时访问的问题
- volatile的原理
- 谈谈volatile关键字的用法
- 谈谈volatile关键字的作用
- 谈谈NIO的理解
- synchronized 和volatile 关键字的区别
- synchronized与Lock的区别
- ReentrantLock 、synchronized和volatile比较
- ReentrantLock的内部实现
- lock原理
- 死锁的四个必要条件？
- 怎么避免死锁？
- 对象锁和类锁是否会互相影响？
- 什么是线程池，如何使用?
- Java的并发、多线程、线程模型
- 谈谈对多线程的理解
- 多线程有什么要注意的问题？
- 谈谈你对并发编程的理解并举例说明
- 谈谈你对多线程同步机制的理解？
- 如何保证多线程读写文件的安全？
- 多线程断点续传原理
- 断点续传的实现



**学习的参考资料如下：**

> Java 内存模型

- [java线程安全总结](https://link.jianshu.com?t=http%3A%2F%2Fwww.iteye.com%2Ftopic%2F806990)
- [深入理解java内存模型系列文章](https://link.jianshu.com?t=http%3A%2F%2Fifeve.com%2Fjava-memory-model-0%2F)

> 线程状态：

- [一张图让你看懂JAVA线程间的状态转换](https://link.jianshu.com?t=https%3A%2F%2Fmy.oschina.net%2Fmingdongcheng%2Fblog%2F139263)

> 锁：

- [锁机制：synchronized、Lock、Condition](https://link.jianshu.com?t=http%3A%2F%2Fblog.csdn.net%2Fvking_wang%2Farticle%2Fdetails%2F9952063)
- [Java 中的锁](https://link.jianshu.com?t=http%3A%2F%2Fwiki.jikexueyuan.com%2Fproject%2Fjava-concurrent%2Flocks-in-java.html)

> 并发编程：

- [Java并发编程：Thread类的使用](https://link.jianshu.com?t=http%3A%2F%2Fwww.cnblogs.com%2Fdolphin0520%2Fp%2F3920357.html)
- [Java多线程编程总结](https://link.jianshu.com?t=http%3A%2F%2Fblog.51cto.com%2Flavasoft%2F27069)
- [Java并发编程的总结与思考](https://www.jianshu.com/p/053943a425c3#)
- [Java并发编程实战-----synchronized](https://link.jianshu.com?t=http%3A%2F%2Fwww.cnblogs.com%2Fchenssy%2Fp%2F4701027.html)
- [深入分析ConcurrentHashMap](https://link.jianshu.com?t=http%3A%2F%2Fwww.infoq.com%2Fcn%2Farticles%2FConcurrentHashMap%23)

##### 网络和安全机制

- 网络框架对比和源码分析
- 自己去设计网络请求框架，怎么做？
- okhttp源码
- 网络请求缓存处理，okhttp如何处理网络缓存的
- 从网络加载一个10M的图片，说下注意事项
- TCP的3次握手和四次挥手
- TCP与UDP的区别
- TCP与UDP的应用
- HTTP协议
- HTTP1.0与2.0的区别
- HTTP报文结构
- HTTP与HTTPS的区别以及如何实现安全性
- 如何验证证书的合法性?
- https中哪里用了对称加密，哪里用了非对称加密，对加密算法（如RSA）等是否有了解?
- client如何确定自己发送的消息被server收到?
- 谈谈你对WebSocket的理解
- WebSocket与socket的区别

##### 算法

- 排序算法有哪些？
- 最快的排序算法是哪个？
- 手写一个冒泡排序
- 手写快速排序代码
- 快速排序的过程、时间复杂度、空间复杂度
- 手写堆排序
- 堆排序过程、时间复杂度及空间复杂度
- 写出你所知道的排序算法及时空复杂度，稳定性
- 二叉树给出根节点和目标节点，找出从根节点到目标节点的路径
- 给阿里2万多名员工按年龄排序应该选择哪个算法？
- GC算法(各种算法的优缺点以及应用场景)
- 蚁群算法与蒙特卡洛算法
- 子串包含问题(KMP 算法)写代码实现
- 一个无序，不重复数组，输出N个元素，使得N个元素的和相加为M，给出时间复杂度、空间复杂度。手写算法
- 万亿级别的两个URL文件A和B，如何求出A和B的差集C(提示：Bit映射->hash分组->多文件读写效率->磁盘寻址以及应用层面对寻址的优化)
- 百度POI中如何试下查找最近的商家功能(提示：坐标镜像+R树)。
- 两个不重复的数组集合中，求共同的元素。
- 两个不重复的数组集合中，这两个集合都是海量数据，内存中放不下，怎么求共同的元素？
- 一个文件中有100万个整数，由空格分开，在程序中判断用户输入的整数是否在此文件中。说出最优的方法
- 一张Bitmap所占内存以及内存占用的计算
- 2000万个整数，找出第五十大的数字？
- 烧一根不均匀的绳，从头烧到尾总共需要1个小时。现在有若干条材质相同的绳子，问如何用烧绳的方法来计时一个小时十五分钟呢？
- 求1000以内的水仙花数以及40亿以内的水仙花数
- 5枚硬币，2正3反如何划分为两堆然后通过翻转让两堆中正面向上的硬8币和反面向上的硬币个数相同
- 时针走一圈，时针分针重合几次
- N*N的方格纸,里面有多少个正方形
- x个苹果，一天只能吃一个、两个、或者三个，问多少天可以吃完

#####JVM

- java虚拟机的特性
- 谈谈对jvm的理解
- JVM内存区域，开线程影响哪块内存
- 对Dalvik、ART虚拟机有什么了解？
- Art和Dalvik对比
- 虚拟机原理，如何自己设计一个虚拟机(内存管理，类加载，双亲委派)
- 谈谈你对双亲委派模型理解
- JVM内存模型，内存区域
- 类加载机制
- 谈谈对ClassLoader(类加载器)的理解
- 谈谈对动态加载（OSGI）的理解
- 内存对象的循环引用及避免
- 内存回收机制、GC回收策略、GC原理时机以及GC对象
- 垃圾回收机制与调用System.gc()区别



> [阿里、腾讯、百度、华为、京东、搜狗和滴滴最新面试题汇集](https://link.jianshu.com/?t=https%3A%2F%2Fmp.weixin.qq.com%2Fs%3F__biz%3DMzIyMjQ0MTU0NA%3D%3D%26mid%3D2247484617%26idx%3D1%26sn%3D3734e643d241ac9615424dd44462ee2d%26chksm%3De82c3deedf5bb4f82e7be0823739774a0a2cf8372284c8409471c2752fea1f367ca3f6857795%26mpshare%3D1%26scene%3D23%26srcid%3D1128DKotEvTe4dheaTextbqp%23rd)
>
> [2017下半年，一二线互联网公司Android面试题汇总](https://link.jianshu.com/?t=https%3A%2F%2Fzhuanlan.zhihu.com%2Fp%2F30016683)
>
> [2017 年初、阿里、腾讯、百度、华为、京东、搜狗和滴滴面试题汇集（更新篇）](https://link.jianshu.com/?t=https%3A%2F%2Fzhuanlan.zhihu.com%2Fp%2F26327485)
>
> 