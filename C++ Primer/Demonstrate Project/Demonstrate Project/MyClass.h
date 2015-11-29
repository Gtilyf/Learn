/****************************************************

****************************************************/
#include <string>

namespace Learn{

	class MyClass{
	public:

		friend void swap(MyClass&, MyClass&);

		MyClass();

		MyClass(std::string);

		MyClass(const MyClass&);

		MyClass(MyClass&&);

		MyClass& operator=(MyClass);
		
	private:
	};

	void CopyConstructorTest();
	void CopyAssignmentOperatorTest();

	MyClass CopyClass(MyClass);

	MyClass CopyClass(std::string);

}