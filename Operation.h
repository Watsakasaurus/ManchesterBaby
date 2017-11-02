//Joe Riemersma
#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>

using namespace std;

class Operation{
	public:
		Operation(int registerSize);

		bool Execute();
		void IncrementCI();
		void DecodeOP();
		int ConvertBinToInt(vector<char> binSequence);
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

		vector<char> CI; //Control instruction
		vector<char> PI; //Present instruction
		vector<char> ACC; //Accumulator instruction
		int operand;
		int opcode;
		int registerWidth;
};


