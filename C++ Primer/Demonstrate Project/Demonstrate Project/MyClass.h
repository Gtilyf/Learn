/****************************************************

****************************************************/
#include <string>
#include <memory>

namespace Learn{

	class MyClass{
	public:

		friend void swap(MyClass&, MyClass&);

		MyClass();
		MyClass(int j);

		MyClass(std::string);

		MyClass(const MyClass&);

		MyClass(MyClass&&);

		MyClass& operator=(MyClass);

		~MyClass();

		void Fun(MyClass);

		int i;
	private:
		int privateI;
	};

	void CopyConstructorTest();
	void CopyAssignmentOperatorTest();
	std::shared_ptr<MyClass> SmartMemoryTest();
	MyClass* DynamicMemoryTest();

	MyClass CopyClass(MyClass);
	void MoveClass1(MyClass&&);
	void MoveClass2(MyClass&&);
	void MoveClass3(MyClass);

	void MoveClassTest();

	MyClass CopyClass(std::string);

}