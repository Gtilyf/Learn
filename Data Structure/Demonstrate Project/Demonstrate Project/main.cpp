/*
*/

#include "SequentialLineraList.hpp"

using namespace std;

int main(){
	DS::SqList<string> sl;
	

	DS::SqList<string> sl1 = sl;

	sl1.Union(sl);

	cout << sl.Size() << endl;

	getchar();
	return 0;
}