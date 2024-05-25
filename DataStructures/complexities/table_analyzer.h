#pragma once

#include <complexities/complexity_analyzer.h>
#include <list>
#include <random>
#include <vector>
#include <libds/adt/table.h>

#include "list_analyzer.h"
#include "../../Semestralka/bus_stop.h"

namespace ds::utils
{
    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    protected:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void growToSize(Table& structure, size_t size) override;

    protected:
        int key_;
        int data_;

    private:
        std::default_random_engine rngData_;
        std::default_random_engine rngKey_;
    };

    /**
     * @brief Analyzes complexity of an insertion at the beginning.
     */
    template<class Table>
    class TableInsertAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };

    template<class Table>
    class TableFindAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableFindAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };

    /**
     * @brief Container for all list analyzers.
     */
    class TablesAnalyzer : public CompositeAnalyzer
    {
    public:
        TablesAnalyzer();
    };

    //----------

    template<class Table>
    TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
        ComplexityAnalyzer<Table>(name),
        rngData_(144),
        rngKey_(144),
		key_(0),
		data_(0)
    {

        ComplexityAnalyzer<Table>::registerBeforeOperation([this](Table& table)
            {
                std::uniform_int_distribution<size_t> indexDist(0, 10000000);
                this->key_ = indexDist(this->rngKey_);
                this->data_ = this->rngData_();
                while (table.contains(this->key_))
                {
                    this->key_ = indexDist(this->rngKey_);
                }
				
            });
    }

    template <class Table>
    void TableAnalyzer<Table>::growToSize(Table& structure, size_t size)
    {
	    size_t count = size - structure.size();
        for (size_t i = 0; i < count; ++i)
        {
            std::uniform_int_distribution<size_t> indexDist(0, 10000000);
            int key = indexDist(this->rngKey_);
            int data = this->rngData_();

            while (structure.contains(key))
            {
            	key = indexDist(this->rngKey_);
            }

            structure.insert(key, data);
		}
    }

    //----------

    template <class Table>
    TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name) :
        TableAnalyzer<Table>(name)
    {
    }

    template <class Table>
    void TableInsertAnalyzer<Table>::executeOperation(Table& structure)
    {
        structure.insert(this->key_, this->data_);
    }

    template <class Table>
    TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name) :
		TableAnalyzer<Table>(name)
    {
    }

    template <class Table>
    void TableFindAnalyzer<Table>::executeOperation(Table& structure)
    {
        structure.find(this->key_);
    }

    //----------

    inline TablesAnalyzer::TablesAnalyzer() :
        CompositeAnalyzer("Tables")
    {
        this->addAnalyzer(std::make_unique<TableInsertAnalyzer<ds::adt::Treap<int, int>>>("treap-insert"));
        this->addAnalyzer(std::make_unique<TableFindAnalyzer<ds::adt::Treap<int, int>>>("treap-find"));
    }
}
