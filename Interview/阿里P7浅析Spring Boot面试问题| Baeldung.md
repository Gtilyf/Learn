# 阿里P7浅析Spring Boot面试问题| Baeldung

Spring Boot一直是Spring生态系统的关键参与者。该项目通过其自动配置功能使我们的生活更加轻松。在本教程中，我们将介绍在求职面试中可能出现的一些与Spring Boot相关的最常见问题。

## Spring和Spring Boot有什么区别？

Spring Framework提供了多种功能，使Web应用程序的开发更加容易。这些功能包括依赖注入，数据绑定，面向方面的编程，数据访问等等。

多年来，Spring变得越来越复杂，这种应用程序所需的配置量可能会令人生畏。这就是Spring Boot派上用场的地方 - 它使配置Spring应用程序变得轻而易举。

从本质上讲，虽然Spring是不受欢迎的，但Spring Boot对平台和库有了自己的看法，让我们快速入门。

以下是Spring Boot带来的两个最重要的好处：

- 根据在类路径中找到的工件自动配置应用程序
- 提供生产中应用程序通用的非功能性功能，例如安全性或健康检查

更多SpringBoot教程

**我们如何使用Maven设置Spring Boot应用程序？**

我们可以像在任何其他库中一样在Maven项目中包含Spring Boot。但是，最好的方法是从spring-boot-starter-parent项目继承并声明对Spring Boot启动器的依赖。这样做可以让我们的项目重用Spring Boot的默认设置。

继承spring-boot-starter-parent项目非常简单 - 我们只需要在pom.xml中指定一个父元素：

```text
<parent> <groupId>org.springframework.boot</groupId> <artifactId>spring-boot-starter-parent</artifactId> <version>2.1.1.RELEASE</version></parent>
```

我们可以在Maven Central找到最新版本的 spring-boot-starter-parent。

使用启动父项目很方便，但并不总是可行。例如，如果我们公司要求所有项目都从标准POM继承，我们就不能依赖Spring Boot的启动父级。

在这种情况下，我们仍然可以通过此POM元素获得依赖关系管理的好处：

```text
<dependencyManagement> <dependencies> <dependency> <groupId>org.springframework.boot</groupId> <artifactId>spring-boot-dependencies</artifactId> <version>2.1.1.RELEASE</version> <type>pom</type> <scope>import</scope> </dependency> </dependencies></dependencyManagement>
```

**有什么Spring Boot启动器可供选择吗？**

依赖管理是任何项目的关键方面。当项目足够复杂时，管理依赖项可能会变成一场噩梦，因为涉及的工件太多了。

这是Spring Boot入门者派上用场的地方。每个入门者都可以作为我们所需的所有Spring技术的一站式服务。然后，以一致的方式传递和管理其他所需的依赖关系。

所有启动器都在org.springframework.boot组下，其名称以spring-boot-starter-开头 。这种命名模式使您可以轻松找到启动器，尤其是在使用支持按名称搜索依赖关系的IDE时。

在撰写本文时，我们有超过50个启动器。最常用的是：

- spring-boot-starter： 核心启动器，包括自动配置支持，日志记录和YAML
- spring-boot-starter-aop： 使用Spring AOP和AspectJ进行面向方面编程的启动器
- spring-boot-starter-data-jpa： 使用Spring Data JPA和Hibernate的启动器
- spring-boot-starter-jdbc： 用于将JDBC与HikariCP连接池一起使用的启动器
- spring-boot-starter-security： 使用Spring Security的启动器
- spring-boot-starter-test： 用于测试Spring Boot应用程序的启动器
- spring-boot-starter-web： 用于构建Web的入门者，包括使用Spring MVC的RESTful应用程序

有关启动器的完整列表，请参阅此存储库

**如何禁用特定的自动配置？**

如果我们要禁用特定的自动配置，我们可以使用@EnableAutoConfiguration批注的exclude属性来指示它

```text
// other annotations@EnableAutoConfiguration(exclude = DataSourceAutoConfiguration.class)public class MyConfiguration { }
```

如果我们使用@SpringBootApplication批注启用自动配置- 它具有@EnableAutoConfiguration作为元注释 - 我们可以使用相同名称的属性禁用自动配置：

```text
// other annotations@SpringBootApplication(exclude = DataSourceAutoConfiguration.class)public class MyConfiguration { }
```

我们还可以使用spring.autoconfigure.exclude环境属性禁用自动配置。application.properties文件中的此设置与以前相同：

```text
spring.autoconfigure.exclude=org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration
```

**如何注册自定义自动配置？**

要注册自动配置类，我们必须在META-INF / spring.factories文件中的EnableAutoConfiguration键下列出其完全限定名称：

```text
org.springframework.boot.autoconfigure.EnableAutoConfiguration=com.baeldung.autoconfigure.CustomAutoConfiguration
```

如果我们使用Maven构建一个项目，那么该文件应放在resources / META-INF目录中，该目录将在程序打包阶段找到该文件。

**如何告诉自动配置在bean已经存在情况下退回？**

要指示自动配置类在bean已经存在时退出，我们可以使用 @ConditionalOnMissingBean批注。此注释的最显着属性是：

- value：要检查的bean类型
- name：要检查的bean的名称

放置在使用@Bean装饰的方法上时，目标类型默认为方法的返回类型：

```text
@Configurationpublic class CustomConfiguration { @Bean @ConditionalOnMissingBean public CustomService service() { ... }}
```

**如何将Spring Boot Web应用程序部署为JAR和WAR文件？**

传统上，我们将Web应用程序打包为WAR文件，然后将其部署到外部服务器中。这样做可以让我们在同一台服务器上安排多个应用程序。在CPU和内存稀缺的时候，这是节省资源的好方法。

但事情发生了变化。计算机硬件现在相当便宜，而且注意力转向服务器配置。在部署期间配置服务器的一个小错误可能会导致灾难性后果。

Spring通过提供一个插件即spring-boot-maven-plugin来解决这个问题，将Web应用程序打包为可执行的JAR。要包含此插件，只需向pom.xml添加一个插件元素：

```text
<plugin> <groupId>org.springframework.boot</groupId> <artifactId>spring-boot-maven-plugin</artifactId></plugin>
```

有了这个插件，我们将在执行打包阶段后生成一个胖JAR 。此JAR包含所有必需的依赖项，包括嵌入式服务器。因此，我们不再需要担心配置外部服务器。

然后我们就像普通的可执行JAR一样运行应用程序。

请注意，必须将pom.xml文件中的packaging元素设置为 jar 才能构建JAR文件：

```text
<packaging>jar</packaging>
```

执行Maven 打包阶段后，我们将拥有一个可部署的WAR文件。

**如何将Spring Boot用于命令行应用程序？**

与任何其他Java程序一样，Spring Boot命令行应用程序必须具有 main方法。此方法用作入口点，它调用SpringApplication＃run方法来引导应用程序：

```text
@SpringBootApplicationpublic class MyApplication { public static void main(String[] args) { SpringApplication.run(MyApplication.class); // other statements }}
```

然后SpringApplication类启动一个Spring容器并自动配置bean。

请注意，我们必须将配置类传递给run方法才能用作主要配置源。按照惯例，这个参数是入门类本身。

在调用run方法之后，我们可以像在常规程序中那样执行其他语句。

**有哪些可能的外部配置源？**

Spring Boot支持外部配置，允许我们在各种环境中运行相同的应用程序。我们可以使用属性文件，YAML文件，环境变量，系统属性和命令行选项参数来指定配置属性。

然后，我们可以访问使用这些属性@Value注释，经由绑定对象 的@ConfigurationProperties注释，或环境抽象。

以下是最常见的外部配置来源：

- 命令行属性：命令行选项参数是以双连字符开头的程序参数，例如-server.port = 8080。Spring Boot将所有参数转换为属性，并将它们添加到环境属性集中。
- 应用程序属性：应用程序属性是从application.properties文件或其YAML对应文件加载的属性。默认情况下，Spring Boot会在当前目录，类路径根或其config子目录中搜索此文件。
- 特定于配置文件的属性：特定于配置文件的属性从application- {profile} .properties文件或其YAML对应文件加载。{profile}是指激活的Profile名称。这些文件与非特定属性文件位于相同位置，并且优先于非特定属性文件。

**Spring Boot支持轻松绑定是什么意思？**

Spring Boot中的轻松绑定适用于配置属性的类型安全绑定。

使用宽松绑定时，环境属性的键不需要与属性名称完全匹配。这样的环境属性可以用驼峰camelCase，kebab-case，snake_case或大写字母写成，单词用下划线分隔。

例如，如果具有@ConfigurationProperties批注的bean类中的属性名为myProp，则可以将其绑定到以下任何环境属性：myProp，my-prop，my_prop或MY_PROP。

**什么是Spring Boot DevTools？**

Spring Boot Developer Tools或DevTools是一组工具，使开发过程更容易。要包含这些开发时功能，我们只需要在pom.xml文件中添加依赖项：

```text
<dependency> <groupId>org.springframework.boot</groupId> <artifactId>spring-boot-devtools</artifactId></dependency>
```

在生产运行模块，Spring Boot devtools将自动禁用。默认情况下，重新打包存档也会排除此模块。因此，它不会给我们的最终产品带来任何开销。

默认情况下，DevTools应用适合开发环境的属性。这些属性禁用模板缓存，为Web组启用调试日志记录，等等。因此，我们拥有这种合理的开发时配置，而无需设置任何属性。

只要类路径上的文件发生更改，使用DevTools的应用程序就会重新启动。这是开发中非常有用的功能，因为它可以快速反馈修改。

默认情况下，静态资源（包括视图模板）不会启动重新启动。相反，资源更改会触发浏览器刷新。请注意，只有在浏览器中安装LiveReload扩展以与DevTools包含的嵌入式LiveReload服务器进行交互时，才会发生这种情况。

Idea中要通过运行配置进行专门配置。

**如何编写集成测试？**

在为Spring应用程序运行集成测试时，我们必须有一个ApplicationContext。

为了让我们的生活更轻松，Spring Boot为测试提供了一个特殊的注释 - @SpringBootTest。此批注从其classes属性指示的配置类创建ApplicationContext。

如果未设置classes属性，Spring Boot将搜索主配置类。搜索从包含测试的包开始，直到找到使用@SpringBootApplication或@SpringBootConfiguration注释的类。

请注意，如果我们使用JUnit 4，我们必须使用@RunWith（SpringRunner.class）修饰测试类。

**什么是Spring Boot Actuator**

从本质上讲，Actuator通过支持生产就绪功能，将Spring Boot应用程序变为现实。这些功能使我们能够在生产中运行时监控和管理应用程序。

将Spring Boot Actuator集成到一个项目中非常简单。我们需要做的就是在pom.xml文件中包含 spring-boot-starter-actuator starter ：

```text
<dependency> <groupId>org.springframework.boot</groupId> <artifactId>spring-boot-starter-actuator</artifactId></dependency>
```

Spring Boot Actuator可以使用HTTP或JMX端点公开操作信息。但是，大多数应用程序都使用HTTP，其中端点的标识和/执行器前缀形成URL路径。

以下是Actuator提供的一些最常见的内置端点：

- auditevents： 公开审计事件信息
- env： 公开环境属性
- health： 显示应用程序运行状况信息
- httptrace： 显示HTTP跟踪信息
- info： 显示任意应用程序信息
- metrics： 显示指标信息
- loggers： 显示和修改应用程序中记录器的配置
- mappings： 显示所有@RequestMapping路径的列表
- scheduledtasks： 显示应用程序中的计划任务
- threaddump： 执行线程转储
