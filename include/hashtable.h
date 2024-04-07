#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "ttable.h"
#include "vector.h"
#include "unorderedmaplist.h"

//hash generator must return hash from 0 to size
template <typename T>
class DefaultHashGenerator
{
public:
    DefaultHashGenerator(){}
    unsigned int operator()(T value, size_t size) const
    {
        return value % size;
    }
};

template <typename TKey, typename TValue, typename HashGenerator = DefaultHashGenerator<TKey>>
class THashTable : public TTable<TKey, TValue>
{
    Vector<TUnorderedMapList<TKey, TValue>> batches;
    HashGenerator generator;
public:
    THashTable(const THashTable& hash_table)
    {
        batches = Vector<TUnorderedMapList<TKey, TValue>>(hash_table.batches);
        generator = HashGenerator();
    }
    THashTable(size_t size)
    {
        batches = Vector<TUnorderedMapList<TKey, TValue>>(size);
        generator = HashGenerator();
    }
    THashTable() : THashTable(100) {}
    void Add(const TKey& key, const TValue& value) override
    {
        size_t size = batches.getSize();
        //I hope hash between 0 and size
        unsigned int hash = generator(key, size);
        batches[hash].Add(key, value);
    }
    void Add(const TPair<TKey, TValue>& pair) override
    {
        Add(pair.key, pair.value);
    }
    void Remove(const TKey& key) override
    {
        size_t size = batches.getSize();
        //I hope hash between 0 and size
        unsigned int hash = generator(key, size);
        batches[hash].Remove(key);
    }
    bool Search(const TKey& key, TValue& value) const override
    {
        size_t size = batches.getSize();
        //I hope hash between 0 and size
        unsigned int hash = generator(key, size);
        return batches[hash].Search(key, value);
    }
    TSingleLinkedList<TKey> GetKeys() override
    {
        TSingleLinkedList<TKey> keys;
        size_t batchesSize = batches.getSize();
        for (size_t i = 0; i < batchesSize; ++i)
        {
            TSingleLinkedList<TKey> batchKeys = batches[i].GetKeys();
            for(auto it = batchKeys.begin(); it != batchKeys.end(); ++it)
            {
                keys.Add(*it);
            }
        }
        return keys;
    }
    TSingleLinkedList<TValue> GetValues(const TKey& key) override
    {
        TSingleLinkedList<TValue> values;
        TValue value;
        if(Search(key, value))
        {
            values.Add(value);
        }
        return values;
    }
    void Resize(size_t size)
    {
        THashTable NewHashTable(size);
        TSingleLinkedList<TKey> keys = GetKeys();
        for (auto it = keys.begin(); it != keys.end(); ++it) {
            TValue val;
            if(Search((*it)), val)
            {
                NewHashTable.Add((*it), val);
            }
        }
        *this = NewHashTable;
    }
};

#endif // HASHTABLE_H
