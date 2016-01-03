# Customizing Operations

> 总结自C++ Primer, C++ Customizing Operations

#### predicate

**谓词**是一个可调用的表达式，其返回结果是一个能作为条件的值。接受谓词参数的算法对输入序列中的元素调用谓词，元素类型必须转换为谓词的参数类型;

#### lambda

```
[capture list](parameter list) -> return type {function body}
```
- lambda是一个可调用对象，可以对其使用调用运算符, 用于满足一元谓词以及二元谓词不能满足需要多参数的操作的情况;
- 可以忽略lambda参数列表以及返回类型，但必须永远包含捕获列表和函数体;
```c++
auto f = [] { return 4; };
f();
```
- 如果忽略返回值类型，lambda根据函数体中的代码推断出返回类型; 如果函数体只包含单一的return语句，则返回类型由表达式推断出来，否则返回void;
```c++
transform(v.begin(), v.end(), [](int i) { return i < 0 ? -i : i; });				// 返回值类型为int
transform(v.begin(), v.end(), [](int i) { if(i < 0) return -1; else return i; });	// 返回值类型为void
```
- 通过捕获列表指明需要使用的局部变量;
```c++
auto wc = find_if(words.begin(), words.end(), [sz](const string& a) { return a.size() >= sz; });
// 值捕获，变量可拷贝
auto f = [v] { return 4; };

// 引用捕获，必须保证在lambda执行期间值是存在的
auto f = [&v] { return v++; };

// 隐式捕获，不显示的列出我们需要使用的变量，由编译器根据函数体代码推断使用的变量
auto f = [=] { return 4; };			// 隐私值捕获
auto f = [&] { return 4; };			// 隐式引用捕获
// 混合使用
auto f = [&, a] { return 4; };		// a是捕获，其余变量均为引用捕获
auto f = [=, &os] { return 4; };	// os是引用捕获，其余变量都为值捕获
```
- 当定义一个lambda，编译器生成一个与lambda对应的新的未命名的类类型（函数对象），该类型包含对应捕获变量的数据成员，在lambda对象创建时被初始化;
```c++
stable_sort(words.begin(), words.end(), 
			[sz](const string& a, cosnt string& b) 
			{ return a.size() > b.size(); });

// 该lambda翻译而成的函数对象
class ShorterString{
public:
	ShorterString() : sz(n) {}
	bool operator()(const string& a, const string& b) const
	{ return a.size() > b.size(); }	
private:
	size_t sz;
};

stabld_sort(words.begin(), words.end(), ShorterString(sz));
```

#### parameter binding

在很多地方使用同一个操作，以及需要很多语句才能完成，在这样的情况下，使用bind更好;
```c++
#include <functional>

using sta::placeholders::_1;

bool check_size(const string& s, sz){}
auto callable = bind(check_size, _1, sz);		//	callable(s) == check_size(s, sz);
auto wc = find_if(words.begin(), words.end(), callable);
auto wc2 = find_if(words.begin(), words.end(), bind(check_size, _1, sz));

// 绑定引用参数
for_each(words.begin(), words.end(), bind(print, ref(os), _1, " "));

// 使用bind重排参数顺序
sort(words.begin(), words.end(), isShorter);				// 由小到大排序
sort(words.begin(), words.end(), bind(isShorter, _2, _1));	// 由大到小排序
```

**bind与lambda**
- lambda不支持移动捕获(move capture)
- lambda无法处理类型多态
```c++
// c++ 11
struct MyStruct{
	tmplate<typename T>
	void operator(std::vector<int>& container T&& value) const {}
};

auto myStruct = bind(MyStruct(), std::ref(container), _1);

// c++ 14
auto myStruct = [&container] (auto&& value) { container.emplace_back(std::forward<decltype(value)>(value)); };
```

#### function

不同的可调用对象可以共享相同的调用形式(int (int, int));
```c++
#include <functional>

// 函数
int add0(int i, int j) {}
// 函数对象
struct add1{
	int operator()(int i, int j) {}
};
// lambda
auto add2 = [](int i, int j) -> int {};
// bind
auto add3 = bind(add0, 9, _1);

map<string, function<int(*) (int, int)>> binops = {
	{"+", add0},									// 函数指针
	{"a", add1},									// 函数对象
	{"b", add2},									// 命名了得lambda对象
	{"c", add3},									// bind
	{"d", [](int i, int j) { return i + j; }}		// 未命名的lambda对象
};
```