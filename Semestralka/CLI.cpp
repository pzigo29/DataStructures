#include "CLI.h"
#include "contains_str.h"
#include "predicate_list.h"

void CLI::vectorStartApp(std::vector<Transporter<std::vector>>& zoznamDopravcov)
{
	
	ContainsStr<BusStop, std::string, std::vector<BusStop>::iterator, std::vector> str;

	while (true)
	{
		std::vector<BusStop> predikatVec;
		std::string predikat, hladanyString, skratkaDopravcu;
		std::vector<int> indexDopravcu;
		int indexStlpca = 0;
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
			predikatVec[i].coutAll(false);

		}
	}
}

void CLI::hierarchyStartApp(BusStopHierarchy& zoznamDopravcov, BlockType* startNode)
{
	/*int* test = (int*)std::malloc(5);
	test[0] = 1;
	std::cout << test[0] << std::endl;
	free (test);*/

	ContainsStr<BusStopStruct, std::string, ds::amt::Hierarchy<BlockType>::PreOrderHierarchyIterator, PredicateList> str;
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

void CLI::chooseApp(std::vector<Transporter<std::vector>>& zoznamDopravcovVector, BusStopHierarchy& zoznamDopravcovHierarchy)
{
	std::string volba;
	while (true)
	{
	std::cout << "Zadajte 'vector' || '-v' pre spustenie aplikacie s vektormi\n"
		"Zadajte 'hierarchy' || '-h' pre spustenie aplikacie s hierarchiou\n"
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
	ContainsStr<BusStopStruct, std::string, ds::amt::Hierarchy<BlockType>::PreOrderHierarchyIterator, PredicateList> str,
	BusStopHierarchy& zoznamDopravcov, BlockType* curNode)
{
	PredicateList<BusStopStruct> predikatVec;
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
	for (int i = 0; i < predikatVec.size(); i++)
	{
		if (predikatVec[i]->data_.getStop() != nullptr)
			predikatVec[i]->data_.getStop()->coutAll(false);
	}
	//predikatVec.clear();
}

BlockType* CLI::prehliadaj(BlockType* curNode)
{
	int indexVrchola = 0;
	std::cout << "Aktualny vrchol: " << curNode->data_.getName() << "\n";
	if (curNode->parent_ == nullptr)
	{
		std::cout << "Synovia" << "\n";
		for (int i = 0; i < curNode->sons_->size(); ++i)
		{
			std::cout << i << " " << curNode->sons_->access(i)->data_->data_.getName() << "\n";
		}
		std::cout << "Zadaj index syna (-1 pre otca)\n";
		std::cin >> indexVrchola;
		if (indexVrchola < 0)
		{
			std::cout << "Rodic je nullptr\n";
			return curNode;
		}
		return curNode->sons_->access(indexVrchola)->data_;
	}

	if (curNode->sons_->size() == 0)
	{
		std::cout << "Otec: " << curNode->parent_->data_.getName() << "\n";
		std::cout << "Zadaj index syna (-1 pre otca)\n";
		std::cin >> indexVrchola;
		if (indexVrchola >= 0)
		{
			std::cout << "Vrchol nema synov\n";
			return curNode;
		}
		return reinterpret_cast<BlockType*>(curNode->parent_);
	}

	std::cout << "Otec: " << curNode->parent_->data_.getName() << "\n";
	std::cout << "Synovia" << "\n";
	for (int i = 0; i < curNode->sons_->size(); ++i)
	{
		std::cout << i << " " << curNode->sons_->access(i)->data_->data_.getName() << "\n";
	}
	std::cout << "Zadaj index syna (-1 pre otca)\n";
	std::cin >> indexVrchola;
	if (indexVrchola < 0)
	{
		return reinterpret_cast<BlockType*>(curNode->parent_);
	}
	return curNode->sons_->access(indexVrchola)->data_;
}


