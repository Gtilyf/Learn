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

   ​

#### synchronized

Java中的同步块用synchronized标记。同步块在Java中是同步在某个对象上。所有同步在一个对象上的同步块在同时只能被一个线程进入并执行操作。所有其他等待进入该同步块的线程将被阻塞，直到执行该同步块中的线程退出。



