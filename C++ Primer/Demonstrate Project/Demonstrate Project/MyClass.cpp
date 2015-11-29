/**************************************************************

**************************************************************/

#include "MyClass.h"
#include <iostream>

using namespace std;

namespace Learn{

	MyClass::MyClass(){
		cout << "call constructor MyClass()" << endl;
	}

	MyClass::MyClass(const MyClass& cls){
		cout << "Call copy constructor" << endl;
	}

	MyClass::MyClass(string s){
		cout << "Call constructor MyClass(string)" << endl;
	}

	MyClass::MyClass(MyClass&& cls){
		cout << "Call move constructor" << endl;
	}

	// 使用swap函数, 自动处理自赋值情况以及天然的异常安全
	// 包含移动赋值以及拷贝赋值
	MyClass& MyClass::operator=(MyClass cls){
		cout << "call copy-assignment operator" << endl;

		swap(*this, cls);

		return *this;
	}

	void swap(MyClass& cls1, MyClass& cls2){
		using std::swap;

		// 交换类成员
	}

	void CopyConstructorTest(){
		MyClass cls;
		MyClass newCls = CopyClass(cls);

		MyClass newCls2 = CopyClass("sdfas");
	}

	void CopyAssignmentOperatorTest(){
		MyClass cls;
		cls = CopyClass(cls); // 调用拷贝赋值运算符
	}

	MyClass CopyClass(MyClass cls){
		cout << "call by value" << endl;

		MyClass newCls = cls;

		return newCls;
	}

	MyClass CopyClass(string s){
		MyClass cls = s;	// 先调用conveting constructor, 再调用copy constructor

		return cls;
	}
	

}