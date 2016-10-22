#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int load(string);

int main(int argc, const char * argv[]) {

	cout << "   loading...." << endl;
	load("cse018.ptx");
	cout << endl;
	cout << "	back to main...." << endl;

	return 0;
}

int load(string filename) {
	ifstream file;
	file.open(filename);
	if (!file.is_open()) {
		cout << "cannot open the file" << endl;
		return -1;
	}
	//while (file) {
	int counter = 0;
	cout << "  can open the file......start printing the lines" << endl;
	while (counter < 20) {
		string line;
		getline(file, line);		//get line until space

		cout << line << endl;

		//istringstream parse(line);

		//string number;
		//for (number; parse >> number;) {		//iterate over words in a line.
		//do something to 4 parameters in each line
		//
		//}
		counter++;
	}
	cout << "end of the printing " << endl;
	file.close();

	return 0;
}