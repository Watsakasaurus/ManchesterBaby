#include <string>
#include <vector> 

string s = "";
int counter1 = 0;
int counter2 = 0;
vector<vector<char> fileArray;

void symbolTable(string s, int counter, vector<vector<char>> fileArray)
{

vector<vector<char>>::iterator row;
vector<char>::iterator col;

for(row = fileArray.begin(); row != fileArray.end(); row++){
	for(col = row->begin(); col != row->end(); col++){
		if(s == fileArray.at(row, col)){
			counter1 == fileArray.at(row);
			counter2 == fileArray.at(col);
		}
	}
}

symbolTable.insert(pair<string, int>(s, counter))

}

int main()
{
	symbolTable()
	return 0;
}