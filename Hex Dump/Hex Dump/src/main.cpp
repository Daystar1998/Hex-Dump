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