#include "AccessControl.h"
#include <iostream>

using namespace std;

A::A(){
	cout << "constructor A()" << endl;
}

A::A(int i)
	: publicA(i)
{
	cout << "constructor A(int)" << endl;
}

A::A(const A& a){
	cout << "copy constructor A(const A&)" << endl;
}

A::A(A&& a){
	cout << "move constructor A(A&&)" << endl;
}

A& A::operator=(A a){
	cout << "assignment function A" << endl;
	return *this;
}

void Fun(B b){
	int a = b.publicA;
	a = b.protectedA;
}

void Fun(C c){
	int a = c.protectedA;
	a = c.publicA;
}

void Fun(D d){
	d.protectedA;
	d.publicA;
}