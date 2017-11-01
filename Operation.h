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
		void FetchExecute();
		void PrintLine(vector<char> toPrint);
	private:
		void ExecuteInstruction();
		void IncrementCI();
		vector<char> GetOpcode(vector<char> instruction);
		vector<char> GetOperand(vector<char> instruction);
		vector<char> FlipBinSequence(vector<char> binSequence);	
		int ConvertBinToInt(vector<char> binSequence);

		vector<char> controlInstruction;
		vector<char> presentInstruction;
		vector<char> accumulator;

		int operand;
		int opcode;
		int registerWidth;
};


