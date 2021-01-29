# d

1. private修饰的方法可以通过反射访问，那么private的意义是什么
2. Java类初始化顺序
3. 对方法区和永久区的理解以及它们之间的关系
4. 一个java文件有3个类，编译后有几个class文件
5. 局部变量使用前需要显式地赋值，否则编译通过不了，为什么这么设计
6. ReadWriteLock读写之间互斥吗
7. Semaphore拿到执行权的线程之间是否互斥
8. 写一个你认为最好的单例模式
9. B树和B+树是解决什么样的问题的，怎样演化过来，之间区别
10. 写一个生产者消费者模式
11. 写一个死锁
12. cpu 100%怎样定位
13. String a = "ab"; String b = "a" + "b"; a == b 是否相等，为什么
14. int a = 1; 是原子性操作吗
15. 可以用for循环直接删除ArrayList的特定元素吗？可能会出现什么问题？怎样解决
16. 新的任务提交到线程池，线程池是怎样处理
17. AQS和CAS原理
18. synchronized底层实现原理
19. volatile作用，指令重排相关
20. AOP和IOC原理
21. Spring怎样解决循环依赖的问题
22. dispatchServlet怎样分发任务的
23. mysql给离散度低的字段建立索引会出现什么问题，具体说下原因



1. jvm gc 复制算法是怎样实现的
2. 注解的原理
3. 进程间通信的方式有哪些
4. ReentrantLock 是可重入锁，什么是可重入锁
5. 线程执行过程中遇到异常会发生什么，怎样处理
6. HashMap
   put()元素产生冲突，为什么用LinkedList（拉链法）而不用ArrayList解决，产生冲突时key值不等，新元素怎样加入链表，为什么这么设计（jdk1.8之前）
7. 双检锁写一个单例模式，为什么要用volatile修饰对象，Object object = new Object();
   object为null吗？为什么
8. Object object = new Object(); 初始化的顺序是什么在jvm各区域做了什么