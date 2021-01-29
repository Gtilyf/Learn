# Mysql面试知识点总结

[https://zhuanlan.zhihu.com/p/58698226?utm_source=qq&utm_medium=social&utm_oi=58097666097152](https://zhuanlan.zhihu.com/p/58698226?utm_source=qq&utm_medium=social&utm_oi=58097666097152)

**数据库设计三范式：**

1. 第一范式：数据库表的每一列都是不可分割的原子数据项，即列不可拆分。
2. 第二范式：建立在第一范式的基础上，要求数据库表中的每个实例或记录必须是可以唯一被区分的，即唯一标识。
3. 第三范式：建立在第二范式的基础上，任何非主属性不依赖与其他非主属性，即引用主键。

## 视图

视图是虚拟表，并不储存数据，只包含定义时的语句的动态数据。

```text
create view view_name as sql查询语句
```

## 存储过程

一条或多条sql语句集合，其优点为(浓缩：简单/安全/高性能)：

- 存储过程能实现较快的执行速度
- 存储过程允许标准组件是编程。
- 存储过程可以用流程控制语句编写，有很强的灵活性，可以完成复杂的判断和较复杂的运算。
- 存储过程可被作为一种安全机制来充分利用。
- 存储过程能够减少网络流量

```text
delimiter 分隔符create procedure|proc proc_name()begin    sql语句end 分隔符delimiter ；    --还原分隔符，为了不影响后面的语句的使用默认的分隔符是；但是为了能在整个存储过程中重用，因此一般需要自定义分隔符（除\外）show procedure status like ""; --查询存储过程，可以不适用like进行过滤drop procedure if exists；--删除存储过程
```

**存储过程和函数的区别?**

```text
相同点：存储过程和函数都是为了可重复的执行操作数据库的 sql 语句的集合。1）存储过程和函数都是一次编译，就会被缓存起来，下次使用就直接命中已经编译好的 sql 语句，不需要重复使用。减少网络交互，减少网络访问流量。不同点：标识符不同，函数的标识符是 function，存储过程是 proceduce。1）函数中有返回值，且必须有返回值，而过程没有返回值，但是可以通过设置参数类型（in,out)来实现多个参数或者返回值。2）存储函数使用 select 调用，存储过程需要使用 call 调用。3）select 语句可以在存储过程中调用，但是除了 select..into 之外的 select 语句都不能在函数中使用。4）通过 in out 参数，过程相关函数更加灵活，可以返回多个结果。
```

## 触发器

在对表数据进行变动的时候进行具体的操作，有六种，分别为增删改的前后操作。

```text
create trigger trigger_name ALTER|BEFORE select|update|deleteon 表for each rowtrigger_stmt
```

**重点：**

- 只有表才支持触发器，视图和临时表都不支持
- 触发器不支持更新和覆盖，修改必须先删除然后创建

## 分区表

分区表是将大表的数据分成称为分区的许多小的子集，常见分区类型：Range、List、Hash、Key

```text
查看是否支持分区表 show plugins 如果有partition就说明支持在创建表时字符集后增加 partition by 分区类型(字段) partitions 4;添加分区 alter table 表 add partition (partition p4 values less than(2018))
```

**交换分区对数据进行归档**

```text
条件：mysql>=5.7 结构相同 归档到的数据表一定要是非分区表 非临时表，不能有外键约束 归档引擎要是archive，可以是innodb，但归档引擎占用空间更小，但只能是查询操作删除分区：alter table 分区表 drop partition 分区名归档分区：alter table 分区表 exchange partition 分区名 with table 归档表
```

- RANGE 分区：基于属于一个给定连续区间的列值，把多行分配给分区。

```text
partition by RANGE(字段)( partition p0 VALUES LESS THAN(10000),...PARTITION p3 VALUES
```

LESS THAN MAXVALUE);不包括上限

- LIST 分区：类似于按 RANGE 分区，区别在于 LIST 分区是基于列值匹配一个离散值集合中的某个 值来进行选择。

```text
partition by list（字段）(partition p0 values in (x,x,x,x)...);
```

- HASH 分区：基于用户定义的表达式的返回值来进行选择的分区，该表达式使用将要插入到表中的 这些行的列值进行计算。这个函数可以包含MySQL 中有效的、产生非负整数值的任何表达式。

```text
partition by hash(字段) partitions 4(       PARTITION p0,       PARTITION p1,       PARTITION p2,       PARTITION p3);
```

![](https://pic1.zhimg.com/80/v2-345dfe80191becf7a74b3afaeec811c4_1440w.jpg)

- KEY 分区：类似于按 HASH 分区，区别在于 KEY 分区只支持计算一列或多列，且 MySQL 服务器提供其自身的哈希函数。必须有一列或多列包含整数值。

```text
partition by hash(字段) partitions 4(       PARTITION p0,       PARTITION p1,       PARTITION p2,       PARTITION p3);
```

## 日志

Mysql主要有四种日志文件：

```text
错误日志：记录启动，运行或者停止 mysql 时出现的问题；查询日志：记录所有msyql的活动二进制日志：记录更新过数据的所有语句缓慢查询日志：记录查询缓慢的任何查询
```

## Archive引擎

这是一个只用于数据插入和查询的引擎，其特点为：

1. 只能对数据进行插入和查询
2. 不支持索引
3. 不支持事务
4. 存储数据占用空间更小
