# OOP

> 总结自C++ Primer, C++ object oriented programming

class之间的继承(inheritance)默认是private的，使用基类(base class)的引用或者指针调用一个虚函数(virtual)实现动态绑定，继承关系中根节点通常定义一个虚析构函数;

#### dynamic binding

基类必须将它的两种成员函数区分开来，一种是希望其派生类进行覆盖的函数，一种是希望派生类直接继承而不进行改变的函数; 使用virtual实现动态绑定，根据引用或者指针所绑定的对象不同，调用对应版本的virtual函数, 对虚函数的调用可能在运行时才被解析;
```c++
class B final {};						// 禁止继承

class BaseClass{
public:
	virtual void Fun();
	void FinalFun() const final;		// 不允许派生类进行覆盖	
};

class DerivedClass : public BaseClass{
public:
	void Fun() override;				// 显示说明进行override
}

DerivedClass derivedCls;
BaseClass& cls = derviedCls;
```

含有纯虚函数的的类是抽象基类，只负责定义接口，不能直接创建一个抽象基类的对象;
```c++
class AbstractClass{
public:
	void Fun() = 0;
}
```

#### derived to base conversion

基类的指针或者引用的静态类型(static type)可能与其动态类型(dynamic type)不一致; 静态类型是在编译时总是已知的，是变量声明时的类型或者表达式生成的类型; 动态类型则是表示的内存中对象的类型，直到运行时才可知;

因为每个派生类对象都包含一个基类部分，所有存在派生类向基类的转换，但不存在基类向派生类的自动转换; 且这种类型转换只对指针或者引用有效; **当我们用一个派生类对象为一个基类对象初始化或者赋值时，只有该派生类中的基类部分才会被拷贝、移动和赋值，其他派生类的部分则被忽略掉;**
- 从派生类的基类的类型转换只对指针或引用类型有效;
- 基类向派生类不存在隐式类型转换;
- 派生类想基类的类型转换也可能会因为访问权限而变得不可行;

#### access control

protected访问控制符主要是控制继承过程中，派生类可以访问的但是基类普通用户（对象）不能访问:
- protected成员对于类的用户（对象）来说是不可访问的;
- protected成员对于派生类的成员及友元是可以访问的;
- 派生类的成员只能通过派生类对象访问基类protected成员，派生类对于一个基类对象中的protected成员没有任何特权;

派生访问说明符主要对派生类用户（包括派生类的派生类）对基类成员的访问控制：
- public继承中，派生类继承下来的基类成员权限不变，派生类普通用户（对象）可以访问基类public成员，派生类的派生类也可以访问
- protected继承中，派生类继承下来的public成员变成protected，则派生类的普通用户（对象）不能对其访问，但派生类的派生类可以访问
- private继承中，派生类继承下来的所有成员都是private，派生类的普通用户（对象）不能对其访问，派生类的派生类也不能访问

**派生访问说明符决定了派生类继承下来的基类成员的访问属性，针对于派生类的用户，包括普通用户和派生类的派生类; [代码示例](../Demostrate Project/Demostrate Project/AccessControl.h)**