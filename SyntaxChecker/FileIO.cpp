#include <iostream>
#include <fstream>
#include "FileIO.h"

using namespace std;
FileIO::FileIO()
{
	inputFile.open("");
	outputFile.open("");
}
FileIO::FileIO(string inputName, string outputName)
{
	inputFile.open(inputName);
	outputFile.open(outputName);
}
FileIO::FileIO(string inputName)
{
	inputFile.open(inputName);
}
FileIO::~FileIO()
{
	inputFile.close();
	outputFile.close();
}
void FileIO::openINFile(string fileName)
{
	inputFile.close();
	inputFile.open(fileName);
}
void FileIO::openOUTFile(string fileName)
{
	outputFile.close();
	outputFile.open(fileName);
}
string FileIO::readFile()
{
	string currentLine;
	while (getline(inputFile,currentLine))
	{
		return currentLine;
	}
}
string FileIO::readFile(string fileName)
{
	openINFile(fileName);
	string currentLine;
	while (getline(inputFile,currentLine))
	{
		return currentLine;
	}
}
void FileIO::writeFile(string output)
{
	if(outputFile.is_open())
	{
		outputFile << output << endl;
	}	
	else
		cout << "No file to output to. Please open an output file." << endl;
}
void FileIO::writeFile(string fileName, string output)
{
	openOUTFile(fileName);
	outputFile << output << endl;
}