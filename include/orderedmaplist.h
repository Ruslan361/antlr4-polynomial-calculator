#pragma once
#include "tsinglelinkedlist.h"
#include "ttable.h"
#include "tpair.h"


template <typename TKey, typename TValue>
class TOrderedMapList : public TTable<TKey, TValue>
{
private:
	TSingleLinkedList<TPair<TKey, TValue>> values;
public:
	TOrderedMapList()
	{
		values = TSingleLinkedList<TPair<TKey, TValue>>();
	}
    Iterator<TPair<TKey, TValue>> begin()
    {
        return values.begin();
    }
    Iterator<TPair<TKey, TValue>> end()
    {
        return values.end();
    }
    virtual TSingleLinkedList<TKey> GetKeys() override
    {
        TSingleLinkedList<TKey> keys;
        for (auto it = values.begin(); it != values.end(); ++it)
        {
            keys.Add((*it).key);
        }
        return keys;
    }
    TSingleLinkedList<TValue> GetValues(const TKey& key) override
    {
        TSingleLinkedList<TValue> val;
        for (auto it = values.begin(); it != values.end(); ++it)
        {
            TPair<TKey, TValue> elem = *it;
            if(elem.key == key)
                val.Add(elem.value);
            else if (elem.key > key)
                break;
        }
        return val;
    }
	bool Search(const TKey& key, TValue& value) const override
	{
		for (auto it = values.begin(); it != values.end(); it++)
		{
			auto elem = *it;
			if (elem.key == key)
			{
				value = elem.value;
				return true;
			}
			if (elem.key > key)
				return false;
		}
		return false;
	}
	void Add(const TKey& key, const TValue& value) override
	{
		TValue search_value;
		if (Search(key, search_value))
		{
			throw std::invalid_argument("you can not add value because key is exist in TUnorderedMapVector");
		}
		//if (values.IsEmpty())
		//{
		//	values.Add(TPair<TKey, TValue>(key, value));
		//	return;
		//}
		for (auto it = values.begin(); it != values.end(); it++)
		{
			auto elem = *it;
			if (elem.key == key)
			{
				throw std::invalid_argument("you can not add value because key is exist in TUnorderedMapVector");
			}
			if (elem.key > key)
			{
				values.Insert(it, TPair<TKey, TValue>(key, value));
				return;
			}
		}
		values.Add(TPair<TKey, TValue>(key, value));
	}
	void Add(const TPair<TKey, TValue>& pair) override
	{
		this->Add(pair.key, pair.value);
	}
	void Remove(const TKey& key) override
	{
		auto it = values.begin();
		for (; it != values.end(); it++)
		{
			auto elem = *it;
			if (elem.key == key)
			{
				break;
			}
			if (elem.key > key)
				return;
		}
		if (it != values.end())
			values.Remove(it);
	}
	~TOrderedMapList() {

	}
};
