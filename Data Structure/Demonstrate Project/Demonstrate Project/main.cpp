/*
*/

#include "SequentialLineraList.hpp"
#include "LinkedLineraList.hpp"

using namespace std;
using namespace DS;

void PrintList(SqList<int>& sl);

int main(){
	LinkedList<int> ll = {1, 2};

	// ≤‚ ‘ SequentiaLineraList
	SqList<int> sl;
	sl.FrontInsert(2);
	sl.FrontInsert(1);
	sl.BackInsert(3);

	PrintList(sl);

	sl.Remove(2);
	PrintList(sl);

	cout << sl.LocalElem(2);

	SqList<int> sl1 = {4, 5, 6};
	PrintList(sl1);

	sl += sl1;
	PrintList(sl);

	getchar();
	return 0;
}

void PrintList(SqList<int>& sl)
{
	for (int i = 0; i < sl.Size(); i++)
		cout << sl[i] << " ";

	cout << endl;
}