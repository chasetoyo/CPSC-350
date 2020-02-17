#include "DNA.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

DNA::DNA() //method prefixed with name of class, then name of function
				//default constructor
{
	resetValues();
}

/*reads the input file and creates two strings of the DNA, one separated by periods.
also calculates sum, mean*/
void DNA::readDNA(string theInputFile, string theLine)
{
	ifstream inputFile;
	inputFile.open(theInputFile);
	while (getline(inputFile, theLine))
	{
		totalString += theLine;
		csvTotalString = csvTotalString + theLine + '.';
		currentString = theLine;
		lineCounter +=1;
		currentSum = currentString.size();
		totalSum += currentSum;
	}
	averageLen = totalSum/lineCounter;
}
/*takes a character and appends it to a string of the entire sequence
also calculates the probabilities of each nucleotide as it adds
*/
void DNA::writeDNA(char c)
{
	totalString += c;
	readString(totalString, false);
	countProbability(totalString);
}

/*uses the value created by the above method.
counts the occurences of each nucleotide
also calculates nucelotide probability, variance, and standard deviation
boolean to check whether the string is normal or a csv*/
void DNA::readString(string csvString, bool isCSV)
{
	int csv = 0;
	char c;
	if(isCSV == true)
	{
		for (int i=0;i<csvString.size();i++)
		{
			c = csvString[i];
			c = toupper(c);
			upperSequence += c; //making everything uppercase
			csv += 1;
			if (csvString[i] == '.') //calculating variance
			{
				csv -=1;
				variancePoint = (averageLen - csv)*(averageLen - csv);
				totalVariance += variancePoint;
				csv = 0;
			}
			else if (c == 'A')
				aCount += 1;
			else if (c == 'T')
				tCount += 1;
			else if (c == 'C')
				cCount += 1;
			else if (c == 'G')
				GCount += 1;
		}
		totalVariance /= (lineCounter-1);
		standardDeviation = sqrt(totalVariance);
	}
	else //if the string isnt a csv
	{
		currentSum = 0;
		totalSum = 0;
		for (int i=0;i<csvString.size();i++)
		{
			c = csvString[i];
			c = toupper(c);
			upperSequence += c; //making everything uppercase
			currentSum = csvString.size();
			totalSum += currentSum;
			if (c == 'A')
				aCount += 1;
			else if (c == 'T')
				tCount += 1;
			else if (c == 'C')
				cCount += 1;
			else if (c == 'G')
				GCount += 1;
		}
	}
}
/*counts the probability of each bigram
given the entire sequence as an input*/
void DNA::countBigram(string totalString)
{
	string theString = "";
	for (int i=0;i<totalString.size();i+=2) //because we are looking at pairs, index every 2
		{
			theString = toupper(totalString[i]);
			theString += toupper(totalString[i+1]); //i+1 to get the pairs

			//16 possible combinations of legit nucleotides
			if(theString == "AA") //all cases with a first
			{
				aaCount +=1;
			}
			else if (theString == "AT")
			{
				atCount +=1;
			}
			else if (theString == "AC")
			{
				acCount +=1;
			}
			else if (theString == "AG")
			{
				agCount +=1;
			}
			else if (theString == "TA") //all cases with t first
			{
				taCount +=1;
			}
			else if (theString == "TT")
			{
				ttCount +=1;
			}
			else if (theString == "TC")
			{
				tcCount +=1;
			}
			else if (theString == "TG")
			{
				tgCount +=1;
			}
			else if (theString == "CA") //all cases with c first
			{
				caCount +=1;
			}
			else if (theString == "CT")
			{
				ctCount +=1;
			}
			else if (theString == "CC")
			{
				ccCount +=1;
			}
			else if (theString == "CG")
			{
				cgCount +=1;
			}
			else if (theString == "GA") //all cases with g first
			{
				gaCount +=1;
			}
			else if (theString == "GT")
			{
				gtCount +=1;
			}
			else if (theString == "GC")
			{
				gcCount +=1;
			}
			else if (theString == "GG")
			{
				ggCount +=1;
			}
			theString = ""; //reset the string because its a new pair for the next index
		}
}
/*basic calculations to get numbers required for output
takes the entire sequence as an input*/
void DNA::countProbability(string totalString)
{
	//nucleotide probabilities 
	aProbability = (aCount/totalSum);
	tProbability = (tCount/totalSum);
	cProbability = (cCount/totalSum);
	GProbability = (GCount/totalSum); 
	//bigram probabilities
	aaProbability = aaCount/(totalString.size()/2);
	atProbability = atCount/(totalString.size()/2);
	acProbability = acCount/(totalString.size()/2);
	agProbability = agCount/(totalString.size()/2);
	taProbability = taCount/(totalString.size()/2);
	ttProbability = ttCount/(totalString.size()/2);
	tcProbability = tcCount/(totalString.size()/2);
	tgProbability = tgCount/(totalString.size()/2);
	caProbability = caCount/(totalString.size()/2);
	ctProbability = ctCount/(totalString.size()/2);
	ccProbability = ccCount/(totalString.size()/2);
	cgProbability = cgCount/(totalString.size()/2);
	gaProbability = gaCount/(totalString.size()/2);
	gtProbability = gtCount/(totalString.size()/2);
	gcProbability = gcCount/(totalString.size()/2);
	ggProbability = ggCount/(totalString.size()/2);
}

/*appending the important results to output file*/
void DNA::writeResults(string theOutputFile)
{
	ofstream outputFile;
	outputFile.open(theOutputFile);
	outputFile << "Sum of sequence lengths: " << totalSum << endl;
	outputFile << "Number of lines: " << lineCounter << endl;
	outputFile << "Length mean: " << averageLen <<endl;
	outputFile << "Variance: " << totalVariance << endl;
	outputFile << "Standard Deviation: " << standardDeviation << endl;
	outputFile << "----------Nucleotide---------"<< endl;
	outputFile << "A: " << aProbability << endl << "T: " << tProbability << endl << "C: " << cProbability << endl << "G: " << GProbability << endl;
	outputFile << "----------Bigram--------" << endl;
	outputFile << "aa: " << aaProbability << endl;
	outputFile << "at: " << atProbability << endl;
	outputFile << "ac: " << acProbability << endl;
	outputFile << "ag: " << agProbability << endl;
	outputFile << "ta: " << taProbability << endl;
	outputFile << "tt: " << ttProbability << endl;
	outputFile << "tc: " << tcProbability << endl;
	outputFile << "tg: " << tgProbability << endl;
	outputFile << "ca: " << caProbability << endl;
	outputFile << "ct: " << ctProbability << endl;
	outputFile << "cc: " << ccProbability << endl;
	outputFile << "cg: " << cgProbability << endl;
	outputFile << "ga: " << gaProbability << endl;
	outputFile << "gt: " << gtProbability << endl;
	outputFile << "gc: " << gcProbability << endl;
	outputFile << "gg: " << ggProbability << endl;
	outputFile.close();
}

/*this is used for the newly generated sequence
takes the name of the output file and the sequence as input
appends the squence to the end of the file provided*/
void DNA::appendDNA(string theOutputFile, string theText)
{
	ofstream outputFile;
	outputFile.open(theOutputFile, ios_base::app); //append to a file rather than overwrite
	outputFile << theText << endl;
	outputFile.close();
}

/*resets all the values, used in beginning of main*/
void DNA::resetValues()
{
	aCount = 0;
	tCount = 0;
	cCount = 0;
	GCount = 0;

	aaCount = 0;
	atCount = 0;
	acCount = 0;
	agCount = 0;
	taCount = 0;
	ttCount = 0;
	tcCount = 0;
	tgCount = 0;
	caCount = 0;
	ctCount = 0;
	ccCount = 0;
	cgCount = 0;
	gaCount = 0;
	gtCount = 0;
	gcCount = 0;
	ggCount = 0;

	lineCounter = 0;
	totalSum = 0;
	averageLen = 0;
	totalVariance = 0;
	standardDeviation = 0;
	variancePoint = 0;
}

string DNA::generateString(DNA* otherDNA, int lineLen)
{
	int nucleoChoice = 0;
	char currentNucleo = '\0';
	string currentLine = "";
	for (int i = 0; i < lineLen; ++i) //until the length from the gaussian distribution is met
	{
		nucleoChoice = rand()%4 + 1; //randomly pick a choice 1-4

		switch(nucleoChoice)
		{
			case 1: //if its 1
				nucleoChoice = rand()%3 + 1; //1-3 to be used if (below) probability is greater
				if(otherDNA->aProbability <= aProbability) //and the current A percentage is less than the analyzed A percentage
				{
					currentNucleo = 'A';
					currentLine += 'A';
					otherDNA->writeDNA(currentNucleo); //add it to the sequence 
				}
				else if(nucleoChoice == 1 && otherDNA->tProbability < tProbability) //if its greater, then randomly pick a different letter
				{
					currentNucleo = 'T';
					currentLine += "T";
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 2 && otherDNA->cProbability < cProbability) //all checking for the same conditions before it adds
				{
					currentNucleo = 'C';
					currentLine += "C";
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 3 &&otherDNA->GProbability < GProbability)
				{
					currentNucleo = 'G';
					currentLine += "G";
					otherDNA->writeDNA(currentNucleo);
				}
				else
				{
					currentNucleo = 'A';
					currentLine += 'A';
					otherDNA->writeDNA(currentNucleo); //add it to the sequence 
				}
				break;

			case 2:
				nucleoChoice = rand()%3 + 1;
				if(otherDNA->tProbability <= tProbability) //repeat of above
				{
					currentNucleo = 'T';
					currentLine += "T";
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 1 && otherDNA->aProbability < aProbability)
				{
					currentNucleo = 'A';
					currentLine += 'A';
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 2 && otherDNA->cProbability < cProbability)
				{
					currentNucleo = 'C';
					currentLine += "C";
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 3 && otherDNA->GProbability < GProbability)
				{
					currentNucleo = 'G';
					currentLine += "G";
					otherDNA->writeDNA(currentNucleo);
				}
				else
				{
					currentNucleo = 'T';
					currentLine += 'T';
					otherDNA->writeDNA(currentNucleo); //add it to the sequence 
				}
				break;

			case 3:
				nucleoChoice = rand()%3 + 1;
				if(otherDNA->cProbability < cProbability)
				{
					currentNucleo = 'C';
					currentLine += "C";
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 1 && otherDNA->aProbability < aProbability)
				{
					currentNucleo = 'A';
					currentLine += 'A';
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 2 && otherDNA->tProbability < tProbability)
				{
					currentNucleo = 'T';
					currentLine += "T";
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 3 && otherDNA->GProbability < GProbability)
				{
					currentNucleo = 'G';
					currentLine += "G";
					otherDNA->writeDNA(currentNucleo);
				}
				else
				{
					currentNucleo = 'C';
					currentLine += 'C';
					otherDNA->writeDNA(currentNucleo); //add it to the sequence 
				}
				break;
				
			case 4:
				nucleoChoice = rand()%3 + 1;
				if(otherDNA->GProbability <= GProbability)
				{
					currentNucleo = 'G';
					currentLine += "G";
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 1 && otherDNA->aProbability < aProbability)
				{
					currentNucleo = 'A';
					currentLine += 'A';
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 2 && otherDNA->cProbability < cProbability)
				{
					currentNucleo = 'C';
					currentLine += "C";
					otherDNA->writeDNA(currentNucleo);
				}
				else if(nucleoChoice == 3 && otherDNA->tProbability < tProbability)
				{
					currentNucleo = 'T';
					currentLine += "T";
					otherDNA->writeDNA(currentNucleo);
				}
				else
				{
					currentNucleo = 'G';
					currentLine += 'G';
					otherDNA->writeDNA(currentNucleo); //add it to the sequence 
				}
				break;
		}
	}
	return currentLine; //returns the dna sequence for one line
}