#pragma once
#include <stdexcept>
#include <ostream>
#include <iterator.h>
#include <iostream>

template <typename T>
class Iterator;

template <typename T>
class TSingleLinkedList;

template <typename T>
class Compare
{
	bool (*cmp) (const T& first, const T& second);
public:
	Compare(bool (*cmp) (const T& first, const T& second)) 
	{
		this->cmp = cmp;
	}
	bool operator() (const T& first, const T& second)
	{
		return cmp(first);
	}
};

template <typename T>
class Node
{
public:
	Node(const T& _value) : value(_value), next(nullptr) {}
	Node(const T& _value, Node* _next) : value(_value), next(_next) {}
	Node& operator=(const Node& node)
	{
		value = node.value;
		next = node.next;
		return *this;
	}
	bool operator==(const Node& node) const
	{
		return (value == node.value) && (next == node.next);
	}
private:
	T value;
	Node* next;
	friend class TSingleLinkedList<T>;
	friend class Iterator<T>;
};



template <typename T>
class TSingleLinkedList
{
public:

	private:
	Node<T>* first;
	Node<T>* last;
	public:
	TSingleLinkedList& operator=(const TSingleLinkedList& node)
	{
		while (begin() != end())
		{
			auto it = begin();
			Remove(it);
		}
		for (Iterator<T> it = node.begin(); it != node.end(); ++it)
		{
			Add(*it);
		}
		return *this;
	}

	bool operator==(const TSingleLinkedList& list) const;


	Iterator<T> begin() const
	{
		return Iterator<T>(first);
	}
	Iterator<T> end() const
	{
		return Iterator<T>();
	}
	Iterator<T> tail() const
	{
		return Iterator<T>(last);
	}
	TSingleLinkedList() {
		first = nullptr;
		last = nullptr;
	}
	TSingleLinkedList(const T& element)
	{
		first = new Node(element);
		last = first;
	}
	TSingleLinkedList(const TSingleLinkedList& list)
	{
		first = nullptr;
		last = nullptr;
		for (Iterator<T> i = list.begin(); i != list.end(); i++)
		{
			Add(*i);
		}
		//Add(*(list.end()));
	}
	void Add(const T& value);
	void Remove(size_t num = 0);
	bool IsEmpty() const
	{
		return !first;
	}
	~TSingleLinkedList();
	T& At(size_t num = 0);
	T& Last()
	{
		return last->value;
	}
	const T& Last() const
	{
		if (!first) throw std::out_of_range("list is over");
		return last->value;
	}
	const T& At(size_t num = 0) const;
	friend std::ostream& operator<< (std::ostream& stream, const TSingleLinkedList<T>& list) {
		stream << list.first->value << '\n';
		Node<T>* current = list.first;
		while (current = current->next) {
			stream << current->value;
		}
		return stream;
	}
	Iterator<T> Insert(const Iterator<T>& iter, const T& element);
	void Remove(Iterator<T>& iter);
};

template<typename T>
bool TSingleLinkedList<T>::operator==(const TSingleLinkedList<T>& list) const
{
	Iterator<T> this_it;
	Iterator<T> list_it;
	for (this_it = begin(), list_it = list.begin(); ((this_it != end()) && (list_it != list.end())); ++this_it, ++list_it)
	{
		if (*this_it != *list_it)
			return false;
	}
	if (this_it != end())
		return false;
	if (list_it != list.end())
		return false;
	return true;
}

template<typename T>
Iterator<T> TSingleLinkedList<T>::Insert(const Iterator<T>& iter, const T& element)
{
	if (!iter.node)
		throw std::out_of_range("null iterator");

	if (IsEmpty())
	{
		first = new Node<T>(element);
		last = first;
		return Iterator<T>(first);
	}
	if (iter.node == last)
	{
		Add(element);
		return Iterator<T>(last);
	}
	Node<T>* current = new Node<T>(element, iter.node->next);
	iter.node->next = current;
	std::swap(current->value, iter.node->value);
	return Iterator<T>(current);
}

template<typename T>
void TSingleLinkedList<T>::Remove(Iterator<T>& iter)
{
	if (iter.node == nullptr)
		throw std::out_of_range("null iterator");
	if (IsEmpty())
		throw std::out_of_range("you can not delete element from empty list");
	if (first == iter.node)
	{
		Node<T>* current = (iter.node->next);
		first = current;
		delete iter.node;
		iter = Iterator<T> (first);
		if (!first)
		{
			last = nullptr;
		}
		return;
	}
	Node<T>* prev = first;
	Node<T>* current = first->next;
	while (current && (iter.node != current))
	{
		prev = current;
		current = current->next;
	}
	if (iter.node == current){
		Node<T>* next = current->next;
		delete current;
		prev->next = next;
		iter = Iterator<T>(next);
		return;
	}
	throw std::out_of_range("this iterator is incorrect");
}

template<typename T>
inline void TSingleLinkedList<T>::Add(const T& value) {
	if (!first)
	{
		first = new Node<T>(value);
		last = first;
	}
	else {
		last->next = new Node<T>(value);
		last = last->next;
	}
}

template<typename T>
inline void TSingleLinkedList<T>::Remove(size_t num) {
	if (!first) throw std::out_of_range("list is over");
	Node<T>* current = first;
	Node<T>* prev = nullptr;
	while (num > 0)
	{
		prev = current;
		if ((current = current->next) == nullptr) throw std::out_of_range("list is over");
		num--;
	}
	Node<T>* next = current->next;
	if (prev != nullptr) prev->next = next;
	else
	{
		first = next;
	}
	delete current;
	if (!first) last = nullptr;
}

template<typename T>
inline TSingleLinkedList<T>::~TSingleLinkedList() {
	if (first == last) {
		delete first;
	}
	else {
		Node<T>* prev = first;
		while (Node<T>* current = prev->next)
		{
			delete prev;
			prev = current;
		}
		delete prev;
	}
}

template<typename T>
inline T& TSingleLinkedList<T>::At(size_t num) {
	if (!first) throw std::out_of_range("list is over");
	Node<T>* current = first;
	while (num > 0)
	{
		if ((current = current->next) == nullptr) throw std::out_of_range("list is over");
		num--;
	}
	return current->value;
}

template<typename T>
inline const T& TSingleLinkedList<T>::At(size_t num) const {
	if (!first) throw std::out_of_range("list is over");
	Node<T>* current = first;
	while (num > 0)
	{
		if ((current = current->next) == nullptr) throw std::out_of_range("list is over");
		num--;
	}
	return current->value;
}
