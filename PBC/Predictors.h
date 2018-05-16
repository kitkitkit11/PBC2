#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

// An unsigned char can store 1 Bytes (8bits) of data (0-255)
typedef unsigned char BYTE;

class Predictors
{
public: 
	long fileSize;
	BYTE *fileBuffer;
	int usedArray[2][10];
	/*	0 - NONE(8)
		1 - NONE(16)
		2 - NONE(32)
		3 - LAST(8)
		4 - LAST(16)
		5 - LAST(32)
		6 - DIFF(8)
		7 - DIFF(16)
		8 - DIFF(32)
		9 - GUESS */

public:
	Predictors(BYTE *file, long filesize, int usedArrayP[2][10]);
	~Predictors();
	void writePred(std::ofstream& fileName, int index);
	void writeResidue(std::ofstream& fileName, std::string data);
	int applyPred();
	void resetPreds(int index);
	std::string StrHexBin(unsigned char data);
};

