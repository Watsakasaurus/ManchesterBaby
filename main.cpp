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


int main(){
	fileName = "MachineCode.txt";
	
	Store store(ADDRESS_NUMBER,REGISTER_WIDTH); //Creates Store object
	if(!store.LoadFileIntoMemory(fileName)){
		cout << "Error reading file: " << fileName << endl;
		return 0;
	}
	store.DisplayStore();

	Operation operation(REGISTER_WIDTH); //Creates Operation object that controlls the fetch execute cycle

	return 0;
}


