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
	bool remainder = true;
	int i = 0;
		while(remainder){
			if(CI[i] == '0'){
				CI[i] = '1';
				remainder = false;
			}else{
				CI[i] = '0';
			}
			i++;
		}
}

void Operation::DecodeOP(){ //Gets Opcode and Operand from Present Instruction
	vector <char> binOpcode(3);
	vector <char> binOperand(5);
	int counter = 0;
	for(int i = 0; i < 5; i++){
		binOperand[i] = PI[i];
	}

	for(int j = 13; j < 16;j++){
		binOpcode[counter] = PI[j];
		counter++;
	}

	operand = ConvertBinToInt(binOperand);
	opcode = ConvertBinToInt(binOpcode);
}


long long int Operation::ConvertBinToInt(vector<char> binSequence){ //Convers Binary to Integer
	long long int multiplier = 1;
	long long int total = 0;

	for(int i = 0; i < binSequence.size();i++){
		if(i == binSequence.size()-1 && binSequence.size() == registerWidth){ //If we are converting a value from the store
			if(binSequence[i] == '1'){ //if negative
				total -= multiplier;
			}
		}else{
			if(binSequence[i] == '1'){
				total += multiplier;
			}
		}
		multiplier = multiplier * 2;
	}

	return total;
}

vector<char> Operation::ConvertIntToBin(long long int integer){ //Converts Integer to Binary
	vector<char> converted(registerWidth,'0');
	bool negative = false;
	long long int smallest = -pow(2,registerWidth-1); //Smallest Integer that our simulation can take
	long long int largest = pow(2,registerWidth-1) - 1; //Largest Integer that our simulation can take

	if(integer < 0){ 		//If number is a negative
		negative = true;
		integer = integer*-1;
	}

	if(integer < smallest || integer > largest){ //If number is too large or too small for the size of our register
		cout << endl << "OUT OF MEMORY!" << endl;
		exit(EXIT_FAILURE);
	}

	//Converts the integer to a binary number
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
	//2's complement conversion
	if(negative){
		for(int i = 0; i < converted.size(); i++){
			if(converted[i] == '0'){
				converted[i] = '1';
			}else{
				converted[i] = '0';
			}
		}

		//add one to binary
		bool remainder = true;
		int counter = 0;
		while(remainder){
			if(converted[counter] == '0'){
				converted[counter] = '1';
				remainder = false;
			}else{
				converted[counter] = '0';
			}
			counter++;
		}
	}
	return converted;
}

vector<char> Operation::FlipBinSequence(vector<char> binSequence){ //Reverses order of binary sequence Only used for testing
	reverse(binSequence.begin(),binSequence.end());
	return binSequence;
}

void Operation::PrintLine(vector<char> toPrint){ //Prints out vector array of characters in one line
	for(int i = 0; i<toPrint.size();i++){
		//cout << toPrint[i];
		if(toPrint[i] == '0'){
			cout << "\u25E6";
		}else{
			cout << "\u2022";
		}

		if((i + 1) % 4 == 0){
			cout << " ";
		}
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
