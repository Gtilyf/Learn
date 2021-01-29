# a

## BTA 常问的 Java基础39道常见面试题

1.八种基本数据类型的大小，以及他们的封装类

2.引用数据类型

3.Switch能否用string做参数

4.equals与==的区别

5.自动装箱，常量池

6.Object有哪些公用方法

7.Java的四种引用，强弱软虚，用到的场景

8.Hashcode的作用

9.HashMap的hashcode的作用

10.为什么重载hashCode方法？

11.ArrayList、LinkedList、Vector的区别

12.String、StringBuffer与StringBuilder的区别

13.Map、Set、List、Queue、Stack的特点与用法

14.HashMap和HashTable的区别

15.JDK7与JDK8中HashMap的实现

16.HashMap和ConcurrentHashMap的区别，HashMap的底层源码

17.ConcurrentHashMap能完全替代HashTable吗

18.为什么HashMap是线程不安全的

19.如何线程安全的使用HashMap

20.多并发情况下HashMap是否还会产生死循环

21.TreeMap、HashMap、LindedHashMap的区别

22.Collection包结构，与Collections的区别

23.try?catch?finally，try里有return，finally还执行么

24.Excption与Error包结构，OOM你遇到过哪些情况，SOF你遇到过哪些情况

25.Java(OOP)面向对象的三个特征与含义

26.Override和Overload的含义去区别

27.Interface与abstract类的区别

28.Static?class?与non?static?class的区别

29.foreach与正常for循环效率对比

30.Java?IO与NIO

31.java反射的作用于原理

32.泛型常用特点

33.解析XML的几种方式的原理与特点：DOM、SAX

34.Java1.7与1.8,1.9,10 新特性

35.设计模式：单例、工厂、适配器、责任链、观察者等等

36.JNI的使用

37.AOP是什么

38.OOP是什么

39.AOP与OOP的区别

------

## Java 多线程面试题

1、多线程有什么用？

2、创建线程的方式

3、start()方法和run()方法的区别

4、Runnable接口和Callable接口的区别

5、CyclicBarrier和CountDownLatch的区别

6、volatile关键字的作用

7、什么是线程安全

8、Java中如何获取到线程dump文件

9、一个线程如果出现了运行时异常会怎么样

10、如何在两个线程之间共享数据

11、sleep方法和wait方法有什么区别

12、生产者消费者模型的作用是什么

13、ThreadLocal有什么用

14、为什么wait()方法和notify()/notifyAll()方法要在同步块中被调用

15、wait()方法和notify()/notifyAll()方法在放弃对象监视器时有什么区别

16、为什么要使用线程池

17、怎么检测一个线程是否持有对象监视器

18、synchronized和ReentrantLock的区别

19、ConcurrentHashMap的并发度是什么

20、ReadWriteLock是什么

21、FutureTask是什么

22、Linux环境下如何查找哪个线程使用CPU最长

23、Java编程写一个会导致死锁的程序

24、怎么唤醒一个阻塞的线程

25、不可变对象对多线程有什么帮助

26、什么是多线程的上下文切换

27、如果你提交任务时，线程池队列已满，这时会发生什么

28、Java中用到的线程调度算法是什么

29、Thread.sleep(0)的作用是什么

30、什么是自旋

31、什么是Java内存模型

32、什么是CAS

33、什么是乐观锁和悲观锁

34、什么是AQS

35、单例模式的线程安全性

36、Semaphore有什么作用

37、Hashtable的size()方法中明明只有一条语句"return count"，为什么还要做同步？

38、线程类的构造方法、静态块是被哪个线程调用的

39、同步方法和同步块，哪个是更好的选择

40、高并发、任务执行时间短的业务怎样使用线程池？并发不高、任务执行时间长的业务怎样使用线程池？并发高、业务执行时间长的业务怎样使用线程池？

------

## 跳槽必备的100道 Java 面试题

**多线程、并发及线程的基础问题**

1）Java 中能创建 volatile 数组吗？

2）volatile 能使得一个非原子操作变成原子操作吗？

3）volatile 修饰符的有过什么实践？

4）volatile 类型变量提供什么保证？

5) 10 个线程和 2 个线程的同步代码，哪个更容易写？

6）你是如何调用 wait（）方法的？使用 if 块还是循环？为什么？

7）什么是多线程环境下的伪共享（false sharing）？

**有经验程序员的 Java 面试题**

8）什么是 Busy spin？我们为什么要使用它？

9）Java 中怎么获取一份线程 dump 文件？

10）Swing 是线程安全的？

11）什么是线程局部变量？

12）Java 中 sleep 方法和 wait 方法的区别？

13）什么是不可变对象（immutable object）？Java 中怎么创建一个不可变对象？

14）我们能创建一个包含可变对象的不可变对象吗？

15）Java 中应该使用什么数据类型来代表价格？

16）怎么将 byte 转换为 String？

17）Java 中怎样将 bytes 转换为 long 类型？

18）我们能将 int 强制转换为 byte 类型的变量吗？如果该值大于 byte 类型的范围，将会出现什么现象？

19）哪个类包含 clone 方法？是 Cloneable 还是 Object？

20）Java 中 ++ 操作符是线程安全的吗？

21）不是线程安全的操作。它涉及到多个指令，如读取变量值，增加，

22）a = a + b 与 a += b 的区别

23）我能在不进行强制转换的情况下将一个 double 值赋值给 long 类型的变量吗？

24）3*0.1 == 0.3 将会返回什么？true 还是 false？

25）int 和 Integer 哪个会占用更多的内存？

26）为什么 Java 中的 String 是不可变的（Immutable）？

27）我们能在 Switch 中使用 String 吗？

28）Java 中的构造器链是什么？

**JVM 底层 与 GC（Garbage Collection） 的面试问题**

29）64 位 JVM 中，int 的长度是多数？

30）Serial 与 Parallel GC之间的不同之处？

31）32 位和 64 位的 JVM，int 类型变量的长度是多数？

32）Java 中 WeakReference 与 SoftReference的区别？

33）WeakHashMap 是怎么工作的？

34）JVM 选项 -XX:+UseCompressedOops 有什么作用？为什么要使

35）怎样通过 Java 程序来判断 JVM 是 32 位 还是 64 位？

36）32 位 JVM 和 64 位 JVM 的最大堆内存分别是多数？

37）JRE、JDK、JVM 及 JIT 之间有什么不同？

**3 年工作经验的 Java 面试题**

38）解释 Java 堆空间及 GC？

39）你能保证 GC 执行吗？

40）怎么获取 Java 程序使用的内存？堆使用的百分比？

41）Java 中堆和栈有什么区别？

**关于内存的的面试问题和答案**

**Java 基本概念面试题**

42）“a==b”和”a.equals(b)”有什么区别？

43）a.hashCode() 有什么用？与 a.equals(b) 有什么关系？

44）final、finalize 和 finally 的不同之处？

45）Java 中的编译期常量是什么？使用它又什么风险？

**Java 集合框架的面试题**

46) List、Set、Map 和 Queue 之间的区别(答案)

47）poll() 方法和 remove() 方法的区别？

48）Java 中 LinkedHashMap 和 PriorityQueue 的区别是什么？

49）ArrayList 与 LinkedList 的不区别？

50）用哪两种方式来实现集合的排序？

51）Java 中怎么打印数组？

52）Java 中的 LinkedList 是单向链表还是双向链表？

53）Java 中的 TreeMap 是采用什么树实现的？(答案)

54) Hashtable 与 HashMap 有什么不同之处？

55）Java 中的 HashSet，内部是如何工作的？

56）写一段代码在遍历 ArrayList 时移除一个元素？

57）我们能自己写一个容器类，然后使用 for-each 循环码？

58）ArrayList 和 HashMap 的默认大小是多数？

59）有没有可能两个不相等的对象有有相同的 hashcode？

60）两个相同的对象会有不同的的 hash code 吗？

61）Java 中，Comparator 与 Comparable 有什么不同？

62）为什么在重写 equals 方法的时候需要重写 hashCode 方法？

Java IO 和 NIO 的面试题

63）Java 中怎么创建 ByteBuffer？

**Java 最佳实践的面试问题**

64）Java 中，编写多线程程序的时候你会遵循哪些最佳实践？

65）说出几点 Java 中使用 Collections 的最佳实践

66）说出 5 条 IO 的最佳实践(答案)

67）说出几条 Java 中方法重载的最佳实践？

**Date、Time 及 Calendar 的面试题**

68）在多线程环境下，SimpleDateFormat 是线程安全的吗？

**单元测试 JUnit 面试题**

69）如何测试静态方法？

70）Java 中如何将字符串转换为整数？

**关于 OOP 和设计模式的面试题**

71）接口是什么？为什么要使用接口而不是直接使用具体类？

72）Java 中，抽象类与接口之间有什么不同？

73）除了单例模式，你在生产环境中还用过什么设计模式？

74) 什么情况下会违反迪米特法则？为什么会有这个问题？

75）适配器模式是什么？什么时候使用？

76）什么是“依赖注入”和“控制反转”？为什么有人使用？

77）抽象类是什么？它与接口有什么区别？你为什么要使用过抽象类？

78）构造器注入和 setter 依赖注入，那种方式更好？

79）依赖注入和工程模式之间有什么不同？

80）适配器模式和装饰器模式有什么区别？

81）适配器模式和代理模式之前有什么不同？

82）什么是模板方法模式？

83）什么时候使用访问者模式？

84）什么时候使用组合模式？

85）继承和组合之间有什么不同？

86）描述 Java 中的重载和重写？

87）Java 中，嵌套公共静态类与顶级类有什么不同？

88) OOP 中的 组合、聚合和关联有什么区别？

89）给我一个符合开闭原则的设计模式的例子？

90）抽象工厂模式和原型模式之间的区别？

91）什么时候使用享元模式？

**Java 面试中其他各式各样的问题**

92）嵌套静态类与顶级类有什么区别？

93）你能写出一个正则表达式来判断一个字符串是否是一个数字吗？

94）Java 中，受检查异常 和 不受检查异常的区别？

95）Java 中，throw 和 throws 有什么区别

96）Java 中，Serializable 与 Externalizable 的区别？

97）Java 中，DOM 和 SAX 解析器有什么不同？

98）说出 JDK 1.7 中的三个新特性？

99）说出 5 个 JDK 1.8 引入的新特性？

100）Java 中，Maven 和 ANT 有什么区别？