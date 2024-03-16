#pragma once
#include <functional>
#include <cctype>
#include <algorithm>
template <typename T>
class ContainsStr
{
private:
	std::function<void(typename std::vector<T>::iterator, typename std::vector<T>::iterator, const std::string&)> 
		containsStr =
		[](typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, const std::string& string)
		{
			auto stringLower = string;
			std::transform(stringLower.begin(), stringLower.end(), stringLower.begin(), std::tolower);
			for (auto i = begin; i != end; ++i)
			{
				auto iLower = *i;
				std::transform(iLower.begin(), iLower.end(), iLower.begin(), std::tolower);
				if (iLower.find(stringLower) != std::string::npos)
				//if (iLower.compare(0, stringLower.length(), stringLower) == 0)
				{
					std::cout << *i << endl;
				}
			}
			//std::cout << endl << endl;
		};
public:
	ContainsStr() = default;

	void callLambda(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, std::string string)
	{
		containsStr(begin, end, string);
	}

	
};

