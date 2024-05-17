#pragma once
#include <functional>
#include <string>
#include "bus_stop.h"
#include "transporter.h"
#include "bus_stop_hierarchy.h"
#include "contains_str.h"
#include "bus_table.h"
#include "predicate_list.h"

class CLI
{
    std::function<bool(const std::string&, const std::string&)> contains = [](const std::string& stringToFind, const std::string& stringToBeFound)
    {
        std::locale locale("en_CA");
        std::string stringToFindLower = stringToFind;
        std::transform(stringToFindLower.begin(), stringToFindLower.end(), stringToFindLower.begin(), std::tolower);
        std::string stringToBeFoundLower = stringToBeFound;
        std::transform(stringToBeFoundLower.begin(), stringToBeFoundLower.end(), stringToBeFoundLower.begin(), std::tolower);
        return stringToBeFoundLower.find(stringToFindLower) != std::string::npos;
    };
    std::function<bool(const std::string&, const std::string&)> startsWith = [](const std::string& stringToFind, const std::string& stringToBeFound)
    {
    	std::locale locale("en_CA");
        std::string stringToFindLower = stringToFind;
        std::transform(stringToFindLower.begin(), stringToFindLower.end(), stringToFindLower.begin(), std::tolower);
        std::string stringToBeFoundLower = stringToBeFound;
        std::transform(stringToBeFoundLower.begin(), stringToBeFoundLower.end(), stringToBeFoundLower.begin(), std::tolower);
        return stringToBeFoundLower.compare(0, stringToFindLower.length(), stringToFindLower) == 0;
    };
    void predikuj(std::string predikat,
        ContainsStr<BusStopStruct*, std::string, ds::amt::Hierarchy<BlockType>::PreOrderHierarchyIterator, PredicateList> str,
        BusStopHierarchy& zoznamDopravcov, BlockType* curNode);
    BlockType* prehliadaj(BlockType* curNode);
    void vectorStartApp(std::vector<Transporter<std::vector>>& zoznamDopravcov);
    void hierarchyStartApp(BusStopHierarchy& zoznamDopravcov, BlockType* startNode = nullptr);
    void tableStartApp(PredicateList<BusTable<std::string, BusStop*>>& array);
public:
    CLI() = default;

    
    void chooseApp(std::vector<Transporter<std::vector>>& zoznamDopravcovVector, BusStopHierarchy& zoznamDopravcovHierarchy, PredicateList<BusTable<std::string, BusStop*>>& busStopTable);
    

};
