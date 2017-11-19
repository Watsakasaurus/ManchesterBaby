//Joe Riemersma
#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

using namespace std;

//Operation Class for Different binary operations that the ManchesterBaby carries out, think of this as the processor.
class Operation{
	public:
		Operation(int registerSize);

		void IncrementCI();
		void DecodeOP();
		long long int ConvertBinToInt(vector<char> binSequence);
		vector<char>ConvertIntToBin(long long int integer);
		vector<char>BinaryToNegative(vector <char> binSequence);
		void PrintLine(vector<char> toPrint);


		int GetOperand();
		int GetOpcode();

		vector<char> GetCI();
		vector<char> GetPI();
		vector<char> GetACC();

		void SetCI(vector<char> CtrI);
		void SetPI(vector<char> PresI);
		void SetACC(vector<char> Accumulator);


	private:
		vector<char> FlipBinSequence(vector<char> binSequence);
		vector<char> CI; //Control instructionm
		vector<char> PI; //Present instruction
		vector<char> ACC; //Accumulator instruction
		int operand;
		int opcode;
		int registerWidth;
};
