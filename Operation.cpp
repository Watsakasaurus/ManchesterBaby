//Joe Riemersma
#include "Operation.h"

using namespace std;

Operation::Operation(int registerSize): registerWidth (registerSize){
	CI.resize(registerWidth);
	PI.resize(registerWidth);
	ACC.resize(registerWidth);

	for(int i=0;i<registerWidth;i++){
		CI[i] = '0';
		PI[i] = '0';
		ACC[i] = '0';
	}
	operand = 0;
	opcode = 0;
}


bool Operation::Execute(){ //TODO
	bool exit;
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
		return false;
			break;
	}
	return true;
}

void Operation::IncrementCI(){
	//TODO
}

void Operation::DecodeOP(){
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

//Get
int Operation::GetOperand(){return operand;}
int Operation::GetOpcode(){return opcode;}
vector<char> Operation::GetCI(){return CI;}
vector<char> Operation::GetPI(){return PI;}
vector<char> Operation::GetACC(){return ACC;}

//Set
void Operation::SetCI(vector<char> CtrI){CI = CtrI;}
void Operation::SetPI(vector<char> PresI){PI = PresI;}
void Operation::SetACC(vector<char> Accumulator){ACC = Accumulator;}


