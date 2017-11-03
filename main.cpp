//Joe Riemersma
#include "Store.h"
#include "Operation.h"
#include <string>
#include <vector> 
#include <iostream>

using namespace std;

int ADDRESS_NUMBER = 32;
int REGISTER_WIDTH = 32;
string fileName;


bool Execute(Operation op, Store store){
	bool exit;
	switch(op.GetOpcode()){
		case 0:  
			op.SetCI(store.GetInstruction(op.GetOperand()));//JMP
			break;
		case 1:	
			op.SetCI(op.ConvertIntToBin(op.ConvertBinToInt(op.GetCI()) + op.ConvertBinToInt((store.GetInstruction(op.GetOperand()))))); //JRP
			break;
		case 2:		  	
			op.SetACC(store.GetInstruction(op.GetOperand())); //LDN
			break;
		case 3:		
			store.WriteToStore(op.GetOperand(),op.GetACC());	//STO
			break;		
		case 4:	
			op.SetACC(op.ConvertIntToBin(op.ConvertBinToInt(op.GetACC()) - op.ConvertBinToInt(store.GetInstruction(op.GetOperand()))));//SUB
			break;
		case 5:	
			op.SetACC(op.ConvertIntToBin(op.ConvertBinToInt(op.GetACC()) - op.ConvertBinToInt(store.GetInstruction(op.GetOperand()))));//SUB
			break;
		case 6:	
			if(op.ConvertBinToInt(op.GetACC()) < 0){op.IncrementCI();}//CMP
			break;
		case 7:			//STP
		return false;
			break;
	}
	return true;
}


void FetchExecute(Operation op, Store store){
	bool exit = false;

	while(!exit){
		op.IncrementCI(); //Increment
		op.SetPI(store.GetInstruction(op.ConvertBinToInt(op.GetCI()))); //Fetch
		op.DecodeOP(); //Decode
		op.SetACC(store.GetInstruction(op.GetOperand()));//Fetch
		exit = Execute(op,store);//Execute
	}
}

void DisplayEverything(){

}


int main(){

	fileName = "MachineCode.txt";
	
	Store store(ADDRESS_NUMBER,REGISTER_WIDTH); //Creates Store object
	if(!store.LoadFileIntoMemory(fileName)){
		cout << "Error reading file: " << fileName << endl;
		return 0;
	}
	store.DisplayStore();

	cout << endl;
	cout << endl;

	Operation op(REGISTER_WIDTH); //Creates Operation object that controlls the fetch execute cycle

	op.IncrementCI(); //Increment

	op.SetPI(store.GetInstruction(op.ConvertBinToInt(op.GetCI()))); //Fetch
	op.DecodeOP(); //Decode

	cout << op.GetOpcode() << endl;
	cout << op.GetOperand() << endl;



	





	return 0;
}


