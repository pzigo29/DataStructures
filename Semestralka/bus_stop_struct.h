#pragma once
#include "bus_stop.h"
#include <libds/heap_monitor.h>

struct BusStopStruct
{
private:
	std::string name;
	BusStop* stop;

public:
	BusStopStruct(BusStop& stop) : name(stop.getName()), stop(&stop) {}
	BusStopStruct(std::string name) : name(name), stop(nullptr) {}
	BusStopStruct() = default;

	std::string getName() { return name; }
	BusStop* getStop() { return stop; }

	auto operator==(BusStopStruct& other) 
	{ 
		return name == other.getName() && stop == other.getStop();
	}
};

