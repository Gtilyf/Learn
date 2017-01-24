# Lambda

#### Lambda & Anonymous Class

> [Java 8 functional interfaces](https://www.oreilly.com/learning/java-8-functional-interfaces)
>
> [lambda-expressions-in-java-8](http://www.drdobbs.com/jvm/lambda-expressions-in-java-8/240166764?pgno=3)

要理解Lambda表达式，首先需要了解函数式接口。所谓函数式接口即是至包含一个抽象方法的接口(an interface with a single abstract method)，像`Runable`、`Callable`、`Comparator`、`ActionListener`等，在没有lambda语法的时候我们可是使用匿名类进行实现;

```java
// 函数式接口, Java 8 的设计者给了我们一个注释，@FunctionalInterface，它被当作接口使用 
// lambda的一个文档提示，但是编译器不需要这个——它决定了”功能性接口”是从接口的结构（单方法接口）
// 而来，而不是从注释。
public interface SomeAction() {
  String action(int a);
}
SomeAction action = (item) -> String.valueOf(item + 2);

// 匿名内部类
list.sort(new Comparator<int>(){
  @Override
  public int compare(int i1, int i2){
    return i1 > i2;
  }
});

// 使用lambda可以使上面的代码变得非常简洁，其中形参的类型由上下文自动推导
list.sort((i1, i2) -> {
  return i1 > i2;
});
```

lambda的合法性检查：

- lambda表达式必须出现在期望使用接口类型实例的地方;
- 期望使用的接口必须只有一个强制方法;
- 这个强制方法的签名要完全匹配lambda表达式;

**Lambda值捕获：**

lambda表达式可以捕获外部作用域的变量，但是为了为了保证被捕获的变量值是定义良好的，线程安全的，该捕获变量在lambda表达式中是不可更改的(**final or effectively final**)；

> It's an implementation detail how that is done. For example, one can translate a lambda expression into an object with a single method, so that the values of the free variables are copied into instance variables of that object.



>A lambda expression can access final local variables or local-non-final-initialized-only-once variables.

```java
String text = "hello";
StringBuild sb = new StringBuild();
Thread thread = new Thread(() -> {
  // ERROR! lambda所捕获的值是final的
  text = "dfa";
  sb = new StringBuild();
  System.out.print(text);
  
  // CORRECT
  sb.append("hello");
});
```

**`this` in lambda:**

不同于匿名内部类，在lambada中this并不是引用lambda，而是引用的定义该lambda的直接环境。

```java
class Hello {
  public Runnable r = new Runnable() {
    public void run() {
      system.out.println(Hello.this);
      // this -> 该匿名内部类
      system.out.println(this);
	}
  }
}

class Hello {
  public Runnable r = () -> {
    // this -> Hello
  	system.out.println(this);
  }
}
```

**lambda覆用:**

DRY(the Don’t Repeat Yourself principle不要重复自己的原则)原则

```java
public class Person {
  // . . .

  public static final Comparator<Person> BY_LAST_AND_AGE =
    (lhs, rhs) -> {
      if (lhs.lastName.equals(rhs.lastName))
        return lhs.age - rhs.age;
      else
        return lhs.lastName.compareTo(rhs.lastName);
    };
}

Collections.sort(people, Person.BY_LAST_AND_AGE);
```

**Pre-Built functions library:**

Java 8提供了一些可重用的函数式接口：`java.util.function`

> - **Predicate**: A property of the object passed as argument
> - **Consumer**: An action to be performed with the object passed as argument
> - **Function**: Transform a T to a U
> - **Supplier**: Provide an instance of a T (such as a factory)
> - **UnaryOperator**: A unary operator from T -> T
> - **BinaryOperator**: A binary operator from (T, T) -> T

```java
@FunctionalInterface
public interface Predicate<T> {
	// Evaluates this predicate on the given argument.
	boolean test(T t);
}

@FunctionalInterface
public interface Function<T, R> {
	// Applies this function to the given argument.
	R apply(T t);
}

@FunctionalInterface
public interface Consumer<T> {
	// Performs this operation on the given argument.
	void accept(T t);
}

@FunctionalInterface
public interface Supplier<T> {
  T get();
}
```

我们可以使用这些函数式接口定义我们自己的调用操作：

```java
class Clazz{
	private int index;
	public Clazz(int i, Predicate<Integer> p){
		if (p.test(i))
			index = i;
		else
			index = 0;
	}

	public static void main(String... arfs){
		Clazz c = new Clazz(8, (i) -> {
			return i > 5;
		});
	}
}
```

