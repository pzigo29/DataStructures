#include "input_data.h"
#include <iostream>,
#include <sstream>

int main(int argc, char* argv[])
{
	//ODSTRANENIE STOPSITE A STOPID Z CSV, NAPISAT DO DOKUMENTACIE
	std::vector<std::vector<BusStop>> zoznamDopravcov;
	for (int i = 0; i < argc; i++)
	{
		std::stringstream ss;
		ss << "data/" << argv[i] << "_busstops.csv";
		InputData input(ss.str());
		std::vector<BusStop> zastavky = input.readFromFile();
		zoznamDopravcov.push_back(zastavky);
	}

	
	//for (int i = 0; i < zoznamDopravcov.size(); i++)
	//{
	//	for (int j = 0; j < zoznamDopravcov[i].size(); j++)
	//	{
	//		zoznamDopravcov[i][j].writeConsole();
	//	}
	//	std::cout << "\n\n\n";
	//}
	return 0;
}