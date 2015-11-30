#include "FileUtility.h"

using namespace std;

void WriteLog(string log, string logFileName){
	ofstream out(logFileName, ofstream::app);

	out << log << endl;

	out.close();
}