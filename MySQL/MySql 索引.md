# MySql 索引

> [MySQL索引原理及慢查询优化](http://tech.meituan.com/mysql-index.html)

#### 建立索引原则

1. 最左前缀匹配原则，mysql会一直向右匹配直到遇到范围查询(>、<、between、like)就停止匹配，比如a = 1 and b = 2 and c > 3 and d = 4 如果建立(a,b,c,d)顺序的索引，d是用不到索引的，如果建立(a,b,d,c)的索引则都可以用到；
2. 尽量选择区分度高的列作为索引，区分度的公式是count(distinct col)/count(*)，表示字段不重复的比例，比例越大我们扫描的记录数越少，唯一键的区分度是1；
3. 尽量的扩展索引，不要新建索引；比如表中已经有a的索引，现在要加(a,b)的索引，那么只需要修改原来的索引即可；


#### 索引选择性

索引的选择性（Selectivity），是指不重复的索引值(也叫基数，Cardinality)与表记录数的比值：`Selectivity = count(distinct(c)) / count(1)`

