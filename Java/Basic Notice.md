# Basic Notice

目录：
- **Polymorphism:** 有关Java多态的实现机制，动态绑定
- **enumerated:** Java枚举类型特性
- **Wrapper Class & Static Import:** 包装类以及静态导入
- **lambda:** Java 8行特性Lambda以及函数式接口

#### Polymorphism

多态的实现需要的必要元素包括：继承、覆盖、向上转型（父类引用子类对象）; 通过动态绑定（auto binding）机制实现执行正确的方法。在JVM加载类的时候，会在方法区存放很多有关于该类的数据结构，其中一个数据结构即叫做方法表，子类和父类的方法表中相同签名方法的索引项是相同的，这样，在实现动态绑定的时候，先由父类引用的类中寻找调用的方法，找到该方法的索引项，再由实例化的内存实际对象的引用找到实际的类的方法表，调用该索引项的方法。

#### enumerated

Java的枚举是特殊的类，既然是类，则其可以定义自己的成员，为这些枚举指定属性，枚举实例由Java运行时创建，在外部不能实例化，所以添加了成员的枚举的构造函数为私有;
```java
public enum RegularPolygon{
	// 有参数的枚举最后必须使用分号结束
	TRIANGLE(3), SQUARE(4), PENTAGON(5), HEXAGON(6);

	private Shape shape;

	private RegularPolygon(int sides){
		switch(sides){
			case 3:
				shape = new Triangle(1, 1, 1, 60, 60);
				break;
			case 4:
			...
		}
	}
}
```

#### Wrapper Class & import static

在需要将基本数据类型当作对象进行处理时使用，主要使用在集合以及本类型与其他类型的转换上。
```java
List<Integer> intList = new ArrayList<>();
Integer i = 3;
short shValue = i.shortValue();
int strToint = Integer.getInteger("3");
```
使用关键字import static导入类型中的静态成员，也可以导入枚举类型;
```java
import static java.lang.System.out;
import static climate.temperate.Season.*

public static void main(String... args)
{
	out.println("hello world");
	Seasons s = WINTER;
}
```
```java
package climate.temperate;

enum Seasons {WINTER, SPRING, SUMMER, AUTUMN};
```

#### Lambda & Anonymous Class
[Java 8 functional interfaces](https://www.oreilly.com/learning/java-8-functional-interfaces),
要理解Lambda表达式，首先需要了解函数式接口。所谓函数式接口即是至包含一个抽象方法的接口(an interface with a single abstract method)，像`Runable`、`Callable`、`Comparator`、`ActionListener`等，在没有lambda语法的时候我们可是使用匿名类进行实现;
```java
Collection.sort(intList, new Comparator<int>(){
	public int compare(int i1, int i2){
		return i1 > i2;
	}
});

// 使用lambda可以使上面的代码变得非常简洁，其中形参的类型由上下文自动推导
Collecton.sort(intList, (i1, i2) -> {
	return i1 > i2;
});
```
lambda的合法性检查：
- lambda表达式必须出现在期望使用接口类型实例的地方;
- 期望使用的接口必须只有一个强制方法;
- 这个强制方法的签名要完全匹配lambda表达式;

**Pre-Built functions library:**

Java 8提供了一些可重用的函数式接口：`java.util.function`
> - **Predicate**: A property of the object passed as argument
- **Consumer**: An action to be performed with the object passed as argument
- **Function**: Transform a T to a U
- **Supplier**: Provide an instance of a T (such as a factory)
- **UnaryOperator**: A unary operator from T -> T
- **BinaryOperator**: A binary operator from (T, T) -> T

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