#include "Predictors.h"


Predictors::Predictors(BYTE *data, long size)
{
	this->fileSize = size;
	this->fileBuffer = data;
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

// calculate the residue
std::string Predictors::BinaryDiff(std::string valE, std::string valP, int lung) {
	std::string rs = "";
	int minus = 0;
	int needed = 0;
	int val1, val2, rezult;
	if (valE.compare(valP) < 0) {
		rs = valP;
		valP = valE;
		valE = rs;
		rs = "";
		minus = 1;
	}
	for (int i = valE.length() - 1; i > -1; i--) {
		if (valE[i].CompareTo('0') == 0) val1 = 0; else val1 = 1;
		if (valP[i].CompareTo('0') == 0) val2 = 0; else val2 = 1;
		val1 = val1 - needed;
		rezult = val1 - val2;
		if (rezult < 0) {
			rs = "1" + rs;
			needed = 1;
		}
		else {
			if (rezult == 0) rs = "0" + rs; else rs = "1" + rs;
			needed = 0;
		}
	}
	while (rs.length() != lung) {
		rs = "0" + rs;
	}
	if (minus == 1) rs = "-" + rs;
	return rs;
}

std::string Predictors::putInMatrix(std::string diffString, int lb) {
	std::ostringstream ss;
	std::string valS;
	unsigned long valLong;
	int minus = 0;
	if (diffString.find("-") != std::string::npos) {
		diffString = diffString.replace(0, 1, "");
		minus = 1;
	}
	switch (lb) {
	case 8: {
		std::bitset<8> temp0(diffString);
		valLong = temp0.to_ulong();
		break;
	}
	case 16: {
		std::bitset<16> temp1(diffString);
		valLong = temp1.to_ulong();
		break;
	}
	case 32: {
		std::bitset<32> temp2(diffString);
		valLong = temp2.to_ullong();
		break;
	}
	}
	ss << valLong;
	valS = ss.str();
	if (minus == 1) {
		valS = "-" + valS;
	}
	return valS;
}
std::string Predictors::applyPred() {
	//create predictor and residue file
	std::ofstream predictor_file;
	std::ofstream residue_file;
	predictor_file.open("predictor.txt");
	residue_file.open("residue.txt");

	//write the initial data in files
	predictor_file << 0;
	residue_file << putInMatrix(StrHexBin(fileBuffer[0]), 8);

	// Get all data 1 by 1 hex value
	int i = 1;
	while (i < fileSize) {

		// try all the predictors
		std::string tableOfR[20];
		//new try
		std::string stringDifs[4][9];

		for (int index = 0; index < 9; index++) {			
			switch (index)
			{
			case 0:	// NONE(8)
				tableOfR[0] = StrHexBin(fileBuffer[i]);	//pred
				stringDifs[0][0] = putInMatrix(tableOfR[0], 8);
				stringDifs[1][2] = stringDifs[0][0];
				if (i < fileSize - 1) {
					tableOfR[1] = StrHexBin(fileBuffer[i + 1]);
					stringDifs[1][0] = putInMatrix(tableOfR[1], 8);
				}
				else {
					tableOfR[1] = "x";
					stringDifs[1][0] = "x";
				}
				stringDifs[2][2] = stringDifs[1][0];
				if (i < fileSize - 2) {
					tableOfR[2] = StrHexBin(fileBuffer[i + 2]);
					stringDifs[2][0] = putInMatrix(tableOfR[2], 8);
				}
				else {
					tableOfR[2] = "x";
					stringDifs[2][0] = "x";
				}
				stringDifs[3][2] = stringDifs[2][0];
				if (i < fileSize - 3) {
					tableOfR[3] = StrHexBin(fileBuffer[i + 3]);
					stringDifs[3][0] = putInMatrix(tableOfR[3], 8);
				}
				else {
					tableOfR[3] = "x";
					stringDifs[3][0] = "x";
				}
				break;
			case 1:	// NONE(16)
				if (i < fileSize - 1) {
					tableOfR[4] = StrHexBin(fileBuffer[i]) + StrHexBin(fileBuffer[i + 1]);	//pred
					stringDifs[0][3] = putInMatrix(tableOfR[4], 16);
				}
				else {
					tableOfR[4] = "x";
					stringDifs[0][3] = "x";
				}
				stringDifs[2][5] = stringDifs[0][3];
				if (i < fileSize - 2) {
					tableOfR[5] = StrHexBin(fileBuffer[i + 1]) + StrHexBin(fileBuffer[i + 2]);
					stringDifs[1][3] = putInMatrix(tableOfR[5], 16);
				}
				else {
					tableOfR[5] = "x";
					stringDifs[1][3] = "x";
				}
				if (i < fileSize - 3) {
					tableOfR[6] = StrHexBin(fileBuffer[i + 2]) + StrHexBin(fileBuffer[i + 3]);
					stringDifs[2][3] = putInMatrix(tableOfR[6], 16);
				}
				else {
					tableOfR[6] = "x";
					stringDifs[2][3] = "x";
				}
				stringDifs[3][3] = "x";
				break;
			case 2:	// NONE(32)
				if (i < fileSize - 3) {
					tableOfR[7] = StrHexBin(fileBuffer[i]) + StrHexBin(fileBuffer[i + 1]) + StrHexBin(fileBuffer[i + 2]) + StrHexBin(fileBuffer[i + 3]);	//pred
					stringDifs[0][6] = putInMatrix(tableOfR[7], 32);
				}
				else {
					tableOfR[7] = "x";
					stringDifs[0][6] = "x";
				}
				stringDifs[1][6] = "x";
				stringDifs[2][6] = "x";
				stringDifs[3][6] = "x";
				break;
			case 3:	// DIFF(8)
				tableOfR[8] = BinaryDiff(StrHexBin(fileBuffer[i]), StrHexBin(fileBuffer[i - 1]), 8);	//pred
				stringDifs[0][1] = putInMatrix(tableOfR[8], 8);
				if (i < fileSize - 1) {
					tableOfR[9] = BinaryDiff(StrHexBin(fileBuffer[i + 1]), StrHexBin(fileBuffer[i]), 8);
					stringDifs[1][1] = putInMatrix(tableOfR[9], 8);
				}
				else {
					tableOfR[9] = "x";
					stringDifs[1][1] = "x";
				}
				if (i < fileSize - 2) {
					tableOfR[10] = BinaryDiff(StrHexBin(fileBuffer[i + 2]), StrHexBin(fileBuffer[i + 1]), 8);
					stringDifs[2][1] = putInMatrix(tableOfR[10], 8);
				}
				else {
					tableOfR[10] = "x";
					stringDifs[2][1] = "x";
				}
				if (i < fileSize - 3) {
					tableOfR[11] = BinaryDiff(StrHexBin(fileBuffer[i + 3]), StrHexBin(fileBuffer[i + 2]), 8);
					stringDifs[3][1] = putInMatrix(tableOfR[11], 8);
				}
				else {
					tableOfR[11] = "x";
					stringDifs[3][1] = "x";
				}
				break;
			case 4:	// DIFF(16)
				if (i > 1 && i < fileSize - 1) {
					tableOfR[12] = BinaryDiff(StrHexBin(fileBuffer[i]) + StrHexBin(fileBuffer[i + 1]), StrHexBin(fileBuffer[i - 2]) + StrHexBin(fileBuffer[i - 1]), 16);	//pred
					stringDifs[0][4] = putInMatrix(tableOfR[12], 16);
				}
				else {
					tableOfR[12] = "x";
					stringDifs[0][4] = "x";
				}
				if (i < fileSize - 2) {
					tableOfR[13] = BinaryDiff(StrHexBin(fileBuffer[i + 1]) + StrHexBin(fileBuffer[i + 2]), StrHexBin(fileBuffer[i - 1]) + StrHexBin(fileBuffer[i]), 16);
					stringDifs[1][4] = putInMatrix(tableOfR[13], 16);
				}
				else {
					tableOfR[13] = "x";
					stringDifs[1][4] = "x";
				}
				if (i < fileSize - 3) {
					tableOfR[14] = BinaryDiff(StrHexBin(fileBuffer[i + 2]) + StrHexBin(fileBuffer[i + 3]), StrHexBin(fileBuffer[i]) + StrHexBin(fileBuffer[i + 1]), 16);
					stringDifs[2][4] = putInMatrix(tableOfR[14], 16);
				}
				else {
					tableOfR[14] = "x";
					stringDifs[2][4] = "x";
				}
				stringDifs[3][4] = "x";
				break;
			case 5:	// DIFF(32)
				if (i > 3 && i < fileSize - 3) {
					tableOfR[15] = BinaryDiff(StrHexBin(fileBuffer[i]) + StrHexBin(fileBuffer[i + 1]) + StrHexBin(fileBuffer[i + 2]) + StrHexBin(fileBuffer[i + 3]), StrHexBin(fileBuffer[i - 4]) + StrHexBin(fileBuffer[i - 3]) + StrHexBin(fileBuffer[i - 2]) + StrHexBin(fileBuffer[i - 1]), 32);	//pred
					stringDifs[0][7] = putInMatrix(tableOfR[15], 32);
				}
				else {
					tableOfR[15] = "x";
					stringDifs[0][7] = "x";
				}
				stringDifs[1][7] = "x";
				stringDifs[2][7] = "x";
				stringDifs[3][7] = "x";
				break;
			case 6:	// LAST(8)
				tableOfR[16] = StrHexBin(fileBuffer[i - 1]);	//pred
				stringDifs[0][2] = putInMatrix(tableOfR[16], 8);
				break;
			case 7:	// LAST(16)
				if (i > 1) {
					tableOfR[17] = StrHexBin(fileBuffer[i - 2]) + StrHexBin(fileBuffer[i - 1]);	//pred
					stringDifs[0][5] = putInMatrix(tableOfR[17], 16);
				} 
				else {
					tableOfR[17] = "x";
					stringDifs[0][5] = "x";
				}
				tableOfR[18] = StrHexBin(fileBuffer[i - 1]) + StrHexBin(fileBuffer[i]);
				stringDifs[1][5] = putInMatrix(tableOfR[18], 16);
				stringDifs[3][5] = "x";
				break;
			case 8:	// LAST(32)
				if (i > 3) {
					tableOfR[19] =StrHexBin(fileBuffer[i - 4]) + StrHexBin(fileBuffer[i - 3]) + StrHexBin(fileBuffer[i - 2]) + StrHexBin(fileBuffer[i - 1]);	//pred
					stringDifs[0][8] = putInMatrix(tableOfR[19], 32);
				} 
				else {
					tableOfR[19] = "x";
					stringDifs[0][8] = "x";
				}
				stringDifs[1][8] = "x";
				stringDifs[2][8] = "x";
				stringDifs[3][8] = "x";
				break;
			default:
				break;
			}
		}
		//get lowest diff
		int predNr = selectPred(stringDifs, predictor_file, residue_file);
		switch (predNr) {
		case 0 :
			i += 1;
			break;
		case 1 :
			i += 2;
			break;
		case 2 :
			i += 4;
			break;
		case 3: 
			i += 1;
			break;
		case 4 :
			i += 2;
			break;
		case 5 :
			i += 4;
			break;
		case 6 :
			i += 1;
			break;
		case 7 :
			i += 2;
			break;
		case 8 :
			i += 4;
			break;
		default :
			break;
		}
	}
	predictor_file.close();
	residue_file.close();
	return "Compression finished...\n\n";
}

int Predictors::selectPred(std::string array[4][9], std::ofstream& filePred, std::ofstream& fileResid) {
	int diffMin = 11;
	int predSel = -1;
	std::string diff = "";

	for (int a = 8; a > -1; a--) {
		if (array[0][a].length() == 1 && array[0][a].compare("x") != 0) {
			predSel = a;
			break;
		}
		// predictori de 32b
		if (a > 5) {
			if (array[0][a].compare("x") != 0 && diffMin > array[0][a].length()) {
				diffMin = array[0][a].length();
				predSel = a;
			}
		} 
		//predictori de 16b
		else if (a > 2 && a < 6) {
			for (int b = 5; b > -1; b--) {
				if (b > 2) {
					diff = array[0][a];
					if (array[2][b].compare("x") != 0) {
						diff += " " +array[2][b];
					}
					if (array[0][a].compare("x") != 0 && diffMin > diff.length()) {
						diffMin = diff.length();
						predSel = a;
					}
				}
				else {
					for (int c = 2; c > -1; c--) {
						diff = array[0][a];
						if (array[2][b].compare("x") != 0) {
							diff += " " + array[2][b];
							if (array[3][c].compare("x") != 0) {
								diff += " " + array[3][c];
							}
						}
						if (array[0][a].compare("x") != 0 && diffMin > diff.length()) {
							diffMin = diff.length();
							predSel = a;
						}
					}
				}
			}
		}
		//predictori de 8b
		else {
			for (int d = 5; d > -1; d--) {
				if (d > 2) {
					for (int e = 2; e > -1; e--) {
						diff = array[0][a];
						if (array[1][d].compare("x") != 0) {
							diff += " " + array[1][d];
							if (array[3][e].compare("x") != 0) {
								diff += " " + array[3][e];
							}
						}
						if (diffMin > diff.length()) {
							diffMin = diff.length();
							predSel = a;
							if (diffMin == 1) break;
						}
					}
				}
				else {
					for (int f = 5; f > -1; f--) {
						if (f > 2) {
							diff = array[0][a];
							if (array[1][d].compare("x") != 0) {
								diff += " " + array[1][d];
								if (array[2][f].compare("x") != 0) {
									diff += " " + array[2][f];
								}
							}
							if (diffMin > diff.length()) {
								diffMin = diff.length();
								predSel = a;
							}
						}
						else {
							for (int g = 2; g > -1; g--) {
								diff = array[0][a];
								if (array[1][d].compare("x") != 0) {
									diff += " " + array[1][d];
									if (array[2][f].compare("x") != 0) {
										diff += " " + array[2][f];
										if (array[3][g].compare("x") != 0) {
											diff += " " + array[3][g];
										}
									}
								}
								if (diffMin > diff.length()) {
									diffMin = diff.length();
									predSel = a;
								}
							}
						}
					}
				}
			}
		}
	}

	//write data in files
	writePred(filePred, predSel);
	writeResidue(fileResid, array[0][predSel]);
	return predSel;
}

/*
void Predictors::findBestPred(std::string array[20], std::ofstream& filePred, std::ofstream& fileResid) {
	std::string toateVar[2][175];
	int i;
	// NONE 8
	toateVar[1][0] = array[0] + array[1] + array[2] + array[2];
	toateVar[1][1] = array[0] + array[1] + array[2] + array[3];
	toateVar[1][2] = array[0] + array[1] + array[2] + array[11];

	toateVar[1][3] = array[0] + array[1] + array[10] + array[2];
	toateVar[1][4] = array[0] + array[1] + array[10] + array[3];
	toateVar[1][5] = array[0] + array[1] + array[10] + array[11];

	toateVar[1][6] = array[0] + array[1] + array[1] + array[2];
	toateVar[1][7] = array[0] + array[1] + array[1] + array[3];
	toateVar[1][8] = array[0] + array[1] + array[1] + array[11];

	toateVar[1][9] = array[0] + array[9] + array[2] + array[2];
	toateVar[1][10] = array[0] + array[9] + array[2] + array[3];
	toateVar[1][11] = array[0] + array[9] + array[2] + array[11];

	toateVar[1][12] = array[0] + array[9] + array[10] + array[2];
	toateVar[1][13] = array[0] + array[9] + array[10] + array[3];
	toateVar[1][14] = array[0] + array[9] + array[10] + array[11];

	toateVar[1][15] = array[0] + array[9] + array[1] + array[2];
	toateVar[1][16] = array[0] + array[9] + array[1] + array[3];
	toateVar[1][17] = array[0] + array[9] + array[1] + array[11];

	toateVar[1][18] = array[0] + array[0] + array[2] + array[2];
	toateVar[1][19] = array[0] + array[0] + array[2] + array[3];
	toateVar[1][20] = array[0] + array[0] + array[2] + array[11];

	toateVar[1][21] = array[0] + array[0] + array[10] + array[2];
	toateVar[1][22] = array[0] + array[0] + array[10] + array[3];
	toateVar[1][23] = array[0] + array[0] + array[10] + array[11];

	toateVar[1][24] = array[0] + array[0] + array[1] + array[2];
	toateVar[1][25] = array[0] + array[0] + array[1] + array[3];
	toateVar[1][26] = array[0] + array[0] + array[1] + array[11];

	toateVar[1][27] = array[0] + array[1] + array[4];
	toateVar[1][28] = array[0] + array[1] + array[6];
	toateVar[1][29] = array[0] + array[1] + array[14];

	toateVar[1][30] = array[0] + array[9] + array[4];
	toateVar[1][31] = array[0] + array[9] + array[6];
	toateVar[1][32] = array[0] + array[9] + array[14];

	toateVar[1][33] = array[0] + array[0] + array[4];
	toateVar[1][34] = array[0] + array[0] + array[6];
	toateVar[1][35] = array[0] + array[0] + array[14];

	toateVar[1][36] = array[0] + array[5] + array[2];
	toateVar[1][37] = array[0] + array[5] + array[3];
	toateVar[1][38] = array[0] + array[5] + array[11];

	toateVar[1][39] = array[0] + array[13] + array[2];
	toateVar[1][40] = array[0] + array[13] + array[3];
	toateVar[1][41] = array[0] + array[13] + array[11];

	toateVar[1][42] = array[0] + array[18] + array[2];
	toateVar[1][43] = array[0] + array[18] + array[3];
	toateVar[1][44] = array[0] + array[18] + array[11];
	for (i = 0; i < 45; i++) toateVar[0][i] = "0";

	// NONE 16
	toateVar[1][45] = array[4] + array[1] + array[2];
	toateVar[1][46] = array[4] + array[1] + array[3];
	toateVar[1][47] = array[4] + array[1] + array[11];

	toateVar[1][48] = array[4] + array[2] + array[2];
	toateVar[1][49] = array[4] + array[2] + array[3];
	toateVar[1][50] = array[4] + array[2] + array[11];

	toateVar[1][51] = array[4] + array[10] + array[2];
	toateVar[1][52] = array[4] + array[10] + array[3];
	toateVar[1][53] = array[4] + array[10] + array[11];

	toateVar[1][54] = array[4] + array[4];
	toateVar[1][55] = array[4] + array[6];
	toateVar[1][56] = array[4] + array[14];
	for (i = 45; i < 57; i++) toateVar[0][i] = "1";

	// NONE 32
	toateVar[1][57] = array[7];
	toateVar[0][57] = "2";
	//---------------------------------------------------//
	// DIFF 8
	toateVar[1][58] = array[8] + array[1] + array[2] + array[2];
	toateVar[1][59] = array[8] + array[1] + array[2] + array[3];
	toateVar[1][60] = array[8] + array[1] + array[2] + array[11];

	toateVar[1][61] = array[8] + array[1] + array[10] + array[2];
	toateVar[1][62] = array[8] + array[1] + array[10] + array[3];
	toateVar[1][63] = array[8] + array[1] + array[10] + array[11];

	toateVar[1][64] = array[8] + array[1] + array[1] + array[2];
	toateVar[1][65] = array[8] + array[1] + array[1] + array[3];
	toateVar[1][66] = array[8] + array[1] + array[1] + array[11];

	toateVar[1][67] = array[8] + array[9] + array[2] + array[2];
	toateVar[1][68] = array[8] + array[9] + array[2] + array[3];
	toateVar[1][69] = array[8] + array[9] + array[2] + array[11];

	toateVar[1][70] = array[8] + array[9] + array[10] + array[2];
	toateVar[1][71] = array[8] + array[9] + array[10] + array[3];
	toateVar[1][72] = array[8] + array[9] + array[10] + array[11];

	toateVar[1][73] = array[8] + array[9] + array[1] + array[2];
	toateVar[1][74] = array[8] + array[9] + array[1] + array[3];
	toateVar[1][75] = array[8] + array[9] + array[1] + array[11];

	toateVar[1][76] = array[8] + array[0] + array[2] + array[2];
	toateVar[1][77] = array[8] + array[0] + array[2] + array[3];
	toateVar[1][78] = array[8] + array[0] + array[2] + array[11];

	toateVar[1][79] = array[8] + array[0] + array[10] + array[2];
	toateVar[1][80] = array[8] + array[0] + array[10] + array[3];
	toateVar[1][81] = array[8] + array[0] + array[10] + array[11];

	toateVar[1][82] = array[8] + array[0] + array[1] + array[2];
	toateVar[1][83] = array[8] + array[0] + array[1] + array[3];
	toateVar[1][84] = array[8] + array[0] + array[1] + array[11];

	toateVar[1][85] = array[8] + array[1] + array[4];
	toateVar[1][86] = array[8] + array[1] + array[6];
	toateVar[1][87] = array[8] + array[1] + array[14];

	toateVar[1][88] = array[8] + array[9] + array[4];
	toateVar[1][89] = array[8] + array[9] + array[6];
	toateVar[1][90] = array[8] + array[9] + array[14];

	toateVar[1][91] = array[8] + array[0] + array[4];
	toateVar[1][92] = array[8] + array[0] + array[6];
	toateVar[1][93] = array[8] + array[0] + array[14];

	toateVar[1][94] = array[8] + array[5] + array[2];
	toateVar[1][95] = array[8] + array[5] + array[3];
	toateVar[1][96] = array[8] + array[5] + array[11];

	toateVar[1][97] = array[8] + array[13] + array[2];
	toateVar[1][98] = array[8] + array[13] + array[3];
	toateVar[1][99] = array[8] + array[13] + array[11];

	toateVar[1][100] = array[8] + array[18] + array[2];
	toateVar[1][101] = array[8] + array[18] + array[3];
	toateVar[1][102] = array[8] + array[18] + array[11];
	for (i = 58; i < 103; i++) toateVar[0][i] = "3";

	// DIFF 16
	toateVar[1][103] = array[12] + array[1] + array[2];
	toateVar[1][104] = array[12] + array[1] + array[3];
	toateVar[1][105] = array[12] + array[1] + array[11];

	toateVar[1][106] = array[12] + array[2] + array[2];
	toateVar[1][107] = array[12] + array[2] + array[3];
	toateVar[1][108] = array[12] + array[2] + array[11];

	toateVar[1][109] = array[12] + array[10] + array[2];
	toateVar[1][110] = array[12] + array[10] + array[3];
	toateVar[1][111] = array[12] + array[10] + array[11];

	toateVar[1][112] = array[12] + array[4];
	toateVar[1][113] = array[12] + array[6];
	toateVar[1][114] = array[12] + array[14];
	for (i = 103; i < 115; i++) toateVar[0][i] = "4";

	// DIFF 32
	toateVar[1][115] = array[15];
	toateVar[0][115] = "5";
	//---------------------------------------------------//
	// LAST 8
	toateVar[1][116] = array[16] + array[1] + array[2] + array[2];
	toateVar[1][117] = array[16] + array[1] + array[2] + array[3];
	toateVar[1][118] = array[16] + array[1] + array[2] + array[11];

	toateVar[1][119] = array[16] + array[1] + array[10] + array[2];
	toateVar[1][120] = array[16] + array[1] + array[10] + array[3];
	toateVar[1][121] = array[16] + array[1] + array[10] + array[11];

	toateVar[1][122] = array[16] + array[1] + array[1] + array[2];
	toateVar[1][123] = array[16] + array[1] + array[1] + array[3];
	toateVar[1][124] = array[16] + array[1] + array[1] + array[11];

	toateVar[1][125] = array[16] + array[9] + array[2] + array[2];
	toateVar[1][126] = array[16] + array[9] + array[2] + array[3];
	toateVar[1][127] = array[16] + array[9] + array[2] + array[11];

	toateVar[1][128] = array[16] + array[9] + array[10] + array[2];
	toateVar[1][129] = array[16] + array[9] + array[10] + array[3];
	toateVar[1][130] = array[16] + array[9] + array[10] + array[11];

	toateVar[1][131] = array[16] + array[9] + array[1] + array[2];
	toateVar[1][132] = array[16] + array[9] + array[1] + array[3];
	toateVar[1][133] = array[16] + array[9] + array[1] + array[11];

	toateVar[1][134] = array[16] + array[0] + array[2] + array[2];
	toateVar[1][135] = array[16] + array[0] + array[2] + array[3];
	toateVar[1][136] = array[16] + array[0] + array[2] + array[11];

	toateVar[1][137] = array[16] + array[0] + array[10] + array[2];
	toateVar[1][138] = array[16] + array[0] + array[10] + array[3];
	toateVar[1][139] = array[16] + array[0] + array[10] + array[11];

	toateVar[1][140] = array[16] + array[0] + array[1] + array[2];
	toateVar[1][141] = array[16] + array[0] + array[1] + array[3];
	toateVar[1][142] = array[16] + array[0] + array[1] + array[11];

	toateVar[1][143] = array[16] + array[1] + array[4];
	toateVar[1][144] = array[16] + array[1] + array[6];
	toateVar[1][145] = array[16] + array[1] + array[14];

	toateVar[1][146] = array[16] + array[9] + array[4];
	toateVar[1][147] = array[16] + array[9] + array[6];
	toateVar[1][148] = array[16] + array[9] + array[14];

	toateVar[1][149] = array[16] + array[0] + array[4];
	toateVar[1][150] = array[16] + array[0] + array[6];
	toateVar[1][151] = array[16] + array[0] + array[14];

	toateVar[1][152] = array[16] + array[5] + array[2];
	toateVar[1][153] = array[16] + array[5] + array[3];
	toateVar[1][154] = array[16] + array[5] + array[11];

	toateVar[1][155] = array[16] + array[13] + array[2];
	toateVar[1][156] = array[16] + array[13] + array[3];
	toateVar[1][157] = array[16] + array[13] + array[11];

	toateVar[1][158] = array[16] + array[18] + array[2];
	toateVar[1][159] = array[16] + array[18] + array[3];
	toateVar[1][160] = array[16] + array[18] + array[11];
	for (i = 116; i < 161; i++) toateVar[0][i] = "6";

	// LAST 16
	toateVar[1][161] = array[17] + array[1] + array[2];
	toateVar[1][162] = array[17] + array[1] + array[3];
	toateVar[1][163] = array[17] + array[1] + array[11];

	toateVar[1][164] = array[17] + array[2] + array[2];
	toateVar[1][165] = array[17] + array[2] + array[3];
	toateVar[1][166] = array[17] + array[2] + array[11];

	toateVar[1][167] = array[17] + array[10] + array[2];
	toateVar[1][168] = array[17] + array[10] + array[3];
	toateVar[1][169] = array[17] + array[10] + array[11];

	toateVar[1][170] = array[17] + array[4];
	toateVar[1][171] = array[17] + array[6];
	toateVar[1][172] = array[17] + array[14];
	for (i = 161; i < 173; i++) toateVar[0][i] = "7";

	// LAST 32
	toateVar[1][173] = array[19];
	toateVar[0][173] = "8";

	// MIN DIF AND PRED NR
	int diff_min = 11, lungP;
	int pred_nr = -1;
	std::string diffG = "";
	for (i = 0; i < 174; i++) {
		diffG = toateVar[1][i].substr(0, toateVar[1][i].find("x"));
		if (diffG.length() != 0) {
			lungP = 0;
			if (i == 173 || i == 115 || i == 57) {
				if (diffG.find("-")) {
					diffG = diffG.replace(diffG.find("-"), 1, "");
					lungP += 1;
				}
				std::bitset<32> var32(diffG);
				lungP += var32.to_ulong();
			}
			else if ((i > 44 && i < 57) || (i > 102 && i <115) || (i > 160 && i < 173)) {

			}
			else {

			}
			if (diff_min <= lungP) {
				diff_min = lungP;
				pred_nr = i;
			}
		}
	}

	//write data in files
	writePred(filePred, pred_nr);
	switch (pred_nr) {
	case 0 : writeResidue(fileResid, array[0]);
		break;
	case 1: writeResidue(fileResid, array[4]);
		break;
	case 2: writeResidue(fileResid, array[7]);
		break;
	case 3: writeResidue(fileResid, array[8]);
		break;
	case 4: writeResidue(fileResid, array[12]);
		break;
	case 5: writeResidue(fileResid, array[15]);
		break;
	case 6: writeResidue(fileResid, array[16]);
		break;
	case 7: writeResidue(fileResid, array[17]);
		break;
	case 8: writeResidue(fileResid, array[19]);
		break;
	}
	resetPreds(pred_nr);
}*/

void Predictors::writePred(std::ofstream& fileName, int index) {
	fileName << index ;
}
void Predictors::writeResidue(std::ofstream& fileName, std::string data) {
	fileName << " ";
	fileName << data;
}

