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
		cout << "call constructor MyClass()" << endl;
	}

	MyClass::MyClass(int j)
		: i(j)
		, privateI(j)
	{}

	MyClass::MyClass(const MyClass& cls)
		: i(cls.i)
		, privateI(cls.privateI)
	{
		WriteLog("Call copy constructor", "log.txt");
		
		cout << "Call copy constructor" << endl;
	}

	MyClass::MyClass(string s){
		WriteLog("Call constructor MyClass(string)", "log.txt");
		cout << "Call constructor MyClass(String)" << endl;
	}

	MyClass::MyClass(MyClass&& cls){
		WriteLog("Call move constructor", "log.txt");
		cout << "call move constructor" << endl;
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

	void MyClass::Fun(MyClass cls)
	{
		cout << cls.privateI << endl;
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
		CopyClass(cls); // ���ÿ�����ֵ�����
		MyClass cls1;
		cls1 = std::move(cls);
	}

	void MoveClassTest()
	{
		MyClass cls;
		MoveClass3(cls);
		MoveClass3(std::move(cls));
	}

	void MoveClass1(MyClass&& cls)
	{
		
	}

	void MoveClass2(MyClass&& cls)
	{

	}

	void MoveClass3(MyClass cls)
	{

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