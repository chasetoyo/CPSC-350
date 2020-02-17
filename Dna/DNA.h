#include <iostream>
#include <fstream>
using namespace std;

class DNA
{
	public:
		double aaCount, atCount, acCount, agCount, taCount, ttCount, tcCount, tgCount,
		caCount, ctCount, ccCount, cgCount, gaCount, gtCount, gcCount, ggCount;
		
		double aaProbability, atProbability, acProbability, agProbability,
		 taProbability, ttProbability, tcProbability, tgProbability,
		 caProbability, ctProbability, ccProbability, cgProbability,
		 gaProbability, gtProbability, gcProbability, ggProbability;
		
		double aCount, tCount, cCount, GCount;

		double aProbability, tProbability, cProbability, GProbability;

		string totalString, csvTotalString, currentString, upperSequence;

		double lineCounter, currentSum, totalSum;

		double variancePoint, totalVariance, averageLen, standardDeviation;

		DNA();
		void resetValues();
		void writeDNA(char c);
		void writeResults(string theInputFile);
		void appendDNA(string theOutputFile, string text);
		void readString(string csvString, bool isCSV);
		void readDNA(string theInputFile, string theLine);
		void countBigram(string totalString);
		void countProbability(string totalString);
		string generateString(DNA* otherDNA, int lineLen);
};