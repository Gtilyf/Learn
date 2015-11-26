/****************************************************

****************************************************/
#include <string>

using namespace std;

namespace Learn{

	class MyClass{
	public:

		friend void swap(MyClass&, MyClass&);

		MyClass();

		MyClass(string);

		MyClass(const MyClass&);

		MyClass& operator=(MyClass);
		
	private:
	};

	void swap(MyClass&, MyClass&);

	void CopyConstructorTest();
	void CopyAssignmentOperatorTest();

	MyClass CopyClass(MyClass);

	MyClass CopyClass(string);

}