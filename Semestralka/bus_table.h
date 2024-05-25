#pragma once
#include "libds/adt/table.h"
#include "libds/adt/tree.h"


template <typename K, typename T>
class BusTable : public ds::adt::Treap<K, T>
{
public:
	~BusTable() override;
	void insert(const K& key, T data, typename BusTable::BSTNodeType* node = nullptr);

	BusTable() = default;
};


template <typename K, typename T>
BusTable<K, T>::~BusTable()
{
	for (auto it = this->begin(); it != this->end(); ++it)
	{
		auto& synonym = (*it).synonym_;
		while (synonym != nullptr)
		{
			auto* nextSynonym = synonym->synonym_;
			delete synonym;
			synonym = nextSynonym;
		}
	}
}

template <typename K, typename T>
void BusTable<K, T>::insert(const K& key, T data, typename BusTable::BSTNodeType* node)
{
	try
	{
		ds::adt::Treap<K, T>::insert(key, data, node);
	}
	catch (std::invalid_argument&)
	{
		//throw std::invalid_argument("Key already exists");
		ds::adt::TreapItem<K, T>* newItem = new ds::adt::TreapItem<K, T>;
		auto& synonym = node->data_.synonym_;
		while (synonym != nullptr)
		{
			synonym = synonym->synonym_;
		}
		newItem->key_ = key;
		newItem->data_ = data;
		synonym = newItem;
	}
}

