#pragma once
#include <functional>
#include <cctype>
#include <algorithm>
#include <libds/heap_monitor.h>

template <typename T1, typename T2, typename iterator, template<typename T1> class T3>
class ContainsStr
{
public:
	ContainsStr() = default;

	void containsString(iterator begin, iterator end, const T2& string, T3<T1>& writeToVec,
		std::function<bool(const T2&, const T2&)> predicate);
};

template<typename T1, typename T2, typename iterator, template<typename T1> class T3>
inline void ContainsStr<T1, T2, iterator, T3>::containsString(iterator begin, iterator end, const T2& string, 
	T3<T1>& writeToVec, std::function<bool(const T2&, const T2&)> predicate)
{
	T2 stringLower = string;
	std::transform(stringLower.begin(), stringLower.end(), stringLower.begin(), std::tolower);
	for (auto i = begin; i != end; ++i)
	{
		T2 iLower = (*i).getName();
		std::transform(iLower.begin(), iLower.end(), iLower.begin(), std::tolower);
		if (predicate(stringLower, iLower))
		{
			writeToVec.push_back(*i);
		}
	}
}
