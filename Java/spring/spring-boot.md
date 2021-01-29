`spring-boot`插件自动应用[Dependency Management Plugin](https://github.com/spring-gradle-plugins/dependency-management-plugin/)

[Dependency Management Plugin](https://docs.spring.io/dependency-management-plugin/docs/current-SNAPSHOT/reference/html/)

[io.spring.dependency-management](https://plugins.gradle.org/plugin/io.spring.dependency-management)

声明的`spring-boot` Gradle插件的版本决定了bom导入的版本

> When you apply the [`io.spring.dependency-management`](https://github.com/spring-gradle-plugins/dependency-management-plugin) plugin, Spring Boot’s plugin will automatically [import the`spring-boot-dependencies` bom](https://docs.spring.io/spring-boot/docs/2.1.5.RELEASE/gradle-plugin/reference/html/#reacting-to-other-plugins-dependency-management) from the version of Spring Boot that you are using.

Spring Boot plugin将会从使用的Spring boot中自动加载spring-boot-dependency pom （[pom.xml](https://link.zhihu.com/?target=https%3A//github.com/spring-projects/spring-boot/blob/master/spring-boot-project/spring-boot-dependencies/pom.xml)），当声明的dependency在pom中被管理，则可以省略该dependency的version

```groovy
apply plugin: 'org.springframework.boot'
apply plugin: 'io.spring.dependency-management'

buildscript {
    ext {
      springBootVersion = '2.1.5.RELEASE'
      dependencyManagementVersion = '1.0.8.RELEASE'
    }
    repositories {
      mavenCentral()
    }
    dependencies {
      classpath("org.springframework.boot:spring-boot-gradle-plugin:${springBootVersion}")
      classpath("io.spring.gradle:dependency-management-plugin:${dependencyManagementVersion}")
    }
}

// 如果不使用spring boot plugin，那么可以使用以下方式指定版本
dependencyManagement {
        imports {
            mavenBom("org.springframework.boot:spring-boot-dependencies:${springBootVersion}")
        }
    }

dependencies {
  // 那么这里就会自动应用2.1.5.RELEASE
  compile("org.springframework.boot:spring-boot-starter-web") 
}
```

The *spring-boot-starter-parent* project is a special starter project – that provides default configurations for our application and a complete dependency tree to quickly build our *Spring Boot* project.

[spring-boot-starter-parent](https://github.com/spring-projects/spring-boot/tree/master/spring-boot-project/spring-boot-parent)

maven专用？里面就一个pom.xml

[spring-boot-dependencies](https://github.com/spring-projects/spring-boot/tree/v2.1.5.RELEASE/spring-boot-project/spring-boot-dependencies)

 根本在于这个项目，在其pom.xml文件中定义了各个依赖包的version，

```xml
<properties>
	<main.basedir>${basedir}/../..</main.basedir>
	<!-- Dependency versions -->
	<activemq.version>5.15.9</activemq.version>
	<antlr2.version>2.7.7</antlr2.version>
	<appengine-sdk.version>1.9.74</appengine-sdk.version>
	<artemis.version>2.6.4</artemis.version>
	<aspectj.version>1.9.4</aspectj.version>
	<assertj.version>3.11.1</assertj.version>
	<atomikos.version>4.0.6</atomikos.version>
	<bitronix.version>2.1.4</bitronix.version>
  ...
</properties>
<dependencyManagement>
		<dependencies>
			<!-- Spring Boot -->
			<dependency>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot</artifactId>
				<version>${revision}</version>
			</dependency>
			<dependency>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-test</artifactId>
				<version>${revision}</version>
			</dependency>
      ...
  </dependencies>
</dependencyManagement>
```

其中`revision`在[spring-boot项目根pom.xml](https://github.com/spring-projects/spring-boot/blob/v2.1.5.RELEASE/pom.xml)中定义的

>Spring Boot’s dependency management can be used in a project without applying Spring Boot’s plugin to that project. The `SpringBootPlugin` class provides a `BOM_COORDINATES` constant that can be used to import the bom without having to know its group ID, artifact ID, or version.

```groovy
plugins {
	id 'org.springframework.boot' version '2.1.5.RELEASE' apply false
}

apply plugin: 'io.spring.dependency-management'

dependencyManagement {
	imports {
		mavenBom org.springframework.boot.gradle.plugin.SpringBootPlugin.BOM_COORDINATES
	}
}
```

#### SpringBootServletInitializer

> This is an extension of *WebApplicationInitializer* which **runs a SpringApplication from a traditional WAR archive**deployed on a web container. This class binds *Servlet*, *Filter* and *ServletContextInitializer* beans from the application context to the server.

SpringBootServletInitializer主要起到web.xml的作用，（加载*filter, servlet…*）