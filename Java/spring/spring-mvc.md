#spring-mvc

对于一个web项目，最重要的就是Mvc相关的控制，SpringBoot通过**WebMvcAutoConfiguration**来完成与Mvc有关的自动配置。如果希望完全接管WebMvc自动配置，可以在项目中创建一个注解了**@EnableWebMvc**的配置类

此时debug模式运行项目，会看到**WebMvcAutoConfiguration**没有被自动配置，说明我们自己定义的`MvcConfig`已经完全接管了默认的自动配置，这是因为**WebMvcAutoConfiguration**有一个条件注解:

```
@ConditionalOnMissingBean({WebMvcConfigurationSupport.class})
```



而我们本例中`MvcConfig`就是WebMvcConfigurationSupport的实现类，同时加入**@EnableWebMvc**注解也会导入一个WebMvcConfigurationSupport的实现类：DelegatingWebMvcConfiguration
，所以`MvcConfig`继承WebMvcConfigurationSupport不是必须的，但是可以方便我们编码。

如果希望可以继续使用**WebMvcAutoConfiguration**的自动配置，而只是需要修改或者增加MVC中的某些配置时，我们可以创建一个配置类，并继承于抽象类**WebMvcConfigurerAdapter**，我们可以通过实现抽象类的方法来注册自己的控制器。

http://hengyunabc.github.io/spring-boot-enablewebmvc-static-404/