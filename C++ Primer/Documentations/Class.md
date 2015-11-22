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

MyClass::MyCalss(int s) : MyCalss() { i = s; }		// 委托构造函数，当受委托构造函数执行完毕后再执行委托原构造函数的函数体
```

**converting constructor :** 只含有一个参数的构造函数，可以在必要的时候将其他类型变量转化为本类型;
```C++
MyClass(string s); 				// string转MyClass

explicit MyClass(string s);		// 阻止隐式转换，只能用于直接初始化
```

#### this

默认情况下指向自身对象的常量指针，在const成员函数中则是指向常量的常量指针（从this的角度看，对象自身为常量）;
```c++
MyClass& MyClass::Fun()
{
	return *this;		// MyClass* const this;
}

const MyClass& MyClass::ConstFun() const
{
	return *this;		// const MyCalss* const this;
}
```
**常量对象，以及常量对象的引用和指向常量对象的指针都只能调用常量成员函数**，同时如果有对const函数的重载，则根据调用对象是否为const决定调用哪个重载函数;

#### copy constructor
发生拷贝的场景：
- 初始化变量（"="），可以发生隐式转换
- 按值传递以及按值返回(编译器优化RVO & NRVO)