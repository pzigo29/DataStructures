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
		std::string hladanyString, skratkaDopravcu;
		//std::string skratkaDopravcu;
		std::vector<int> indexDopravcu;
		int indexStlpca;
		std::cout << "Zadaj: contains alebo startsWith (exit pre ukoncenie aplikacie)" << std::endl;
		std::cin >> predikat;
		if (predikat == "exit")
		{
			return 0;
		}
        std::cout << "hladanyString" << std::endl;
        std::getline(std::cin >> std::ws, hladanyString);
        std::cout << "dopravca" << std::endl;
        std::getline(std::cin >> std::ws, skratkaDopravcu);


		if (skratkaDopravcu == "COW" || skratkaDopravcu == "cow" || skratkaDopravcu == "0")
		{
			indexDopravcu.push_back(0);
		}
		else if (skratkaDopravcu == "KAM" || skratkaDopravcu == "kam" || skratkaDopravcu == "1")
		{
			indexDopravcu.push_back(1);
		}
		else if (skratkaDopravcu == "NAN" || skratkaDopravcu == "nan" || skratkaDopravcu == "2")
		{
			indexDopravcu.push_back(2);
		}
		else if (skratkaDopravcu == "VIC" || skratkaDopravcu == "vic" || skratkaDopravcu == "3")
		{
			indexDopravcu.push_back(3);
		}
		else if (skratkaDopravcu == "VLY" || skratkaDopravcu == "vly" || skratkaDopravcu == "4")
		{
			indexDopravcu.push_back(4);
		}
		else if (skratkaDopravcu == "WHI" || skratkaDopravcu == "whi" || skratkaDopravcu == "5")
		{
			indexDopravcu.push_back(5);
		}
		else if (skratkaDopravcu == "WIL" || skratkaDopravcu == "wil" || skratkaDopravcu == "6")
		{
			indexDopravcu.push_back(6);
		}
		else if (skratkaDopravcu == "WKT" || skratkaDopravcu == "wkt" || skratkaDopravcu == "7")
		{
			indexDopravcu.push_back(7);
		}
		else
		{
			if (skratkaDopravcu != "ALL" && skratkaDopravcu != "all")
				std::cout << "Neplatný vstup, prehladavam vsetky" << std::endl;
			for (int i = 0; i < zoznamDopravcov.size(); i++)
			{
				indexDopravcu.push_back(i);
			}
		}
		if (predikat == "contains")
		{
			for (int i = 0; i < indexDopravcu.size(); ++i)
			{
				str.containsString(zoznamDopravcov[indexDopravcu[i]].begin(), zoznamDopravcov[indexDopravcu[i]].end(),
					hladanyString, predikatVec, contains, 0);
			}
		}
		else if (predikat == "startsWith")
		{
			for (int i = 0; i < indexDopravcu.size(); ++i)
			{
				str.containsString(zoznamDopravcov[indexDopravcu[i]].begin(), zoznamDopravcov[indexDopravcu[i]].end(),
					hladanyString, predikatVec, startsWith, 0);
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