

作者：Java浮世绘  
链接：[https://zhuanlan.zhihu.com/p/165265682](https://zhuanlan.zhihu.com/p/165265682)  
来源：知乎  
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。



- JAVA并发知识库
- JAVA线程实现/创建方式
- 4种线程池
- 线程生命周期(状态)
- 终止线程4种方式
- sleep与wait 区别
- start与run区别
- JAVA后台线程
- JAVA锁
- 线程基本方法
- 线程上下文切换
- 同步锁与死锁
- 线程池原理
- JAVA阻塞队列原理
- CyclicBarrier、CountDownLatch、Semaphore的用法
- volatile关键字的作用（变量可见性、禁止重排序）
- 如何在两个线程之间共享数据
- ThreadLocal作用（线程本地存储）
- synchronized和ReentrantLock的区别
- ConcurrentHashMap并发
- Java中用到的线程调度
- 进程调度算法
- 什么是CAS（比较并交换-乐观锁机制-锁自旋）
- 什么是 AQS（抽象的队列同步器）



- 设计原则
- 工厂方法模式
- 抽象工厂模式
- 单例模式
- 建造者模式
- 原型模式
- 适配器模式
- 装饰器模式
- 代理模式
- 外观模式
- 桥接模式
- 组合模式
- 享元模式
- 策略模式
- 模板方法模式
- 观察者模式
- 迭代子模式
- 责任链模式
- 命令模式
- 备忘录模式



- Spring 特点
- 轻量级
- 控制反转
- 面向切面
- 容器
- 框架集合
- Spring 核心组件
- Spring 常用模块
- Spring 主要包
- Spring 常用注解
- Spring IOC原理
- Spring APO原理
- Spring MVC原理
- Spring Boot原理
- JPA原理
- Mybatis缓存
- Tomcat架构




- 服务注册发现
- 客户端注册（zookeeper）
- 第三方注册（独立的服务Registrar）
- 客户端发现
- 服务端发现
- Consul
- Eureka
- SmartStack
- Etcd
- API 网关
- 请求转发
- 响应合并
- 协议转换
- 数据转换
- 安全认证
- 配置中心
- zookeeper配置中心
- 配置中心数据分类
- 事件调度（kafka）
- 服务跟踪（starter-sleuth）
- 服务熔断（Hystrix）
- Hystrix断路器机制
- API管理



- 四层负载均衡 vs 七层负载均衡
- 负载均衡算法/策略
- LVS
- Keepalive
- Nginx反向代理负载均衡
- HAProxy



- 接口继承关系和实现
- List
- ArrayList（数组）
- Vector（数组实现、线程同步）
- LinkList（链表）
- Set
- HashSet（Hash表）
- TreeSet（二叉树）
- LinkHashSet（HashSet+LinkedHashMap）
- Map
- HashMap（数组+链表+红黑树）
- JAVA7实现
- JAVA8实现
- ConcurrentHashMap
- Segment段
- 线程安全（Segment 继承 ReentrantLock 加锁）
- 并行度（默认16）
- HashTable（线程安全）
- TreeMap（可排序）
- LinkHashMap（记录插入顺序）



## JVM

![](https://pic3.zhimg.com/v2-1672fc6f9ecfbba146d0f505994a96a7_b.jpg)

- 线程
- JVM内存区域
- JVM运行时内存
- 垃圾回收与算法
- JAVA 四种引用类型
- GC分代收集算法 VS 分区收集算法
- GC垃圾收集器
- JAVA IO/NIO
- JVM 类加载机制

- JAVA异常分类及处理
- 异常分类
- 异常的处理方式
- Throw和throws的区别
- JAVA反射
- 动态语言
- 反射机制概念 （运行状态中知道类所有的属性和方法）
- Java反射API
- 反射使用步骤（获取Class对象、调用对象方法）
- 获取Class对象的3种方法
- 创建对象的两种方法
- JAVA注解
- JAVA内部类
- JAVA泛型
- JAVA序列化(创建可复用的Java对象)
- JAVA复制



- Netty 原理
- Netty 高性能
- 多路复用通讯方式
- 异步通讯NIO
- 零拷贝（DIRECT BUFFERS使用堆外直接内存）
- 内存池（基于内存池的缓冲区重用机制）
- 高效的Reactor线程模型
- 无锁设计、线程绑定
- 高性能的序列化框架
- Netty RPC实现
- 关键技术
- 核心流程
- 消息编解码
- 通讯过程
- RMI实现方式
- 实现步骤
- Protoclol Buffer
- Thrift



- 缓存雪崩
- 缓存穿透
- 缓存预热
- 缓存更新
- 缓存降级

- 网络7层架构
- TCP/IP原理
- 网络访问层(Network Access Layer)
- 网络层(Internet Layer)
- 传输层(Tramsport Layer-TCP/UDP)
- 应用层(Application Layer)
- TCP三次握手/四次挥手
- HTTP原理
- 传输流程
- HTTP状态
- HTTPS
- CDN 原理
- 分发服务系统
- 负载均衡系统
- 管理系统



- Slf4j
- Log4j
- LogBack
- Logback优点
- ELK

- Zookeeper概念
- Zookeeper角色
- Leader
- Follower
- Observer
- ZAB协议
- 事务编号 Zxid（事务请求计数器+ epoch）
- epoch
- Zab协议有两种模式-恢复模式（选主）、广播模式（同步）
- ZAB协议4阶段
- Leader election（选举阶段-选出准Leader）
- ZAB协议JAVA实现（FLE-发现阶段和同步合并为 Recovery Phase（恢复阶段））
- 投票机制
- Zookeeper工作原理（原子广播）
- Znode有四种形式的目录节点



## Kafka

![](https://pic3.zhimg.com/v2-13f60984712a26ce237687ba3fac5e79_b.jpg)

- Kafka概念
- Kafka数据存储设计
- partition的数据文件（offset，MessageSize，data）
- 数据文件分段segment（顺序读写、分段命令、二分查找）
- 数据文件索引（分段索引、稀疏存储）
- 生产者设计
- 负载均衡（partition会均衡分布到不同broker上）
- 批量发送
- 压缩（GZIP或Snappy）
- 消费者设计
- Consumer Group

## RabbitMQ

![](https://picb.zhimg.com/v2-a31ab5b10d55459527be87a500ccfc5a_b.jpg)

- RabbitMQ概念
- RabbitMQ架构
- Exchange 类型



作者：Java浮世绘  
链接：https://zhuanlan.zhihu.com/p/165265682  
来源：知乎  
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。  

## Hbase

![](https://pic3.zhimg.com/v2-3e3edb8eef656f46604b24ee54f04ca6_b.jpg)

- Hbase概念
- 列式存储
- Hbase核心概念
- Hbase核心架构
- Hbase的写逻辑
- HBase vs Cassandra
- MongoDB
- MongoDB概念
- MongoDB特点

## Cassandra

![](https://pic1.zhimg.com/v2-14ef6ca644ff27851a6f7bd491a43cb5_b.jpg)

- Cassandra概念
- 数据模型
- Cassandra一致Hash和虚拟节点
- Gossip协议
- 数据复制
- 数据写请求和协调者
- 数据读请求和后台修复
- 数据存储（CommitLog、MemTable、SSTable）
- 二级索引（对要索引的value摘要，生成RowKey）
- 数据读写

## 数据库

![](https://pic3.zhimg.com/v2-85dd80b0ad5b3981d07979b590394b5d_b.jpg)

- 存储引擎
- 索引
- 数据库三范式
- 数据库是事务
- 存储过程(特定功能的SQL 语句集)
- 触发器(一段能自动执行的程序)
- 数据库并发策略
- 数据库锁
- 基于Redis分布式锁
- 分区分表
- 两阶段提交协议
- 三阶段提交协议
- 柔性事务
- CAP

## 一致性算法

![](https://picb.zhimg.com/v2-7d0af78cd6c3b3a8ccaaf779a92af7e3_b.jpg)

- Paxos
- Zab
- Raft
- NWR
- Gossip
- 一致性Hash
- 一致性Hash特性
- 一致性Hash原理

## JAVA算法

![](https://picb.zhimg.com/v2-11c9fe10a80a5bc792f0d619b4eb90ef_b.jpg)

- 二分查找
- 冒泡排序算法
- 插入排序算法
- 快速排序算法
- 希尔排序算法
- 归并排序算法
- 桶排序算法
- 基数排序算法
- 剪枝算法
- 回溯算法
- 最短路径算法
- 最大子数组算法
- 最长公共子序算法
- 最小生成树算法

## 数据结构

![](https://pic3.zhimg.com/v2-d28329e2621765c2abdd3bc0d2ef9f30_b.jpg)

- 栈（stack）
- 队列（queue）
- 链表（Link）
- 散列表（Hash Table）
- 排序二叉树
- 红黑树
- B-TREE
- 位图

## 加密算法

![](https://picb.zhimg.com/v2-ca173ad26d1a1d94a2ce0d45175520f2_b.jpg)

- AES
- RSA
- CRC
- MD5

## Hadoop

![](https://pic2.zhimg.com/v2-838c5f8ee50cae98326f04963d577868_b.jpg)

- Hadoop概念
- HDFS
- Client
- NameNode
- Secondary NameNode
- DataNode
- MapReduce
- JobTracker
- TaskTracker
- Task
- Reduce Task 执行过程
- Hadoop MapReduce 作业的生命周期
- 作业提交与初始化
- 任务调度与监控。
- 任务运行环境准备
- 任务执行
- 作业完成

## Spark

![](https://picb.zhimg.com/v2-f362ca86bd99b56edfddf23ef0eb3c0d_b.jpg)

- Spark概念
- 核心架构
- 核心组件
- SPARK编程模型
- SPARK计算模型
- SPARK运行流程
- SPARK RDD流程
- SPARK RDD

## Storm

![](https://pic2.zhimg.com/v2-aabbaac5993ee58c510d18bc0d896a6a_b.jpg)

- Storm概念
- 集群架构
- Nimbus（master-代码分发给Supervisor）
- Supervisor（slave-管理Worker进程的启动和终止）
- Worker（具体处理组件逻辑的进程）
- Task
- ZooKeeper
- 编程模型（spout->tuple->bolt）
- opology运行
- Storm Streaming Grouping
- ResourceManager
- NodeManager
- ApplicationMaster
- YARN运行流程

## 机器学习

![](https://pic4.zhimg.com/v2-b04fb3f550aa96b646c0b5738b3db8ec_b.jpg)

- 决策树
- 随机森林算法
- 逻辑回归
- SVM
- 朴素贝叶斯
- K 最近邻算法
- K 均值算法
- Adaboost 算法
- 神经网络
- 马尔可夫

## 云计算

![](https://picb.zhimg.com/v2-fa12d8d75a042718da0e2b90e26bbf2f_b.jpg)

- SaaS
- PaaS
- IaaS
- Docker
- Openstack
- Namespaces
- 进程(CLONE_NEWPID 实现的进程隔离)
- Libnetwork与网络隔离
- 资源隔离与CGroups
- 镜像与UnionFS
- 存储驱动
