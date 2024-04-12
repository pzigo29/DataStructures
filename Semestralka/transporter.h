#pragma once
#include "bus_stop.h"
#include <vector>

template <template <typename T1> class T>
class Transporter
{
    typename T<BusStop> zoznamObci_; //std::vector<BusStop>
public:
    Transporter(T<BusStop> zoznamObci) :
        zoznamObci_(zoznamObci) {}

    typename T<BusStop>::iterator begin() { return zoznamObci_.begin(); }
    typename T<BusStop>::iterator end() { return zoznamObci_.end(); }
    std::string getNameTrans() { return zoznamObci_[0].getNameTrans(); }
    int size() { return zoznamObci_.size(); }
};
