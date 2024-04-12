#include "input_data.h"
#include <iostream>
#include <sstream>
#include "contains_str.h"
#include "CLI.h"
#include "transporter.h"
#include "bus_stop_hierarchy.h"
#include "fill_bus_stop_hierarchy.h"


int main(int argc, char* argv[])
{
	//ODSTRANENIE STOPSITE A STOPID Z CSV, NAPISAT DO DOKUMENTACIE
	std::vector<Transporter<std::vector>> zoznamDopravcov;
	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss;
		ss << "data/" << argv[i] << "_busstops.csv";
		InputData input(ss.str());
		Transporter<std::vector> zastavky = input.readFromFile();
		zoznamDopravcov.push_back(zastavky);
	}
	//CLI().vectorStartApp(zoznamDopravcov);

	BusStopHierarchy bsh;
	FillBusStopHierarchy fbsh(zoznamDopravcov);
	fbsh.fill(bsh);

	auto son = bsh.getSon(*bsh.getRoot(), 0);
	auto sonSon = bsh.getSon(*son, 1);
	std::cout << son->data_ << std::endl;
	std::cout << sonSon->data_ << std::endl;
	std::cout << bsh.getSon(*sonSon, 0)->data_;
	return 0;
}