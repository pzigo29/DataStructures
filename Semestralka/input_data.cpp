#include "input_data.h"

Transporter<std::vector> InputData::readFromFile()
{
	std::vector<BusStop> busStops;
	std::ifstream inputStream(file_);
	std::string line;
	std::getline(inputStream, line);
	while (std::getline(inputStream, line))
	{
		std::vector<std::string> atributtes;
		std::stringstream sstream(line);
		while (std::getline(sstream, line, ';'))
		{
			atributtes.push_back(line);
		}
		std::string id = atributtes.at(0);
		std::string name = atributtes.at(1);
		std::string stopSite = atributtes.at(2);
		std::string latitude = atributtes.at(3);
		std::string longtitude = atributtes.at(4);
		std::string code = atributtes.at(5);
		std::string system = atributtes.at(6);
		std::string town = atributtes.at(7);

		busStops.emplace_back(id, name, stopSite, latitude, longtitude, code, system, town);
	}
	//std::cout << "Data read from file: " << file_ << '\n';
	return Transporter<std::vector>(busStops);
}