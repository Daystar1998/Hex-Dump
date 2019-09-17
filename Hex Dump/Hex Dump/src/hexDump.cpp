/******************************************************************************
	Name: hexDump.cpp

	Des:
		This program will read a binary file and output the hex dump

	Author: Matthew Day

	Due Date: 9/20/2019
******************************************************************************/

#include <fstream>
#include<iostream>
#include<string>

using namespace std;

/******************************************************************************
		Name: readBinaryFile

		Des:
			Reads data from a binary file

		Params:
			fileName - type string &, the name of the file

		Return:
			type unsigned char *, the binary data

******************************************************************************/
unsigned char *readBinaryFile(string &fileName) {

	unsigned char *buffer;

	ifstream fin(fileName, ios::in | ios::binary | ios::ate);

	if (fin.is_open()) {

		int sizeOfFile = (int)fin.tellg();

		try {

			buffer = new unsigned char[sizeOfFile];
		} catch (bad_alloc&) {

			cout << "Error: Unable to allocate buffer" << endl;
			exit(EXIT_FAILURE);
		}

		fin.seekg(0, ios::beg);
		fin.read((char *)buffer, sizeOfFile);

		fin.close();
	} else {

		cout << "Error: Unable to open file: " << fileName << endl;
		exit(EXIT_FAILURE);
	}

	return buffer;
}

int main() {

	string fileName = "";

	do {

		getline(cin, fileName);
	} while (fileName == "");

	unsigned char *buffer = readBinaryFile(fileName);

	return 0;
}