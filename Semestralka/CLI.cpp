#include "CLI.h"
#include "contains_str.h"
#include "predicate_list.h"
#include "sorting.h"

void CLI::vectorStartApp(std::vector<Transporter<std::vector>>& zoznamDopravcov)
{
	
	ContainsStr<BusStop*, std::string, std::vector<BusStop>::iterator, std::vector> str;

	while (true)
	{
		std::vector<BusStop*> predikatVec;
		std::string predikat, hladanyString, skratkaDopravcu;
		std::vector<int> indexDopravcu;
		std::cout << "Algoritmus Contains:\n 'contains' || '-c'\n"
			   "Algoritmus StartsWith:\n 'startsWith' || '-s'\n"
		       "Ukoncenie aplikacie:\n 'exit' || '-e'\n";
		std::cin >> predikat;
		if (predikat == "exit" || predikat == "-e")
		{
			return;
		}
		std::cout << "hladanyString" << std::endl;
		std::getline(std::cin >> std::ws, hladanyString);
		std::cout << "dopravca" << std::endl;
		std::getline(std::cin >> std::ws, skratkaDopravcu);


		if (skratkaDopravcu == "COW" || skratkaDopravcu == "cow" || skratkaDopravcu == "0")
		{
			indexDopravcu.push_back(0);
		}
		else if (skratkaDopravcu == "KAM" || skratkaDopravcu == "kam" || skratkaDopravcu == "1")
		{
			indexDopravcu.push_back(1);
		}
		else if (skratkaDopravcu == "NAN" || skratkaDopravcu == "nan" || skratkaDopravcu == "2")
		{
			indexDopravcu.push_back(2);
		}
		else if (skratkaDopravcu == "VIC" || skratkaDopravcu == "vic" || skratkaDopravcu == "3")
		{
			indexDopravcu.push_back(3);
		}
		else if (skratkaDopravcu == "VLY" || skratkaDopravcu == "vly" || skratkaDopravcu == "4")
		{
			indexDopravcu.push_back(4);
		}
		else if (skratkaDopravcu == "WHI" || skratkaDopravcu == "whi" || skratkaDopravcu == "5")
		{
			indexDopravcu.push_back(5);
		}
		else if (skratkaDopravcu == "WIL" || skratkaDopravcu == "wil" || skratkaDopravcu == "6")
		{
			indexDopravcu.push_back(6);
		}
		else if (skratkaDopravcu == "WKT" || skratkaDopravcu == "wkt" || skratkaDopravcu == "7")
		{
			indexDopravcu.push_back(7);
		}
		else
		{
			if (skratkaDopravcu != "ALL" && skratkaDopravcu != "all")
				std::cout << "Neplatny vstup, prehladavam vsetky" << std::endl;
			for (int i = 0; i < zoznamDopravcov.size(); i++)
			{
				indexDopravcu.push_back(i);
			}
		}
		if (predikat == "contains" || predikat == "-c")
		{
			for (int i = 0; i < indexDopravcu.size(); ++i)
			{
				str.containsString(zoznamDopravcov[indexDopravcu[i]].begin(), zoznamDopravcov[indexDopravcu[i]].end(),
					hladanyString, predikatVec, contains);
			}
		}
		else if (predikat == "startsWith" || predikat == "-s")
		{
			for (int i = 0; i < indexDopravcu.size(); ++i)
			{
				str.containsString(zoznamDopravcov[indexDopravcu[i]].begin(), zoznamDopravcov[indexDopravcu[i]].end(),
					hladanyString, predikatVec, startsWith);
			}
		}
		else
		{
			std::cout << "Neplatny vstup" << std::endl;
			continue;
		}


		for (int i = 0; i < predikatVec.size(); ++i)
		{
			predikatVec[i]->coutAll(false);
		}
	}
}

void CLI::hierarchyStartApp(BusStopHierarchy& zoznamDopravcov, BlockType* startNode)
{
	/*int* test = (int*)std::malloc(5);
	test[0] = 1;
	std::cout << test[0] << std::endl;
	free (test);*/

	ContainsStr<BusStopStruct*, std::string, ds::amt::Hierarchy<BlockType>::PreOrderHierarchyIterator, PredicateList> str;
	if (startNode == nullptr)
		startNode = zoznamDopravcov.getRoot();

	BlockType* curNode = startNode;
	std::string predikat;
	while (true)
	{
		std::cout << "Algoritmus Contains alebo StartsWith:\n 'predikat' || '-p'\n "
			"prechadzanie hierarchiou:\n 'prehliadka' || '-l'\n "
			"ukoncenie aplikacie: \n 'exit' || '-e'\n ";
		std::cin >> predikat;
		if (predikat == "predikat" || predikat == "-p")
			this->predikuj(predikat, str, zoznamDopravcov, curNode);
		if (predikat == "prehliadka" || predikat == "-l")
			curNode = this->prehliadaj(curNode);
		if (predikat == "exit" || predikat == "-e")
			return;
	}
}

void CLI::tableStartApp(PredicateList<BusTable<std::string, BusStop*>>& array)
{
	ContainsStr<BusStop*, std::string, BusTable<std::string, BusStop*>::IteratorType, PredicateList> str;
	
	std::string predikat, hladanyString, skratkaDopravcu;
		
	while (true)
	{
		PredicateList<BusStop*> predikatVec;
		int indexDopravcu; 
		std::cout << "Hladanie podla kluca:\n 'key' || '-k'\n"
		       "Ukoncenie aplikacie:\n 'exit' || '-e'\n";
		std::cin >> predikat;
		if (predikat == "exit" || predikat == "-e")
		{
			return;
		}
		std::cout << "hladanyString" << std::endl;
		std::getline(std::cin >> std::ws, hladanyString);
		std::cout << "dopravca" << std::endl;
		std::getline(std::cin >> std::ws, skratkaDopravcu);


		if (skratkaDopravcu == "COW" || skratkaDopravcu == "cow" || skratkaDopravcu == "0")
		{
			indexDopravcu = 0;
		}
		else if (skratkaDopravcu == "KAM" || skratkaDopravcu == "kam" || skratkaDopravcu == "1")
		{
			indexDopravcu = 1;
		}
		else if (skratkaDopravcu == "NAN" || skratkaDopravcu == "nan" || skratkaDopravcu == "2")
		{
			indexDopravcu = 2;
		}
		else if (skratkaDopravcu == "VIC" || skratkaDopravcu == "vic" || skratkaDopravcu == "3")
		{
			indexDopravcu = 3;
		}
		else if (skratkaDopravcu == "VLY" || skratkaDopravcu == "vly" || skratkaDopravcu == "4")
		{
			indexDopravcu = 4;
		}
		else if (skratkaDopravcu == "WHI" || skratkaDopravcu == "whi" || skratkaDopravcu == "5")
		{
			indexDopravcu = 5;
		}
		else if (skratkaDopravcu == "WIL" || skratkaDopravcu == "wil" || skratkaDopravcu == "6")
		{
			indexDopravcu = 6;
		}
		else if (skratkaDopravcu == "WKT" || skratkaDopravcu == "wkt" || skratkaDopravcu == "7")
		{
			indexDopravcu = 7;
		}
		else
		{
			std::cout << "Neplatny vstup!" << std::endl;
			continue;
		}
		if (predikat == "key" || predikat == "-k")
		{
			/*BusStop* stop = array.access(indexDopravcu)->data_.find(hladanyString);
			stop->coutAll(false);*/
			auto* item = array.access(indexDopravcu)->data_.findItem(hladanyString);
			item->data_->coutAll(false);
			auto* synonym = item->synonym_;
			while (synonym != nullptr)
			{
				synonym->data_->coutAll(false);
				synonym = synonym->synonym_;
			}
			/*str.containsStringTable(array.access(indexDopravcu)->data_.begin(), array.access(indexDopravcu)->data_.end(),
			hladanyString, predikatVec, [](const std::string& stringToFind, const std::string& stringToBeFound)
			{
				std::string stringToFindLower = stringToFind;
				std::transform(stringToFindLower.begin(), stringToFindLower.end(), stringToFindLower.begin(), std::tolower);
				std::string stringToBeFoundLower = stringToBeFound;
				std::transform(stringToBeFoundLower.begin(), stringToBeFoundLower.end(), stringToBeFoundLower.begin(), std::tolower);
				return stringToBeFoundLower == stringToFindLower;
			});*/
		}
		else
		{
			std::cout << "Neplatny vstup" << std::endl;
			continue;
		}


		for (size_t i = 0; i < predikatVec.size(); ++i)
		{
			predikatVec[i]->data_->coutAll(false);
		}
		
	}
}

void CLI::chooseApp(std::vector<Transporter<std::vector>>& zoznamDopravcovVector, BusStopHierarchy& zoznamDopravcovHierarchy, PredicateList<BusTable<std::string, BusStop*>>& busStopTable)
{
	std::string volba;
	while (true)
	{
	std::cout << "Zadajte 'vector' || '-v' pre spustenie aplikacie s vektormi\n"
		"Zadajte 'hierarchy' || '-h' pre spustenie aplikacie s hierarchiou\n"
		"Zadajte 'table' || '-t' pre spustenie aplikacie s tabulkou\n"
		"Zadajte 'exit' || '-e' pre ukoncenie aplikacie\n";
	std::cin >> volba;
	
		if (volba == "vector" || volba == "-v")
		{
			vectorStartApp(zoznamDopravcovVector);
		}
		else if (volba == "hierarchy" || volba == "-h")
		{
			hierarchyStartApp(zoznamDopravcovHierarchy);
		}
		else if (volba == "table" || volba == "-t")
		{
			tableStartApp(busStopTable);
		}
		else if (volba == "exit" || volba == "-e")
		{
			return;
		}
		else
		{
			std::cout << "Neplatny vstup\n";
		}
	}
}

void CLI::predikuj(std::string predikat, 
	ContainsStr<BusStopStruct*, std::string, ds::amt::Hierarchy<BlockType>::PreOrderHierarchyIterator, PredicateList> str,
	BusStopHierarchy& zoznamDopravcov, BlockType* curNode)
{
	PredicateList<BusStopStruct*> predikatVec;
	std::string hladanyString;
	std::cout << "hladanyString" << std::endl;
	std::getline(std::cin >> std::ws, hladanyString);
	std::cout << "Algoritmus Contains:\n 'contains' || '-c'\n"
		"Algoritmus StartsWith:\n 'startsWith' || '-s'\n";
	std::getline(std::cin >> std::ws, predikat);

	auto begin = BusStopHierarchy::PreOrderHierarchyIterator(&zoznamDopravcov, curNode);

	if (predikat == "contains" || predikat == "-c")
	{
		str.containsString(begin, zoznamDopravcov.end(),
			hladanyString, predikatVec, contains);

	}
	else if (predikat == "startsWith" || predikat == "-s")
	{
		str.containsString(begin, zoznamDopravcov.end(),
			hladanyString, predikatVec, startsWith);
	}
	std::cout << "Utriedenie vysledku:\n"
		"Alphabetical: 'alpha' || '-a'\n"
		"ConsonantCount: 'consonant' || '-c'\n"
		"Netriedit: anything\n";
	std::string utriedenie;
	std::cin >> utriedenie;
	Sorting<BusStopStruct*>* sorter = new Sorting(predikatVec);
	if (utriedenie == "alpha" || utriedenie == "-a")
	{
		sorter->sortAlphabetical();
	}
	else if (utriedenie == "consonant" || utriedenie == "-c")
	{
		sorter->sortConsonantCount();
	}
	
	for (size_t i = 0; i < predikatVec.size(); ++i)
	{
		if (predikatVec[i]->data_->getStop() != nullptr)
			predikatVec[i]->data_->getStop()->coutAll(false);
	}
	delete sorter;
	sorter = nullptr;
	//predikatVec.clear();
}

BlockType* CLI::prehliadaj(BlockType* curNode)
{
	std::string indexVrcholaStr;
	int indexVrchola;
	std::cout << "Aktualny vrchol: " << curNode->data_.getName() << "\n";
	if (curNode->parent_ == nullptr)
	{
		std::cout << "Synovia" << "\n";
		for (int i = 0; i < curNode->sons_->size(); ++i)
		{
			std::cout << i << " " << curNode->sons_->access(i)->data_->data_.getName() << "\n";
		}
		std::cout << "Zadaj index syna (-1 pre otca)\n";
		std::cin >> indexVrcholaStr;
		try
		{
			indexVrchola = stoi(indexVrcholaStr);
		}
		catch (const std::exception&)
		{
			std::cout << "Neplatny vstup\n";
			return curNode;
		}
		if (indexVrchola < 0)
		{
			std::cout << "Rodic je nullptr\n";
			return curNode;
		}
		if (indexVrchola >= curNode->sons_->size())
		{
			std::cout << "Neplatny index\n";
			return curNode;
		}
		return curNode->sons_->access(indexVrchola)->data_;
	}

	if (curNode->sons_->size() == 0)
	{
		std::cout << "Otec: " << curNode->parent_->data_.getName() << "\n";
		std::cout << "Zadaj index syna (-1 pre otca)\n";
		std::cin >> indexVrcholaStr;
		try
		{
			indexVrchola = stoi(indexVrcholaStr);
		}
		catch (const std::exception&)
		{
			std::cout << "Neplatny vstup\n";
			return curNode;
		}
		if (indexVrchola < 0)
		{
			return reinterpret_cast<BlockType*>(curNode->parent_);
		}
		std::cout << "Vrchol nema synov\n";
		return curNode;
	}

	std::cout << "Otec: " << curNode->parent_->data_.getName() << "\n";
	std::cout << "Synovia" << "\n";
	for (int i = 0; i < curNode->sons_->size(); ++i)
	{
		std::cout << i << " " << curNode->sons_->access(i)->data_->data_.getName() << "\n";
	}
	std::cout << "Zadaj index syna (-1 pre otca)\n";
	std::cin >> indexVrcholaStr;
	try
	{
		indexVrchola = stoi(indexVrcholaStr);
	}
	catch (const std::exception&)
	{
		std::cout << "Neplatny vstup\n";
		return curNode;
	}
	if (indexVrchola < 0)
	{
		return reinterpret_cast<BlockType*>(curNode->parent_);
	}
	if (indexVrchola >= curNode->sons_->size())
	{
		std::cout << "Neplatny index\n";
		return curNode;
	}
	return curNode->sons_->access(indexVrchola)->data_;
}


