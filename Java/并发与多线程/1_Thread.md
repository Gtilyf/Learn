# Thread

#### Defining and Starting a thread

1. `Runnable`接口

   ```java
   public class HelloRunnable implements Runnable {

       public void run() {
           System.out.println("Hello from a thread!");
       }

       public static void main(String args[]) {
           (new Thread(new HelloRunnable())).start();
       }

   }
   ```

2. `Thread`父类

   ```java
   public class HelloThread extends Thread {

       public void run() {
           System.out.println("Hello from a thread!");
       }

       public static void main(String args[]) {
           (new HelloThread()).start();
       }

   }
   ```




#### synchronized

Java中的同步块用synchronized标记。同步块在Java中是同步在某个对象上。所有同步在一个对象上的同步块在同时只能被一个线程进入并执行操作。所有其他等待进入该同步块的线程将被阻塞，直到执行该同步块中的线程退出。

同步块在Java中是同步在某个对象上的，所有同步在同一对象上的同步块在同时只能被一个线程进入并执行操作。所有其他等待进入该同步块的线程将被阻塞，直到执行该同步块的线程退出。

在同步构造器中用括号括起来的对象叫做监视器对象，一次只有一个线程能够在同步于同一个监视器对象的Java方法内执行。

> 管程 (Monitors，也称为监视器) 是一种程序结构，结构中的多个子程序（对象或模块）形成的多个工作线程互斥访问的共享资源。管程实现了在一个时间点，最多只有一个线程在执行它的某个子程序。管程是一个编程语言概念，编译器必须要识别出管程并用某种方式对互斥做出安排

```java
// 实例方法同步块
public synchronized void add(int value){
	this.count += value;
}

// 静态方法同步块
public static synchronized void add(int value){
	count += value;
}

// 实例方法中的同步块
public void add(int value){
    synchronized(this){
       this.count += value;
    }
}

// 实例方法中的同步块
public class MyClass {
   public void log2(String msg1, String msg2){
      synchronized(this){
         log.writeln(msg1);
      }
   }
}

// 静态方法中的同步块
public class MyClass {
    public static void log2(String msg1, String msg2){
       synchronized(MyClass.class){
          log.writeln(msg1);
       }
    }
 }
```