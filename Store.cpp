//Joe Riemersma

#include "Store.h"

using namespace std;

Store::Store(int addresses, int registerWidth): addressNumber (addresses), maxRegisterWidth (registerWidth){
	storeArray.resize(addresses);
	for(int i = 0;i < storeArray.size();i++){	//Initialise 2d array;
		storeArray[i].resize(maxRegisterWidth);
	}	
}


bool Store::LoadFileIntoMemory(const string fileName){
	int j = 0;
	string line;
	ifstream machineCode("MachineCode.txt");

	if(machineCode.is_open()){
		while(getline(machineCode,line)){
			if(line.length() == maxRegisterWidth + 1){ //+1 Allows for newline character
				for(int i = 0; i < storeArray.size(); i++){
					if(line.at(i) != '1' && line.at(i) != '0'){
						return false;
					}
					storeArray[j][i] = line.at(i);
				}
			}else{
				return false;
			}
			j++;
		}
		machineCode.close();
	}else{
		return false;
	}

	return true;
}

vector<char> Store::GetInstruction(int i){
	return storeArray[i];
}

void Store::DisplayStore(){
	for(int i=0;i<storeArray.size();i++){
		for(int j=0;j<storeArray[i].size();j++){
			cout << storeArray[i][j];
		}
		cout << endl;
	}
}