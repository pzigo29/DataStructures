#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "bus_stop.h"


class InputData
{
	//ODSTRANENIE STOPSITE Z CSV, NAPISAT DO DOKUMENTACIE
	std::string file_;
public:
	InputData(std::string file)
		: file_(file) {};
	std::vector<BusStop> readFromFile();

};
		
	



