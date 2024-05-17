#pragma once
#include "bus_stop_hierarchy.h"

#include "bus_table.h"
#include "libds/adt/array.h"

template <typename T>
class FillBusStops
{
	T& zoznamDopravcov_; //std::vector<Transporter>
public:
	FillBusStops(T& zoznamDopravcov) :
		zoznamDopravcov_(zoznamDopravcov) {}
	void fillHierarchy(BusStopHierarchy& busStopHierarchy);
	void fillTable(PredicateList<BusTable<std::string, BusStop*>>& busStopTable);
};

template<typename T>
void FillBusStops<T>::fillHierarchy(BusStopHierarchy& busStopHierarchy)
{
	for (auto i = 0; i < zoznamDopravcov_.size(); ++i)
	{
		if (zoznamDopravcov_[i].size() != 0)
		{
			BlockType* curTransporter = busStopHierarchy.addTransporter(zoznamDopravcov_[i].getNameTrans(), i);
			BlockType* curTown = busStopHierarchy.addMunicipality(zoznamDopravcov_[i].begin()->getTown(), curTransporter, 0);
			
			for (auto ii = zoznamDopravcov_[i].begin(); ii != zoznamDopravcov_[i].end(); ++ii)
			{
			BusStopLoop:
				if (curTown->data_.getName() == ii->getTown())
				{
					busStopHierarchy.addBusStop(BusStopStruct(*ii), curTown, curTown->sons_->size());
				}
				else
				{
					for (auto iii = 0; iii < curTransporter->sons_->size(); ++iii)
					{
						if (ii->getTown() == curTransporter->sons_->access(iii)->data_->data_.getName())
						{
							curTown = curTransporter->sons_->access(iii)->data_;
							goto BusStopLoop;
						}
					}
					curTown = busStopHierarchy.addMunicipality(ii->getTown(), curTransporter, curTransporter->sons_->size());
					goto BusStopLoop;
				}
			}
		}
	}
}

template <typename T>
void FillBusStops<T>::fillTable(PredicateList<BusTable<std::string, BusStop*>>& busStopTable)
{
	
	for (int i = 0; i < busStopTable.size(); ++i)
	{
		for (auto ii = zoznamDopravcov_[i].begin(); ii != zoznamDopravcov_[i].end(); ++ii)
		{
			busStopTable.access(i)->data_.insert((*ii).getName(), &*ii, nullptr);
		}
	}
}
