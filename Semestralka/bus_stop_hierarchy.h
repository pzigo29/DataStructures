#pragma once
#include <libds/amt/explicit_hierarchy.h>
#include <string>
using Data = ds::amt::MultiWayExplicitHierarchyBlock<std::string>;
class BusStopHierarchy
{
	Data* root_;
    ds::amt::MultiWayExplicitHierarchy<std::string> busStopHierarchy_;

public:
	BusStopHierarchy();
	Data* addTransporter(std::string transporter, int index);
	Data* addMunicipality(std::string municipality, Data* transporter, int index);
	void addBusStop(std::string busStop, Data* municipality, int index);
	Data* getSon(Data& parent, int index);
	Data* getParent(Data& son);
	Data* getRoot();
};

