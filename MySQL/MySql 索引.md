# MySql 索引

> [MySQL索引原理及慢查询优化](http://tech.meituan.com/mysql-index.html)

#### 建立索引原则

1. 最左前缀匹配原则



#### explain

![](./explain.png)

[explain详解](http://www.cnblogs.com/xuanzhi201111/p/4175635.html)

[EXPLAIN Output Format](http://dev.mysql.com/doc/refman/5.7/en/explain-output.html)



#### 索引选择性

索引的选择性（Selectivity），是指不重复的索引值(也叫基数，Cardinality)与表记录数的比值：`Selectivity = count(distinct(c)) / count(1)`

