//Joe Riemersma
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Operator{
	public:
		Operator();
		void FetchExecute();

	private:
		void IncrementCI();
		void DecodeOpcode(vector<char> instruction);
		void DecodeOperand(vector<char> instruction);
		int ConvertBinToInt(vector<char> binSequence);

		vector<char> controlInstruction;
		vector<char> presentInstruction;

		vector<char> operand;
		vector<char> opcode;

};


