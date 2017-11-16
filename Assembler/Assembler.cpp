#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

vector< vector<string>> toAssemble;

void createSymbolTable()
{

	/*2nd pass thru tokens

	search for variables and labels(start, end)

	everytime a variable is called, use the reference to the place in memory the variable is stored

	if var01 = 1025, points to the space in memory*/

}

void instructionConversion(){
	string opCode = ""; //this needs to be passed from symbol table function

	if(opCode == "JMP"){
		opCode = "000";
	}else if(opCode == "JRP"){
		opCode = "100";
	}else if(opCode == "LDN"){
		opCode = "010";
	}else if(opCode == "STO"){
		opCode = "110";
	}else if(opCode == "SUB"){
		opCode = "001";
	}else if(opCode == "SUB"){
		opCode = "101";
	}else if(opCode == "CMP"){
		opCode = "011";
	}else if(opCode == "STP"){
		opCode = "111";
	}

}

void convertToMachineCode(){
/*
	address location = operand

	input opcode

	fill out rest of 32 bit strings with "appropriate" */

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

		for(int i=0;i < cleaned.size();i++){
			cout << cleaned[i] << " ";
		}
		cout << endl;
	}

	return cleaned;
}


vector<string> RemoveWhitespace(string line){ //I will give you a crisp highfive if you can guess what this does...

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



int main(int argc, char* argv[]){
	string USAGE = "Usage: ./mb++ [filename]";
	if(argc != 2){
		cout << USAGE << endl;
		return 0;
	}

	if(!ReadFile(string(argv[1]))){return 0;}

	cout << toAssemble.size() << endl;
	return 0;
}
