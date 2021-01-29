# MySQL sql优化

> http://www.uml.org.cn/sjjm/201610184.asp
> 
> http://coolshell.cn/articles/1846.html

> 很多时候用 exists 代替 in 是一个好的选择：
> 
> select num from a where num in(select num from b)
> 
> 用下面的语句替换：
> 
> select num from a where exists(select 1 from b where num=a.num)
> 
> **如果查询的两个表大小相当，那么用in和exists差别不大**。 
> 
> 如果两个表中一个较小，一个是大表，则子查询表大的用exists，子查询表小的用in。
> 
> not in 和not exists如果查询语句使用了not in 那么内外表都进行全表扫描，没有用到索引；而not extsts 的子查询依然能用到表上的索引。**所以无论那个表大，用not exists都比not in要快**。

https://stackoverflow.com/questions/28759576/mysql-using-index-condition-vs-using-where-using-index

https://segmentfault.com/q/1010000004197413

http://hedengcheng.com/?p=577
