#pragma once
#include <functional>

template <typename T1, typename T2, typename iterator, template<typename T1> class T3>
class ContainsStr
{
public:
	ContainsStr() = default;

	void containsString(iterator begin, iterator end, const T2& string, T3<T1>& writeToVec,
		std::function<bool(const T2&, const T2&)> predicate);
};

template<typename T1, typename T2, typename iterator, template<typename T1> class T3>
void ContainsStr<T1, T2, iterator, T3>::containsString(iterator begin, iterator end, const T2& string, 
	T3<T1>& writeToVec, std::function<bool(const T2&, const T2&)> predicate)
{
	for (auto i = begin; i != end; ++i)
	{
		if (predicate(string, (*i).getName()))
			writeToVec.push_back(&(*i));
	}
}