//Joe Riemersma
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

struct Symbol{ //Struct for item in the symbolTable.
	string name;
	int address;
};

vector< vector<string> > toAssemble;
vector< vector<char> > assembled;
vector<Symbol> symbolTable;

template <typename T>
void PrintLine(vector<T> toPrint,bool a){
	for(int i = 0; i<toPrint.size();i++){
		cout << toPrint[i];
		if(a){cout << " ";}
	}
	cout << endl;
}

int SearchTable(string search){	 //Search through table
	for(int i = 0; i < symbolTable.size(); i++){
		if(symbolTable[i].name == search){
			return symbolTable[i].address;
		}
	}
	return -1;
}

void AddToTable(string name, int address){ //Add item to symbolTable table
	if(SearchTable(name) != -1){
		return;
	}
	string shortName = name.substr(0, name.size()-1);
	Symbol newSymbol;
	newSymbol.name = shortName;
	newSymbol.address = address;

	symbolTable.push_back(newSymbol);
}

int InstructionConversion(string opCode){ //returns number that corresponds to instruction
	if(opCode == "JMP"){
		return 0;
	}else if(opCode == "JRP"){
		return 1;
	}else if(opCode == "LDN"){
		return 2;
	}else if(opCode == "STO"){
		return 3;
	}else if(opCode == "SUB"){
		return 4;
	}else if(opCode == "SUB"){
		return 5;
	}else if(opCode == "CMP"){
		return 6;
	}else if(opCode == "STP"){
		return 7;
	}else if(opCode == "ADD"){
		return 8;
	}else if(opCode == "MTP"){
		return 9;
	}else if(opCode == "DIV"){
		return 10;
	}else if(opCode == "MOD"){
		return 11;
	}else if(opCode == "SQR"){
		return 12;
	}else if(opCode == "LDP"){
		return 13;
	}else{
		return -1;
	}
}

long long int StringToInt(string s){ //Turns String to int
	long long int x;
	stringstream ss(s);
	ss >> x;
	return x;
}

vector<char> ConvertIntToBin(long long int integer){ //Converts Integer to Binary
	vector<char> converted(32,'0');
	bool negative = false;
	long long int smallest = -pow(2,32-1); //Smallest Integer that our assembler can take
	long long int largest = pow(2,32-1) - 1; //Largest Integer that our assembler

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

vector<char> ConvertInstruction(string opcode, string operand){ //Converts into an Instruction line to binary
	vector<char> line(32,'0');
	vector<char> opcodeSeq(32,'0');
	vector<char> operandSeq(32,'0');

	int x = InstructionConversion(opcode);

	if(x == -1){
		cout << "Invalid Instruction: " << opcode << endl;
		exit(EXIT_FAILURE);
	}
	opcodeSeq = ConvertIntToBin(x);

	if(InstructionConversion(opcode) != 7){
		if(SearchTable(operand) == -1){
			cout << endl << "Unknown Lable: " << operand << endl;
			exit(EXIT_FAILURE);
		}
		operandSeq = ConvertIntToBin(SearchTable(operand));
		for(int i = 0; i < 5; i++){
			line[i] = operandSeq[i];
		}
	}

	for(int i = 0; i < 4; i++){
		line[i + 13] = opcodeSeq[i];
	}
	return line;
}

bool ConvertMC(){ //Works out if line contains a variable or command, calls functions to translate accordingly
	for(int i = 0; i < toAssemble.size(); i++){
		cout <<"Converting Instruction:"; PrintLine(toAssemble[i],true);
		if(toAssemble[i][0] == "VAR"){
			assembled.push_back(ConvertIntToBin(StringToInt(toAssemble[i][1])));
		}else if(toAssemble[i][0] == "STP"){
			assembled.push_back(ConvertInstruction(toAssemble[i][0],"0"));
		}else{
			assembled.push_back(ConvertInstruction(toAssemble[i][0],toAssemble[i][1]));
		}
		cout << "Machine code: "; PrintLine(assembled.back(),false); cout << endl;
	}
	return true;
}


void CleanLine(vector<string> tokens){ //Removes comments from code;
	int i = 0;
	bool clean = false;
	vector<string> cleaned;

	while(!clean && i < tokens.size()){
		if(tokens[i].at(0) == ';'){
			clean = true;
		}else{
			cleaned.push_back(tokens[i]);
		}
		i++;
	}

	if(cleaned.size() > 0){
		toAssemble.push_back(cleaned);
	}
}


vector<string> RemoveWhitespace(string line){ //removes... wait for it ... Whitespace!
	//Answer modified from https://stackoverflow.com/questions/19887232/how-to-loop-through-a-string-by-space-how-do-i-know-the-index-no-of-the-word-i
	//User: deepmax
	string toAdd;
	vector<string> tokens;

	for(stringstream s(line); s >> toAdd;){
	    tokens.push_back(toAdd);
	}
	return tokens;
}

bool ReadFile(string fileName){ //reads file
	string line;
	ifstream file(fileName.c_str());

	if(file.is_open()){
		while(getline(file,line)){
			CleanLine(RemoveWhitespace(line));
		}
		file.close();
	}else{
		cout << "Unable to locate '" << fileName << "'" << endl;
		return false;
	}
	return true;
}

void LoadSymbolTable(){ //Adds Lables to symbol table, then strips them from code
	for(int i = 0; i < toAssemble.size(); i++){
		if(toAssemble[i].size() == 3 || toAssemble[i][0].back() == ':'){
			AddToTable(toAssemble[i][0],i);
			toAssemble[i].erase(toAssemble[i].begin());
		}
	}

}

void DisplayAndWrite(bool write, string fileName){ //Writes to file and displays
	cout << "Machine Code: " << endl;

	if(write){
		ofstream file ("MC"+fileName);
	  	if(file.is_open()){
			for(int i=0;i<assembled.size();i++){
				for(int j=0;j<assembled[i].size();j++){
					file << assembled[i][j];
				}
				file << "\n";
			}
	  	}
	  else cout << "Unable to open file";
	}

	for(int i=0;i<assembled.size();i++){
		PrintLine(assembled[i],false);
	}

	if(write){
		cout << "Output file: MC" << fileName << endl;
	}

}

int main(int argc, char* argv[]){ //Gets user input, calls functions to start convertion
	char input;
	string USAGE = "Usage: ./mb++ [filename]";
	if(argc != 2){
		cout << USAGE << endl;
		return 0;
	}

	if(!ReadFile(string(argv[1]))){return 0;} //Read File that user entered
	LoadSymbolTable();	//Load symbols into table

	if(SearchTable("START") == -1 && SearchTable("END") == -1){ //Check if file is readable by the assmbler (poor test and can be maniplualted to pass but it works)
		cout << "Unable to recogise file!\nPlease include a 'START:' and an 'END:' lable to your file!" << endl;
		return 0;
	}

	ConvertMC(); //Starts convertion

	for (;;){
	    cout << "Do you wish to write the output to a file: y/n" << endl;
	    if (cin >> input && input == 'y' || input == 'n') {
			if(input == 'y'){
				DisplayAndWrite(true,string(argv[1]));
			}
			else{
				DisplayAndWrite(false,"");
			}
	        break;
	    } else {
	        cout << "Please enter either y or n" << endl;
	        cin.clear();
	        cin.ignore();
	    }
	}
	return 0;
}
