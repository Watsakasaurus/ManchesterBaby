//Joe Riemersma
#include "Store.h"
#include <string>
#include <vector> 

int ADDRESS_NUMBER = 32;
int REGISTER_WIDTH = 32;
string fileName;


int main(){
	fileName = "MachineCode.txt";
	
	Store store(ADDRESS_NUMBER,REGISTER_WIDTH); //Set as 32 each for now


	if(!store.LoadFileIntoMemory(fileName)){
		cout << "Error reading file: " << fileName << endl;
		return 0;
	}

	store.DisplayStore();


	return 0;
}


