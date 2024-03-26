#pragma once
#include <functional>
#include <cctype>
#include <algorithm>
template <typename T1, template<typename T1> class T2, typename T3>
class ContainsStr
{
private:
	
public:
	ContainsStr() = default;

	void containsString(typename T2<T1>::iterator begin, typename T2<T1>::iterator end, typename const T3& string, typename T2<T1>& writeToVec,
		std::function<bool(typename const T3&, typename const T3&)> predicate);
	void containsString(typename T2<T1>::iterator begin, typename T2<T1>::iterator end, typename const T3& string, typename T2<T1>& writeToVec,
		std::function<bool(typename const T3&, typename const T3&)> predicate, int indexOfColumn);
};
;
template<typename T1, template<typename T1> class T2, typename T3>
inline void ContainsStr<T1, T2, T3>::containsString(typename T2<T1>::iterator begin, typename T2<T1>::iterator end, typename const T3& string, typename T2<T1>& writeToVec,
	std::function<bool(typename const T3&, typename const T3&)> predicate)
{
	T3 stringLower = string;
	std::transform(stringLower.begin(), stringLower.end(), stringLower.begin(), std::tolower);
	for (auto i = begin; i != end; ++i)
	{
		T3 iLower = *i;
		std::transform(iLower.begin(), iLower.end(), iLower.begin(), std::tolower);
		if (predicate(stringLower, iLower))
		{
			writeToVec.push_back(*i);
		}
	}
}

template<typename T1, template<typename T1> class T2, typename T3>
inline void ContainsStr<T1, T2, T3>::containsString(typename T2<T1>::iterator begin, typename T2<T1>::iterator end, typename const T3& string, typename T2<T1>& writeToVec,
	std::function<bool(typename const T3&, typename const T3&)> predicate, int indexOfColumn)
{
	T3 stringLower = string;
	std::transform(stringLower.begin(), stringLower.end(), stringLower.begin(), std::tolower);
	for (auto i = begin; i != end; ++i)
	{
		T3 iLower = i->getBlockAt(indexOfColumn);
		std::transform(iLower.begin(), iLower.end(), iLower.begin(), std::tolower);
		if (predicate(stringLower, iLower))
		{
			writeToVec.push_back(*i);
		}
	}
}
