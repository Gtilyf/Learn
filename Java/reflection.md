# Reflection

Java反射机制可以让我们在编译期(Compile Time)之外的运行期(Runtime)检查类，接口，变量以及方法的信息。反射还可以让我们在运行期实例化对象，调用方法。

#### method.invoke

通过添加`-XX:+TraceClassLoading` JVM参数，我们可以看到method.invoke的调用过程中class load情况：

```
[Loaded com.dh.reflect.MyReflect from file:/Users/dh.huang/Workbench/private/untitled/out/production/untitled/]
[Loaded sun.launcher.LauncherHelper$FXHelper from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded java.lang.Class$MethodArray from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded java.lang.Void from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded com.dh.reflect.MethodInvoke from file:/Users/dh.huang/Workbench/private/untitled/out/production/untitled/]
: hello
0-310546
: hello
1-41996
: hello
2-36763
: hello
3-33413
: hello
4-29722
: hello
5-27786
: hello
6-28337
: hello
7-27434
: hello
8-27212
: hello
9-27593
: hello
10-32117
: hello
11-38572
: hello
12-31952
: hello
13-27904
: hello
14-27556
[Loaded sun.reflect.ClassFileConstants from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.AccessorGenerator from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.MethodAccessorGenerator from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.ByteVectorFactory from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.ByteVector from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.ByteVectorImpl from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.ClassFileAssembler from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.UTF8 from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.Label from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.Label$PatchInfo from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded java.util.ArrayList$Itr from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.MethodAccessorGenerator$1 from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.ClassDefiner from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.ClassDefiner$1 from /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home/jre/lib/rt.jar]
[Loaded sun.reflect.GeneratedMethodAccessor1 from __JVM_DefineClass__]
: hello
15-4299035
: hello
16-48111
: hello
17-35524
```

在第15次调用的时候，很明显的发生了一些神奇的事情，其中`sun.reflect.GeneratedMethodAccessor1 `并不是从某个jar中load出来的，而是`from __JVM_DefineClass__`，通过`method.invoke`源码我们可以大致推断出这过程中都发生了什么：

```java
@CallerSensitive
public Object invoke(Object obj, Object... args) throws IllegalAccessException, IllegalArgumentException, InvocationTargetException {
  if (!override) {
    if (!Reflection.quickCheckMemberAccess(clazz, modifiers)) {
      Class<?> caller = Reflection.getCallerClass();
      checkAccess(caller, clazz, obj, modifiers);
    }
  }
  MethodAccessor ma = methodAccessor;             // read volatile
  if (ma == null) {
    ma = acquireMethodAccessor();
  }
  return ma.invoke(obj, args);
}
...
// NOTE that there is no synchronization used here. It is correct
// (though not efficient) to generate more than one MethodAccessor
// for a given Method. However, avoiding synchronization will
// probably make the implementation more scalable.
private MethodAccessor acquireMethodAccessor() {
  // First check to see if one has been created yet, and take it
  // if so
  MethodAccessor tmp = null;
  if (root != null) tmp = root.getMethodAccessor();
  if (tmp != null) {
    methodAccessor = tmp;
  } else {
    // Otherwise fabricate one and propagate it up to the root
    tmp = reflectionFactory.newMethodAccessor(this);
    setMethodAccessor(tmp);
  }

  return tmp;
}
```

`method.invoke`的真正调用是委托给了MethodAccessor，其中methodAccessor是通过reflectionFactory创建的，在研究reflectionFactory是怎么创建methodAccessor之前，`acquireMethodAccessor`方法的两个比较有意思的点也是值得研究一下的：

- **Method.root：**
  
  要理解root的作用，首先来看一个Method中很有意思的函数：
  
  ```java
  /**
   * Package-private routine (exposed to java.lang.Class via
   * ReflectAccess) which returns a copy of this Method. The copy's
   * "root" field points to this Method.
   */
  Method copy() {
    // This routine enables sharing of MethodAccessor objects
    // among Method objects which refer to the same underlying
    // method in the VM. (All of this contortion is only necessary
    // because of the "accessibility" bit in AccessibleObject,
    // which implicitly requires that new java.lang.reflect
    // objects be fabricated for each reflective call on Class
    // objects.)
    if (this.root != null)
      throw new IllegalArgumentException("Can not copy a non-root Method");
  
    Method res = new Method(clazz, name, parameterTypes, returnType,
                            exceptionTypes, modifiers, slot, signature,
                            annotations, parameterAnnotations, annotationDefault);
    res.root = this;
    // Might as well eagerly propagate this if already present
    res.methodAccessor = methodAccessor;
    return res;
  }
  ```
  
  copy函数的作用就是共享在虚拟机中最底层的method的MethodAccessor，我们通过`Class.getMethods`等方法得到的method，都是最底层method复制出来的：
  
  ```java
  // Class.java
  @CallerSensitive
  public Method[] getMethods() throws SecurityException {
    checkMemberAccess(Member.PUBLIC, Reflection.getCallerClass(), true);
    return copyMethods(privateGetPublicMethods());
  }
  ...
  private static Method[] copyMethods(Method[] arg) {
    Method[] out = new Method[arg.length];
    ReflectionFactory fact = getReflectionFactory();
    for (int i = 0; i < arg.length; i++) {
      out[i] = fact.copyMethod(arg[i]);
    }
    return out;
  }
  
  // ReflectAccess.java
  //
  // Copying routines, needed to quickly fabricate new Field,
  // Method, and Constructor objects from templates
  //
  public Method      copyMethod(Method arg) {
    return arg.copy();
  }
  ```
  
  那么通过这个机制我们大概可以理解这样一个概念：每个Java方法只有一个对应的Method对象（root），这个对象在每次通过反射获取Method的时候，通过新创建Method对象，将root包装起来返回给用户。
  
  **_为啥要这样做呢？？？To be continue…_**

- **no synchronization use:**
  
  `acquireMethodAccessor`方法是非线程安全的，意思就是说有可能会创建多个methodAccessor，给出的解释是：`avoiding synchronization will probably make the implementation more scalable`，可扩展性；
  
  **_为啥呢？？？To be continue…_**
  
  

**reflectionFactory.newMethodAccessor:**

```java
// ReflectionFactory.java
public MethodAccessor newMethodAccessor(Method var1) {
  checkInitted();
  // noInflation = false，通过-Dsun.reflect.noInflation=true设置
  if(noInflation && !ReflectUtil.isVMAnonymousClass(var1.getDeclaringClass())) {
    // bytecode accessor
    return (new MethodAccessorGenerator()).generateMethod(var1.getDeclaringClass(), var1.getName(), var1.getParameterTypes(), var1.getReturnType(), var1.getExceptionTypes(), var1.getModifiers());
  } else {
    // JNI accessor
    NativeMethodAccessorImpl var2 = new NativeMethodAccessorImpl(var1);
    DelegatingMethodAccessorImpl var3 = new DelegatingMethodAccessorImpl(var2);
    var2.setParent(var3);
    return var3;
  }
}
```

如果没有进行配置的情况下，`newMethodAccessor`返回的就是`DelegatingMethodAccessorImpl`：

```java
class DelegatingMethodAccessorImpl extends MethodAccessorImpl {
  private MethodAccessorImpl delegate;

  DelegatingMethodAccessorImpl(MethodAccessorImpl var1) {
    this.setDelegate(var1);
  }

  // 实际调用的是delegate.invoke，而delegate可以视情况而改变
  public Object invoke(Object var1, Object[] var2) throws IllegalArgumentException, InvocationTargetException {
    return this.delegate.invoke(var1, var2);
  }

  void setDelegate(MethodAccessorImpl var1) {
    this.delegate = var1;
  }
}
```

结合`DelegatingMethodAccessorImpl`以及`reflectionFactory.newMethodAccessor`的代码，可以知道`Method.invoke`最开始的实际调用者是`NativeMethodAccessorImpl`:

```java
class NativeMethodAccessorImpl extends MethodAccessorImpl {
  private final Method method;
  private DelegatingMethodAccessorImpl parent;
  private int numInvocations;

  NativeMethodAccessorImpl(Method var1) {
    this.method = var1;
  }

  public Object invoke(Object var1, Object[] var2) throws IllegalArgumentException, InvocationTargetException {
    // inflation机制
    // private static int ReflectionFactory.inflationThreshold = 15;
    if(++this.numInvocations > ReflectionFactory.inflationThreshold() 
       && !ReflectUtil.isVMAnonymousClass(this.method.getDeclaringClass())) {
      // bytecode accessor
      MethodAccessorImpl var3 = (MethodAccessorImpl)(new MethodAccessorGenerator()).generateMethod(this.method.getDeclaringClass(), this.method.getName(), this.method.getParameterTypes(), this.method.getReturnType(), this.method.getExceptionTypes(), this.method.getModifiers());
      // 修改delegate accessor的delegate，实现更换调用方式
      this.parent.setDelegate(var3);
    }

    return invoke0(this.method, var1, var2);
  }

  void setParent(DelegatingMethodAccessorImpl var1) {
    this.parent = var1;
  }

  // JNI调用
  private static native Object invoke0(Method var0, Object var1, Object[] var2);
}
```

invoke调用一次，numInvocations就+1，当其大于`ReflectionFactory.inflationThreshold`的时候，就会创建`bytecode accessor`，并且修改其parent的delegate，更换调用方式；

> When using Java reflection, the JVM has two methods of accessing the information on the class being reflected. It can use a JNI accessor, or a Java bytecode accessor.

其中，更换invoke方式的机制称为`inflation`：

> The JVM will use the JNI accessor first, then after some number of accesses on the same class, will change to use the Java bytecode accessor. 

控制不进行JNI调用，直接生成bytecode accessor:

```
Oracle JVM：
-Dsun.reflect.inflationThreshold=2147483647
IBM JVM：
-Dsun.reflect.inflationThreshold=0
或者：
-Dsun.reflect.noInflation=true
```

**为什么要这么做：**

JNI运行相对缓慢，但是初始化更快；字节码直接类调用运行相对更快，但是初始化缓慢；Inflation机制就是为了优化调节这两者，调用超过一定的阈值，就切换调用方式；为了解耦以及一些其他的原因，比如增加对访问权限的检查之类的，所以就有了MethodAccessor；

> 这是HotSpot的优化方式带来的性能特性，同时也是许多虚拟机的共同点：跨越native边界会对优化有阻碍作用，它就像个黑箱一样让虚拟机难以分析也将其内联，于是运行时间长了之后反而是托管版本的代码更快些。 

`inflation`机制就是为了平衡这两种accessor的性能，

**GeneratedMethodAccessor:**

而`bytecode accessor`是通过 `MethodAccessorGenerator.generateMethod`创建的，这里涉及到Java动态创建字节码的知识，**_To be continue..._**

假如有个类A

```java
public class A {
  public void foo(String a) {}
}
```

通过反射调用A.foo，生成的`MethodAccessorImpl`大致如下：

```java
package sun.reflect;  

public class GeneratedMethodAccessor1 extends MethodAccessorImpl {      
    public GeneratedMethodAccessor1() {  
        super();  
    }  

    public Object invoke(Object obj, Object[] args)     
        throws IllegalArgumentException, InvocationTargetException {  
        // prepare the target and parameters  
        if (obj == null) throw new NullPointerException();  
        try {  
            A target = (A) obj;  
            if (args.length != 1) throw new IllegalArgumentException();  
            String arg0 = (String) args[0];  
        } catch (ClassCastException e) {  
            throw new IllegalArgumentException(e.toString());  
        } catch (NullPointerException e) {  
            throw new IllegalArgumentException(e.toString());  
        }  
        // make the invocation  
        try {  
            target.foo(arg0);  
        } catch (Throwable t) {  
            throw new InvocationTargetException(t);  
        }  
    }  
}
```

至此，`method.invoke`的调用过程就已经梳理完整了；

**参考资料：**

[关于反射调用方法的一个log](http://rednaxelafx.iteye.com/blog/548536)

[Java Reflection: Why is it so slow?](https://stackoverflow.com/questions/1392351/java-reflection-why-is-it-so-slow)

[What makes JNI calls slow?](https://stackoverflow.com/questions/7699020/what-makes-jni-calls-slow)

[What is a de-reflection optimization in HotSpot JIT and how does it implemented?](https://stackoverflow.com/questions/28793118/what-is-a-de-reflection-optimization-in-hotspot-jit-and-how-does-it-implemented)

[大量DelegatingClassLoader类加载器，导致Perm区溢出](http://wujc.cn/archives/90)

[Potential native memory use in reflection delegating classloaders](http://www-01.ibm.com/support/docview.wss?uid=swg21566549)

