# Variable

> 总结自C++ Primer，包括C++引用、指针、左值、右值、常量、函数等;

#### declaration & deginition
declaration不申请内存空间，变量可以重复声明`(extern)`; definition申请内存空间，变量只能定义一次;

#### compound type
- **reference :** 
	```c++
	int a = 10;
	int& re = a;
	```
	引用即别名，定义引用时必须对其进行初始化（引用一旦定义，则不能再将其绑定到另外一个对象），对引用的所有操作都是在其绑定的对象上进行的，引用没有实际地址，所以不存在指向引用的指针;

	引用类型必须与其所引用对象类型一致，但是有两种例外：
	1. 对常量的引用（常量引用）允许使用任意表达式作为初始值，只要该表达式的结果能转换成引用类型即可，比如字面值常量;
	2. 基类引用绑定派生类对象

- **pointer :** point to 
	```c++
	int a = 10;
	int* ptr = &a;
	```
	指针本身即是一个对象;

- **const :**
	```c++
	const int a = 1080;
	```
	常量一旦定义就不可以再修改，所以常量必须进行初始化;

- **reference to pointer :** 对指针的引用
	```c++
	int a = 10;
	int* ptr = &a;
	int*& rePtr = ptr;
	```

- **reference to const & pointer to const :** 对常量的引用（常量引用）& 指向常量的指针
	```c++
	const int& re = a;
	const int* ptr = &a;
	```
	不可以通过指向常量的指针或引用去改变其绑定对象的值，如果该对象不是常量，则可以通过其他途径改变其值（该指针或引用自以为自己指向的是常量，对const的引用可能引用一个并非cosnt的对象）;
	当然，对于常量对象只能使用指向常量的指针或引用;

- **const pointer :** 常量指针
	```c++
	int* const ptr = &a;
	const int* const cPtr = &a; // 指向常量的常量指针，指针以及其指向的对象都不可以进行修改;
	```
	指针是常量，即该指针不可改变，但是可以通过该指针修改其指向的对象;

- **top-level const & low-level const :** 
	```c++
	int* const ptr = &a; // top level const
	const int* ptr = &a; // low level const
	```
	对拷贝操作的影响：top-level const对拷贝操作的影响可以忽略，拷入、拷出对象是否为常量对拷贝操作并无影响; 但是拷贝对象之间必须具有相同的low-level const，或者拷出对象是非常量，其可以转换为常量;

	auto类型推断也会忽略top-level const，但不会忽略low-level const, 如果想要保留top-level const则需明确指定( `const auto a = r;` );