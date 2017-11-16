#include <string>
#include <vector> 
#include <iostream>
#include <fstream>

using namespace std;

void readAndVectorise()
{

	string fileName = "";
	bool exists = false;

	while (fileName == "" && exists == false)
	{

		cout << "Please enter the name of the file you would like to read from: " << '\n';

		cin >> fileName;

		ifstream myfile(fileName);

		if (myfile.is_open())
		{
			cout << "The file you entered exists." << endl;


			






			
		}
		else
		{
			cin.ignore(100);
			cin.clear();
			cout << "The file you entered does not exist" << endl;
		} 
	}

	//stringstream ss

	//vector methods, how to read lines of text into vectors 

}

void deleteComments()
{
	/*1st pass thru tokens

	get rid of comments from the vector created before

	use .erase to get rid of anything after semi-colon*/

}


void createSymbolTable()
{

	/*2nd pass thru tokens

	search for variables and labels(start, end)

	everytime a variable is called, use the reference to the place in memory the variable is stored

	if var01 = 1025, points to the space in memory*/

}

void instructionConversion()
{
	string opCode = ""; //this needs to be passed from symbol table function

	if(opCode == "JMP")
		{
			opCode = "000";
		}

	else if(opCode == "JRP")
		{
			opCode = "100";
		}

	else if(opCode == "LDN")
		{
			opCode = "010";
		}

	else if(opCode == "STO")
		{
			opCode = "110";
		}

	else if(opCode == "SUB")
		{
			opCode = "001";
		}

	else if(opCode == "SUB")
		{
			opCode = "101";
		}

	else if(opCode == "CMP")
		{
			opCode = "011";
		}

	else if(opCode == "STP")
		{
			opCode = "111";
		}

}

void convertToMachineCode()
{
/*
	address location = operand

	input opcode

	fill out rest of 32 bit strings with "appropriate" */

}

int main () 

{
	readAndVectorise();
	return 0;
} 
