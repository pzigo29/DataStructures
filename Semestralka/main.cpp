#include "input_data.h"
#include <sstream>
#include "CLI.h"
#include "transporter.h"
#include "bus_stop_hierarchy.h"
#include "fill_bus_stops.h"
#include <libds/heap_monitor.h>

#include "bus_table.h"
#include "sorting.h"

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



	/*BusStop* stop = new BusStop("1", "Daèo Slovenské", "null", "456", "654", "SK", "SKT", "RK");
	std::vector<BusStop*> stops;
	stops.push_back(stop);
	Transporter<std::vector>* skZastavka = new Transporter<std::vector>(stops);*/
	PredicateList<BusTable<std::string, BusStop*>> busTables(zoznamDopravcov.size());
	
	FillBusStops fillBusStops(zoznamDopravcov);
	fillBusStops.fillTable(busTables);

	//duplicita Valleyview at Knollwood (WB) - KAM

	BusStopHierarchy bsh;
	fillBusStops.fillHierarchy(bsh);
	CLI().chooseApp(zoznamDopravcov, bsh, busTables);

	return 0;
}
