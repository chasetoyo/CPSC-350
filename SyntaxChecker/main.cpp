#include <stdlib.h>
#include "GenStack.h"
#include "FileIO.h"
#include "SyntaxChecker.h"
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char const *argv[])
{ 
	string fileName = argv[1];
	SyntaxChecker check(fileName);
	int result; //1 if no erorrs, 0 if error
	char choice;

	result = check.findDelimiters();
	while(result == 1) //while no errors were found 
	{
		cout << "No errors found." << endl;
		cout << "Would you like to analyze another file? y/n" << endl;
		cin >> choice;
		while(choice != 'y' && choice != 'n') 
		{
			cout << "Invalid choice. Please re enter choice." << endl;
			cin >> choice;
		}
		if(choice == 'y')
		{
			cout << "Enter name of file you would like to analyze" << endl;
			cin >> fileName;
			check.fileReader->openINFile(fileName);
		}
		else if(choice == 'n') //exits if choice is no 
		{
			cout << "Bye!" << endl;
			return 1;
		}
		result = check.findDelimiters(); //set result again
	}
	return 1;
}