#include <functional>
#include <string>
#include "bus_stop.h"
#include "transporter.h"

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
public:
    CLI() = default;
    void vectorStartApp(std::vector<Transporter<std::vector>> zoznamDopravcov);
};
