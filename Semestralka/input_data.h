#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "bus_stop.h"


using namespace std;

template <typename T>
class InputData
{
	//ODSTRANENIE STOPSITE Z CSV, NAPISAT DO DOKUMENTACIE
	std::string file_;
public:
	InputData(std::string file)
		: file_(file) {};
	std::vector<std::vector<T>> readFromFile();

};

	template <typename T>
	std::vector<std::vector<T>> InputData<T>::readFromFile()
	{
		/*vector<T> name;
		vector<T> latitude;
		vector<T> longtitude;
		vector<T> code;
		vector<T> system;
		vector<T> town;*/
		vector<vector<T>> busStops;
		//busStops.insert(busStops.end(), { name, latitude, longtitude, code, system, town });
		ifstream inputStream(file_);
		string line;
		getline(inputStream, line);
		while (getline(inputStream, line))
		{
			vector<T> attributes;
			stringstream sstream(line);
			while (getline(sstream, line, ';'))
			{
				attributes.push_back(line);
			}
			/*name.push_back(attributes.at(0));
			latitude.push_back(attributes.at(1));
			longtitude.push_back(attributes.at(2));
			code.push_back(attributes.at(3));
			system.push_back(attributes.at(4));
			town.push_back(attributes.at(5));*/
			busStops.push_back(attributes);
		}


		return busStops;
	}



