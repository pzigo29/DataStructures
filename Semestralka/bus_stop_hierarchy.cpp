#include "bus_stop_hierarchy.h"

BusStopHierarchy::BusStopHierarchy()
{
    root_ = &this->busStopHierarchy_.emplaceRoot();
}

Data* BusStopHierarchy::addTransporter(std::string transporter, int index)
{
    Data& son = this->busStopHierarchy_.emplaceSon(*root_, index);
    son.data_ = transporter;
    //this->busStopHierarchy_.changeSon(*root_, index, &son);
    return &son;
}

Data* BusStopHierarchy::addMunicipality(std::string municipality, Data* transporter, int index)
{
    Data& son = this->busStopHierarchy_.emplaceSon(*transporter, index);
    son.data_ = municipality;
    //this->busStopHierarchy_.changeSon(transporter, index, &son);
    return &son;
}

void BusStopHierarchy::addBusStop(std::string busStop, Data* municipality, int index)
{
    Data& son = this->busStopHierarchy_.emplaceSon(*municipality, index);
    son.data_ = busStop;
	//this->busStopHierarchy_.changeSon(municipality, index, &busStop);
}

Data* BusStopHierarchy::getSon(Data& parent, int index)
{
    return this->busStopHierarchy_.accessSon(parent, index);
}

Data* BusStopHierarchy::getParent(Data& son)
{
    return this->busStopHierarchy_.accessParent(son);
}

Data* BusStopHierarchy::getRoot()
{
    return root_;
}
