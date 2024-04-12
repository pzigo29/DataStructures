#pragma once
#include "bus_stop_hierarchy.h"

using Data = ds::amt::MultiWayExplicitHierarchyBlock<std::string>;
template <typename T>
class FillBusStopHierarchy
{
	T& zoznamDopravcov_; //std::vector<Transporter>
public:
	FillBusStopHierarchy(T& zoznamDopravcov) :
		zoznamDopravcov_(zoznamDopravcov) {}
	void fill(BusStopHierarchy& busStopHierarchy);
};

template<typename T>
inline void FillBusStopHierarchy<T>::fill(BusStopHierarchy& busStopHierarchy)
{
	for (auto i = 0; i < zoznamDopravcov_.size(); ++i)
	{
		if (zoznamDopravcov_[i].size() != 0)
		{
			Data* curTransporter = busStopHierarchy.addTransporter(zoznamDopravcov_[i].getNameTrans(), i);
			Data* curTown = busStopHierarchy.addMunicipality(zoznamDopravcov_[i].begin()->getTown(), curTransporter, 0);
			
			for (auto ii = zoznamDopravcov_[i].begin(); ii != zoznamDopravcov_[i].end(); ++ii)
			{
			BusStopLoop:
				if (curTown->data_ == ii->getTown())
				{
					busStopHierarchy.addBusStop(ii->getName(), curTown, curTown->sons_->size());
				}
				else
				{
					// neviem ci kvoli tomuto to nebude O(n), ale neviem ako to inak spravit
					for (auto iii = 0; iii < curTransporter->sons_->size(); ++iii)
					{
						if (ii->getTown() == curTransporter->sons_->access(iii)->data_->data_)
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
