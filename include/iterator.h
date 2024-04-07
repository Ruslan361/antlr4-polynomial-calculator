#pragma once
#include <tsinglelinkedlist.h>
#include <vector.h>

template <typename T>
class TSingleLinkedList;
template <typename T>
class Node;

template <typename T>
class Iterator
{
	friend class TSingleLinkedList<T>;
private:
	Node<T>* node;

public:
	Iterator() 
	{
		this->node = nullptr;
	}
	Iterator(Node<T>* d)
	{
		node =  d;
	}
	Iterator(const Iterator& d)
	{
		node = d.node;
	}
	Iterator& operator=(const Iterator& d)
	{
		this->node = d.node;
		return *this;
	}
	bool operator==(const Iterator& iterator) const
	{
		return node == iterator.node;
	}
	bool operator!=(const Iterator& iterator) const
	{
		return node != iterator.node;
	}
	Iterator& operator++();
	Iterator operator++(int);
	const T& operator*() const;
	T& operator*();
	Iterator operator+(size_t n) const;
};

template <typename T>
Iterator<T>& Iterator<T>::operator++()
{
	if (node == nullptr)
	{
		throw std::out_of_range("iterator is out of range");
	}
	node = node->next;
	return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int)
{
	Iterator it = *this;
	if (node == nullptr)
	{
		throw std::out_of_range("iterator is out of range");
	}
	node = node->next;
	return it;
}

template <typename T>
const T& Iterator<T>::operator*() const
{
	if (node == nullptr)
	{
		throw std::out_of_range("iterator is out of range");
	}
	return node->value;
}

template <typename T>
T& Iterator<T>::operator*()
{
	if (node == nullptr)
	{
		throw std::out_of_range("iterator is out of range");
	}
	return node->value;
}

template <typename T>
Iterator<T> Iterator<T>::operator+(size_t n) const
{
	Iterator it = *this;
	for (size_t i = 0; i < n; i++)
	{
		it = ++it;
	}
	return it;
}
