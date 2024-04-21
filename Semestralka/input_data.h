#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "bus_stop.h"
#include "transporter.h"
#include <libds/heap_monitor.h>


class InputData
{
	//ODSTRANENIE STOPSITE Z CSV, NAPISAT DO DOKUMENTACIE
	std::string file_;
public:
	InputData(std::string file)
		: file_(file) {};
	Transporter<std::vector> readFromFile();

};
		
	



