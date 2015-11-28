# Class

> 总结自C++ Primer, C++ Class

#### Class & Struct

- struct成员默认为public，struct间的继承也默认为public;
- class成员默认为private，class间的继承也默认为private;

#### Constructor

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
MyClass(string s); 						// string转MyClass

item.Combine(static_cast<MyCalss>(s));	// 显示的使用隐式转换

explicit MyClass(string s);				// 阻止隐式转换，只能用于直接初始化
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

#### Distructor

```c++
MyClass::~MyClass(){}
```
当对象将要被销毁时调用

#### copy constructor

```c++
MyClass::MyClass(const MyClass& cls)
: p(new string(*cls.p))
{}
```
发生拷贝的场景：
- 初始化变量（"="），可以发生隐式转换
- 按值传递以及按值返回(编译器优化RVO & NRVO
- **拷贝初始化：**编译器将右侧运算符对象拷贝到正在创建的对象中，如果需要的话还将进行类型转换
- 对于标准库容器，insert或push成员时，使用拷贝初始化；当使用emplace成员时，对成员进行直接初始化
- 禁止拷贝：`MyCalss(const MyCalss&) = delete;`

#### copy-assignment operator

```c++
MyClass& operator=(const MyClass& cls)
{
	// 错误的工作方式，典型情况：右侧对象是其自身
	delete this->s;
	this->s = cls.s;

	// 正确的工作方式
	auto tmpString = new string(cls.s);	// 先将右侧对象数据拷贝到临时变量
	delete this->s;						// 再删除左侧对象数据，释放内存
	this->s = tmpString;				// 拷贝数据到左侧对象

	return *this;
}
```
- 如果将一个对象赋给其自身，赋值运算符必须能正确工作
- 大多数赋值运算符组合了析构函数（释放原对象占有的内存）和拷贝构造函数（分配新的空间并且拷贝赋值）的工作;
- 对于一个赋值运算符，一个好的模式就是先将右侧运算对象拷贝到一个临时变量中
- 对定义有swap函数的类，copy and swap，自动处理自赋值以及天然的异常安全
```c++
void swap(MyClass& cls1, MyClass& cls2)
{
	using std::swap;
	swap(cls1.p, cls2.p); // 并未限定使用std::swap
}

// cls是按值传递的，将会调用拷贝构造函数，函数调用结束即被销毁
MyClass& MyClass::operator=(MyClass cls)
{
	swap(*this, cls);
	return *this;
}
```

#### Swap

```c++
class MyClass{
public:
	friend void swap(MyClass&, MyClass&);
private:
	string* p;	
};

inline 										// swap的存在目的即是优化代码，所以应当定义为inline
void swap(MyClass& cls1, MyClass& cls2)
{
	//string* tmp = cls2.p;
	//cls1.p = cls2.p;
	//cls2.p = tmp;

	using std::swap;
	swap(cls1.p, cls2.p);					// 优先使用成员对象自身定义的swap，如果没有定义，则使用std::swap;
}
```
swap函数应当是friend函数，以便于访问class成员，以及满足交换律，对于分配了资源的类，swap是一种很重要的优化手段(对于排序等需要对成员进行交换的算法);

#### Copy control & Resource manager

> 当一个类的成员是不能拷贝、赋值或销毁时，该类的合成拷贝控制成员都将被定义为删除的;（删除的或不可访问的析构函数、引用成员、无法默认构造的const成员）

当一个类需要进行动态分配资源时，由默认拷贝控制成员可能引起指针悬挂的问题，解决此问题的办法是定义我们自己的拷贝语义，使类的行为看起来像一个值或者指针;

**定义行为像值的类：**每个对象拥有自己的状态，当拷贝一个值的时候，副本和原对象是完全独立的，改变副本不会对原对象有任何影响;
- 定义自己的拷贝控制成员，对动态资源进行拷贝以及单独释放，而不只是复制指针;

**定义行为像指针的类：**对象处于共享状态，副本和原对象拥有相同的底层数据，改变副本同时也会改变原对象;
- 创建引用计数器，保存于动态内存中，拷贝控制时，复制动态资源的指针（包括引用计数器），将引用计数器+1，只有当引用计数器为1的时候才能释放资源;
```c++
MyClass::MyClass(const MyCalss& cls)
: p(cls.p)
{
	++*use;
}

MyClass& MyClass::operator=(const MyClass& cls)
{
	// 增加右侧运算对象的引用计数
	++*cls.use;	
	string* tmp_p = cls.p;
	// 如果左侧对象的引用计数为0，则释放原对象的共享数据
	if(--*use == 0){
		delete p;
	}
	p = tmp_p;
	use = cls.use;

	return *this;
}

MyClass::~MyClass()
{
	if(--*use == 0){
		delete p;
	}
}
```

#### Move constructor & Move-assignment operator

```c++
MyClass::MyClass(MyClass&& cls) noexcept   // 移动操作不会抛出任何异常，以此通知标准库，避免不必要的操作
: p(cls.p)						// 直接将p指向移动对象的内存
{
	cls.p = nullptr;			// 在将移动对象指向nullptr，避免移动对象析构造成数据失效（析构安全）
}

MyClass& MyClass::opertator=(MyClass& cls) noexcept
{
	// 处理自赋值
	if(this != &cls){
		free();				// 释放已有元素
		p = cls.p;

		cls.p = nullptr;	// 至于析构安全状态
	}
	return *this;
}
```
定义了move constructor和move-assignment operator的类，必须也定义自己的copy control，否则这些move control都将会默认为删除的;

- **移动右值，拷贝左值（响应的左值右值，调用响应的拷贝或移动控制函数）**
- **如果不可移动，右值也被拷贝（MyClass&& 可以转换为const MyClass&）**
- **move and copy with swap function**
```c++
// 实参进行拷贝初始化，则根据传入的值决定使用copy constructor或move constructor —— 左值拷贝，右值移动
// 当cls离开作用域后，自动被销毁
MyClass& MyClass::operator=(MyClass cls)
{
	swap(*this, cls);
	return *this;
}

cls = cls2;				// 拷贝构造函数拷贝cls2
cls = std::move(cls2)	// 移动构造函数移动cls2
```

**由于一个以后源对象具有不确定的状态，对其调用std::move是一个非常危险的行为; 当我们调用move时，必须绝对确认以后源对象没有其他用户; 在move constructor和move-assignment operator这些类实现代码之外的地方，只有当我们确信需要进行移动操作切移动操作是安全的时候，才可以使用std::move**

#### 引用限定符

指定this是一个左值或者是一个右值，即调用者（对象）是左值或者右值; 如果定义两个或两个以上的重载函数，要么所有函数都加上引用限定符，要么都不加;
```c++
MyClass MyClass::RetVal(){}
MyClass& MyClass::RetRef(){}

// this为右值，即本对象为右值，进行当该类对象为右值时应当进行的操作，比如进行源址排序
// 当该对象是右值时，即表明其没有其他用户，我们可以安全的改变该对象
MyClass MyClass::Sorted() &&
{
	sort(data.begin(), data.end());

	return *this;
}

// this为左值，即本对象为左值，进行当该类对象为左值时应担进行的操作
MyClass MyClass::Sorted() const &
{
	MyClass cls(*this);
	sort(cls.data.begin(), cls.data.end());
	return cls;
}

RetVal.Sorted();
RetRef.Sorted();
```

#### 合成的copy control以及move control有可能是删除的