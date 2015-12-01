#include "MyClass.h"
#include <stdio.h>
#include <iostream>
#include <utility>

using namespace std;

void Fun(shared_ptr<int> p){
	cout << p.use_count() << endl;
}

int main(){

	//Learn::CopyAssignmentOperatorTest();
	//Learn::CopyConstructorTest();

	/*Learn::MyClass* cls = Learn::DynamicMemoryTest();

	cout << cls->i << endl;*/

	int* a(new int(3));

	/*shared_ptr<int> p(a);

	shared_ptr<int> q(a);*/

	shared_ptr<int> p = make_shared<int>(*a);
	shared_ptr<int> q = p;

	p = make_shared<int>(2);

	cout << q.use_count() << endl;

	getchar();

	return 0;
}