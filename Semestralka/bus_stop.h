#pragma once
#include <string>
#include <iostream>
#include <libds/heap_monitor.h>

class BusStop
{
private:
	std::string id_;
	std::string name_;
	std::string stopSite_;
	std::string posX_;
	std::string posY_;
	std::string code_;
	std::string nameTrans_;
	std::string town_;

public:
	BusStop(std::string id, std::string name, std::string stopSite, std::string posX, std::string posY, std::string code, std::string nameTrans, std::string town)
		: id_(id), name_(name), stopSite_(stopSite), posX_(posX), posY_(posY), code_(code), nameTrans_(nameTrans), town_(town) {}

	std::string getTown()
	{
		return town_;
	}
	std::string getNameTrans()
	{
		return nameTrans_;
	}
	std::string getName()
	{
		return name_;
	}
	void coutId() const
	{
		std::cout << id_ << " ";
	}
	void coutName() const
	{
		std::cout << name_ << " ";
	}
	void coutStopSite() const
	{
		std::cout << stopSite_ << " ";
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
			/*coutId();
			std::cout << std::endl;*/
			coutName();
			std::cout << std::endl;
			/*coutStopSite();
			std::cout << std::endl;*/
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
			/*coutId();*/
			coutName();
			//coutStopSite();
			coutPosX();
			coutPosY();
			coutCode();
			coutNameTrans();
			coutTown();
			std::cout << std::endl;
		}
	}
};