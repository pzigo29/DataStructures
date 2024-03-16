#include "input_data.h"
#include <iostream>
#include <sstream>
#include "contains_str.h"


int main(int argc, char* argv[])
{
	//ODSTRANENIE STOPSITE A STOPID Z CSV, NAPISAT DO DOKUMENTACIE
	std::vector<std::vector<std::vector<std::string>>> zoznamDopravcov;
	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss;
		ss << "data/" << argv[i] << "_busstops.csv";
		InputData<std::string> input(ss.str());
		std::vector<std::vector<std::string>> zastavky = input.readFromFile();
		zoznamDopravcov.push_back(zastavky);

		
	}
	auto containsStr = [](vector<string>::iterator begin, vector<string>::iterator end)
		{
			for (auto i = begin; i != end; ++i)
			{
				cout << *i << endl;
			}
		};
	//containsStr(zoznamDopravcov[0][0].begin(), zoznamDopravcov[0][0].end());

	ContainsStr<std::string> str;
	for (int i = 0; i < zoznamDopravcov[0].size(); i++)
	{
		str.callLambda(zoznamDopravcov[0][i].begin(), zoznamDopravcov[0][i].end(), "778704");
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