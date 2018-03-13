# Java 泛型

#### 泛型类

```java
public class Container<k,V>{
        private k key;
        private V value;
}
```

#### 泛型接口

```java
public interface Generator<T>{
          public T next();
}
//然后定义这个生成器类来实现这个接口
public class FruitGenerator implements Generator<String>{
          private String[] fruits=new String[]{"Apple","Banana","Pear"};
          @Override
          public String next(){
                    Ramdom rand=new Random();
                    return fruits[rand.nextInt(3)];
          }
}

interface Info<T>{
        public T getVar();
}
class InfoImpl<T> implements Info {
      public T getVar(){
                  return this.var;
      }   
}
```

#### 泛型方法

```java
public <T> Future<T> submit(Callable<T> task) {}
// 通配符?来表示未知类型
public static <T> List invokeAll(List<? extends Callable<T>> tasks) {}
```

#### 类型擦除（type erasure）

> java的泛型基本上都是在编译器层次实现的，生成的java字节码中是不包含泛型的类型信息的，类型参数会在编译的时候去掉，这个过程就被称为类型擦除。如在代码中定义的List<Object>和List<String>等类型，在编译之后都会变成List。

- 泛型类并没有自己独有的Class类对象，比如并不存在List<String>.class或是List<Integer>.class，而只有List.class;
- 静态变量是被泛型类的所有实例所共享的，对于声明为MyClass<T>的类，访问其中的静态变量的方法仍然是 MyClass.myStaticVar；
- 泛型的类型参数不能用在Java异常处理的catch语句中，因为异常处理是由JVM在运行时刻来进行的。由于类型信息被擦除，JVM是无法区分两个异常类型MyException<String>和MyException<Integer>的，对于JVM来说，它们都是 MyException类型的；

类型擦除的基本过程也比较简单，首先是找到用来替换类型参数的具体类。这个具体类一般是Object。如果指定了类型参数的上界的话，则使用这个上界。把代码中的类型参数都替换成具体的类。同时去掉出现的类型声明，即去掉<>的内容。比如T get()方法声明就变成了Object get()；List<String>就变成了List。接下来就可能需要生成一些桥接方法（bridge method），这是由于擦除了类型之后的类可能缺少某些必须的方法。

```java
public class GenericClass<T>{
  public T field1;
}

// 类型擦除后
public class GenericClass{
  public Object field1;
}
```

由于泛型擦除的机制，泛型只能作用与编译时，告诉编译器如何进行类型检查。运行期间，泛型是不存在的，所有的 'T' 都被转换成了Object。如果使用反射(Method.invoke)的方式进行操作，那么就很有可能将一个String的值传递给一个Long的对象，使用到该值时，会尝试进行强转，则有可能就会抛出异常。

**桥接方法：**

```java
abstract class A<T> {  
    abstract T get(T t);  
}  

class B extends A {  
    String get(String s) {  
        return "";  
    }  
}  

// 编译后
abstract class A {  
    abstract Object get(Object t);  
}
class B extends A {  
    String get(String s) {  
        return "";  
    }  
  	Object get(Object t) {
        return (Object) get((String) s);
    } 
}  
```

