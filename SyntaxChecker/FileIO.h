#include <iostream>
#include <fstream>
#ifndef FILEIO_H
#define FILEIO_H
using namespace std;

class FileIO
{
public:
	FileIO(); //default constructor
	FileIO(string inputName, string outputName); //opens two files to read and write from
	FileIO(string inputName); //read only
	~FileIO();
	void openINFile(string fileName); //changes the input file
	void openOUTFile(string fileName); //changes the output file
	string readFile(); //parses through file and returns line
	string readFile(string fileName); //parses through specific file'
	void writeFile(string output); //writes  a string to prev opened file
	void writeFile(string fileName, string output); //writes a string to a specific file
	ifstream inputFile;
	ofstream outputFile;
};

#endif