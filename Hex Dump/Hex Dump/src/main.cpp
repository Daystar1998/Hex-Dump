/******************************************************************************
	Name: main.cpp

	Des:
		This program will read a binary file and output the hex dump

	Author: Matthew Day

	Due Date: 9/20/2019
******************************************************************************/

#include<iostream>
#include<string>

using namespace std;

int main() {

	string fileName = "";

	do {

		getline(cin, fileName);
	} while (fileName == "");

	return 0;
}