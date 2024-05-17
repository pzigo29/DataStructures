#pragma once
#include "bus_stop_hierarchy.h"
#include <libds/amt/implicit_sequence.h>
#include <libds/heap_monitor.h>

template <typename T>
class PredicateList : public ds::amt::ImplicitSequence<T>
{
public:
	PredicateList() = default;
	PredicateList(size_t size)
	{
		for (size_t i = 0; i < size; i++)
		{
			this->insertLast();
		}
	}
	void push_back(T str)
	{
		auto& data = ds::amt::ImplicitSequence<T>::insertLast();
		data.data_ = str;
	}
	auto operator[](size_t index) const
	{
		return ds::amt::ImplicitSequence<T>::access(index);
	}
};

