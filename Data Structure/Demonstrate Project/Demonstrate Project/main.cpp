#include "SequentialLineraList.hpp"
#include "LinkedLineraList.hpp"

using namespace std;
using namespace DS;


int main()
{
	SqList<int> sl = {1, 2, 3, 4};
	LinkedList<int> ll = { 1, 2, 3, 4 };

	sl.push_back(5);
	sl.push_front(0);

	auto ptr = ll.push_back(5);
	ll.push_front(8);

	sl.erase(2);

	sl.Traverse();
	ll.Traverse();

	//ll.erase(ptr);

	//ll.Traverse();

	ll.insert(ptr, 2, 9);
	ll.Traverse();

	getchar();
	return 0;
}
