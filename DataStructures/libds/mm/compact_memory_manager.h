#pragma once

#include <libds/mm/memory_manager.h>
#include <libds/mm/memory_omanip.h>
#include <libds/constants.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <utility>

namespace ds::mm {

    template<typename BlockType>
    class CompactMemoryManager : public MemoryManager<BlockType> {
    public:
        CompactMemoryManager();
        CompactMemoryManager(size_t size);
        CompactMemoryManager(const CompactMemoryManager<BlockType>& other);
        ~CompactMemoryManager() override;

        BlockType* allocateMemory() override;
        BlockType* allocateMemoryAt(size_t index);
        void releaseMemory(BlockType* pointer) override;
        void releaseMemoryAt(size_t index);
        void releaseMemory();

        size_t getCapacity() const;

        CompactMemoryManager<BlockType>& assign(const CompactMemoryManager<BlockType>& other);
        void changeCapacity(size_t newCapacity);
        void shrinkMemory();
        void clear();
        bool equals(const CompactMemoryManager<BlockType>& other) const;
        void* calculateAddress(const BlockType& data);
        size_t calculateIndex(const BlockType& data);
        BlockType& getBlockAt(size_t index);
        void swap(size_t index1, size_t index2);

        void print(std::ostream& os);

    private:
        size_t getAllocatedBlocksSize() const;
        size_t getAllocatedCapacitySize() const;

    private:
        BlockType* base_;
        BlockType* end_;
        BlockType* limit_;

        static const size_t INIT_SIZE = 4;
    };

    template<typename BlockType>
    CompactMemoryManager<BlockType>::CompactMemoryManager() :
        CompactMemoryManager(INIT_SIZE)
    {
    }

    template<typename BlockType>
    CompactMemoryManager<BlockType>::CompactMemoryManager(size_t size) :
        base_(static_cast<BlockType*>(std::calloc(size, sizeof(BlockType)))),
        end_(base_),
        limit_(base_ + size)
    {
    }

    template<typename BlockType>
    CompactMemoryManager<BlockType>::CompactMemoryManager(const CompactMemoryManager<BlockType>& other) :
        CompactMemoryManager(other.getAllocatedBlockCount())
    {
        // TODO 02
        assign(other);
    }

    template<typename BlockType>
    CompactMemoryManager<BlockType>::~CompactMemoryManager()
    {
        // TODO 02
        releaseMemory(base_);
        std::free(base_); //vr�Pam�??
        base_ = nullptr;
        end_ = nullptr;
        limit_ = nullptr;
        //finalizujPredka??
    }

    template<typename BlockType>
    BlockType* CompactMemoryManager<BlockType>::allocateMemory()
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        return allocateMemoryAt(end_ - base_);

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    BlockType* CompactMemoryManager<BlockType>::allocateMemoryAt(size_t index)
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        if (end_ == limit_)
        {
            changeCapacity(2 * getAllocatedBlockCount());
        }
        if ((end_ - base_) > index)
        {
            memmove(base_ + index + 1, base_ + index, ((end_ - base_) - index) * sizeof(BlockType));
        }
        allocatedBlockCount_++;
        end_++;
        return placement_new(base_ + index);

        //throw std::runtime_error("Not implemented yet");
    }

    //nechapem co tato funkcia robi uplne
    template<typename BlockType>
    void CompactMemoryManager<BlockType>::releaseMemory(BlockType* pointer)
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        BlockType* p = pointer;
        while (p != end_)
        {
            destroy(p);
            p++; //neviem ci ++p alebo p++
        }
        end_ = pointer;
        allocatedBlockCount_ = end_ - base_;
        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    void CompactMemoryManager<BlockType>::releaseMemoryAt(size_t index)
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        destroy(&getBlockAt(index));
        memmove(base_ + index, base_ + index + 1, ((end_ - base_) - index - 1) * sizeof(BlockType));
        end_--;
        allocatedBlockCount_--;

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    void CompactMemoryManager<BlockType>::releaseMemory()
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        releaseMemory(end_ - 1);

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    size_t CompactMemoryManager<BlockType>::getCapacity() const
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        return limit_ - base_;

        //throw std::runtime_error("Not implemented yet");
    }

    //pad� to pri teste :)
    template<typename BlockType>
    CompactMemoryManager<BlockType>& CompactMemoryManager<BlockType>::assign
    (const CompactMemoryManager<BlockType>& other)
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        if (this != &other)
        {
            releaseMemory(base_);
            allocatedBlockCount_ = other.getAllocatedBlockCount();
            BlockType* newBase = (BlockType*)realloc(base_, other.getAllocatedCapacitySize());
            if (newBase == NULL)
            {
                throw std::runtime_error("Nov� b�za je NULL!");
            }
            base_ = newBase;
            end_ = base_ + getAllocatedBlockCount();
            limit_ = base_ + (other.limit_ - other.base_);

            for (size_t i = 0; i < getAllocatedBlockCount(); i++)
            {
                //base_ + i = new BlockType(other.base_ + i);//neviem �o sa deje
                placement_copy((base_ + i), *(other.base_ + i));
            }
            return *this;
        }

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    void CompactMemoryManager<BlockType>::shrinkMemory()
    {
        size_t newCapacity = static_cast<size_t>(end_ - base_);

        if (newCapacity < CompactMemoryManager<BlockType>::INIT_SIZE)
        {
            newCapacity = CompactMemoryManager<BlockType>::INIT_SIZE;
        }

        this->changeCapacity(newCapacity);
    }

    template<typename BlockType>
    void CompactMemoryManager<BlockType>::changeCapacity(size_t newCapacity)
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        if (newCapacity == getCapacity())
        {
            return;
        }
        if (newCapacity < getAllocatedBlockCount())
        {
            releaseMemory(base_ + newCapacity);
        }
        BlockType* newBase = (BlockType*)realloc(base_, newCapacity * sizeof(BlockType));
        if (newBase == NULL)
        {
            throw std::runtime_error("Nov� b�za je NULL!");
        }
        base_ = newBase;
        end_ = base_ + getAllocatedBlockCount();
        limit_ = base_ + newCapacity;

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    void CompactMemoryManager<BlockType>::clear()
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!
        
        releaseMemory(base_);
        
        //throw std::runtime_error("Not implemented yet");
    }

    //neviem �i to je dobre lebo v pseudok�de je nie�o in�
    template<typename BlockType>
    bool CompactMemoryManager<BlockType>::equals(const CompactMemoryManager<BlockType>& other) const
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!
      
        /*return (this == &other) || (allocatedBlockCount_ == other.getAllocatedBlockCount() && memcmp(base_, other.base_, getAllocatedBlocksSize());*/
        if (this == &other)
        {
            return true;
        }
        else if (getAllocatedBlockCount() == other.getAllocatedBlockCount()
            && memcmp(base_, other.base_, getAllocatedBlocksSize()) == 0)
        {
            return true;
        }
        return false;

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    void* CompactMemoryManager<BlockType>::calculateAddress(const BlockType& data)
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        BlockType* p = base_;
        while (p != end_ && p != &data)
        {
            p++;
        }
        return ((p == end_) ? NULL : p);

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    size_t CompactMemoryManager<BlockType>::calculateIndex(const BlockType& data)
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        if (&data < end_ && &data >= base_)
        {
            return &data - base_;
        }
        return -1;

        /*throw std::runtime_error("Not implemented yet");*/
    }

    template<typename BlockType>
    BlockType& CompactMemoryManager<BlockType>::getBlockAt(size_t index)
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        return *(base_ + index);

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    void CompactMemoryManager<BlockType>::swap(size_t index1, size_t index2)
    {
        std::swap(this->getBlockAt(index1), this->getBlockAt(index2));
    }

    template<typename BlockType>
    size_t CompactMemoryManager<BlockType>::getAllocatedBlocksSize() const
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        return (end_ - base_) * sizeof(BlockType);

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    size_t CompactMemoryManager<BlockType>::getAllocatedCapacitySize() const
    {
        // TODO 02
        // po implementacii vymazte vyhodenie vynimky!

        return (limit_ - base_) * sizeof(BlockType);

        //throw std::runtime_error("Not implemented yet");
    }

    template<typename BlockType>
    void CompactMemoryManager<BlockType>::print(std::ostream& os)
    {
        os << "first = " << base_ << std::endl;
        os << "last = " << end_ << std::endl;
        os << "limit = " << limit_ << std::endl;
        os << "block size = " << sizeof(BlockType) << "B" << std::endl;

        BlockType* ptr = base_;
        while (ptr != limit_)
        {
            std::cout << ptr;
            os << PtrPrintBin<BlockType>(ptr);

            if (ptr == base_) {
                os << "<- first";
            }
            else if (ptr == end_) {
                os << "<- last";
            }
            os << std::endl;
            ++ptr;
        }

        os << limit_ << "|<- limit" << std::endl;
    }

}