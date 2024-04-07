#pragma once
template <typename TKey, typename TValue>
struct TPair
{
	TKey key;
	TValue value;
	TPair(const TKey& key, const TValue& value)
	{
		this->key = key;
		this->value = value;
    }
    TPair() : TPair(TKey(), TValue())
    {

	}
};
