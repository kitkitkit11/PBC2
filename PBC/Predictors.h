#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <bitset>

// An unsigned char can store 1 Bytes (8bits) of data (0-255)
typedef unsigned char BYTE;

class Predictors
{
public: 
	long fileSize;
	BYTE *fileBuffer;
	/*	0 - NONE(8)
		1 - NONE(16)
		2 - NONE(32)
		3 - DIFF(8)
		4 - DIFF(16)
		5 - DIFF(32)
		6 - LAST(8)
		7 - LAST(16)
		8 - LAST(32)  */

public:
	Predictors(BYTE *file, long filesize);
	~Predictors();
	void writePred(std::ofstream& fileName, int index);
	void writeResidue(std::ofstream& fileName, std::string data);
	std::string applyPred();
	std::string StrHexBin(unsigned char data);
	std::string BinaryDiff(std::string valE, std::string valP, int lung);
	//void findBestPred(std::string array[20], std::ofstream& filePred, std::ofstream& fileResiduu);
	std::string putInMatrix(std::string diffString, int l);
	int selectPred(std::string array[4][9], std::ofstream& filePred, std::ofstream& fileResid);
};

