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

	void containsString(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, const std::string& string, typename std::vector<T>& writeToVec, 
		std::function<bool(const std::string&, const std::string&)> predicate = 
		[](const std::string& string, const std::string& iLower)
		{return iLower.find(string) != std::string::npos; });
};

template<typename T>
inline void ContainsStr<T>::containsString(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, const std::string& string, typename std::vector<T>& writeToVec, std::function<bool(const std::string&, const std::string&)> predicate)
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
