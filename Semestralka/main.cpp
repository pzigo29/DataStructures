#include "input_data.h"
#include <iostream>
#include <sstream>
#include "contains_str.h"


int main(int argc, char* argv[])
{
	//ODSTRANENIE STOPSITE A STOPID Z CSV, NAPISAT DO DOKUMENTACIE
	std::vector<std::vector<BusStop>> zoznamDopravcov;
	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss;
		ss << "data/" << argv[i] << "_busstops.csv";
		InputData input(ss.str());
		std::vector<BusStop> zastavky = input.readFromFile();
		zoznamDopravcov.push_back(zastavky);

		
	}
	auto contains = [](const std::string& stringToFind, const std::string& stringToBeFound)
		{return stringToBeFound.find(stringToFind) != std::string::npos; };
	auto startsWith = [](const std::string& stringToFind, const std::string& stringToBeFound)
		{return stringToBeFound.compare(0, stringToFind.length(), stringToFind) == 0; };

	ContainsStr<BusStop, std::vector, std::string> str;
	

	while (true)
	{
		std::vector<BusStop> predikatVec;
		std::string predikat;
		std::string hladanyString;
		int indexStlpca;
		std::cout << "Zadaj: contains alebo startsWith (exit pre ukoncenie aplikacie)" << std::endl;
		std::cin >> predikat;
		if (predikat == "exit")
		{
			return 0;
		}
		std::cout << "Parametre (oddelené medzerou) : hladanyString indexStlpca" << std::endl;
		std::cin >> hladanyString >> indexStlpca;

		if (predikat == "contains")
		{
			for (int i = 0; i < zoznamDopravcov.size(); ++i)
			{
				str.containsString(zoznamDopravcov[i].begin(), zoznamDopravcov[i].end(), 
					hladanyString, predikatVec, contains, indexStlpca);
			}
		}
		else if (predikat == "startsWith")
		{
			for (int i = 0; i < zoznamDopravcov.size(); ++i)
			{
				str.containsString(zoznamDopravcov[i].begin(), zoznamDopravcov[i].end(),
					hladanyString, predikatVec, startsWith, indexStlpca);
			}
		}
		else
		{
			std::cout << "Neplatný vstup" << std::endl;
			continue;
		}


		for (int i = 0; i < predikatVec.size(); ++i)
		{
			predikatVec[i].coutAll(false);

		}
	}
	return 0;
}