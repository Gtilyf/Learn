# Class

> 总结自C++ Primer, C++ Dynamic Memory

Static Memory用来保存局部static对象、类static成员以及定义在任何函数之外的变量; stack memory用来保存定义在函数内部的非static对象; 分配在static memeory以及stack memory中的对象由编译器自动创建和销毁。

除了static memory以及stack memory，每个程序还拥有一个内存池（free store/heap），用于存储程序运行时分配的对象，这些动态对象的生存期由程序自己控制，而动态内存的管理通过`new`以及`delete`来实现，如果程序结束时如果忘记了释放则会造成内存泄露，或者尚有指针引用内存的情况下就释放了，引起指针悬挂，产生引用非法内存的指针，从而引入**智能指针(smart pointer)**，包含于**memory头文件**。

#### shared_ptr

允许多个指针指向同一个对象，同时保存一个引用计数，表示该对象指针的数量，并且会被自动释放;
```c++
shared_ptr<MyClass> Fun(){
	shared_ptr<MyClass> cls(new MyClass());

	return cls;			// 在该内存指向的对象不在使用的时候释放，调用destructor function
}
```

shared_ptr基本操作:
```c++
shared_ptr<MyClass> p = make_shared<MyClass>("hello world");		// 根据传入参数调用MyClass对应的constructor function
if(p->empty()){}		// 判断p是否是一个为初始化的指针
// 交换指针p、q
p.swap(q);
swap(p, q);
p.use_count()			// 返回p共享对象的智能指针数量
p = q;					// p和q共享相同的元素，引用计数+1
```

**尽量使用make_shared而不是new来给shared_ptr分配对象，避免无意中将同一块内存绑定到多个独立创立的share_ptr上，当其中任何一个share_ptr的引用计数为0，则会释放该内存，导致其他shared_ptr变成空悬指针**
```c++
int* a(new int(3));
// 使用new初始化shared_ptr
shared_ptr<int> q(a);
shared_ptr<int> p(a);		// 此时有两个shared_ptr绑定了a内存
p.reset();					// 释放p，则p指向的对象a也就被释放了，结果导致q变成空悬指针，指向一个非法的内存
cout << *q << endl;
// 使用make_share分配对象
shared_ptr<int> q(a);
make_share<int> q(*a);		// make_share重新创建了一个以*a为初始值的对象，是p绑定到该内存
p.reset();					// 释放p指向的内存，但因其是重新分配的对象，不会对源对象即a造成影响
cout << *q << endl;

// 或者使用get去初始化另一个只能指针也会导致多个不同的只能指针绑定到同一块内存上
shared_ptr<int> p(a);
{
	shared_ptr<int> q(p.get());
}	
// 程序块结束后，q的引用计数为0，其指向的内存被释放，那么p就成了空悬指针了，再去访问该内存成了一个非法的行为
cout << *p << endl;
```
> get用来将指针的访问权限传递给代码，只有在确定代码不会delete指针的情况下才能使用get。特别是永远不要使用get去初始化另一个只能指针或者为另一个智能指针赋值

**也不要将shared_ptr与内置指针混用，当我们将一个shared_ptr绑定到一个内置指针上时，我们就将内存管理的人物交给了这个shared_ptr，那么我们就不应该使用内置指针来访问shared_ptr指向的内容了，因为我们无法知道该对象何时被销毁**
```c++
void Fun(shared_ptr<int> p){}
int* a(new int(4));

// 正确使用Fun的方式
shared_ptr<int> p(a);
Fun(p);						// 在Fun中，p的引用计数为2，fun结束后引用计数-1，这样也不会释放p指向的对象

// 错误的使用方式
Fun(shared_ptr<int>(a));	// 在Fun中，p的引用计数为1，fun结束后引用计数-1，结果导致p指向的对象被释放，导致a指针空悬
cout << *a << endl;
```

使用智能指针的基本规范：
- 不使用相同的内置指针的值初始化(或reset)多个智能指针
- 不delete get()返回的指针
- 不适用get()初始化或reset另一个智能指针
- 如果使用get()返回的指针，一定记住该指针会在其绑定的最后一个智能指针销毁后失效
- 如果使用智能指针管理的资源不是new分配的内存，记得传递给其一个删除器

#### unique_ptr

#### weak_ptr