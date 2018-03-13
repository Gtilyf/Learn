# 阿里社招Java面试题总结

[https://www.imooc.com/article/22941](https://www.imooc.com/article/22941)

**面试题**
1、String和StringBuffer的区别
2、gc的概念，如果A和B对象循环引用，是否可以被GC？
3、Java中的内存溢出是如何造成的
4、String s = “123”;这个语句有几个对象产生
5、Error、Exception和RuntimeException的区别，作用又是什么？
6、列举3个以上的RuntimeException
7、reader和inputstream区别
8、hashCode的作用
9、Object类中有哪些方法，列举3个以上（可以引导）
10、char型变量中能不能存贮一个中文汉字?为什么?
11、列举几个Java Collection类库中的常用类
12、List、Set、Map是否都继承自Collection接口？
13、HashMap和Hashtable的区别
14、HashMap中是否任何对象都可以做为key,用户自定义对象做为key有没有什么要求？
15、interface 和 abstrat class的区别 是否可以继承多个接口，是否可以继承多个抽象类
16、 启动一个线程是用run()还是start()? 多线程有几种实现 同步和并发是如何解决的 什么叫守护线程，用什么方法实现守护线程（Thread.setDeamon()的含义） 如何停止一个线程？ 解释是一下什么是线程安全？举例说明一个线程不安全的例子。解释Synchronized关键字的作用。 当一个线程进入一个对象的一个synchronized方法后，其它线程是否可进入此对象的其它方法?
17、了解过哪些JDK8的新特性，举例描述下相应的特性？
18、对sql进行优化的原则有哪些？
19、servlet生命周期是生命与cgi的区别？
20、StringBuffer有什么优势？为什么快？

**other**
谈谈你对HashMap的理解，底层原理的基本实现，HashMap怎么解决碰撞问题的？
开发中用了那些数据库？回答mysql，储存引擎有哪些？然后问了我悲观锁和乐观锁问题使用场景、分布式集群实现的原理。
springmvc和mybatis的工作原理，有没有看过底层源码？
熟悉IO么？与NIO的区别，阻塞与非阻塞的区别
微信红包怎么实现。
海量数据分析。
线程安全和非线程安全。
HTTP2.0、thrift。
java反射应用
分布式事务一致性。
nio的底层实现。
jvm基础是必问的，jvm GC原理，JVM怎么回收内存。
API接口与SDI接口的区别
dubbo如何一条链接并发多个调用。Dubbo的原理，序列化相关问题。
用过哪些中间件。
做过工作流引擎没有。
以前的工作经历，自己觉得出彩的地方
线程池的一些原理，锁的机制升降级
从系统层面考虑，分布式从哪些纬度考虑
Hadoop底层怎么实现
threadLocal，线程池，hashMap/hashTable/coccurentHashMap等
秒杀系统的设计
虚拟机，IO相关知识点
Linux的命令
一个整形数组，给定一个数，在数组中找出两个数的和等于这个数，并打印出来，我写的时间复杂度高，要求O(n)。
n个整数，找出连续的m个数加和是最大。
更重视开源技术
数据库锁隐原理
1000个线程同时运行，怎么防止不卡
并列的并发消费问题）
高并发量大的话怎么处理热点，数据等
如何获取一个本地服务器上可用的端口
流量控制相关问题
数据库TPS是多少，是否进行测试过
缓存击穿有哪些方案解决
Java怎么挖取回收器相关原理
Java的集合都有哪些，都有什么特点
分布式锁，redis缓存，spring aop，系统架构图，MySQL的特性
场景，同时给10万个人发工资，怎么样设计并发方案，能确保在1分钟内全部发完 打个比方会提出类似的场景