#include "bus_stop_hierarchy.h"

BusStopHierarchy::BusStopHierarchy()
{
    root_ = &ds::amt::MultiWayEH<BusStopStruct>::emplaceRoot();
    root_->data_ = BusStopStruct("root");
}

BlockType* BusStopHierarchy::addTransporter(std::string transporter, int index)
{
    BlockType& son = this->emplaceSon(*root_, index);
    son.data_ = transporter;
    return &son;
}

BlockType* BusStopHierarchy::addMunicipality(std::string municipality, BlockType* transporter, int index)
{
    BlockType& son = this->emplaceSon(*transporter, index);
    son.data_ = municipality;
    return &son;
}

BlockType* BusStopHierarchy::addBusStop(BusStopStruct busStop, BlockType* municipality, int index)
{
    BlockType& son = this->emplaceSon(*municipality, index);
    son.data_ = busStop;
    return &son;
}

BlockType* BusStopHierarchy::getSon(BlockType& parent, int index) const
{
    return this->accessSon(parent, index);
}

BlockType* BusStopHierarchy::getParent(BlockType& son) const
{
    return this->accessParent(son);
}

BlockType* BusStopHierarchy::getRoot() const
{
    return root_;
}

BlockType* BusStopHierarchy::getTransporter(int indexTrans) const
{
	return this->accessSon(*root_, indexTrans);
}

BlockType* BusStopHierarchy::getMunicipality(int indexTrans, int indexMuni) const
{
	return this->accessSon(*this->accessSon(*root_, indexTrans), indexMuni);
}

BlockType* BusStopHierarchy::getBusStop(int indexTrans, int indexMuni, int indexStop) const
{
	return this->accessSon(*this->accessSon(*this->accessSon(*root_, indexTrans), indexMuni), indexStop);
}
