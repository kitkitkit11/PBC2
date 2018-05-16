#include "Predictors.h"


Predictors::Predictors(BYTE *data, long size, int usedArrayP[2][10])
{
	this->fileSize = size;
	this->fileBuffer = data;
	this->usedArray[2][10] = usedArrayP[2][10];
}


Predictors::~Predictors()
{
}

// get data from buffer in hex and convert to binary
std::string Predictors::StrHexBin(unsigned char data){
	std::stringstream ss;
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)data;
	std::string hex = ss.str();
	std::string binS = "";
	for (int i = 0; i < 2; i++) {
		switch (hex[i]) {
		case '0':  binS += "0000";
			break;
		case '1':  binS += "0001";
			break;
		case '2':  binS += "0010";
			break;
		case '3':  binS += "0011";
			break;
		case '4':  binS += "0100";
			break;
		case '5':  binS += "0101";
			break;
		case '6':  binS += "0110";
			break;
		case '7':  binS += "0111";
			break;
		case '8':  binS += "1000";
			break;
		case '9':  binS += "1001";
			break;
		case 'a':  binS += "1010";
			break;
		case 'b':  binS += "1011";
			break;
		case 'c':  binS += "1100";
			break;
		case 'd':  binS += "1101";
			break;
		case 'e':  binS += "1110";
			break;
		case 'f':  binS += "1111";
			break;
		default: binS += "0000";
			break;
		}
	}

	return binS;
}

int Predictors::applyPred() {
	//create predictor and residue file
	std::ofstream predictor_file;
	std::ofstream residue_file;
	predictor_file.open("predictor.txt");
	residue_file.open("residue.txt");

	// Get all data 1 by 1 hex value
	int i = 0;
	while (i < fileSize) {
		//write the initial data in files
		if (i == 0) {
			writePred(predictor_file, 0);
			writeResidue(residue_file, StrHexBin(fileBuffer[0]));
			resetPreds(0);
			i++;
		}
		// get all the diference 
		int diff[10] = {};
		// try all the predictors
		std::string predictedVal;
		int diffsFromIndexes[10];

		for (int index = 0; index < 10; index++) {			
			switch (usedArray[0][index])
			{
			case 0:	// NONE(8)

				break;
			case 1:	// NONE(16)

				break;
			case 2:	// NONE(32)

				break;
			case 3:	// LAST(8)

				break;
			case 4:	// LAST(16)
				if (i > 1) {

				}
				break;
			case 5:	// LAST(32)
				if (i > 3) {

				}
				break;
			case 6:	// DIFF(8)

				break;
			case 7:	// DIFF(16)
				if (i > 1) {

				}
				break;
			case 8:	// DIFF(32)
				if (i > 3) {

				}
				break;
			case 9:	// GUESS
				if (i > 5) {

				}
				break;
			default:
				break;
			}
		}
		//get lowest diff

	}
		
	return 0;
}

void Predictors::resetPreds(int index) {
	for (int i = 0; i < 10; i++) {
		if (usedArray[0][i] == index) {
			int j = i - 1;
			int done = usedArray[1][i] + 1;
			while (j > -1 && done != -1) {
				if (usedArray[1][j] < done) {
					usedArray[0][j + 1] = usedArray[0][j];
					usedArray[1][j + 1] = usedArray[1][j];
				}
				else {
					usedArray[0][j + 1] = index;
					usedArray[1][j + 1] = done;
					done = -1;
				}
				j--;
			}
			if (j == -1 && done != -1) {
				usedArray[0][0] = index;
				usedArray[1][0] = done;
			}
			break;
		}
	}
}

void Predictors::writePred(std::ofstream& fileName, int index) {
	fileName << index ;
}
void Predictors::writeResidue(std::ofstream& fileName, std::string data) {
	fileName << data ;
}

