# spring-security

```java
http.authorizeRequests()
        .antMatchers("/api/alive").permitAll()
        .antMatchers("/gateway/**").permitAll()
        .antMatchers("/**").access("hasAnyAuthority(\"我\")")
        .antMatchers("/").access("hasAnyAuthority(\"我\")")
        .anyRequest().authenticated()
        .and()
        .sessionManagement().sessionCreationPolicy(SessionCreationPolicy.STATELESS)
        .and()
        // 默认使用UsernamePasswordAuthenticationFilter进行用户名密码验证，且不可修改
        .formLogin()
        // 设置登陆表单页面地址，当登陆失败的时候，会重定向到这个页面
        // 即默认使用LoginUrlAuthenticationEntryPoint
        .loginPage("/account/ns/login#/page/login")
        // 登陆请求地址，AuthenticationProcessingFilter处理登陆请求的地址，AuthenticationProcessingFilter默认处理成功登陆请求后，就不会再继续doFilter
                 // AbstractAuthenticationProcessingFilter
              // .setRequiresAuthenticationRequestMatcher(
              //         createLoginProcessingUrlMatcher(loginProcessingUrl)
              // ); 
        .loginProcessingUrl("/wapi/authentication/login")
        .usernameParameter("username").passwordParameter("password")
        .and()
        .httpBasic()
        .and()
        .csrf().disable()
        .headers().disable();
```

security默认filter.order = `OrderedFilter.REQUEST_WRAPPER_FILTER_MAX_ORDER - 100;`，可以通过spring.security.filter.order进行配置，`SecurityFilterAutoConfiguration`



loginPage的作用：

```
FilterSecurityInterceptor中会检查Authentication，通过accessDecisionManager判断是否可访问，如果不允许访问，则会抛出AccessDeniedException，ExceptionTranslationFilter会catch该异常，如果isAnonymous，则sendStartAuthentication，调用authenticationEntryPoint.commence，如果配置的是LoginUrlAuthenticationEntryPoint，那么就会进行302到配置的登陆页面，ExceptionTranslationFilter中的authenticationEntryPoint即为配置的LoginUrlAuthenticationEntryPoint，如果isNotAnonymos或者isNotRememberMe（not fully authenticated），则会调用accessDeniedHandler
```

```
AuthenticationProcessingFilter中unsuccessfulAuthentication，会调用rememberMeServices.loginFail以及failureHandler.onAuthenticationFailure；
AuthenticationProcessingFilter中successfulAuthentication，会保存SecurityContext，会调用rememberMeServices.loginSuccess以及successHandler.onAuthenticationSuccess，并且会eventPublisher.publishEvent(new InteractiveAuthenticationSuccessEvent；
```

```
spring boot中会WebSecurityEnablerConfiguration自动启用EnableWebSecurity
```

```
RememberMeConfigurer.init中，会添加一个RememberMeAuthenticationProvider，会比较设置的key是否相等
```

```
WebSecurityConfigurerAdapter.init调用getHttp会先创建一个AuthenticationManager，只包含DaoAuthenticationProvider，并且这个provider可以根据Local转换error msg，这个会放到AuthenticationManagerBuilder中，配置为parentAuthenticationManager；
之后getHttp调用configure时会根据配置加载userdetailsservice时候，会默认加载DaoAuthenticationConfigurer，该configurer会默认使用DaoAuthenticationProvider
之后WebSecurityConfiguration.springSecurityFilterChain时，会再次
AnonymousConfigurer.init中会默认添加一个AnonymousAuthenticationProvider
RememberMeConfigurer.init中会默认添加一个RememberMeAuthenticationProvider
initializeUserDetailsBeanManagerConfigurer.InitializeUserDetailsManagerConfigurer.configure中会默认添加一个DaoAuthenticationProvider
以上就是springSecurity默认添加的3个AuthenticationProvider，最后会在AuthenticationManagerBuilder.performBuild中组装成ProviderManager
```

messages_zh_CN.properties中有对应错误的中文错误信息

```
显示配置HttpSecurity.userDetailsService的情况：
initializeUserDetailsBeanManagerConfigurer.InitializeUserDetailsManagerConfigurer.configure中会默认添加一个DaoAuthenticationProvider (1)
WebSecurityConfigurerAdapter.init调用getHttp会先创建一个AuthenticationManager，只包含DaoAuthenticationProvider，并且这个provider可以根据Local转换error msg，这个会放到AuthenticationManagerBuilder中，配置为parentAuthenticationManager；
之后getHttp调用configure时会根据配置加载userdetailsservice时候，会在AuthenticationManagerBuilder.userDetailsService创建一个新的DaoAuthenticationConfigurer
DaoAuthenticationConfigurer，该configurer会默认使用DaoAuthenticationProvider (2)，并在WebSecurityConfiguration.springSecurityFilterChain时配置到AuthenticationManagerBuilder中，
然后在HttpSecurity.beforeConfigure中创建ProviderManager，并配置到sharedObjects中
最后ProviderManager中会有3个provider（ano, rememberme, dao）以及一个parent，parent中包含一个provider(dao)

最后在AbstractAuthenticationFilterConfigurer.configure中将加载好的ProviderManager配置到AbstractAuthenticationProcessingFilter中

不显示配置HttpSecurity.userDetailsService的情况，以bean的形式注入：
initializeUserDetailsBeanManagerConfigurer.InitializeUserDetailsManagerConfigurer.configure中会默认添加一个DaoAuthenticationProvider (1)，此时会将userDetailsService注入到provider中
WebSecurityConfigurerAdapter.init调用getHttp会先创建一个AuthenticationManager，只包含DaoAuthenticationProvider，并且这个provider可以根据Local转换error msg，这个会放到AuthenticationManagerBuilder中，配置为parentAuthenticationManager；
然后在HttpSecurity.beforeConfigure中创建ProviderManager，并配置到sharedObjects中
最后ProviderManager中会有2个provider（ano, rememberme）以及一个parent，parent中包含一个provider(dao)
最后在AbstractAuthenticationFilterConfigurer.configure中将加载好的ProviderManager配置到AbstractAuthenticationProcessingFilter中

显示配置HttpSecurity.userDetailsService的情况，但不以bean的形式注入：
initializeUserDetailsBeanManagerConfigurer.InitializeUserDetailsManagerConfigurer.configure中会默认添加一个DaoAuthenticationProvider (1)，此时会将userDetailsService注入到provider中
WebSecurityConfigurerAdapter.init调用getHttp会先创建一个AuthenticationManager，只包含DaoAuthenticationProvider，并且这个provider可以根据Local转换error msg，这个会放到AuthenticationManagerBuilder中，配置为parentAuthenticationManager；
这里会默认使用InMemoryUserDetailsService
之后getHttp调用configure时会根据配置加载userdetailsservice时候，会在AuthenticationManagerBuilder.userDetailsService创建一个新的DaoAuthenticationConfigurer
DaoAuthenticationConfigurer，该configurer会默认使用DaoAuthenticationProvider (2)，并在WebSecurityConfiguration.springSecurityFilterChain时配置到AuthenticationManagerBuilder中，
然后在HttpSecurity.beforeConfigure中创建ProviderManager，并配置到sharedObjects中
最后ProviderManager中会有3个provider（ano, rememberme, dao - 配置的userdetailsservice）以及一个parent，parent中包含一个provider(dao - InMemoryUserDetailsService)

不显示配置HttpSecurity.userDetailsService的情况，也不以bean的形式注入：
initializeUserDetailsBeanManagerConfigurer.InitializeUserDetailsManagerConfigurer.configure中会默认添加一个DaoAuthenticationProvider (1)，此时会将userDetailsService注入到provider中
WebSecurityConfigurerAdapter.init调用getHttp会先创建一个AuthenticationManager，只包含DaoAuthenticationProvider，并且这个provider可以根据Local转换error msg，这个会放到AuthenticationManagerBuilder中，配置为parentAuthenticationManager；
这里会默认使用InMemoryUserDetailsService
然后在HttpSecurity.beforeConfigure中创建ProviderManager，并配置到sharedObjects中
最后ProviderManager中会有3个provider（ano, rememberme）以及一个parent，parent中包含一个provider(dao - InMemoryUserDetailsService)


如果以bean的形式注入自定义的AuthenticationProvider，那么就会在InitializeAuthenticationProviderBeanManagerConfigurer.InitializeUserDetailsManagerConfigurer.config中注入该bean到ProviderManager，并成为parent，那么在initializeUserDetailsBeanManagerConfigurer.InitializeUserDetailsManagerConfigurer.configure中就会检查到auth.isConfiged，就不会再添加一个DaoAuthenticationProvider
```

```
http.authorizeRequests()配置会注入一个filter: FilterSecurityInterceptor，详见AbstractInterceptUrlConfigurer
FilterSecurityInterceptor.dofilter中beforeInvocation调用accessDecisionManager.decide（AffirmativeBased.decide）判断是否满足permission要求
```
