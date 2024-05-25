#pragma once
#include "bus_stop.h"

struct BusStopStruct
{
private:
	std::string name_;
	BusStop* stop_;

public:
	BusStopStruct(BusStop& stop) : name_(stop.getName()), stop_(&stop) {}
	BusStopStruct(std::string name) : name_(name), stop_(nullptr) {}
	BusStopStruct() = default;

	std::string getName() { return name_; }
	BusStop* getStop() const { return stop_; }

	auto operator==(BusStopStruct& other) const
	{ 
		return name_ == other.getName() && stop_ == other.getStop();
	}
};

