#pragma once

#include <libds/adt/abstract_data_type.h>
#include <libds/amt/implicit_sequence.h>
#include <libds/amt/explicit_sequence.h>
#include <libds/amt/implicit_hierarchy.h>
#include <cmath>
#include <functional>

namespace ds::adt {

	template <typename P, typename T>
	struct PriorityQueueItem
	{
		P priority_;
		T data_;

		bool operator==(const PriorityQueueItem<P, T>& other) const
		{
			return priority_ == other.priority_ && data_ == other.data_;
		}

		bool operator!=(const PriorityQueueItem<P, T>& other) const
		{
			return !(*this == other);
		}
	};

	template <typename P, typename T>
	using PQItem = PriorityQueueItem<P, T>;

	//----------

	template <typename P, typename T>
	class PriorityQueue :
		virtual public ADT
	{
	public:
		virtual void push(P priority, T data) = 0;
		virtual T& peek() = 0;
		virtual T pop() = 0;
	};

	template <typename P, typename T>
	using PQ = PriorityQueue<P, T>;

	//----------

	template <typename P, typename T, typename SequenceType>
	class SequencePriorityQueue :
		public PriorityQueue<P, T>,
		public ADS<PQItem<P, T>>
	{
	public:
		SequencePriorityQueue();
		SequencePriorityQueue(const SequencePriorityQueue& other);

		bool equals(const ADT& other) override;

	protected:
		SequenceType* getSequence() const;
	};

	template <typename P, typename T, typename SequenceType>
	using SPQ = SequencePriorityQueue<P, T, SequenceType>;

	//----------

	template <typename P, typename T, typename SequenceType>
	class UnsortedSequencePriorityQueue :
		public SequencePriorityQueue<P, T, SequenceType>
	{
	public:
		T& peek() override;

	protected:
		typename SequenceType::BlockType* findHighestPriorityBlock();
	};

	template <typename P, typename T, typename SequenceType>
	using UnsortedSPQ = UnsortedSequencePriorityQueue<P, T, SequenceType>;

	//----------

	template <typename P, typename T, typename SequenceType>
	class SortedSequencePriorityQueue :
		public SequencePriorityQueue<P, T, SequenceType>
	{
	public:
		T& peek() override;
		T pop() override;

	protected:
		virtual size_t indexOfHighestPriorityBlock() const = 0;
	};

	template <typename P, typename T, typename SequenceType>
	using SortedSPQ = SortedSequencePriorityQueue<P, T, SequenceType>;

	//----------

	template <typename P, typename T>
	class UnsortedImplicitSequencePriorityQueue :
		public UnsortedSequencePriorityQueue<P, T, amt::IS<PQItem<P,T>>>
	{
	public:
		void push(P priority, T data) override;
		T pop() override;

	private:
		using SequenceBlockType = typename amt::IS<PQItem<P, T>>::BlockType;
	};

	template <typename P, typename T>
	using UnsortedISPQ = UnsortedImplicitSequencePriorityQueue<P, T>;

	//----------

	template <typename P, typename T>
	class UnsortedExplicitSequencePriorityQueue :
		public UnsortedSequencePriorityQueue<P, T, amt::SinglyLS<PQItem<P, T>>>
	{
	public:
		void push(P priority, T data) override;
		T pop() override;

	private:
		using SequenceBlockType = typename amt::SinglyLS<PQItem<P, T>>::BlockType;
	};

	template <typename P, typename T>
	using UnsortedESPQ = UnsortedExplicitSequencePriorityQueue<P, T>;

	//----------

	template <typename P, typename T>
	class SortedImplicitSequencePriorityQueue :
		public SortedSequencePriorityQueue<P, T, amt::IS<PQItem<P, T>>>
	{
	public:
		void push(P priority, T data) override;

	protected:
		size_t indexOfHighestPriorityBlock() const override;

	private:
		using SequenceBlockType = typename amt::IS<PQItem<P, T>>::BlockType;
	};

	template <typename P, typename T>
	using SortedISPQ = SortedImplicitSequencePriorityQueue<P, T>;

	//----------

	template <typename P, typename T>
	class SortedExplicitSequencePriorityQueue :
		public SortedSequencePriorityQueue<P, T, amt::SinglyLS<PQItem<P, T>>>
	{
	public:
		void push(P priority, T data) override;

	protected:
		size_t indexOfHighestPriorityBlock() const override;

	private:
		using SequenceBlockType = typename amt::SinglyLS<PQItem<P, T>>::BlockType;
	};

	template <typename P, typename T>
	using SortedESPQ = SortedExplicitSequencePriorityQueue<P, T>;

	//----------

	template <typename P, typename T>
	class TwoLists :
		public AUMS<PQItem<P, T>>,
		public PriorityQueue<P, T>
	{
	public:
		TwoLists(size_t expectedSize);
		TwoLists(const TwoLists<P, T>& other);
		~TwoLists();

		ADT& assign(const ADT& other) override;
		void clear() override;
		size_t size() const override;
		bool isEmpty() const override;
		bool equals(const ADT& other) override;

		void push(P priority, T data) override;
		T& peek() override;
		T pop() override;

	private:
		using ShortSequenceType = amt::IS<PQItem<P, T>>;
		using LongSequenceType = amt::SinglyLS<PQItem<P, T>>;
		using ShortSequenceBlockType = typename ShortSequenceType::BlockType;
		using LongSequenceBlockType = typename LongSequenceType::BlockType;

		ShortSequenceType* shortSequence_;
		LongSequenceType* longSequence_;
	};

	//----------

	template <typename P, typename T>
	class BinaryHeap :
		public PriorityQueue<P, T>,
		public ADS<PQItem<P, T>>
	{
	public:
		BinaryHeap();
		BinaryHeap(const BinaryHeap& other);

		bool equals(const ADT& other) override;

		void push(P priority, T data) override;
		T& peek() override;
		T pop() override;

	private:
		using HierarchyBlockType = typename amt::BinaryIH<PQItem<P, T>>::BlockType;
		amt::BinaryIH<PQItem<P, T>>* getHierarchy();
	};

	//----------

	template<typename P, typename T, typename SequenceType>
	SequencePriorityQueue<P, T, SequenceType>::SequencePriorityQueue() :
		ADS<PQItem<P, T>>(new SequenceType())
	{
	}

	template<typename P, typename T, typename SequenceType>
	SequencePriorityQueue<P, T, SequenceType>::SequencePriorityQueue(const SequencePriorityQueue& other) :
		ADS<PQItem<P, T>>(new SequenceType(), other)
	{
	}

	template <typename P, typename T, typename SequenceType>
	bool SequencePriorityQueue<P, T, SequenceType>::equals(const ADT&)
	{
		throw std::logic_error("Unsupported operation!");
	}


	template<typename P, typename T, typename SequenceType>
	SequenceType* SequencePriorityQueue<P, T, SequenceType>::getSequence() const
	{
		return dynamic_cast<SequenceType*>(this->memoryStructure_);
	}

	template<typename P, typename T, typename SequenceType>
	T& UnsortedSequencePriorityQueue<P, T, SequenceType>::peek()
	{
		if (this->isEmpty())
		{
			throw std::out_of_range("Queue is empty!");
		}

		return this->findHighestPriorityBlock()->data_.data_;
	}

	template<typename P, typename T, typename SequenceType>
	typename SequenceType::BlockType* UnsortedSequencePriorityQueue<P, T, SequenceType>::findHighestPriorityBlock()
	{
		// TODO 09
		typename SequenceType::BlockType* highestPriorityBlock = this->getSequence()->accessFirst();
		this->getSequence()->processBlocksForward(
			this->getSequence()->accessNext(*highestPriorityBlock),
			[&highestPriorityBlock](typename SequenceType::BlockType* b)
			{
				if (highestPriorityBlock->data_.priority_ > b->data_.priority_)
				{
					highestPriorityBlock = b;
				}
			}
		);
		return highestPriorityBlock;
	}

	template<typename P, typename T, typename SequenceType>
	T& SortedSequencePriorityQueue<P, T, SequenceType>::peek()
	{
		if (this->isEmpty())
		{
			throw std::out_of_range("Queue is empty!");
		}

		return this->getSequence()->access(this->indexOfHighestPriorityBlock())->data_.data_;
	}

	template<typename P, typename T, typename SequenceType>
	T SortedSequencePriorityQueue<P, T, SequenceType>::pop()
	{
		// TODO 09
		if (this->isEmpty())
		{
			throw std::out_of_range("SortedSequencePriorityQueue<>::pop: Queue is empty!");
		}
		int index = this->indexOfHighestPriorityBlock();
		T element = this->getSequence()->access(index)->data_.data_;
		this->getSequence()->remove(index);
		return element;
	}

	template<typename P, typename T>
	void UnsortedImplicitSequencePriorityQueue<P, T>::push(P priority, T data)
	{
		// TODO 09
		PriorityQueueItem<P, T>& queueItem = this->getSequence()->insertLast().data_;
		queueItem.priority_ = priority;
		queueItem.data_ = data;
	}

	template<typename P, typename T>
	T UnsortedImplicitSequencePriorityQueue<P, T>::pop()
	{
		// TODO 09
		if (this->isEmpty())
		{
			throw std::out_of_range("UnsortedImplicitSequencePriorityQueue<>::pop: Queue is empty!");
		}
		
		SequenceBlockType* highestPriorityBlock = this->findHighestPriorityBlock();
		T element = highestPriorityBlock->data_.data_;
		SequenceBlockType* lastBlock = this->getSequence()->accessLast();
		if (highestPriorityBlock != lastBlock)
		{
			std::swap(highestPriorityBlock->data_, lastBlock->data_);
		}
		this->getSequence()->removeLast();
		return element;
	}

	template<typename P, typename T>
	void UnsortedExplicitSequencePriorityQueue<P, T>::push(P priority, T data)
	{
		// TODO 09
		PriorityQueueItem<P, T>& queueItem = this->getSequence()->insertLast().data_;
		queueItem.priority_ = priority;
		queueItem.data_ = data;
	}

	template<typename P, typename T>
	T UnsortedExplicitSequencePriorityQueue<P, T>::pop()
	{
		// TODO 09
		if (this->isEmpty())
		{
			throw std::out_of_range("UnsortedExplicitSequencePriorityQueue<>::pop: Queue is empty!");
		}
		SequenceBlockType* highestPriorityBlock = this->findHighestPriorityBlock();
		T element = highestPriorityBlock->data_.data_;
		SequenceBlockType* firstBlock = this->getSequence()->accessFirst();
		if (highestPriorityBlock != firstBlock)
		{
			std::swap(highestPriorityBlock->data_, firstBlock->data_);
		}
		this->getSequence()->removeFirst();
		return element;
	}

	template<typename P, typename T>
	void SortedImplicitSequencePriorityQueue<P, T>::push(P priority, T data)
	{
		// TODO 09
		PriorityQueueItem<P, T>* queueItem = nullptr;
		if (this->isEmpty() || priority <= this->getSequence()->accessLast()->data_.priority_)
		{
			queueItem = &this->getSequence()->insertLast().data_;
		}
		else if(priority >= this->getSequence()->accessFirst()->data_.priority_)
		{
			queueItem = &this->getSequence()->insertFirst().data_;
		}
		else
		{
			queueItem = &this->getSequence()->insertBefore(*(this->getSequence()->findBlockWithProperty(
				[&](SequenceBlockType* b)
				{
					return b->data_.priority_ <= priority;
				}
			))).data_;
		}
		queueItem->priority_ = priority;
		queueItem->data_ = data;
	}

	template<typename P, typename T>
	size_t SortedImplicitSequencePriorityQueue<P, T>::indexOfHighestPriorityBlock() const
	{
		// TODO 09
		return this->size() - 1;
	}

	template<typename P, typename T>
	void SortedExplicitSequencePriorityQueue<P, T>::push(P priority, T data)
	{
		// TODO 09
		PriorityQueueItem<P, T>* queueItem = nullptr;
		if (this->isEmpty() || priority <= this->getSequence()->accessFirst()->data_.priority_)
		{
			queueItem = &this->getSequence()->insertFirst().data_;
		}
		else if (priority >= this->getSequence()->accessLast()->data_.priority_)
		{
			queueItem = &this->getSequence()->insertLast().data_;
		}
		else
		{
			SequenceBlockType* blockBefore = this->getSequence()->findPreviousToBlockWithProperty(
				[&](SequenceBlockType* b)
				{
					return b->data_.priority_ >= priority;
				}
			);
			queueItem = &this->getSequence()->insertAfter(*blockBefore).data_;
		}
		queueItem->priority_ = priority;
		queueItem->data_ = data;
	}

	template<typename P, typename T>
	size_t SortedExplicitSequencePriorityQueue<P, T>::indexOfHighestPriorityBlock() const
	{
		// TODO 09
		return 0;
	}

	template<typename P, typename T>
	TwoLists<P, T>::TwoLists(size_t expectedSize):
		shortSequence_(new ShortSequenceType(static_cast<size_t>(std::ceil(std::sqrt(expectedSize))), false)),
		longSequence_(new LongSequenceType())
	{
	}

	template <typename P, typename T>
	TwoLists<P, T>::TwoLists(const TwoLists<P, T>& other) :
		shortSequence_(new ShortSequenceType()),
		longSequence_(new LongSequenceType())
	{
		assign(other);
	}

	template<typename P, typename T>
	TwoLists<P, T>::~TwoLists()
	{
		delete shortSequence_;
		shortSequence_ = nullptr;
		delete longSequence_;
		longSequence_ = nullptr;
	}

	template<typename P, typename T>
	ADT& TwoLists<P, T>::assign(const ADT& other)
	{
		if (this != &other)
		{
			const TwoLists<P, T>& otherTwoLists = dynamic_cast<const TwoLists<P, T>&>(other);

			shortSequence_->assign(*otherTwoLists.shortSequence_);
			longSequence_->assign(*otherTwoLists.longSequence_);
		}

		return *this;
	}

	template<typename P, typename T>
	void TwoLists<P, T>::clear()
	{
		shortSequence_->clear();
		longSequence_->clear();
	}

	template<typename P, typename T>
	size_t TwoLists<P, T>::size() const
	{
		return shortSequence_->size() + longSequence_->size();
	}

	template<typename P, typename T>
	bool TwoLists<P, T>::isEmpty() const
	{
		return shortSequence_->isEmpty();
	}

	template<typename P, typename T>
	bool TwoLists<P, T>::equals(const ADT& other)
	{
		throw std::logic_error("Unsupported operation!");
	}

	template<typename P, typename T>
	void TwoLists<P, T>::push(P priority, T data)
	{
		// TODO 09
		PriorityQueueItem<P, T>* queueItem = nullptr;
		if (longSequence_->size() == 0 || !shortSequence_->isEmpty() && shortSequence_->accessFirst()->data_.priority_ > priority)
		{
			if (shortSequence_->size() == shortSequence_->getCapacity())
			{
				ShortSequenceBlockType* shortBlock = shortSequence_->accessFirst();
				LongSequenceBlockType* longBlock = &longSequence_->insertLast();
				longBlock->data_.priority_ = shortBlock->data_.priority_;
				longBlock->data_.data_ = shortBlock->data_.data_;
				shortSequence_->removeFirst();
			}
			if (shortSequence_->isEmpty() || priority < shortSequence_->accessLast()->data_.priority_)
			{
				queueItem = &shortSequence_->insertLast().data_;
			}
			else
			{
				if (priority > shortSequence_->accessFirst()->data_.priority_)
				{
					queueItem = &shortSequence_->insertFirst().data_;
				}
				else
				{
					queueItem = &shortSequence_->insertBefore(*(shortSequence_->findBlockWithProperty(
						[&](ShortSequenceBlockType* b)
						{
							return b->data_.priority_ <= priority;
						}
					))).data_;
				}
			}
		}
		else
		{
			queueItem = &longSequence_->insertLast().data_;
		}
		queueItem->priority_ = priority;
		queueItem->data_ = data;
	}

	template<typename P, typename T>
	T& TwoLists<P, T>::peek()
	{
		// TODO 09
		if (shortSequence_->isEmpty())
		{
			throw std::out_of_range("TwoLists<>::peek: Queue is empty!");
		}
		return shortSequence_->accessLast()->data_.data_;
	}

	template<typename P, typename T>
	T TwoLists<P, T>::pop()
	{
		// TODO 09
		if (shortSequence_->isEmpty())
		{
			throw std::out_of_range("TwoLists<>::pop: Queue is empty!");
		}
		T element = shortSequence_->accessLast()->data_.data_;
		shortSequence_->removeLast();
		if (shortSequence_->size() == 0 && longSequence_->size() > 0)
		{
			amt::SinglyLinkedSequence<PriorityQueueItem<P, T>>* oldLongSequence = longSequence_;
			longSequence_ = new amt::SinglyLinkedSequence<PriorityQueueItem<P, T>>();
			shortSequence_->changeCapacity(
				ceil(sqrt(oldLongSequence->size()))
			);
			while (!oldLongSequence->isEmpty())
			{
				LongSequenceBlockType* block = oldLongSequence->accessFirst();
				this->push(block->data_.priority_, block->data_.data_);
				oldLongSequence->removeFirst();
			}
			delete oldLongSequence;
		}
		return element;
	}

	template<typename P, typename T>
	BinaryHeap<P, T>::BinaryHeap() :
		ADS<PQItem<P, T>>(new amt::BinaryIH<PQItem<P, T>>())
	{
	}

	template<typename P, typename T>
	BinaryHeap<P, T>::BinaryHeap(const BinaryHeap& other) :
		ADS<PQItem<P, T>>(new amt::BinaryIH<PQItem<P, T>>(), other)
	{
	}

	template<typename P, typename T>
	inline bool BinaryHeap<P, T>::equals(const ADT& other)
	{
		throw std::logic_error("Unsupported operation!");
	}

	template<typename P, typename T>
	void BinaryHeap<P, T>::push(P priority, T data)
	{
		// TODO 09
		PriorityQueueItem<P, T>& queueItem = this->getHierarchy()->insertLastLeaf().data_;
		queueItem.priority_ = priority;
		queueItem.data_ = data;
		HierarchyBlockType* curBlock = this->getHierarchy()->accessLastLeaf();
		HierarchyBlockType* parentBlock = this->getHierarchy()->accessParent(*curBlock);
		while (parentBlock != nullptr && curBlock->data_.priority_ < parentBlock->data_.priority_)
		{
			std::swap(curBlock->data_, parentBlock->data_);
			curBlock = parentBlock;
			parentBlock = this->getHierarchy()->accessParent(*curBlock);
		}
	}

	template<typename P, typename T>
	T& BinaryHeap<P, T>::peek()
	{
		// TODO 09
		if (this->isEmpty())
		{
			throw std::out_of_range("BinaryHeap<>::peek: Queue is empty!");
		}
		return this->getHierarchy()->accessRoot()->data_.data_;
	}

	template<typename P, typename T>
	T BinaryHeap<P, T>::pop()
	{
		// TODO 09
		if (this->isEmpty())
		{
			throw std::out_of_range("BinaryHeap<>::pop: Queue is empty!");
		}
		HierarchyBlockType* curBlock = this->getHierarchy()->accessRoot();
		T element = curBlock->data_.data_;
		std::swap(curBlock->data_, this->getHierarchy()->accessLastLeaf()->data_);
		this->getHierarchy()->removeLastLeaf();
		if (!this->isEmpty())
		{
			auto findSonWithHigherPriority = [&](HierarchyBlockType* parentBlock) -> HierarchyBlockType*
			{
				HierarchyBlockType* leftSon = this->getHierarchy()->accessLeftSon(*parentBlock);
				HierarchyBlockType* rightSon = this->getHierarchy()->accessRightSon(*parentBlock);
				if (rightSon == nullptr || leftSon->data_.priority_ < rightSon->data_.priority_)
				{
					return leftSon;
				}
				return rightSon;
			};
			HierarchyBlockType* sonBlock = findSonWithHigherPriority(curBlock);
			while (sonBlock != nullptr && curBlock->data_.priority_ > sonBlock->data_.priority_)
			{
				std::swap(curBlock->data_, sonBlock->data_);
				curBlock = sonBlock;
				sonBlock = findSonWithHigherPriority(curBlock);
			}
		}
		return element;
	}

	template<typename P, typename T>
	amt::BinaryIH<PQItem<P, T>>* BinaryHeap<P, T>::getHierarchy()
	{
		return dynamic_cast<amt::BinaryIH<PQItem<P, T>>*>(this->memoryStructure_);
	}

}