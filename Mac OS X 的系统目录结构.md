# Mac OS X 的系统目录结构

#### Unix通用目录

```
/bin       		传统unix命令的存放目录，如ls，rm，mv等。 
/sbin      		传统unix管理类命令存放目录，如fdisk，ifconfig等等。 
/usr       		第三方程序安装目录，/usr/bin, /usr/sbin, /usr/lib，其中/usr/lib目录中存放了共享库（动态链接库）。
/usr/bin   		存放应用程序。
/usr/share 		存放共享数据。
/usr/lib   		存放不能直接运行的，却是许多程序运行所必需的一些函数库文件。
/usr/local 		存放软件升级包。
/usr/share/doc	系统说明文件存放目录。
/usr/share/man	程序说明文件存放目录 
/dev       		设备文件存放目录，如何代表硬盘的/dev/disk0。
/etc       		标准unix系统配置文件存放目录，如用户密码文件/etc/passwd。此目录实际为指向/private/etc的链接。 
/tmp       		临时文件存放目录，其权限为所有人任意读写。此目录实际为指向/private/tmp的链接。 
/var       		存放经常变化的文件，如日志文件。此目录实际为指向/private/var的链接。
```

#### Mac特有目录

```
/Applications        应用程序目录，默认所有的GUI应用程序都安装在这里
/Library             系统的数据文件、帮助文件、文档等等
/Network             网络节点存放目录
/System              只包含一个名为Library的目录，这个子目录中存放了系统的绝大部分组件，如各种framework，以及内核模块，字体文件等等。
/Users               存放用户的个人资料和配置。每个用户有自己的单独目录。
/Volumes             文件系统挂载点存放目录。 
/cores               内核转储文件存放目录。当一个进程崩溃时，如果系统允许则会产生转储文件。 
/private             里面的子目录存放了/tmp, /var, /etc等链接目录的目标目录。
```

