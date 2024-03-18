#pragma once
#include <functional>
#include <cctype>
#include <algorithm>
template <typename T>
class ContainsStr
{
private:

public:
	ContainsStr() = default;

	void containsString(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, typename const T& string, typename std::vector<T>& writeToVec,
		std::function<bool(typename const T&, typename const T&)> predicate);
};

template<typename T>
inline void ContainsStr<T>::containsString(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, typename const T& string, typename std::vector<T>& writeToVec, std::function<bool(typename const T&, typename const T&)> predicate)
{
	auto stringLower = string;
	std::transform(stringLower.begin(), stringLower.end(), stringLower.begin(), std::tolower);
	for (auto i = begin; i != end; ++i)
	{
		auto iLower = *i;
		std::transform(iLower.begin(), iLower.end(), iLower.begin(), std::tolower);
		if (predicate(stringLower, iLower))
		{
			writeToVec.push_back(*i);
		}
	}
}
