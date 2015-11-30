/**************************************************************

**************************************************************/

#include "MyClass.h"
#include <iostream>
#include "FileUtility.h"

using namespace std;

namespace Learn{

	MyClass::MyClass()
		: i(1)
	{
		WriteLog("call constructor MyClass()", "log.txt");
	}

	MyClass::MyClass(const MyClass& cls){
		WriteLog("Call copy constructor", "log.txt");
	}

	MyClass::MyClass(string s){
		WriteLog("Call constructor MyClass(string)", "log.txt");
	}

	MyClass::MyClass(MyClass&& cls){
		WriteLog("Call move constructor", "log.txt");
	}

	MyClass::~MyClass(){
		WriteLog("call destructor", "log.txt");
	}

	// 使用swap函数, 自动处理自赋值情况以及天然的异常安全
	// 包含移动赋值以及拷贝赋值
	MyClass& MyClass::operator=(MyClass cls){
		cout << "call = operator" << endl;

		swap(*this, cls);

		return *this;
	}

	void swap(MyClass& cls1, MyClass& cls2){
		using std::swap;

		// 交换类成员
	}

	void CopyConstructorTest(){
		/*MyClass cls;
		MyClass newCls = CopyClass(cls);*/

		MyClass newCls2 = CopyClass("sdfas");
	}

	void CopyAssignmentOperatorTest(){
		MyClass cls;
		cls = CopyClass(cls); // 调用拷贝赋值运算符
	}

	shared_ptr<MyClass> SmartMemoryTest(){
		shared_ptr<MyClass> cls = make_shared<MyClass>();

		return cls;
	}

	MyClass* DynamicMemoryTest(){
		MyClass* cls = new MyClass();

		return cls;
	}

	MyClass CopyClass(MyClass cls){
		cout << "call by value" << endl;

		MyClass newCls = cls;

		return newCls;
	}

	MyClass CopyClass(string s){
		MyClass cls = s;	// 直接构造cls, MyClass(string)

		cout << "test" << endl;

		return cls;
	}


}