#pragma once

#include <libds/adt/abstract_data_type.h>
#include <libds/amt/implicit_sequence.h>
#include <libds/amt/explicit_sequence.h>

namespace ds::adt {

    template <typename T>
    class Queue :
        virtual public ADT
    {
    public:
        virtual void push(T element) = 0;
        virtual T& peek() = 0;
        virtual T pop() = 0;
    };

    //----------

    template<typename T>
    class ImplicitQueue :
        public Queue<T>,
        public ADS<T>
    {
    public:
        ImplicitQueue();
        ImplicitQueue(const ImplicitQueue& other);
        ImplicitQueue(size_t capacity);

        size_t getCapacity() const;

        ADT& assign(const ADT& other) override;
        void clear() override;
        size_t size() const override;
        bool equals(const ADT& other) override;

        void push(T element) override;
        T& peek() override;
        T pop() override;

        static const int INIT_CAPACITY = 100;

    private:
        amt::CIS<T>* getSequence() const;

    private:
        size_t insertionIndex_;
        size_t removalIndex_;
        size_t size_;
    };

    //----------

    template<typename T>
    class ExplicitQueue :
        public Queue<T>,
        public ADS<T>
    {
    public:
        ExplicitQueue();
        ExplicitQueue(const ExplicitQueue& other);
        void push(T element) override;
        T& peek() override;
        T pop() override;

    private:
        amt::SinglyLS<T>* getSequence() const;
    };

    //----------

    template<typename T>
    ImplicitQueue<T>::ImplicitQueue():
        ImplicitQueue(INIT_CAPACITY)
    {
    }

    template<typename T>
    ImplicitQueue<T>::ImplicitQueue(size_t capacity) :
        ADS<T>(new amt::CIS<T>(capacity, true)),
        insertionIndex_(0),
        removalIndex_(0),
        size_(0)
    {
    }

    template <typename T>
    size_t ImplicitQueue<T>::getCapacity() const
    {
        return this->getSequence()->size();
    }

    template<typename T>
    ImplicitQueue<T>::ImplicitQueue(const ImplicitQueue& other) :
        ADS<T>(new amt::CIS<T>(), other),
        insertionIndex_(other.insertionIndex_),
        removalIndex_(other.removalIndex_),
        size_(other.size_)
    {
    }

    template<typename T>
    ADT& ImplicitQueue<T>::assign(const ADT& other)
    {
        // TODO 09
        if (typeid(other) != typeid(*this))
        {
	        throw std::runtime_error("ImplicitQueue<T>::assign: Other AUT is not ImplicitQueue");
        }
        if (this != &other)
        {
	        if (this->getSequence()->size() < other.size())
	        {
		        throw std::runtime_error("ImplicitQueue<T>::assign: Capacity is too small");
	        }
            this->clear();
            this->insertionIndex_ = this->getSequence()->indexOfNext(other.size() - 1);
            this->removalIndex_ = 0;
            this->size_ = other.size();
            size_t removalOfOther = dynamic_cast<const ImplicitQueue&>(other).removalIndex_;
            for (int i = 0; i < this->size(); ++i)
            {
	            this->getSequence()->access(i)->data_ = dynamic_cast<const ImplicitQueue&>(other).getSequence()->access(removalOfOther)->data_;
                removalOfOther = dynamic_cast<const ImplicitQueue&>(other).getSequence()->indexOfNext(removalOfOther);
            }
        }
        return *this;
    }

    template<typename T>
    void ImplicitQueue<T>::clear()
    {
        insertionIndex_ = removalIndex_;
        size_ = 0;
    }

    template<typename T>
    size_t ImplicitQueue<T>::size() const
    {
        return size_;
    }

    template<typename T>
    bool ImplicitQueue<T>::equals(const ADT& other)
    {
        // TODO 09
        if (this == &other)
        {
            return true;
        }
        if (this->size_ != other.size())
        {
	        return false;
        }
        if (typeid(*this) != typeid(other))
        {
	        return false;
        }
        int myIndex = removalIndex_;
        int otherIndex = dynamic_cast<const ImplicitQueue&>(other).removalIndex_;
        for (int i = 0; i < this->size(); ++i)
        {
	        if (this->getSequence()->access(myIndex)->data_ != 
                dynamic_cast<const ImplicitQueue&>(other).getSequence()->access(otherIndex)->data_)
	        {
		        return false;
	        }
			myIndex = this->getSequence()->indexOfNext(myIndex);
			otherIndex = dynamic_cast<const ImplicitQueue&>(other).getSequence()->indexOfNext(otherIndex);
        }
        return true;
    }

    template<typename T>
    void ImplicitQueue<T>::push(T element)
    {
        // TODO 09
        if (this->size() == this->getSequence()->size())
        {
	        throw std::runtime_error("ImplicitQueue<T>::push: Queue is full");
        }
        this->getSequence()->access(insertionIndex_)->data_ = element;
        insertionIndex_ = this->getSequence()->indexOfNext(insertionIndex_);
        ++size_;
    }

    template<typename T>
    T& ImplicitQueue<T>::peek()
    {
        // TODO 09
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    T ImplicitQueue<T>::pop()
    {
        // TODO 09
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    amt::CIS<T>* ImplicitQueue<T>::getSequence() const
    {
        return dynamic_cast<amt::CIS<T>*>(this->memoryStructure_);
    }

    template<typename T>
    ExplicitQueue<T>::ExplicitQueue() :
        ADS<T>(new amt::SinglyLS<T>())
    {
    }

    template<typename T>
    ExplicitQueue<T>::ExplicitQueue(const ExplicitQueue& other) :
        ADS<T>(new amt::SinglyLS<T>(), other)
    {
    }

    template<typename T>
    void ExplicitQueue<T>::push(T element)
    {
        // TODO 09
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    T& ExplicitQueue<T>::peek()
    {
        // TODO 09
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    T ExplicitQueue<T>::pop()
    {
        // TODO 09
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    amt::SinglyLS<T>* ExplicitQueue<T>::getSequence() const
    {
        return dynamic_cast<amt::SinglyLS<T>*>(this->memoryStructure_);
    }
}