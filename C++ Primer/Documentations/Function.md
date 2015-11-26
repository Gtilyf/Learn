# Function

> 总结自C++ Primer，对C++函数的使用

#### static object

_local static object_ will not be released  after the end of the function, will be released after the end of program.

#### reference and function

_called by value_会引起拷贝操作，_called by reference_可以避免引起拷贝，同时也可以在函数内部修改外部变量;

#### array and function

数组作为形参时，需要为函数提供额外的数字大小信息：
- 显示的传递一个表示数组大小的形参
- 使用标记指定数组长度，数组本身包含一个结束标记
```c++
void print(const char* cp){
	if(cp)
		while(*cp)			// 当指向的字符为空字符的时候退出
			cout << *cp++;
}
```
- **使用标准库begin() & end()**
```c++
void print(const int* beg, const int* end){
	while(beg != end)		// end指向尾元素的下一个元素
		cout << *beg++;
}

print(begin(a), end(a));
```

#### return value
> 函数的返回值用于初始化调用点的一个临时量，如果不是返回引用则会引起拷贝（不考虑编译器优化），即拷贝初始化;

**函数返回引用得到左值，否则得到右值;**
```c++
char& get_val(string& str, string::size_type index){
	return str[index];
}

get_val(str, 0) = 'a';
```
列表初始化返回值，用于初始化返回的临时量;
```c++
vector<string> process(){
	return {"function", "return"};
}
```

#### trailing return value

尾置返回类型，用于定义返回类型较为复杂的函数;
```c++
auto func(int i) -> int(*)[10]; // 返回指向含有10个int元素的数组指针
```

#### overloaded
拷贝操作会忽略[top-level const](/C++ Primer/Documentations/Variable.md#top-level const & low-level const)(`int* const p`)，所以一个拥有top-level const的形参无法和一个没有top-level const的形参区分开，所以通过区分形参是否具有top-level const是无法实现函数重载，相反可以通过区分low-level const的形参实现函数重载;
```c++
int Fun(int);
int Fun(const int);			// 重复定义函数Fun

int Fun(int*);
int Fun(int* const);		// 重复定义函数Fun

int Fun(int*);
int Fun(const int*);		// 重载函数Fun
```

#### assert

#### function pointer

```c++
// 定义函数指针
typedef char (*FUN) (int, char);
FUN fp = fun;
char (*fp) (int, char);

using f = int(int*, int);			// f是函数类型
using pf = int(*)(int*., int);		// pf是函数指针类型

int (*f1(int)) (int *, int); 		// 返回int (int *, int)类型的函数指针，函数参数为(int)
auto f1(int) -> int(*)(int *, int); // 尾置返回值类型

// 函数指针形参
void useBigger(const string& s, bool pf(const string&));	// 自动转换
void useBigger(const string& s, bool (*pf)(const string&));	// 显示定义
```