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


bool Execute(Operation &op, Store &store){
	bool exit;
	switch(op.GetOpcode()){
		case 0:  
			op.SetCI(store.GetInstruction(op.GetOperand()));//JMP
			break;
		case 1:	
			op.SetCI(op.ConvertIntToBin(op.ConvertBinToInt(op.GetCI()) + op.ConvertBinToInt((store.GetInstruction(op.GetOperand()))))); //JRP
			break;
		case 2:	 	
			op.SetACC(op.ConvertIntToBin(-op.ConvertBinToInt(store.GetInstruction(op.GetOperand())))); //LDN 
			break;
		case 3:	
			store.WriteToStore(op.GetOperand(),op.GetACC()); //STO WORKS
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
		case 7:	
			cout << "STOP" << endl;		//STP
			return true;
			break;
	}
	return false;
}


void FetchExecute(Operation &op, Store &store){
	bool exit = false;
	int i = 0;

	while(!exit){
		op.IncrementCI(); //Increment
		op.SetPI(store.GetInstruction(op.ConvertBinToInt(op.GetCI()))); //Fetch
		op.DecodeOP(); //Decode
		exit = Execute(op, store);//Execute
		/*cout << op.ConvertBinToInt(op.GetCI()) << "|";	//Used to debug
		cout << op.GetOpcode() << " | ";
		cout << op.GetOperand() << endl; 
		op.PrintLine(op.GetPI());
		op.PrintLine(op.GetACC());*/
	}
}

void DisplayEverything(Operation &op, Store &store){
	vector<vector<char> > storeArray = store.GetStore();

	cout << "STORE 								CI:";
	op.PrintLine(op.GetCI());
	cout << endl;

	for(int i=0;i<storeArray.size();i++){
		for(int j=0;j<storeArray[i].size();j++){
			if(storeArray[i][j] =='0')
			{
				cout << "\u25E6"; //displays alternative unicode character for 0
			}
			else if (storeArray[i][j] == '1')
			{
				cout << "\u2022"; //displays alternative unicode character for 1
			}
			if((j +1) % 4 == 0){
				cout << " ";
			}

		}
		if(i == 0)
		{
			cout << "			PI:";
			op.PrintLine(op.GetPI());
		}
		else if (i == 1)
		{
			cout << "			ACC:";
			op.PrintLine(op.GetACC());
		}
		cout << endl;
	} 
}


int main(){

	fileName = "MachineCode.txt";
	
	Store store(ADDRESS_NUMBER,REGISTER_WIDTH); //Creates Store object
	if(!store.LoadFileIntoMemory(fileName)){
		cout << "Error reading file: " << fileName << endl;
		return 0;
	}

	cout << endl;
	cout << endl;

	Operation op(REGISTER_WIDTH); //Creates Operation object that controlls the fetch execute cycle

	
	DisplayEverything(op,store);

	FetchExecute(op,store);

	DisplayEverything(op,store);

	

	return 0;
}


