#pragma once
#include "tpair.h"
#include "tsinglelinkedlist.h"
template <typename TKey, typename TValue>
class TTable
{
public:
	virtual void Add(const TKey& key, const TValue& value) = 0;
	virtual void Add(const TPair<TKey, TValue>& pair) = 0;
	virtual void Remove(const TKey& key) = 0;
	virtual bool Search(const TKey& key, TValue& value) const = 0;
    virtual TSingleLinkedList<TKey> GetKeys() = 0;
    virtual TSingleLinkedList<TValue> GetValues(const TKey& key) = 0;
    //virtual TPair<Tkey, TValue>& At();
	virtual ~TTable() {}
};

