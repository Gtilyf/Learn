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

	// ʹ��swap����, �Զ������Ը�ֵ����Լ���Ȼ���쳣��ȫ
	// �����ƶ���ֵ�Լ�������ֵ
	MyClass& MyClass::operator=(MyClass cls){
		cout << "call = operator" << endl;

		swap(*this, cls);

		return *this;
	}

	void swap(MyClass& cls1, MyClass& cls2){
		using std::swap;

		// �������Ա
	}

	void CopyConstructorTest(){
		/*MyClass cls;
		MyClass newCls = CopyClass(cls);*/

		MyClass newCls2 = CopyClass("sdfas");
	}

	void CopyAssignmentOperatorTest(){
		MyClass cls;
		cls = CopyClass(cls); // ���ÿ�����ֵ�����
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
		MyClass cls = s;	// ֱ�ӹ���cls, MyClass(string)

		cout << "test" << endl;

		return cls;
	}


}