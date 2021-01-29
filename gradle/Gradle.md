# Gradle

Gradle可以在没有安装Gradle的情况下使用，这时候就需要Gradle Wrapper了。Gradle Wrapper其实就是一个脚本文件，它会在没有安装Gradle的情况下为我们下载Gradle，之后我们就可以使用gradlew命令，像使用gradle一样来使用Gradle了。

使用gradle wrapper来创建一组Wrapper文件。Gradle官方建议我们在所有Gradle项目中都创建Wrapper文件，方便没有安装Gradle的用户使用。创建完毕之后，会发现我们的项目中多了如下一些文件：

- gradlew (Unix Shell 脚本) gradlew.bat (Windows批处理文件)
- gradle/wrapper/gradle-wrapper.jar (Wrapper JAR文件)
- gradle/wrapper/gradle-wrapper.properties (Wrapper属性文件)

gradle在执行脚本时，会优先执行buildscript代码块中的内容，然后才会执行剩余的build脚本。

https://docs.gradle.org/current/userguide/tutorial_using_tasks.html#sec:build_script_external_dependencies



使用plugin有两个步骤：

1. 解析（resolve）到指定plugin的代码位置；
2. 应用（apply）plugin，即调用plugin。如果是脚本plugin，就执行脚本，如果是二进制plugin，就执行Plugin.apply(T)

```groovy
// 旧的用法 （legacy method？）
// https://docs.gradle.org/current/userguide/plugins.html#sec:old_plugin_application
// 解析
buildscript {   
  repositories {     
    mavenCentral()   
  }   
  dependencies {     
    classpath("org.springframework.boot:spring-boot-gradle-plugin:${springBootVersion}")
  } 
}  
// 应用
apply plugin: 'org.springframework.boot'

// 新的用法 （plugins DSL）
// https://docs.gradle.org/current/userguide/plugins.html#sec:plugins_block
plugins {
    id 'org.springframework.boot' version '2.1.5.RELEASE'
}
```

[plugins DSL](https://docs.gradle.org/current/userguide/plugins.html#sec:plugins_block)

- Optimize the loading and reuse of plugin classes.
- Allow different plugins to use different versions of dependencies.
- Provide editors detailed information about the potential properties and values in the buildscript for editing assistance.



#### implementation

