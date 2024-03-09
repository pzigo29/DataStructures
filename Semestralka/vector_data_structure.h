#pragma once
#include <vector>
template <typename T>
class VectorDataStructure
{
private:
	std::vector<T> data_;
public:
	VectorDataStructure() = default;
	void addData(T data)
	{
		data_.push_back(data);
	}
	void removeData(int index)
	{
		data_.erase(data_.begin + index);
	}
};

