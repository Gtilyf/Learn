#include "SequentialLineraList.hpp"
#include "LinkedLineraList.hpp"
#include "stack.hpp"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace DS;


int main()
{
	SqList<int> sl = { 1, 2, 3, 4 };

	auto begin = sl.begin();

	cout << *begin << endl;

	sl.insert(begin, 9);

	sl.Traverse([](int i) { cout << i << "\t"; });

	getchar();
	return 0;
}
