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

#### unique_ptr

#### weak_ptr