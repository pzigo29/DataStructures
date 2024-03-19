#pragma once
#include <string>
#include <iostream>

class BusStop
{
private:
	std::string name_;
	std::string posX_;
	std::string posY_;
	std::string code_;
	std::string nameTrans_;
	std::string town_;
	std::vector<std::string> columns;

public:
	BusStop(std::string name, std::string posX, std::string posY, std::string code, std::string nameTrans, std::string town)
		: name_(name), posX_(posX), posY_(posY), code_(code), nameTrans_(nameTrans), town_(town), 
			columns({name_, posX_, posY_, code_, nameTrans_, town_}) {}
	std::string getBlockAt(int index)
	{
		return columns[index];
	}
	void coutName() const
	{
		std::cout << name_ << " ";
	}
	void coutPosX() const
	{
		std::cout << posX_ << " ";
	}
	void coutPosY() const
	{
		std::cout << posY_ << " ";
	}
	void coutCode() const
	{
		std::cout << code_ << " ";
	}
	void coutNameTrans() const
	{
		std::cout << nameTrans_ << " ";
	}
	void coutTown() const
	{
		std::cout << town_ << " ";
	}
	void coutAll(bool podSebou) const
	{
		if (podSebou)
		{
			coutName();
			std::cout << std::endl;
			coutPosX();
			std::cout << std::endl;
			coutPosY();
			std::cout << std::endl;
			coutCode();
			std::cout << std::endl;
			coutNameTrans();
			std::cout << std::endl;
			coutTown();
			std::cout << std::endl;
		}
		else
		{
			coutName();
			coutPosX();
			coutPosY();
			coutCode();
			coutNameTrans();
			coutTown();
			std::cout << std::endl;
		}
	}
};