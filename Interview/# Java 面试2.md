## Java 面试2

## 一、Java 基础

1.JDK 和 JRE 有什么区别？

2.== 和 equals 的区别是什么？

3.两个对象的 hashCode()相同，则 equals()也一定为 true，对吗？

4.final在 java 中有什么作用？

5. java 中的 Math.round(-1.5) 等于多少？

6.String 属于基础的数据类型吗？

7. java 中操作字符串都有哪些类？它们之间有什么区别？

8.String str="i"与 String str=new String(“i”)一样吗？

9.如何将字符串反转？

10.String 类的常用方法都有那些？

11.抽象类必须要有抽象方法吗？

12.普通类和抽象类有哪些区别？

13.抽象类能使用 final 修饰吗？

14.接口和抽象类有什么区别？

15. java 中 IO 流分为几种？

16. BIO、NIO、AIO 有什么区别？

17.Files的常用方法都有哪些？

## 二、容器

18. java 容器都有哪些？

19.Collection 和 Collections 有什么区别？

20.List、Set、Map 之间的区别是什么？

21.HashMap 和 Hashtable 有什么区别？

22.如何决定使用 HashMap 还是 TreeMap？

23.说一下 HashMap 的实现原理？

24.说一下 HashSet 的实现原理？

25.ArrayList 和 LinkedList 的区别是什么？

26.如何实现数组和 List 之间的转换？

27.ArrayList 和 Vector 的区别是什么？

28.Array 和 ArrayList 有何区别？

29.在 Queue 中 poll()和 remove()有什么区别？

30.哪些集合类是线程安全的？

31.迭代器 Iterator 是什么？

32.Iterator 怎么使用？有什么特点？

33.Iterator 和 ListIterator 有什么区别？

34.怎么确保一个集合不能被修改？

## 三、多线程

35.并行和并发有什么区别？

36.线程和进程的区别？

37.守护线程是什么？

38.创建线程有哪几种方式？

39.说一下 runnable 和 callable 有什么区别？

40.线程有哪些状态？

41.sleep() 和 wait() 有什么区别？

42.notify()和 notifyAll()有什么区别？

43.线程的 run()和 start()有什么区别？

44.创建线程池有哪几种方式？

45.线程池都有哪些状态？

46.线程池中 submit()和 execute()方法有什么区别？

47.在 java 程序中怎么保证多线程的运行安全？

48.多线程锁的升级原理是什么？

49.什么是死锁？

50.怎么防止死锁？

51.ThreadLocal 是什么？有哪些使用场景？

52.说一下 synchronized 底层实现原理？

53.synchronized 和 volatile 的区别是什么？

54.synchronized 和 Lock 有什么区别？

55.synchronized 和 ReentrantLock 区别是什么？

56.说一下 atomic 的原理？

## 四、设计模式

57.说一下你熟悉的设计模式？

58.简单工厂和抽象工厂有什么区别？

## 五、Spring/Spring MVC

59.为什么要使用 spring？

60.解释一下什么是 aop？

61.解释一下什么是 ioc？

62.spring 有哪些主要模块？

63.spring 常用的注入方式有哪些？

64.spring 中的 bean 是线程安全的吗？

65.spring 支持几种 bean 的作用域？

66.spring 自动装配 bean 有哪些方式？

67.spring 事务实现方式有哪些？

68.说一下 spring 的事务隔离？

69.说一下 spring mvc 运行流程？

70.spring mvc 有哪些组件？

71.@RequestMapping 的作用是什么？

72.@Autowired 的作用是什么？

## 六、Spring Boot/Spring Cloud

73.什么是 spring boot？

74.为什么要用 spring boot？

75.spring boot 核心配置文件是什么？

76.spring boot 配置文件有哪几种类型？它们有什么区别？

77.spring boot 有哪些方式可以实现热部署？

78.jpa 和 hibernate 有什么区别？

79.什么是 spring cloud？

80.spring cloud 断路器的作用是什么？

81.spring cloud 的核心组件有哪些？

## 七、Mybatis

82.mybatis 中 #{}和 ${}的区别是什么？

83.mybatis 有几种分页方式？

84.RowBounds 是一次性查询全部结果吗？为什么？

85.mybatis 逻辑分页和物理分页的区别是什么？

86.mybatis 是否支持延迟加载？延迟加载的原理是什么？

87.说一下 mybatis 的一级缓存和二级缓存？

88.mybatis 和 hibernate 的区别有哪些？

89.mybatis 有哪些执行器（Executor）？

90.mybatis 分页插件的实现原理是什么？

91.mybatis 如何编写一个自定义插件？

## 八、Kafka

92.kafka 可以脱离 zookeeper 单独使用吗？为什么？

93.kafka 有几种数据保留的策略？

94.kafka 同时设置了 7 天和 10G 清除数据，到第五天的时候消息达到了 10G，这个时候 kafka 将如何处理？

95.什么情况会导致 kafka 运行变慢？

96.使用 kafka 集群需要注意什么？

## 九、Zookeeper

97.zookeeper 是什么？

98.zookeeper 都有哪些功能？

99.zookeeper 有几种部署模式？

100.zookeeper 怎么保证主从节点的状态同步？

101.集群中为什么要有主节点？

102.集群中有 3 台服务器，其中一个节点宕机，这个时候 zookeeper 还可以使用吗？

103.说一下 zookeeper 的通知机制？

## 十、MySql

104.数据库的三范式是什么？

105.一张自增表里面总共有 7 条数据，删除了最后 2 条数据，重启 mysql 数据库，又插入了一条数据，此时 id 是几？

106.如何获取当前数据库版本？

107.说一下 ACID 是什么？

108.char 和 varchar 的区别是什么？

109.float 和 double 的区别是什么？

110.mysql 的内连接、左连接、右连接有什么区别？

111.mysql 索引是怎么实现的？

112.怎么验证 mysql 的索引是否满足需求？

113.说一下数据库的事务隔离？

114.说一下 mysql 常用的引擎？

115.说一下 mysql 的行锁和表锁？

116.说一下乐观锁和悲观锁？

117.mysql 问题排查都有哪些手段？

118.如何做 mysql 的性能优化？

## 十一、Redis

119.redis 是什么？都有哪些使用场景？

120.redis 有哪些功能？

121.redis 和 memecache 有什么区别？

122.redis 为什么是单线程的？

123.什么是缓存穿透？怎么解决？

124.redis 支持的数据类型有哪些？

125.redis 支持的 java 客户端都有哪些？

126.jedis 和 redisson 有哪些区别？

127.怎么保证缓存和数据库数据的一致性？

128.redis 持久化有几种方式？

129.redis 怎么实现分布式锁？

130.redis 分布式锁有什么缺陷？

131.redis 如何做内存优化？

132.redis 淘汰策略有哪些？

133.redis 常见的性能问题有哪些？该如何解决？

**十二、JVM**

134.说一下 jvm 的主要组成部分？及其作用？

135.说一下 jvm 运行时数据区？

136.队列和栈是什么？有什么区别？

137.什么是双亲委派模型？

138.说一下类加载的执行过程？

139.怎么判断对象是否可以被回收？

140.java 中都有哪些引用类型？

141.说一下 jvm 有哪些垃圾回收算法？

142.详细介绍一下 CMS 垃圾回收器？

143.新生代垃圾回收器和老生代垃圾回收器都有哪些？有什么区别？

144.简述分代垃圾回收器是怎么工作的？

145.说一下 jvm 调优的工具？

146.常用的 jvm 调优的参数都有哪些？
