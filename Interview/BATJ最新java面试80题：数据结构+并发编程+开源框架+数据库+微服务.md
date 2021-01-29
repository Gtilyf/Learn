# BATJ最新java面试80题：数据结构+并发编程+开源框架+数据库+微服务

https://zhuanlan.zhihu.com/p/57034459?utm_source=qq&utm_medium=social&utm_oi=58097666097152

## **数据结构与算法**

1. 链表与数组？
2. 队列和栈，出钱与入栈？
3. 链表的删除、插入、反向？
4. Hash表的hash函数，冲突解决方法有哪些？
5. 各种俳序：冒泡、选择、插入、希尔、归并、快排、堆俳、桶排、基数的原理、平均时间复杂度、最坏时间复杂度、空间复杂度、是否稳定？
6. 对冒泡与快排的改进？
7. 二分查找，与变种二分查找？
8. 二叉树、B+树、AVL树、红黑树、哈夫曼树？
9. 二叉树的前中后续遍历：递归与非递归写法，层序遍历算法？
10. KMP算法？
11. 排列组合问题？
12. 贪心算法、分治算法？

## **并发编程**

1. 跟 Synchronized 相比，可重入锁 ReentrantLock 其实现原理有什么不同？
2. 那么请谈谈 AQS 框架是怎么回事儿？
3. 请尽可能详尽地对比下 Synchronized 和 ReentrantLock 的异同。
4. ReentrantLock 是如何实现可重入性的？
5. 除了 ReetrantLock，你还接触过 JUC 中的哪些并发工具？
6. 请谈谈 ReadWriteLock 和 StampedLock。
7. 如何让 Java 的线程彼此同步？你了解过哪些同步器？请分别介绍下。
8. CyclicBarrier 和 CountDownLatch 看起来很相似，请对比下呢？
9. Synchronized 用过吗，其原理是什么？
10. 你刚才提到获取对象的锁，这个“锁”到底是什么？如何确定对象的锁？
11. 什么是可重入性，为什么说 Synchronized 是可重入锁？
12. JVM 对 Java 的原生锁做了哪些优化？
13. 为什么说 Synchronized 是非公平锁？
14. 什么是锁消除和锁粗化？
15. 为什么说 Synchronized 是一个悲观锁？乐观锁的实现原理又是什么？什么是
16. 乐观锁一定就是好的吗？
17. 什么是 Java 的内存模型，Java 中各个线程是怎么彼此看到对方的变量的？
18. 请谈谈 volatile 有什么特点，为什么它能保证变量对所有线程的可见性？
19. 请对比下 volatile 对比 Synchronized 的异同。
20. 请谈谈 ThreadLocal 是怎么解决并发安全的？
21. 很多人都说要慎用 ThreadLocal，谈谈你的理解，使用 ThreadLocal 需要注意些什么？
22. Java 中的线程池是如何实现的？
23. 创建线程池的几个核心构造参数？
24. 线程池中的线程是怎么创建的？
25. 如何在 Java 线程池中提交线程？

## **开源框架**

1. IOC和DI是什么？
2. Spring IOC的理解，其初始化过程？
3. BeanFactory 和 FactoryBean的区别？
4. BeanFactory和ApplicationContext的区別？
5. ApplicationContext上下文的生命周期？
6. Spring Bean的生命周期？
7. Spring AOP的实现原理？
8. Spring是如何管理事务的，事务管理机制？
9. Spring的不同事务传播行为有哪些，干什么闬的？
10. Spring中用到了那些设计模式？
11. Spring MVC的工作原理？
12. Spring如何解决循环依赖？
13. Spring如何保证Controller并发的安全？

## **数据库**

1. 事务四大特性（ACID)？
2. 数据库隔离级别，每个级别会引发什么问题，mysql默认是哪个级别？
3. innodb和myisam存储引擎的区別？
4. MYSQL的两种存储引擎区别（事务、锁级别等等），各自的适用场景？
5. 查询语句不同元素（where、jion、limit, group by、having等等）执行先后顺序？
6. 数据库的优化（sql语句优化和索引）？
7. 索引有B+索引和hash索引，各自的区别？
8. B+索引数据结构，和B树的区別？
9. 索引的分类（主键索引、唯一索引），最左前缀原则，哪些情况索引会失效？
10. 聚集索引和非聚集索引区别
11. 有哪些锁（乐观锁悲观锁），select时怎么加排它锁？
12. 关系型数据库和非关系型数据库区别？
13. 数据库三范式，根据某个场费设计数据表？
14. 数据库的读写分离、主从复制？
15. 使用explain优化sql和索引？
16. long_query怎么解决？
17. 死锁判定原理和具体场景，死锁怎么解决？
18. varchar和char的使用场景？
19. mysql并发情况下怎么解决（通过事务、隔离级别、锁）？
20. 数据库崩溃时事务的恢复机制（REDO日志和UNDO日志） ？

## **微服务**

1. 什么是微服务？
2. 微服务之间是如何独立通讯的？
3. springCloud和dubbo 有哪些区别？
4. springboot和springcloud,请谈谈对它们的理解？
5. 什么是微服务熔断？什么是服务降级？
6. 微服务的优缺点分别是什么？说下在项目开发中碰到的问题？
7. 你所知道的微服务技术栈有哪些？
8. eureka和zookeeper都可以提供服务的注册和发现的功能，请说说两者的区别？

