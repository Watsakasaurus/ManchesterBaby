//Joe Riemersma
#include "Store.h"
#include "Operation.h"
#include <string>
#include <vector> 
#include <iostream>

using namespace std;

bool step;
bool decodeCommentary;

string mnemonic;



int ADDRESS_NUMBER = 32;
int REGISTER_WIDTH = 32;
string fileName;


bool Execute(Operation &op, Store &store){
	bool exit;
	switch(op.GetOpcode()){
		case 0:  
			op.SetCI(store.GetInstruction(op.GetOperand()));//JMP
			mnemonic = "JMP";
			break;
		case 1:	
			op.SetCI(op.ConvertIntToBin(op.ConvertBinToInt(op.GetCI()) + op.ConvertBinToInt((store.GetInstruction(op.GetOperand()))))); //JRP
			mnemonic = "JRP";
			break;
		case 2:	 	
			op.SetACC(op.ConvertIntToBin(-op.ConvertBinToInt(store.GetInstruction(op.GetOperand())))); //LDN 
			mnemonic = "LDN";
			break;
		case 3:	
			store.WriteToStore(op.GetOperand(),op.GetACC()); //STO 
			mnemonic = "STO";
			break;		
		case 4:	
			op.SetACC(op.ConvertIntToBin(op.ConvertBinToInt(op.GetACC()) - op.ConvertBinToInt(store.GetInstruction(op.GetOperand()))));//SUB 
			mnemonic = "SUB";
			break;
		case 5:	
			op.SetACC(op.ConvertIntToBin(op.ConvertBinToInt(op.GetACC()) - op.ConvertBinToInt(store.GetInstruction(op.GetOperand()))));//SUB
			mnemonic = "SUB";
			break;
		case 6:	
			if(op.ConvertBinToInt(op.GetACC()) < 0){op.IncrementCI();}//CMP
			mnemonic = "CMP";
			break;
		case 7:	
			mnemonic = "STP";
			return true;
			break;
	}
	return false;
}

void DisplayEverything(Operation &op, Store &store){	
	vector<vector<char> > storeArray = store.GetStore();

	if(step){cout << "\033c" << endl;} //clears terminal
	
	cout << "STORE" << endl;

	for(int i=0;i<storeArray.size();i++){
		for(int j=0;j<storeArray[i].size();j++){
			if(storeArray[i][j] =='0'){
				cout << "\u25E6"; //displays alternative unicode character for 0
			}
			else{
				cout << "\u2022"; //displays alternative unicode character for 1
			}

			if((j +1) % 4 == 0){
				cout << " ";
			}
		}
		cout << endl;
	} 

	cout << "CI: " << endl;
	op.PrintLine(op.GetCI());
	cout << "PI: " << endl;
	op.PrintLine(op.GetPI());
	cout << "ACC: " << endl;
	op.PrintLine(op.GetACC());

	if(decodeCommentary){
		cout << endl << "Decode Commentary: " << endl << endl << "Mnemonic: "<< mnemonic << endl << "Operand: " << op.GetOperand() << endl << "Binary: ";
		op.PrintLine(store.GetInstruction(op.GetOperand()));
	}

	if(mnemonic == "STP"){
		cout << endl << endl <<"STOP STOP STOP STOP STOP STOP STOP" << endl << endl;
	}


	cout << endl << endl << endl;
}

void FetchExecute(Operation &op, Store &store){
	bool exit = false;
	int i = 0;

	while(!exit){
		op.IncrementCI(); //Increment
		op.SetPI(store.GetInstruction(op.ConvertBinToInt(op.GetCI()))); //Fetch
		op.DecodeOP(); //Decode
		exit = Execute(op, store);//Execute
		DisplayEverything(op,store);
		if(step){getchar();}
	}
}

int main(){
	step = false;
	decodeCommentary = true;

	fileName = "MachineCode.txt";
	
	Store store(ADDRESS_NUMBER,REGISTER_WIDTH); //Creates Store object
	if(!store.LoadFileIntoMemory(fileName)){
		cout << "Error reading file: " << fileName << endl;
		return 0;
	}

	cout << endl;
	cout << endl;

	Operation op(REGISTER_WIDTH); //Creates Operation object that controlls the fetch execute cycle

	FetchExecute(op,store);


	

	return 0;
}


