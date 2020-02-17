#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <math.h>
#include "DNA.h"

using namespace std;

//generating the length based on a gaussian distribution
double generateLength(double standardDeviation, double averageLen)
{
	const double PI = 3.14159265358979323846;
	double ranA, ranB, ranC, ranD, theLog, theCos;
	ranA = rand() / (RAND_MAX + 1.);
	ranB = rand() / (RAND_MAX + 1.);
	while (ranB > .25 || ranB < -.25)
	{
		ranB = rand() / (RAND_MAX + 1.);
	}
	ranC = sqrt((-2.0)*(log(ranA))*cos(2*PI*ranB));
	ranD = (standardDeviation*ranC) + averageLen;
	return ranD;
}

int main(int argc, char** argv)
{
	srand (time(NULL)); //randomizes the seed
	ifstream inputFile;
	ofstream outputFile;
	
	string line = "";
	string inName = argv[1];
	string outName = "output.txt";
	string newDNA;
	string choice = "Y"; //start with the choice that the user wants to process a list, uses command line for intiial file name
	int lineLen = 0;

	DNA *initialDNA = new DNA;
	DNA *nextDNA = new DNA;

	outputFile.open(outName);
	outputFile.close();

	while(choice == "Y")
	{
		cout << "Processing..." << endl;

		initialDNA->readDNA(inName,line);
		initialDNA->readString(initialDNA->csvTotalString, true);
		initialDNA->countBigram(initialDNA->totalString);
		initialDNA->countProbability(initialDNA->totalString);
		initialDNA->writeResults(outName);
		
		for (int i=0;i<1000;i++) //generate 1000 strings
		{
			
			lineLen = generateLength(initialDNA->standardDeviation, initialDNA->averageLen); //gaussian distribution length
			newDNA = initialDNA->generateString(nextDNA, lineLen); //creates a string based on the length above
			nextDNA->appendDNA(outName, newDNA); //appends to the outfile
			if(i==999)
				nextDNA->appendDNA(outName, "\n----------------------------------------------------\n");
		}
		cout << "Would you like to process another list? (Y / N)";
		cin >> choice;
		if(choice != "Y")
			cout << "Goodbye!" << endl;
		else
		{
			cout << "What file would you like to read from?";
			cin >> inName;
		}	
	}
	
	return 0;
}