#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


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
		vector<vector<T>> busStops;
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
			busStops.push_back(attributes);
		}
		return busStops;
	}



