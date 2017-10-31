//Joe Riemersma

#include <iostream>
#include <string>
#include <fstream>
#include <vector> 

using namespace std;

class Store{ 
	public:
		Store(int addresses, int registerWidth);

		vector<char> GetInstruction(int i);
		bool LoadFileIntoMemory(const string fileName); 
		void DisplayStore();


	private:
		vector<vector<char> > storeArray; //2d char array
		int addressNumber;
		int maxRegisterWidth;
};