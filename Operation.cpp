//Joe Riemersma
#include "Operation.h"

using namespace std;

Operation::Operation(int registerSize): registerWidth (registerSize){

	controlInstruction.resize(registerWidth);
	presentInstruction.resize(registerWidth);
	accumulator.resize(registerWidth);

	for(int i=0;i<registerWidth;i++){
		controlInstruction[i] = '0';
		presentInstruction[i] = '0';
		accumulator[i] = '0';
	}
	operand = 0;
	opcode = 0;
}

void Operation::FetchExecute(){
	//TODO
}

void Operation::ExecuteInstruction(){ //TODO
	switch(opcode){
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;		
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
	}

}

void Operation::IncrementCI(){
	//TODO
}

vector<char> Operation::GetOpcode(vector<char> instruction){
	//TODO
}

vector<char> Operation::GetOperand(vector<char> instruction){
	//TODO
}

int Operation::ConvertBinToInt(vector<char> binSequence){
	//TODO
}

vector<char> Operation::FlipBinSequence(vector<char> binSequence){ //Reverses order of binary sequence
	reverse(binSequence.begin(),binSequence.end());
	return binSequence;
}

void Operation::PrintLine(vector<char> toPrint){ //Prints out vector array of characters
	for(int i = 0; i<toPrint.size();i++){
		cout << toPrint[i];
	}
	cout << endl;
}



