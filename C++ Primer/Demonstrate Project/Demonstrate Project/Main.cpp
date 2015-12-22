#include "MyClass.h"
#include <stdio.h>
#include <iostream>
#include <utility>
#include "AccessControl.h"
#include <vector>

using namespace std;

void Fun(shared_ptr<int> p){
	cout << p.use_count() << endl;
}

void Fun(unique_ptr<int> p){
	
}

int main(){

	Learn::MyClass cls(3);

	Learn::MyClass cls1;
	cls1.Fun(cls);

	//Learn::MoveClassTest();

	//vector<int> v = {1, 2, 3};

	//cout << v[1] << endl;

	//Learn::CopyAssignmentOperatorTest();
	//Learn::CopyConstructorTest();

	/*Learn::MyClass* cls = Learn::DynamicMemoryTest();

	cout << cls->i << endl;*/

	//int* a(new int(3));

	///*shared_ptr<int> p(a);

	//shared_ptr<int> q(a);*/

	//shared_ptr<int> p(a);
	//shared_ptr<int> q = make_shared<int>(*a);

	/*p = make_shared<int>(2);*/

	//p.reset();

	//cout << *q << endl;

	/*Fun(unique_ptr<int>(a));*/

	//int i = 1;
	//B b;
	////B b1(b);
	//B b2(std::move(b));

	//b = b1;

	getchar();

	return 0;
}