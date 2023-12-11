#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

class Currency {
	
	public:
	long int currency_value; 
	string currency_name;
	
	Currency(void) {
	}

	void print_currency() {
		cout << currency_name << " ";
		cout << currency_value << '\n';
	}
};

// Array of objects
// Maximum 100 currencies
Currency curr[100];

// Func that splits string by word 
int splitStr(string str)
	{
		string name = "";
		string value = "";
		
		int previous_blank = 1;
		int n = 0;					//n indicates if the variable is a str or int (name or value)
		int b = 0;					//b indicates the holder for one currency
		for (auto x : str)
		{
			if (x == ' ' || x == '\n' || x == '\t')
			{
				if (previous_blank == 1) 
				{
					continue;
				}
				if (n == 0)
				{
					curr[b].currency_name = name;
					name = "";
					n = 1;
				}
				else if (n == 1)
				{
					curr[b].currency_value = strtol(value.c_str(), NULL, 10);
					b+=1;
					value = "";
					n = 0;
				}
				previous_blank = 1;
			}
			else 
			{
				if (n == 0)
				{
					name = name + x;
				}
				else if (n == 1)
				{
					value = value + x;
				}
				previous_blank = 0;
			}
		}
		if (previous_blank == 0) 
		{
			curr[b].currency_value = strtol(value.c_str(), NULL, 10);
			b+=1;
		}
		return b;
	}


// Driver code
int main() {
	
	ifstream file;
	
	file.open("currency.txt");
	if (file.fail())
	{
		cout << "File failed to open." << endl;
		return 1;
	}
	
	stringstream buffer;
	buffer << file.rdbuf();
	string file_content;
	
	file_content = buffer.str();

	file.close();
	
	int n = splitStr(file_content);
	
	for (int i = 0; i < n; i++) 
	{
		curr[i].print_currency();
	}
	
	return 0;
}