#pragma once
#include <libds/amt/explicit_hierarchy.h>
#include <string>
#include <libds/amt/hierarchy.h>
#include "bus_stop_struct.h"
#include <libds/heap_monitor.h>

using BlockType = ds::amt::MultiWayExplicitHierarchyBlock<BusStopStruct>;
class BusStopHierarchy : public ds::amt::MultiWayEH<BusStopStruct>
{
	BlockType* root_;
public:
	BusStopHierarchy();
	BlockType* addTransporter(std::string transporter, int index);
	BlockType* addMunicipality(std::string municipality, BlockType* transporter, int index);
	BlockType* addBusStop(BusStopStruct busStop, BlockType* municipality, int index);
	BlockType* getSon(BlockType& parent, int index) const;
	BlockType* getParent(BlockType& son) const;
	BlockType* getRoot() const;
	BlockType* getTransporter(int indexTrans) const;
	BlockType* getMunicipality(int indexTrans ,int indexMuni) const;
	BlockType* getBusStop(int indexTrans, int indexMuni, int indexStop) const;
};

