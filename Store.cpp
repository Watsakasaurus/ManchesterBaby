//Joe Riemersma

#include "Store.h"

using namespace std;

Store::Store(int addresses, int registerWidth): addressNumber (addresses), maxRegisterWidth (registerWidth){
	storeArray.resize(addresses);
	for(int i = 0;i < storeArray.size();i++){	//Initialise 2d array;
		storeArray[i].resize(maxRegisterWidth);
		for (int j = 0; j < storeArray[i].size(); j++)
		{
			storeArray[i][j] = '0';
		}
	}	
}


bool Store::LoadFileIntoMemory(const string fileName){ //Reads file into 2D array 
	int i = 0;
	string line;

	ifstream machineCodeFile(fileName.c_str());

	if(machineCodeFile.is_open()){
		while(getline(machineCodeFile,line)){
			if(line.length() == maxRegisterWidth + 1){ //+1 Allows for newline character
				for(int j = 0; j < storeArray.size(); j++){
					if(line.at(j) != '1' && line.at(j) != '0'){
						return false;
					}
					storeArray[i][j] = line.at(j);
				}
			}else{
				return false;
			}
			i++;
		}
		machineCodeFile.close();
	}else{
		return false;
	}

	return true;
}

vector<char> Store::GetInstruction(int i){ //Returns store line from store
	return storeArray[i];
}

void Store::DisplayStore(){ //Displays contents of the store
	for(int i=0;i<storeArray.size();i++){
		for(int j=0;j<storeArray[i].size();j++){
			cout << storeArray[i][j];
		}
		cout << endl;
	}
}