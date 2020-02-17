#include <iostream>
#include <fstream>
#include "SyntaxChecker.h"
#include "FileIO.h"

using namespace std;
SyntaxChecker::SyntaxChecker()
{
	fileReader = new FileIO();
	delimStack = new GenStack<char>(1);
	lineStack = new GenStack<int>(1);
}
SyntaxChecker::SyntaxChecker(string fileName)
{
	fileReader = new FileIO(fileName);
	delimStack = new GenStack<char>(1);
	lineStack = new GenStack<int>(1);
}
SyntaxChecker::~SyntaxChecker()
{
	delete fileReader;
	delete delimStack;
	delete lineStack;
}

void SyntaxChecker::displayErrors(int line, char open, char close, int type)
{
	cout << "Error found at line: " << line << endl;
	if (type == 1) 
	{
		if(open == '(')
			cout << "\tExpected ')' and found \'" << close << "\'" << endl;
		else if(open == '{')
			cout << "\tExpected '}' and found \'" << close << "\'" << endl;
		else if(open == '[')
			cout << "\tExpected ']' and found \'" << close << "\'" << endl;
	}
	else if (type == 2)
	{
		// cout << "\tNo opening delimeter for '" << close << "'" << endl;
		if (close == ')')
			cout << "\t')' used with no '('" << endl;
		else if (close == '}')
			cout << "\t'}' used with no '{'" << endl;
		else if (close == ']')
			cout << "\t']' used with no '['" << endl;
	}
	else if (type == 3)
	{
		cout << "\tNo closing delimeter for '" << open << "'" << endl;
	}
}

/*
bool checkMatching(char c, char d)
takes two characters as parameters and checks to see if they are pairs
returns true if they are a pair
order of input matters
*/
bool SyntaxChecker::checkMatching(char open, char close)
{
	if(open == '(' && close != ')')
		return false;
	else if(open == '{' && close != '}')
		return false;
	else if(open == '[' && close != ']')
		return false;
	else
		return true;
}
/*
int findDelimeters(string fileName, GenStack stack)
pushes to stack if opening delimeter is found
pops from stack if closing delimeter is found
compares popped value and current value using "checkMatching"
checks if stack isn't empty after reading entire file
returns 0 if an erorr was found, 1 if no errors found
*/
int SyntaxChecker::findDelimiters()
{
	char currentChar;
	char tempChar;
	bool isMatch;
	bool sawQuotes = false;
	bool passedCheck = true;
	int lineCounter = 1;
	string currentLine;

	while (!fileReader->inputFile.eof())
	{
		currentLine = fileReader->readFile();

		for(int i=0;i<currentLine.size();++i)
		{
			currentChar = currentLine[i];

			if (currentChar == '\'' or currentChar == '"') //ignore characters that are in strings
			{
				if (sawQuotes == false)
					sawQuotes = true;
				else
					sawQuotes = false;
			}

			if (sawQuotes == false) //only consider characters that are not enclosed in a string
			{
				if(currentChar == '(')
				{
					delimStack->push(currentChar);
					lineStack->push(lineCounter);
				}
				else if(currentChar == '{')
				{
					delimStack->push(currentChar);
					lineStack->push(lineCounter);
				}
				else if(currentChar == '[')
				{
					delimStack->push(currentChar);
					lineStack->push(lineCounter);
				}
			

				else if(currentChar == ')')
				{
					if(!delimStack->isEmpty()) //if an opening delimeter was found earlier, check if they are pairs
					{
						tempChar = delimStack->pop();
						isMatch = checkMatching(tempChar, currentChar);
					}
					else //no opening delimeter was found, so theres an erorr
					{
						displayErrors(lineCounter, '\0', currentChar, 2);
						passedCheck = false;
					}
				}
				else if(currentChar == '}')
				{
					if(!delimStack->isEmpty())
					{
						tempChar = delimStack->pop();
						isMatch = checkMatching(tempChar, currentChar);
					}
					else
					{
						displayErrors(lineCounter, '\0', currentChar, 2);
						return 0;
						passedCheck = false;
					}
				}
				else if(currentChar == ']')
				{
					if(!delimStack->isEmpty())
					{
						tempChar = delimStack->pop();
						isMatch = checkMatching(tempChar, currentChar);
					}
					else
					{
						displayErrors(lineCounter, '\0', currentChar, 2);
						return 0;
						passedCheck = false;
					}
				}
			}
			if(isMatch == false && tempChar != '\0') //if they werent a match, display what the error was and where
			{
				// cout << tempChar << endl;
				// cout << currentChar << endl;
				displayErrors(lineCounter, tempChar, currentChar, 1);
				passedCheck = false;
			}
			else if (isMatch == true){
				// cout << "match was found on line " << lineCounter<< endl;
			}
		}

		lineCounter +=1;
	}

	if(!checkEmpty())
		passedCheck = false;

	if (passedCheck == true)
		return 1;
	else
		return 0;
}

bool SyntaxChecker::checkEmpty()
{
	if(!delimStack->isEmpty()) //if after reaching the end of the file and not every delimeter had a pair
	{
		while(!delimStack->isEmpty())
		{
			displayErrors(lineStack->pop(), delimStack->pop(), '\0', 3);
		}
		return false;
	}
	else
		return true;
}