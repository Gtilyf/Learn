# Template

> 总结自C++ Primer，C++ template

#### function template

一个函数模板就是一个公式，可以生成针对特定类型的函数版本;
```c++
template <typename T>
void Function(const T& v1, const T& v2){}
```

使用函数模板时，我们显示或隐式的指定模板实参，将其绑定到模板参数上，由此实例化不同版本的模板的实例;
```c++
Function(12, 23);		// 编译器会使用实参的类型来确定绑定到模板参数T的类型
Function<int>(12, 23);	// 显示指定模板实参
```

#### class template

```c++
template <typename T>
class MyClass{
public:
	T& par;
	void Function(T& t);	
};

template <typename T>
void MyClass<T>::Function(T& t){}
```
- 一个类模板的每个实都形成一个独立的类，定义在类模板之外的成员函数必须以template关键字开头，后接模板参数列表;
- 默认情况下，对于一个实例化了得类模板，其成员只有在使用时才被实例化;
- 如果类模板中定义了static对象，类模板的实例拥有独立的static对象;