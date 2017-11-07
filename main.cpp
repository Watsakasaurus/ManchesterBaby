//Joe Riemersma
#include "Store.h"
#include "Operation.h"
#include <string>
#include <vector> 
#include <iostream>

using namespace std;

bool step = false;
bool allstep = false;
bool decodeCommentary = false;

string mnemonic;



int ADDRESS_NUMBER = 32;
int REGISTER_WIDTH = 32;
string fileName = "Example.txt";


bool Execute(Operation &op, Store &store){
	bool exit;
	switch(op.GetOpcode()){
		case 0:  
			op.SetCI(store.GetInstruction(op.GetOperand()));//JMP - Control instruction is set to line from store
			mnemonic = "JMP";
			break;
		case 1:	
			op.SetCI(op.ConvertIntToBin(op.ConvertBinToInt(op.GetCI()) + op.ConvertBinToInt((store.GetInstruction(op.GetOperand()))))); //JRP - Line from store is added to control instrustion
			mnemonic = "JRP";
			break;
		case 2:	 	
			op.SetACC(op.ConvertIntToBin(-op.ConvertBinToInt(store.GetInstruction(op.GetOperand())))); //LDN - Sets Accumulator to negative of line from the store
			mnemonic = "LDN"; 
			break;
		case 3:	
			store.WriteToStore(op.GetOperand(),op.GetACC()); //STO - Stores contents of Accumulator in line of the store
			mnemonic = "STO";
			break;		
		case 4:	
			op.SetACC(op.ConvertIntToBin(op.ConvertBinToInt(op.GetACC()) - op.ConvertBinToInt(store.GetInstruction(op.GetOperand()))));//SUB - Subtracts Line from store from Accumulator
			mnemonic = "SUB";
			break;
		case 5:	
			op.SetACC(op.ConvertIntToBin(op.ConvertBinToInt(op.GetACC()) - op.ConvertBinToInt(store.GetInstruction(op.GetOperand()))));//SUB - Subtracts Line from store from Accumulator
			mnemonic = "SUB";
			break;
		case 6:	
			if(op.ConvertBinToInt(op.GetACC()) < 0){op.IncrementCI();}//CMP - If contents of Accumulator is less than zero, increment the CI;
			mnemonic = "CMP";
			break;
		case 7:	
			mnemonic = "STP";
			return true;		//STP
			break;
	}
	return false;
}

void DisplayEverything(Operation &op, Store &store){	//Take a wild guess 
	vector<vector<char> > storeArray = store.GetStore();

	if(step || allstep){cout << "\033c" << endl;} //Clears terminal
	
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

void FetchExecute(Operation &op, Store &store){ //Loops through the fetch execute cycle until stop code is reached
	bool exit = false;
	int i = 1;

	if(!step && !allstep){cout << "Initial: \n" << endl;DisplayEverything(op,store);}

	while(!exit){
		op.IncrementCI(); //Increment
		if(allstep){DisplayEverything(op,store);cout << endl << "Cycle Number: " << i << endl;getchar();}

		op.SetPI(store.GetInstruction(op.ConvertBinToInt(op.GetCI()))); //Fetch
		if(allstep){DisplayEverything(op,store);cout << endl << "Cycle Number: " << i << endl;getchar();}

		op.DecodeOP(); //Decode
		if(allstep){DisplayEverything(op,store);cout << endl << "Cycle Number: " << i << endl;getchar();}

		exit = Execute(op, store);//Execute
		if(step || allstep){DisplayEverything(op,store);cout << endl << "Cycle Number: " << i << endl;getchar();}

		i++;
	}

	if(!step && !allstep){cout << "Final: \n" << endl;DisplayEverything(op,store);}
}

bool TestInt(char* argv){ //Test argument char array for an integer
	string s(argv);

	//Taken from first answer https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int 
	//user paercebal
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
    char * p ;
    strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

bool ParseArgs(int argc, char* argv[]){ //Takes arguments from user   
	int argIndex = 1;
	string USAGE = "USAGE: ./ManchesterBaby [step=<'more'|'less'>] [commentary] [file=<'filename'>] [store=<'store size'>] [register=<'register size']\nUse command '-help' to view the help file.";
	string STEPUSAGE = "USAGE ./ManchesterBaby step [more] [less]\nUse command '-help' to view the help file.";
	string STOREUSAGE = "USAGE ./ManchesterBaby store [store size]\nUse command '-help' to view the help file.";
	string REGISTERUSAGE = "USAGE ./ManchesterBaby register [register size]\nUse command '-help' to view the help file.";

	while(argIndex < argc){
		if(string(argv[argIndex]) == "step"){
			argIndex++;
			if(argIndex >= argc){cout << STEPUSAGE << endl;return false;}

			if(string(argv[argIndex]) == "more"){allstep = true;}
			else if(string(argv[argIndex]) == "less"){step = true;}
			else{cout << STEPUSAGE << endl;return false;}

		}else if(string(argv[argIndex]) == "commentary"){
			decodeCommentary = true;
		}else if(string(argv[argIndex]) == "file"){
			argIndex++;
			if(argIndex >= argc){cout << USAGE << endl;return false;}
			fileName = string(argv[argIndex]);
		}else if(string(argv[argIndex]) == "-help"){
			string line;
			ifstream helpfile("helpfile");
			if(helpfile.is_open()){
				while(getline(helpfile,line)){
					cout << line << endl;
				}
				helpfile.close();
			}else{
				cout << "Unable to open helpfile, please make sure it has not been deleted or moved.";
			}	
			return false;
		}else if(string(argv[argIndex]) == "store"){
			argIndex++;
			if(argIndex >= argc){cout << STOREUSAGE << endl;return false;}

			if(TestInt(argv[argIndex])){
				if(atoi(argv[argIndex]) < 32){
					cout << STOREUSAGE << endl;return false;
				}else{
					ADDRESS_NUMBER = atoi(argv[argIndex]);
				}
			}else{
				cout << "Please follow 'store' with an integer" << endl;
				cout << STOREUSAGE << endl;
				return false;
			}
		}else if(string(argv[argIndex]) == "register"){
			argIndex++;
			if(argIndex >= argc){cout << REGISTERUSAGE << endl;return false;}

			if(TestInt(argv[argIndex])){
				if(atoi(argv[argIndex]) < 32 || atoi(argv[argIndex])> 63){
					cout << REGISTERUSAGE << endl << "Make sure that the number you enter is between 32 and 63, inclusive.\nThis simulation can only take a maximum of 63 bits as it requires negative numbers to run"<< endl;return false;
				}else{
					REGISTER_WIDTH = atoi(argv[argIndex]);
				}
			}else{
				cout << "Please follow 'store' with an integer" << endl;
				cout << REGISTERUSAGE << endl;
				return false;
			}
		}else{
			cout << USAGE << endl;
			return false;
		}
		argIndex++;
	}
	return true;
}

int main(int argc, char* argv[]){

	if(!ParseArgs(argc,argv)){return 0;}

	
	Store store(ADDRESS_NUMBER,REGISTER_WIDTH); //Creates Store object
	
	if(!store.LoadFileIntoMemory(fileName)){
		cout << "Error reading file: " << fileName << endl;
		return 0;
	}

	Operation op(REGISTER_WIDTH); //Creates Operation object that controlls the fetch execute cycle

	FetchExecute(op,store);

	return 0;
}


