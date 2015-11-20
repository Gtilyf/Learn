# Class

> 总结自C++ Primer, C++ Class

#### Class & Struct

- struct成员默认为public，struct间的继承也默认为public;
- class成员默认为private，class间的继承也默认为private;

#### Class constructor

**initializer list :**
- 用于初始化成员变量，如果构造函数没有定义初始化列表，而是在函数内部对类成员变量进行复制，则类成员变量会在该构造函数执行前进行默认初始化;
- **类的const、引用、没有定义默认构造函数的类类型的成员必须使用初始化列表进行初始化，因为其不支持默认初始化;**
- 先定义的类成员最先进行初始化，与其初始化列表顺序无关;
```c++
MyClass::MyClass()
: i(0)
, j(1)
{}
```

**converting constructor :** 只含有一个参数的构造函数，可以在必要的时候将其他类型变量转化为本类型;
```C++
MyClass(string s; // string转MyClass
```)