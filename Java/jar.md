# jar

#### jar

http://www.jianshu.com/p/61cfa1347894

https://docs.oracle.com/javase/tutorial/deployment/jar/build.html

Java归档文件格式(Java Archive, JAR)能够将多个源码、资源等文件打包到一个归档文件中，jar是通过zip格式进行打包的。说白了就是一个压缩包，里面包含相关的class文件、resources文件，以及包含jar包信息的manifest文件；如果是可以直接执行的jar包，则manifest文件中必须包含Main-Class参数；jar包class只是供其他应用使用(import)，则涉及到[类加载](./class load.md)相关内容。

> Options:
>
> ​    -c  create new archive
>
> ​    -t  list table of contents for archive
>
> ​    -x  extract named (or all) files from archive
>
> ​    -u  update existing archive
>
> ​    -v  generate verbose output on standard output
>
> ​    -f  specify archive file name
>
> ​    -m  include manifest information from specified manifest file
>
> ​    -n  perform Pack200 normalization after creating a new archive
>
> ​    -e  specify application entry point for stand-alone application bundled into an executable jar file
>
> ​	(为捆绑到可执行 jar 文件的独立应用程序指定应用程序入口点)
>
> ​    -0  store only; use no ZIP compression
>
> ​    -P  preserve leading '/' (absolute path) and ".." (parent directory) components from file names
>
> ​	(保留文件名中的前导 '/' (绝对路径) 和 ".." (父目录) 组件)
>
> ​    -M  do not create a manifest file for the entries
>
> ​    -i  generate index information for the specified jar files
>
> ​    -C  change to the specified directory and include the following file
>
> ​	（更改为指定的目录并包含其中的文件(可以理解为首先cd到指定目录)）
>
> If any file is a directory then it is processed recursively.
>
> The manifest file name, the archive file name and the entry point name are
>
> specified in the same order as the 'm', 'f' and 'e' flags.
>
> Example 1: to archive two class files into an archive called classes.jar: 
>
> ​       `jar cvf classes.jar Foo.class Bar.class `
>
> Example 2: use an existing manifest file 'mymanifest' and archive all the files in the foo/ directory into 'classes.jar': 
>
> ​      ` jar cvfm classes.jar mymanifest -C foo/ .`

**生成jar包，会同时添加manifest文件**

```
jar -cvf hello.jar HelloJar.class
added manifest
adding: HelloJar.class(in = 443) (out= 308)(deflated 30%)
```

**指定应用程序入口（java -jar hello.jar）**

```
jar -cvfe hello.jar HelloJar HelloJar.class
```

**带package的class打包**

[java package相关](./类文件结构.md)

```
javac -d result com/dh/HelloJar.java
jar cvfe hello.jar com/dh/HelloJar com
jar cvfe hello.jar com/dh/huang/Hello -C bin . # 指定目录
```

**添加自定义清单信息到jar包**

```
jar -cvfm HelloWorld.jar manifest.txt HelloWorld.class 
```

**查看jar包内容**

```
jar -tf hello.jar
META-INF/
META-INF/MANIFEST.MF
HelloJar.class
```

**以文件列表的形式展示**

     jar -vtf hello.jar 
     0 Mon Apr 24 22:59:00 CST 2017 META-INF/
    68 Mon Apr 24 22:59:00 CST 2017 META-INF/MANIFEST.MF
    443 Mon Apr 24 22:51:48 CST 2017 HelloJar.class
**解压jar包（特定的文件或者整个jar包）**

```
jar -xf hello.jar META-INF/MANIFEST.MF 
jar -xf hello.jar 
```

**带package信息的class以及带上资源文件**

```
jar cvfe hello.jar com/dh/HelloJar com resouces 
added manifest
adding: com/(in = 0) (out= 0)(stored 0%)
adding: com/dh/(in = 0) (out= 0)(stored 0%)
adding: com/dh/HelloJar.class(in = 428) (out= 298)(deflated 30%)
adding: com/dh/HelloJar.java(in = 126) (out= 112)(deflated 11%)
adding: resouces/(in = 0) (out= 0)(stored 0%)
adding: resouces/resouces.jpg(in = 0) (out= 0)(stored 0%)

jar tf hello.jar                               
META-INF/
META-INF/MANIFEST.MF
com/
com/dh/
com/dh/HelloJar.class
com/dh/HelloJar.java
resouces/
resouces/resouces.jpg
```

**-C参数**

指定打包的文件目录，会把指定目录里的指定文件打包到jar包，会忽略其顶级目录

```
jar cf ImageAudio.jar -C images . -C audio .
META-INF/MANIFEST.MF
cross.gif
yahoo2.au
```

**MANIFEST.MF**

> When you create a JAR file, it automatically receives a default manifest file. There can be only one manifest file in an archive, and it always has the pathname
>
> ```
> META-INF/MANIFEST.MF
> ```

- Manifest-Version表示版本号，一般由IDE工具（如eclipse）自动生成
- Main-Class 是jar文件的主类，程序的入口
- Class-Path 指定需要的jar，多个jar必须要在一行上，多个jar之间以空格隔开，如果引用的jar在当前目录的子目录下，windows下使用\来分割，linux下用/分割
- 文件的冒号后面必须要空一个空格，否则会出错
- 文件的最后一行必须是一个回车换行符，否则也会出错
