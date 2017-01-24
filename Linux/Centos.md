# Centos

#### chkconfig

> chkconfig命令主要用来更新（启动或停止）和查询系统服务的运行级信息。chkconfig不是立即自动禁止或激活一个服务，它只是简单的改变了符号连接。

- 常用命令：
  - chkconfig --list [name]：显示所有运行级系统服务的运行状态信息（on或off）。如果指定了name，那么只显示指定的服务在不同运行级的状态。
  - chkconfig --add name：增加一项新的服务。chkconfig确保每个运行级有一项启动(S)或者杀死(K)入口。如有缺少，则会从缺省的init脚本自动建立。
  - chkconfig --del name：删除服务，并把相关符号连接从/etc/rc[0-6].d删除。
  - chkconfig [--level levels] name：设置某一服务在指定的运行级是被启动，停止还是重置。
- level
  - 等级0表示：表示关机
  - 等级1表示：单用户模式
  - 等级2表示：无网络连接的多用户命令行模式
  - 等级3表示：有网络连接的多用户命令行模式
  - 等级4表示：不可用
  - 等级5表示：带图形界面的多用户模式
  - 等级6表示：重新启动

#### service

/etc/init.d下的脚本http://www.cnblogs.com/wangtao_20/p/3645690.html