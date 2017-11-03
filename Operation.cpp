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

void Operation::IncrementCI(){ //Adds one to binary sequence
	for(int i = 0; i < CI.size(); i++){
		if(CI[i] == '0'){
			CI[i] = '1';
			break;
		}
		CI[i] = '0';
	}
}

void Operation::DecodeOP(){ //Gets Opcode and Operand from Present Instruction
	vector <char> binOpcode(3);
	vector <char> binOperand(4);
	int counter = 0;
	for(int i = 0; i < 5; i++){
		binOperand[i] = PI[i];
	}

	for(int j = 13; j < 15;j++){
		binOpcode[counter] = PI[j];
		counter++;
	}
	operand = ConvertBinToInt(binOperand);
	opcode = ConvertBinToInt(binOpcode);
}


int Operation::ConvertBinToInt(vector<char> binSequence){
	int multiplier = 1;
	int total = 0;

	for(int i = 0; i < binSequence.size();i++){
		if(binSequence[i] == '1'){
			total += multiplier;
		}
		multiplier = multiplier + multiplier;
	}
	return total;
}

vector<char> Operation::ConvertIntToBin(long long int integer){
	vector<char> converted(registerWidth,'0');
	bool negative = false;
	long long int smallest = -1*(pow(2,registerWidth-1)); //Smallest Integer that our simulation can take
	long long int largest = pow(2,registerWidth-1) - 1; //Largest Integer that our simulation can take

	if(integer < 0){
		negative = true;
	}else if(integer < smallest || integer > largest){
		cout << endl << "OUT OF MEMORY!" << endl;
		exit(EXIT_FAILURE);
	}

	int bit = 0;
	int quot = 0; //quotient
	int counter = 0;

	while(integer > 0){
		bit = integer % 2;
		quot = integer / 2;
		integer = quot;
		if(bit == 0){
			converted[counter] = '0';
		}else{
			converted[counter] = '1';
		}
		counter++;
	}

	if(negative){
		for(int i = 0; i < converted.size(); i++){
			if(converted[i] == '0'){
				converted[i] = '1';
			}else{
				converted[i] = '0';
			}
		}
		converted = ConvertIntToBin(ConvertBinToInt(converted) + 1);
	}

	return converted;
}

vector<char> Operation::BinaryToNegative(vector<char> binSequence){
	return ConvertIntToBin(-1*ConvertBinToInt(binSequence));
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