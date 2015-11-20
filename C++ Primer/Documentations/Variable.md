# Variable

> 总结自C++ Primer，包括C++引用、指针、左值、右值、常量等;

### declaration & deginition

declaration不申请内存空间，变量可以重复声明`(extern)`; definition申请内存空间，变量只能定义一次;

### compound type

#### reference
```c++
int a = 10;
int& re = a;
```
引用即别名，定义引用时必须对其进行初始化（引用一旦定义，则不能再将其绑定到另外一个对象），对引用的所有操作都是在其绑定的对象上进行的，引用没有实际地址，所以不存在指向引用的指针;

引用类型必须与其所引用对象类型一致，但是有两种例外：
 1. 对常量的引用（常量引用）允许使用任意表达式作为初始值，只要该表达式的结果能转换成引用类型即可，比如字面值常量;
 2. 基类引用绑定派生类对象

#### pointer 
```c++
int a = 10;
int* ptr = &a;
```
point to, 指针本身即是一个对象;

#### const
```c++
const int a = 1080;
```
常量一旦定义就不可以再修改，所以常量必须进行初始化;

#### reference to pointer
```c++
int a = 10;
int* ptr = &a;
int*& rePtr = ptr;
```
对指针的引用

#### reference to const & pointer to const
```c++
const int& re = a;
const int* ptr = &a;
```
对常量的引用（常量引用）& 指向常量的指针

不可以通过指向常量的指针或引用去改变其绑定对象的值，如果该对象不是常量，则可以通过其他途径改变其值（该指针或引用自以为自己指向的是常量，对const的引用可能引用一个并非cosnt的对象）;

当然，对于常量对象只能使用指向常量的指针或引用;

#### const pointer
```c++
int* const ptr = &a;
const int* const cPtr = &a; // 指向常量的常量指针，指针以及其指向的对象都不可以进行修改;
```
常量指针，指针是常量，即该指针不可改变，但是可以通过该指针修改其指向的对象;

#### top-level const & low-level const
```c++
int* const ptr = &a; // top level const
const int* ptr = &a; // low level const
```
对拷贝操作的影响：top-level const对拷贝操作的影响可以忽略，拷入、拷出对象是否为常量对拷贝操作并无影响; 但是拷贝对象之间必须具有相同的low-level const，或者拷出对象是非常量，其可以转换为常量;

auto类型推断也会忽略top-level const，但不会忽略low-level const, 如果想要保留top-level const则需明确指定( `const auto a = r;` );

#### lvalue & rvalue
> An lvalue (so called, historically, because lvalues could appear on the left-hand side of an assignment expression) designates a function or an object. [ Example: If E is an expression of pointer type, then *E is an lvalue expression referring to the object or function to which E points. As another example, the result of calling a function whose return type is an lvalue reference is an lvalue. —end example ]

> An rvalue (so called, historically, because rvalues could appear on the right-hand side of an assignment expressions) is an xvalue, a temporary object (12.2) or subobject thereof, or a value that is not associated with an object.

- 当一个对象被当做**左值**的时候，用的是对象的身份，即其在内存中的位置;
- 当一个对象被当做**右值**的时候，用的是对象的值，即其内容; 只能绑定到一个将要被销毁的对象，不能直接绑定到一个左值上;
- 在需要右值的地方可以使用左值代替，但是不能把右值当成左值; (例外情况：对象移动)
- 右值引用：绑定到要求转换的表达式、字面值常量以及返回右值的表达式，所引用的对象将要被销毁，该对象没有其他用户;
- **使用右值引用可以自由的接管所引用对象的资源**(移动而并非拷贝); 使用move即表示之后不会再对该对象进行除销毁以及赋值之外的任何操作;
```c++
int&& rRe = 2; 			// 右值引用
int&& rRe1 = move(a); 	// 左值显式的转换成右值引用
```

> Functions that return lvalue references, alone with the assignment, subscript, dereference and prefix increment/decrement operators, all of these expressions return lvalue, we can bind an lvalue reference to the result of any of these expressions;

> Functions that return a nonreference type, alone with the arithmetic, relational, bitwise, and postfix increment/decrement operators, all yield rvalues, we cannot bind an lvalue reference to these expressions, but we can bind either an lvalue reference to `const` or an rvalue reference to such expressions;

**右值引用的使用场景:**

**运算符与左值右值 :**
	1. 赋值运算符需要一个（非常量）左值作为其左侧运算对象，得到的结果仍然是一个左值;
	2. 取地址运算符作用于一个左值对象，返回一个该运算对象的指针，该指针是一个**右值**;
	3. 内置解引用运算符、下标运算符、迭代器解引用运算符、string和vector的下表运算得到的结果都是**左值**;
	4. 内置类型和迭代器的递增递减运算符作用于左值对象，其前置版本得到的结果也是左值;

#### decltype
```c++
decltype( f() ) sum = x; // sum的类型就是函数f的返回类型
```
如果是对**表达式**使用decltype，如果表达式的结果是一个左值(可以对其结果进行赋值)则得到一个**左值引用**类型(`decltype(*ptr)`得到int&)，如果表达式的结果是一个右值则得到一个**左值**类型(`decltype(&ptr)`得到int**); 

如果是对**变量**使用decltype，只有当变量的类型是引用的时候才会得到引用类型，或者将变量视为表达式(`decltype( (a) )`);