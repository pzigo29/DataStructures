#pragma once

#include <libds/amt/implicit_sequence.h>
#include <libds/adt/queue.h>
#include <libds/adt/array.h>
#include <functional>
#include <cmath>
#include <algorithm>
#include <type_traits>

namespace ds::adt
{
    template <typename T>
    struct Sort
    {
    public:
        virtual void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) = 0;
        void sort(amt::ImplicitSequence<T>& is) { sort(is, [](const T& a, const T& b)->bool {return a < b; }); }
    };

    //----------

    template <typename T>
    class SelectSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class InsertSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class BubbleSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class QuickSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void quick(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max);
    };

    //----------

    template <typename T>
    class HeapSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class ShellSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t k);
    };

    //----------

    template <typename Key, typename T>
    class RadixSort :
        public Sort<T>
    {
        static_assert(std::is_integral_v<Key>, "Radix sort supports only integral types.");

    public:
        RadixSort();
        RadixSort(std::function<Key(const T&)> getKey);

        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        std::function<Key(const T&)> getKey_;
    };

    //----------

    template <typename T>
    class MergeSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void split(size_t n);
        void merge(std::function<bool(const T&, const T&)> compare, size_t n);

    private:
        ImplicitQueue<T>* queue1_ {nullptr};
        ImplicitQueue<T>* queue2_ {nullptr};
        ImplicitQueue<T>* mergeQueue_ {nullptr};
    };

    //----------

    template<typename T>
    void SelectSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        for (size_t i = 0; i < is.size() - 1; ++i)
        {
            size_t minIndex = i;
	        for (size_t j = i + 1; j < is.size(); ++j)
	        {
		        if (compare(is.access(j)->data_, is.access(minIndex)->data_))
		        {
			        minIndex = j;
		        }
	        }
        	std::swap(is.access(i)->data_, is.access(minIndex)->data_);
            
        }
    }

    template<typename T>
    void InsertSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        for (size_t i = 1; i < is.size(); ++i)
        {
            T tmp = is.access(i)->data_;
            size_t j = i;
            while (j > 0 && compare(tmp, is.access(j - 1)->data_))
            {
	            is.access(j)->data_ = is.access(j - 1)->data_;
                --j;
            }
            is.access(j)->data_ = tmp;
        }
    }

    template<typename T>
    void BubbleSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        bool exchange;
        do
        {
	        exchange = false;
            for (size_t i = 0; i < is.size() - 1; ++i)
            {
	            if (compare(is.access(i + 1)->data_, is.access(i)->data_))
	            {
                    std::swap(is.access(i + 1)->data_, is.access(i)->data_);
                    exchange = true;
	            }
            }
        }
        while (exchange);
    }

    template<typename T>
    void QuickSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        if (!is.isEmpty())
        {
            quick(is, compare, 0, is.size() - 1);
        }
    }

    template<typename T>
    void QuickSort<T>::quick(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max)
    {
        // TODO 12
        T pivot = is.access(min + (max - min) / 2)->data_;
        int left = min;
        int right = max;
        do
        {
	        while (compare(is.access(left)->data_, pivot))
	        {
		        ++left;
	        }
	        while (right > 0 && compare(pivot, is.access(right)->data_))
	        {
                --right;
	        }
	        if (left <= right)
	        {
                std::swap(is.access(left)->data_, is.access(right)->data_);
                ++left;
                if (right > 0)
                {
                    --right;
                }
	        }
        }
        while (left <= right);
        if (min < right)
        {
            quick(is, compare, min, right);
        }
        if (left < max)
        {
            quick(is, compare, left, max);
        }
    }

    template<typename T>
    void HeapSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        for (size_t i = 1; i < is.size(); ++i)
        {
            bool exchange;
            int actual = i;
            do
            {
                exchange = false;
                int parent = (actual - 1) / 2;
                if (actual > 0 && compare(is.access(parent)->data_, is.access(actual)->data_))
                {
                    std::swap(is.access(actual)->data_, is.access(parent)->data_);
                    actual = parent;
                    exchange = true;
                }
            } while (exchange);
        }
        for (size_t i = is.size() - 1; i > 0; --i)
        {
            std::swap(is.access(0)->data_, is.access(i)->data_);
            bool exchange;
            int actual = 0;
	        do
	        {
                exchange = false;
                int left = 2 * actual + 1;
                int right = 2 * actual + 2;
                int max;
                if (left < i && right < i)
                {
                    max = compare(is.access(right)->data_, is.access(left)->data_) ? left : right;
                }
                else
                {
	                max = left < i ? left : right;
                }
                if (max < i && compare(is.access(actual)->data_, is.access(max)->data_))
                {
                    std::swap(is.access(actual)->data_, is.access(max)->data_);
                	actual = max;
					exchange = true;
                }
	        }
	        while (exchange);
        }
    }

    template<typename T>
    void ShellSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        shell(is, compare, static_cast<size_t>(std::ceil(std::log10(is.size()))));
    }

    template<typename T>
    void ShellSort<T>::shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t k)
    {
        // TODO 12
        for (size_t d = 0; d < k; ++d)
        {
	        for (size_t i = d; i < is.size(); ++i)
	        {
		        int j = i;
		        while (j >= k && (j - k) >= d && 
                    compare(is.access(j)->data_, is.access(j - k)->data_))
		        {
                    std::swap(is.access(j)->data_, is.access(j - k)->data_);
                    j = j - k;
		        }
	        }
        }
        if (k > 1)
        {
            shell(is, compare, k - 1);
        }
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort() :
        getKey_([](auto const& x) { return x; })
    {
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort(std::function<Key(const T&)> getKey) :
        getKey_(getKey)
    {
    }

    template<typename Key, typename T>
    void RadixSort<Key, T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        Array<ExplicitQueue<T>*> sections = 10;
        for (int i = 0; i < 10; ++i)
        {
            sections.set(new ExplicitQueue<T>, i);
        }
        int component = 1;
        bool existsNextComponent = true;
        while (existsNextComponent)
        {
            existsNextComponent = false;
            for (auto element : is)
            {
                auto key = getKey_(element);
                sections.access((key / component) % 10)->push(element);
                if (element / (component * 10) > 0)
                {
                    existsNextComponent = true;
                }
            }
            component = component * 10;
            int index = 0;
            for (int i = 0; i < 10; ++i)
            {
                ExplicitQueue<T>* section = sections.access(i);
                while (!section->isEmpty())
                {
                    is.access(index)->data_ = section->pop();
                    ++index;
                }
            }
        }
        for (int i = 0; i < 10; ++i)
        {
            delete sections.access(i);
        }
    }

    template<typename T>
    void MergeSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
    	queue1_ = new ImplicitQueue<T>(is.size());
    	queue2_ = new ImplicitQueue<T>(is.size());
        mergeQueue_ = new ImplicitQueue<T>(is.size());
        for (auto element: is)
        {
            mergeQueue_->push(element);
        }
        int i = 1;
        while (i < is.size())
        {
            split(i);
            merge(compare, i);
            i = i * 2;
        }
        split(i);
        merge(compare, i);
        for (int i = 0; i < is.size(); ++i)
        {
        	is.access(i)->data_ = mergeQueue_->pop();
		}
        delete queue1_;
        delete queue2_;
        delete mergeQueue_;
        queue1_ = nullptr;
        queue2_ = nullptr;
        mergeQueue_ = nullptr;
        
    }

    template<typename T>
    void MergeSort<T>::split(size_t n)
    {
        // TODO 12
        int count = 0;
        bool isFirst = true;
        while (!mergeQueue_->isEmpty())
        {
	        if (count % n == 0)
	        {
		        count = 0;
                isFirst = !isFirst;
	        }
	        if (isFirst)
	        {
		        queue1_->push(mergeQueue_->pop());
	        }
            else
            {
            	queue2_->push(mergeQueue_->pop());
			}
			++count;
        }
    }

    template<typename T>
    void MergeSort<T>::merge(std::function<bool(const T&, const T&)> compare, size_t n)
    {
        // TODO 12
        int count1 = 0;
        int count2 = 0;
        do
        {
	        if (count1 == 0 && count2 == 0)
	        {
                count1 = std::min(n, queue1_->size());
                count2 = std::min(n, queue2_->size());
	        }
            T* key1 = count1 > 0 ? &queue1_->peek() : nullptr;
            T* key2 = count2 > 0 ? &queue2_->peek() : nullptr;
	        if (key1 != nullptr && key2 != nullptr)
	        {
		        if (compare(*key1, *key2))
		        {
			        --count1;
                    mergeQueue_->push(queue1_->pop());
		        }
                else
                {
                	--count2;
					mergeQueue_->push(queue2_->pop());
				}
	        }
	        else
	        {
		        if (key1 != nullptr)
		        {
			        --count1;
					mergeQueue_->push(queue1_->pop());
		        }
                else
                {
	                if (key2 != nullptr)
	                {
		                --count2;
                        mergeQueue_->push(queue2_->pop());
	                }
                }
	        }
        }
        while (!queue1_->isEmpty() || !queue2_->isEmpty());
    }
}