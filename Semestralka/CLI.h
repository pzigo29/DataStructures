#pragma once
#include <functional>
#include <string>
#include "bus_stop.h"
#include "transporter.h"
#include "bus_stop_hierarchy.h"
#include "contains_str.h"
#include <libds/heap_monitor.h>
#include "predicate_list.h"

class CLI
{
    std::function<bool(const std::string&, const std::string&)> contains = [](const std::string& stringToFind, const std::string& stringToBeFound)
    {
        return stringToBeFound.find(stringToFind) != std::string::npos;
    };
    std::function<bool(const std::string&, const std::string&)> startsWith = [](const std::string& stringToFind, const std::string& stringToBeFound)
    {
        return stringToBeFound.compare(0, stringToFind.length(), stringToFind) == 0;
    };
    void predikuj(std::string predikat,
        ContainsStr<BusStopStruct*, std::string, ds::amt::Hierarchy<BlockType>::PreOrderHierarchyIterator, PredicateList> str,
        BusStopHierarchy& zoznamDopravcov, BlockType* curNode);
    BlockType* prehliadaj(BlockType* curNode);
    void vectorStartApp(std::vector<Transporter<std::vector>>& zoznamDopravcov);
    void hierarchyStartApp(BusStopHierarchy& zoznamDopravcov, BlockType* startNode = nullptr);
public:
    CLI() = default;
    
    void chooseApp(std::vector<Transporter<std::vector>>& zoznamDopravcovVector, BusStopHierarchy& zoznamDopravcovHierarchy);
    

};
