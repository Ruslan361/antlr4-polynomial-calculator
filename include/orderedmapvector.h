#pragma once
#include "vector.h"
#include "ttable.h"
#include "tpair.h"


template <typename TKey, typename TValue>
class TOrderedMapVector : public TTable<TKey, TValue>
{
private:
	Vector<TPair<TKey, TValue>> values;
public:
	TOrderedMapVector(size_t size)
	{
		values = Vector<TPair<TKey, TValue>>();
		values.setCopacity(size);
    };
    TOrderedMapVector() : TOrderedMapVector(100)
    {

    };
	//false if is not exist 
	//true if exist
	bool SearchInsertPos(const TKey& key, size_t& pos)
	{
		size_t size = values.getSize();
		if (size == 0)
		{
			pos = 0;
			return false;
		}
		size_t start = 0;
		size_t end = size - 1;
		size_t middle = start + (end - start) / 2;
		while (end - start > 5)
		{
			if (values[middle].key > key)
			{
				end = middle;
			}
			else if (values[middle].key < key)
			{
				start = middle;
			}
			else
			{
                //
                pos = middle;
				return true;
			}
			middle = start + (end - start) / 2;
		}
		for (size_t i = start; i <= end; i++)
		{
			if (values[i].key == key)
			{
                pos = i;
				return true;
			}
			if (values[i].key > key)
			{
				pos = i;
				return false;
			}
		}
		pos = end + 1;
		return false;
		//size_t size = values.getSize();
		//for (size_t i = 0; i < size; i++)
		//{
		//	if (values[i].key == key)
		//	{
		//		value = values[i].value;
		//		return false;
		//	}
		//}
		//return true;
	}
    virtual TSingleLinkedList<TKey> GetKeys() override
    {
        TSingleLinkedList<TKey> keys;
        for (int var = 0; var < values.getSize(); ++var) {
            TKey current_key = values[var].key;
            keys.Add(current_key);
        }
        return keys;
    }
    TSingleLinkedList<TValue> GetValues(const TKey& key) override
    {
        TSingleLinkedList<TValue> val;
        TValue searched_val;
        if (Search(key, searched_val))
        {
            val.Add(searched_val);
        }
        return val;
    }
	bool Search(const TKey& key, TValue& value) const override
	{
		size_t size = values.getSize();
		if (size == 0) return false;
		size_t start = 0;
		size_t end = size - 1;
		size_t middle = start + (end - start) / 2;
		while (end - start > 5)
		{
			if (values[middle].key > key)
			{
				end = middle;
			}
			else if (values[middle].key < key)
			{
				start = middle;
			}
			else 
			{
				value = values[middle].value;
				return true;
			}
			middle = start + (end - start) / 2;
		}
		for (size_t i = start; i <= end; i++)
		{
			if (values[i].key == key)
			{
				value = values[i].value;
				return true;
			}
		}
		/*size_t size = values.getSize();
		for (size_t i = 0; i < size; i++)
		{
			if (values[i].key == key)
			{
				value = values[i].value;
				return true;
			}
		}*/
		return false;
	}
	void Add(const TKey& key, const TValue& value) override
	{
		size_t index;
		if (SearchInsertPos(key, index))
		{
			throw std::invalid_argument("you can not add value because key is exist in TUnorderedMapVector");
		}
		else
		{
			values.Insert(index, TPair<TKey, TValue>(key, value));
		}
		//values.push_back(TPair<TKey, TValue>(key, value));
	}
	void Add(const TPair<TKey, TValue>& pair) override
	{
		this->Add(pair.key, pair.value);
	}
	void Remove(const TKey& key) override
	{
		size_t index;
		if (SearchInsertPos(key, index))
		{
			values.Remove(index);
		}
	}
	~TOrderedMapVector() {

	}
};
