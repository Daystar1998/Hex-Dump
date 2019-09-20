/******************************************************************************
	Name: hexDump.cpp

	Des:
		This program will read a binary file and output the hex dump

	Author: Matthew Day

	Due Date: 9/20/2019
******************************************************************************/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

/******************************************************************************
		Name: readBinaryFile

		Des:
			Reads data from a binary file

		Params:
			fileName - type string &, the name of the file
			oDataLength - type int &, output the number of bytes in the data

		Return:
			type unsigned char *, the binary data

******************************************************************************/
unsigned char *readBinaryFile(string &fileName, int &oDataLength) {

	unsigned char *buffer;

	ifstream fin(fileName, ios::in | ios::binary | ios::ate);

	if (fin.is_open()) {

		int sizeOfFile = (int)fin.tellg();

		try {

			buffer = new unsigned char[sizeOfFile];
		} catch (bad_alloc) {

			cout << "Error: Unable to allocate buffer" << endl;
			exit(EXIT_FAILURE);
		}

		oDataLength = sizeOfFile;

		fin.seekg(0, ios::beg);
		fin.read((char *)buffer, sizeOfFile);

		fin.close();
	} else {

		cout << "Error: Unable to open file: " << fileName << endl;
		exit(EXIT_FAILURE);
	}

	return buffer;
}

/******************************************************************************
		Name: printHexDump

		Des:
			Print hex dump of the data to a file

		Params:
			fileName - type string &, the name of the original file
			data - type unsigned char *, the data to be printed
			dataLength - type int, length of the data

******************************************************************************/
void printHexDump(string &fileName, unsigned char *data, int dataLength) {

	string outputFileName = fileName.substr(0, fileName.find_last_of('.')) + ".dmp";

	ofstream fout(outputFileName, ios::out);

	if (!fout.bad()) {

		fout << "HEX DUMP FOR FILE: " << fileName << endl;

		string asciiOutput = "";

		for (int i = 0; i < dataLength; i++) {

			if (i % 16 == 0) {

				fout << "  " << asciiOutput << endl;
				asciiOutput = "";
				fout << hex << setw(8) << setfill('0') << uppercase << i << ": ";
			}

			fout << ' ' << hex << setw(2) << setfill('0') << uppercase << (int)data[i];

			// Non-printable characters are replaced with '.'
			if ((int)data[i] < 31 || (int)data[i] > 126) {

				asciiOutput += '.';
			} else {

				asciiOutput += (int)data[i];
			}
		}

		if (asciiOutput != "") {

			if (dataLength % 16 != 0) {

				// Align with other ascii sections
				for (int i = 0; i < 16 - (dataLength % 16); i++) {

					fout << "   ";
				}
			}

			fout << "  " << asciiOutput << endl;
		}
	} else {

		cout << "Error: Unable to write to file: " << outputFileName << endl;
		fout.close();
		exit(EXIT_FAILURE);
	}

	fout.close();
}

int main() {

	string fileName = "";

	do {

		cout << "Enter file name: ";

		getline(cin, fileName);
	} while (fileName == "");

	int dataLength;

	unsigned char *data = readBinaryFile(fileName, dataLength);

	printHexDump(fileName, data, dataLength);

	delete data;

	return 0;
}