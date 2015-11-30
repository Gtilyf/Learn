#include "MyClass.h"
#include <stdio.h>
#include <iostream>
#include <utility>

using namespace std;

int main(){

	//Learn::CopyAssignmentOperatorTest();
	//Learn::CopyConstructorTest();

	Learn::MyClass* cls = Learn::DynamicMemoryTest();

	cout << cls->i << endl;

	getchar();
	return 0;
}