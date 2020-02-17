#include <iostream>
#include <fstream>
#ifndef SYNTAXCHECKER_H
#define SYNTAXCHECKER_H
#include "GenStack.h"
#include "FileIO.h"
using namespace std;

class SyntaxChecker
{
public:
	SyntaxChecker(); //default constructor
	SyntaxChecker(string fileName); //constructor
	~SyntaxChecker();
	bool checkMatching(char open, char close); //checks if delimeters are pairs
	bool checkEmpty(); //check if stack is empty and act accordingly
	int findDelimiters(); //locates delimeters and pushes/pops from stack if found
	void displayErrors(int line, char open, char close, int type);
	int lineCounter;
	FileIO *fileReader;
	GenStack<char> *delimStack;
	GenStack<int> *lineStack;
};
#endif