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

	// ʹ��swap����, �Զ������Ը�ֵ����Լ���Ȼ���쳣��ȫ
	// �����ƶ���ֵ�Լ�������ֵ
	MyClass& MyClass::operator=(MyClass cls){
		cout << "call copy-assignment operator" << endl;

		swap(*this, cls);

		return *this;
	}

	void swap(MyClass& cls1, MyClass& cls2){
		using std::swap;

		// �������Ա
	}

	void CopyConstructorTest(){
		MyClass cls;
		MyClass newCls = CopyClass(cls);

		MyClass newCls2 = CopyClass("sdfas");
	}

	void CopyAssignmentOperatorTest(){
		MyClass cls;
		cls = CopyClass(cls); // ���ÿ�����ֵ�����
	}

	MyClass CopyClass(MyClass cls){
		cout << "call by value" << endl;

		MyClass newCls = cls;

		return newCls;
	}

	MyClass CopyClass(string s){
		MyClass cls = s;	// �ȵ���conveting constructor, �ٵ���copy constructor

		return cls;
	}
	

}