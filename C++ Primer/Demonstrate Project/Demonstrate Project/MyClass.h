/****************************************************

****************************************************/
#include <string>
#include <memory>

namespace Learn{

	class MyClass{
	public:

		friend void swap(MyClass&, MyClass&);

		MyClass();

		MyClass(std::string);

		MyClass(const MyClass&);

		MyClass(MyClass&&);

		MyClass& operator=(MyClass);

		~MyClass();
		
		int i;
	private:
	};

	void CopyConstructorTest();
	void CopyAssignmentOperatorTest();
	std::shared_ptr<MyClass> SmartMemoryTest();
	MyClass* DynamicMemoryTest();

	MyClass CopyClass(MyClass);

	MyClass CopyClass(std::string);

}