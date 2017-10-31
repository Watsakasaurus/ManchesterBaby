//Joe Riemersma
#include <vector>
#include <iostream>
#include <string>

class Operator{
	public:
		Operator();
		FetchExcectue();

	private:
		IncrementCI();
		DecodeOpcode();
		DecodeOperand();
		CovnvertBinToInt();

		vector<char> controlInstruction;
		vector<char> presentInstruction;

		vector<char> operand(4,'0');
		vector<char> opcode(3,'0');

}


