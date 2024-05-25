#pragma once
#include <locale>
#include "libds/adt/sorts.h"

template <typename T>
class Sorting : public ds::adt::HeapSort<T>
{
	std::locale loc_;
	std::function<bool(const T&, const T&)> compareAlphabetical = [&](const T& a, const T& b) -> bool
	{
		return loc_(a->getName(), b->getName());
	};
	std::function<bool(const T&, const T&)> compareConsonantCount = [&](const T& a, const T& b) -> bool
	{
		return consonantCount(a) < consonantCount(b);
	};
	ds::amt::ImplicitSequence<T>* array_;

public:
	Sorting(ds::amt::ImplicitSequence<T>& array) : loc_("en_CA.UTF-8"), array_(&array)
	{
	}
	~Sorting() = default;
	int consonantCount(const T& string);
	void sortAlphabetical()
	{
		return this->sort(*array_, compareAlphabetical);
	}
	void sortConsonantCount()
	{
		return this->sort(*array_, compareConsonantCount);
	}
};

template <typename T>
int Sorting<T>::consonantCount(const T& string)
{
	int count = 0;
	std::string consonantsSKLow = u8"bcèdïfghjkl¾åmnòpqràsštvwxzž";
	std::string consonantsSKUp = u8"BCÈDÏFGHJKL¼ÅMNÒPQRÀSŠTVWXZŽ";
	std::string consonantsSK = consonantsSKLow + consonantsSKUp;
	//std::string consonantsENLow = "bcdfghjklmnpqrstvwxyz";
	//std::string consonantsENUp = "BCDFGHJKLMNPQRSTVWXYZ";
	//std::string consonantsEN = consonantsENLow + consonantsENUp;
	for (auto element : string->getName())
	{
		if (std::isalpha(element) && std::strchr(consonantsSK.c_str(), element))
			count++;
	}
	return count;
}
