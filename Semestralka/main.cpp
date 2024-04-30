#include "input_data.h"
#include <sstream>
#include "CLI.h"
#include "transporter.h"
#include "bus_stop_hierarchy.h"
#include "fill_bus_stop_hierarchy.h"
#include <libds/heap_monitor.h>

int main(int argc, char* argv[])
{
	initHeapMonitor();
	std::vector<Transporter<std::vector>> zoznamDopravcov;
	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss;
		ss << "data/" << argv[i] << "_busstops.csv";
		InputData input(ss.str());
		Transporter<std::vector> zastavky = input.readFromFile();
		zoznamDopravcov.push_back(zastavky);
	}

	BusStopHierarchy bsh;
	FillBusStopHierarchy(zoznamDopravcov).fill(bsh);
	CLI().chooseApp(zoznamDopravcov, bsh);

	return 0;
}