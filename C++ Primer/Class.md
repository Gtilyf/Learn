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
- 按值传递以及按值返回(编译器优化RVO & NRVO或者优先移动构造)
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

> 当一个类的成员是不能拷贝、赋值或销毁时，该类的合成拷贝控制成员都将被定义为删除的;（删除的或不可访问的析构函数、引用成员、无法默认构造的const成员）; 当一个类的析构函数是delete的或者其某个成员的类型删除了析构函数，我们则不能通过该类定义变量或创建对象;

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

> 如果我们不申明自己的拷贝构造函数或拷贝复制运算符，编译器总会帮我们合成这些操作，要么被定义为逐成员拷贝，要么被定义为对象赋值，要么被定义为删除的函数; 编译器不会为某些类合成移动操作，特别是如果一个类定义了自己的拷贝构造函数、拷贝复制运算符或者析构函数，编译器就不会为其合成移动构造函数和移动复制运算符; 只有当一个类没有定义任何自己版本的拷贝控制成员，切类的每个非static成员都能移动时，编译器才会为它合成移动构造函数或移动赋值运算符;

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
// 实参初始化，根据传入的值决定使用copy constructor或move constructor —— 左值拷贝，右值移动
// 当cls离开作用域后，自动被销毁
MyClass& MyClass::operator=(MyClass cls)
{
	swap(*this, cls);
	return *this;
}

cls = cls2;				// 拷贝构造函数拷贝cls2
cls = std::move(cls2)	// 移动构造函数移动cls2
```

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

#### Operator override

- 当在内置的操作运算符和我们自己的操作之间存在逻辑映射关系的时候，运算符重载的效果最好.
- 如果类含有算术运算符或者位运算符，则最好也提供对应的符合赋值运算符。
- 赋值(=)、下标([ ])、调用(())和成员访问(->)运算符必须是类成员;
- 复合赋值运算符应当是类成员，但也并非必须;
- 改变对象状态或者与给定类型密切相关的运算符，如递增(++)、递减(--)、解引用(*)运算符应当是类成员;
- 具有对称性的运算符可以转换任意一端的运算对象，如算术、相等性、关系、和位运算符等，应当是非类成员;

```c++
// 重载<<与>>运算符
ostream& operator<<(ostream& os, const MyClass& cls){
	os << cls.s;
	return os;
}
istream& operator>>(istream& is, MyClass& cls){
	is >> cls.s;
	return is;
}

// 如果类同时定义了算术运算符和相关的符合赋值运算符，通常情况下应该使用符合赋值运算符实现算术运算符
MyClass& MyClass::operator+=(const MyClass& cls){
	this.s += cls.s;
	return *this;
}

MyClass operator+(const MyClass& cls1, cont MyClass& cls2){
	MyClss sum = cls1;
	sum += cls2;
	return sum;
}

// 关系运算符以及相等运算符
bool operator==(const MyClass& cls1, const MyClass& cls2){
	return cls1.s == cls2.s;
}

bool operator>(const MyClass& cls1, const MyClass& cls2){
	return cls1.s > cls2.s;
}

// 下标运算符，表示容器的类
std::string& MyClass::operator[](std::size_t i){
	return this.s[i];
}
// 常量对象调用，避免对返回值赋值
const std::string& MyClass::operator[](std::size_t i) const
{
	return this.s[i];
}

// 前置递增、递减
MyClass& MyClass::operator++(){
	MyClass cls = *this;
	++*this;
	return cls;
}
MyClass& MyClass::operator--(){}
// 后置递增、递减
MyClass MyClass::operator++(int){}
MyClass MyClass::operator--(ini){}
```

**重载调用运算符以及函数对象：**
```c++
class MyClass{
public:
	MyClass(ostream &o = cout, char c = ' ') : os(0), sep(c) {}
	void operator()(cosnt string& s) const { os << s << sep; }
private:
	ostream& os;
	char sep;
};

MyClass cls;
cls("Hello");

for_each(vs.begin(), vs.end(), MyClass(cout, '\n');
```