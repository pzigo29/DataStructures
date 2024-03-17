#include "input_data.h"
#include <iostream>
#include <sstream>
#include "contains_str.h"


int main(int argc, char* argv[])
{
	//ODSTRANENIE STOPSITE A STOPID Z CSV, NAPISAT DO DOKUMENTACIE
	vector<vector<vector<string>>> zoznamDopravcov;
	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss;
		ss << "data/" << argv[i] << "_busstops.csv";
		InputData<std::string> input(ss.str());
		std::vector<std::vector<std::string>> zastavky = input.readFromFile();
		zoznamDopravcov.push_back(zastavky);

		
	}
	auto contains = [](const std::string& stringToFind, const std::string& stringToBeFound)
		{return stringToBeFound.find(stringToFind) != std::string::npos; };
	auto startsWith = [](const std::string& stringToFind, const std::string& stringToBeFound)
		{return stringToBeFound.compare(0, stringToFind.length(), stringToFind) == 0; };

	ContainsStr<std::string> str;
	vector<vector<string>> predikatVec(zoznamDopravcov.size());
	for (int i = 0; i < zoznamDopravcov.size(); ++i)
	{
		for (int j = 0; j < zoznamDopravcov[i].size(); ++j)
		{
			str.containsString(zoznamDopravcov[i][j].begin(), zoznamDopravcov[i][j].end(), "dan", predikatVec[i], contains);
		}
	}
	
	for (int i = 0; i < predikatVec.size(); ++i)
	{
		cout << endl << i << zoznamDopravcov[i][0][3] << endl;
		for (int j = 0; j < predikatVec[i].size(); ++j)
		{
			cout << predikatVec[i][j] << endl;
		}
		
	}
	

	
	/*for (int i = 0; i < zoznamDopravcov.size(); i++)
	{
		for (int j = 0; j < zoznamDopravcov[i].size(); j++)
		{
			for (int k = 0; k < zoznamDopravcov[i][j].size(); k++)
			{
				cout << zoznamDopravcov[i][j][k] << "\t";
			}
			cout << endl;
		}
		std::cout << "\n\n\n";
	}*/
	return 0;
}