#pragma once
#include <string>
#include <iostream>

class GeoPosition
{
private:
	double latitude_;
	double longtitude_;
	friend class BusStop;
public:
	GeoPosition(double latitude, double longtitude)
	{
		setPosition(latitude, longtitude);
	}
	void setPosition(double latitude, double longtitude)
	{
		latitude_ = latitude;
		longtitude_ = longtitude;
	}
};

class Transit
{
private:
	std::string code_;
	std::string name_;
	friend class BusStop;
public:
	Transit(std::string code, std::string name)
	{
		setTransit(code, name);
	}
	void setTransit(std::string code, std::string name)
	{
		code_ = code;
		name_ = name;
	}
};

class BusStop
{
private:
	std::string name_;
	GeoPosition geoPosition_;
	Transit transit_;
	std::string town_;

public:
	BusStop(std::string name, GeoPosition pos, Transit transit, std::string town)
		: name_(name), geoPosition_(pos), transit_(transit), town_(town) {}
	void writeConsole()
	{
		std::cout << name_ << " " << geoPosition_.latitude_ << " " << geoPosition_.longtitude_ << " " << transit_.code_ << " " << transit_.name_ << " " << town_ << std::endl;
	}
};



