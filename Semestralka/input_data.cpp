#include "input_data.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

std::vector<BusStop> InputData::readFromFile()
{
	vector<BusStop> busStops;
	ifstream inputStream(file_);
	string line;
	getline(inputStream, line);
	while (getline(inputStream, line))
	{
		vector<string> atributtes;
		stringstream sstream(line);
		while (getline(sstream, line, ';'))
		{
			atributtes.push_back(line);
		}
		string name = atributtes.at(0);
		double latitude = stod(atributtes.at(1));
		double longtitude = stod(atributtes.at(2));
		string code = atributtes.at(3);
		string system = atributtes.at(4);
		string town = atributtes.at(5);

		busStops.push_back(BusStop(name, GeoPosition(latitude, longtitude), Transit(code, system), town));
	}
	

	return busStops;
}