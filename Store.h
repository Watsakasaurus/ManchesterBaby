//Joe Riemersma

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//Store Class, contains operations for accessing and changing contents of the store.
class Store{
	public:
		Store(int addresses, int registerWidth);

		vector<char> GetInstruction(int i);
		bool LoadFileIntoMemory(const string fileName);
		void WriteToStore(int i, vector<char> newItem);
		void DisplayStore();
		vector<vector<char> > GetStore();

	private:
		vector<vector<char> > storeArray; //2d char array
		int addressNumber;
		int maxRegisterWidth;
};
