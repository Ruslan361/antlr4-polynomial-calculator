#pragma once
#include <ostream>
#include <istream>
#include <iostream>
#include <iomanip>
#include <exception>
#include <vector>
template<typename T>
class VectorIter
{
    T* pointer;
    VectorIter(T* pointer)
    {

    }
    VectorIter operator++(int)
    {
        T* newptr = pointer;
        pointer+=1;
        return newptr;
    }
};

#define SETW 5
template <typename T1>
class Vector;
template <typename T>
std::ostream& operator<< (std::ostream& stream, const Vector<T>& _vector);
template <typename T>
std::istream& operator>> (std::istream& stream, const Vector<T>& _vector);
//template <typename T>
//Vector<T> operator/ (const T& scalar, const Vector<T>& _vector);
template <typename T>
class Vector {
private:
	T* _array;
	size_t copacity;
	size_t size;
public:
	Vector() {
		_array = nullptr;
		size = 0;
		copacity = 0;
	}
	Vector(size_t size) {
		_array = new T[size];
		this->size = size;
		this->copacity = size;
	}
	Vector(const std::vector<T>& vector) {
		size = vector.size();
		_array = new T[size];
		copacity = size;
		this->size = size;
		for (size_t i = 0; i < size; i++)
		{
			_array[i] = vector[i];
		}
	}
	void setCopacity(size_t copacity)
	{
		T* new_array = new T[copacity];
		size_t min = copacity < size ? copacity : size;
		for (size_t i = 0; i < min; i++)
		{
			new_array[i] = _array[i];
		}
		delete[] _array;
		_array = new_array;
		if (copacity < size)
		{
			size = copacity;
		}
		this->copacity = copacity;
	}
	void Insert(size_t pos, const T& value)
	{
		if (pos == size) {
			push_back(value);
			return;
		}
		if (pos > size)
			throw std::out_of_range("position is greater then size + 1");
		resize(size + 1);
		for (size_t i = size; i > pos; i--)
		{
			_array[i] = _array[i - 1];
		}
		_array[pos] = value;
	}
	size_t getCopacity() const { return copacity; }
	Vector(const Vector<T>& _vector);
	size_t getSize() const{
		return size;
	}
	T& at(size_t index) {
		if (index >= size)
			throw std::out_of_range( __FUNCTION__);
		return _array[index];
	}
	int Search(const T& elem)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (elem == _array[i])
			{
				return i;
			}
		}
		return -1;
	}
	void Remove(const T& elem)
	{
		int pos = Search(elem);
		if (pos == -1)
			return;
		for (size_t i = pos+1; i < size; i++)
		{
			_array[i - 1] = _array[i];
		}
		size -= 1;
	}
	void Remove(size_t index)
	{
		for (size_t i = index + 1; i < size; i++)
		{
			_array[i - 1] = _array[i];
		}
		size -= 1;
	}
	~Vector() {
		if (_array != nullptr)
			delete[] _array;
		size = 0;
	}
	void push_back(const T& element);
	T& getBack() {
		return _array[size - 1];
	}
	T& getFront() {
		return _array[0];
	}
	bool operator==(const Vector<T>& _vector) const;
	void resize(size_t size);
	bool operator!=(const Vector<T>& _vector) const;
	Vector<T>& operator-= (const Vector<T>& _vector);
	Vector<T>& operator=(const Vector<T>& _vector);
	bool operator<= (const Vector<T>& _vector) const;
	bool operator>= (const Vector<T>& _vector) const;
	bool operator< (const Vector<T>& _vector) const;
	bool operator> (const Vector<T>& _vector) const;
	Vector<T> operator+ (const Vector<T>& _vector) const;
	Vector<T> operator* (const T& scalar) const;
	Vector<T> operator- (const Vector<T>& _vecctor) const;
	Vector<T> operator/ (const T& scalar) const;
	Vector<T>& operator*= (const T& scalar);
	Vector<T>& operator+= (const Vector<T>& _vector);
	Vector<T>& operator/= (const T& scalar);
	Vector<T>& operator++();
	Vector<T> operator++(int);
	T operator* (const Vector<T>) const;
	const T& operator[] (size_t index) const { return _array[index]; }
	T& operator[] (size_t index) { return _array[index]; }
	friend std::ostream& operator<< <T>(std::ostream& stream, const Vector<T>& _vector);
	//friend Vector<T> operator/ (const T& scalar, const Vector<T>& vector);
	friend std::istream& operator>> <T> (std::istream& stream, const Vector<T>& _vector);
};

template <typename T>
std::ostream& operator<< (std::ostream& stream, const Vector<T>& _vector) {
	for (size_t i = 0; i < _vector.size; i++)
	{
		stream << std::setw(SETW) << _vector._array[i];
	}
	return stream;
}

template <typename T>
std::istream& operator>> (std::istream& stream, const Vector<T>& _vector) {
	for (size_t i = 0; i < _vector.size; i++)
	{
		stream >> _vector._array[i];
	}
	return stream;
}

template <typename T>
T Vector<T>::operator* (const Vector<T> _vector) const {
	size_t min = size < _vector.size ? size : _vector.size;
	T temp = static_cast<T>(0);
	for (size_t i = 0; i < min; i++)
	{
		temp += _array[i] * _vector._array[i];
	}
	return temp;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& _vector) 
{
	this->copacity = _vector.copacity;
	this->size = _vector.size;
	this->_array = new T[copacity];
	for (size_t i = 0; i < _vector.size; i++)
	{
		_array[i] = _vector._array[i];
	}
	//memcpy(_array, _vector._array, (size * sizeof(T)));
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& _vector) {
	if (_array != nullptr) {
		delete[] _array;
	}
	size = _vector.size;
	_array = new T[size];
	for (size_t i = 0; i < size; i++)
	{
		_array[i] = _vector._array[i];
	}
	return *this;
}

template <typename T>
Vector<T> Vector<T>::operator+ (const Vector<T>& _vector) const {
	size_t max = size > _vector.size ? size : _vector.size;
	size_t min = size < _vector.size ? size : _vector.size;
	Vector<T> temp(max);
	size_t i;
	for (i = 0; i < min; i++)
	{
		temp._array[i] = _array[i] + _vector._array[i];
	}
	for (; i < size; i++)
	{
		temp._array[i] = _array[i];
	}
	for (; i < _vector.size; i++)
	{
		temp._array[i] = _vector._array[i];
	}
	return temp;
}

template <typename T>
Vector<T>& Vector<T>::operator+= (const Vector<T>& _vector) {
	*this = *this + _vector;
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-= (const Vector<T>& _vector) {
	*this = *this - _vector;
	return *this;
}

template <typename T>
Vector<T> Vector<T>::operator- (const Vector<T>& _vector) const {
	size_t max = size > _vector.size ? size : _vector.size;
	size_t min = size < _vector.size ? size : _vector.size;
	Vector<T> temp(max);
	size_t i;
	for (i = 0; i < min; i++)
	{
		temp._array[i] = _array[i] - _vector._array[i];
	}
	for (; i < size; i++)
	{
		temp._array[i] = _array[i];
	}
	for (; i < _vector.size; i++)
	{
		temp._array[i] = _vector._array[i];
	}
	return temp;
}

template <typename T>
Vector<T> Vector<T>::operator* (const T& scalar) const {
	Vector<T> temp(size);
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = _array[i] * scalar;
	}
	return temp;
}
template <typename T>
Vector<T> operator* (const T& scalar, const Vector<T> right) {
	return right * scalar;
}

template <typename T>
Vector<T> Vector<T>::operator/ (const T& scalar) const {
	Vector<T> temp(size);
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = _array[i] / scalar;
	}
	return temp;
}

//template <typename T>
//Vector<T> operator/ (const T& scalar, const Vector<T>& _vector) {
//	Vector<T> temp(_vector.size);
//	for (size_t i = 0; i < _vector.size; i++)
//	{
//		temp[i] = scalar / _vector._array[i];
//	}
//	return temp;
//}

template <typename T>
Vector<T>& Vector<T>::operator*= (const T& scalar) {
	*this = *this * scalar;
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator/= (const T& scalar) {
	*this = *this / scalar;
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator++() {
	for (size_t i = 0; i < size; i++)
	{
		++_array[i];
	}
	return *this;
}

template <typename T>
Vector<T> Vector<T>::operator++(int) {
	Vector<T> temp(*this);
	for (size_t i = 0; i < size; i++)
	{
		_array[i]++;
	}
	return temp;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& _vector) const {
	if (size != _vector.size)
		return false;
	for (size_t i = 0; i < size; i++)
	{
		if (_array[i] != _vector._array[i])
			return false;
	}
	return true;
}
template <typename T>
bool Vector<T>::operator!=(const Vector<T>& _vector) const {
	return !(*this == _vector);
}

template <typename T>
void Vector<T>::resize(size_t size) {
	if (copacity < size) {
		T* new_array = new T[size * 2];
		for (size_t i = 0; i < this->size; i++)
		{
			new_array[i] = _array[i];
		}
		delete[] _array;
		_array = new_array;
		copacity = size * 2;
		this->size = size;
		//Vector<T> temp(*this);
		//if (_array != nullptr) {
		//	delete[] _array;
		//}
		//this->copacity = size * 2;
		//_array = new T[copacity];
		//size_t min = this->size < size ? this->size : size;
		//memcpy(_array, temp._array, (min * sizeof(T)));
		//this->size = size;
	}
	else {
		//if (copacity / 3 > size) {
		//	Vector<T> temp(*this);
		//	if (_array != nullptr) {
		//		delete[] _array;
		//	}
		//	this->copacity = size / 2;
		//	_array = new T[copacity];
		//	size_t min = this->size < size ? this->size : size;
		//	memcpy(_array, temp._array, (min * sizeof(T)));
		//}
		this->size = size;
	}
}

template <typename T>
bool Vector<T>::operator<= (const Vector<T>& _vector) const {
	return !(*this > _vector);
}

template <typename T>
bool Vector<T>::operator>= (const Vector<T>& _vector) const {
	return !(*this < _vector);
}

template <typename T>
bool Vector<T>::operator< (const Vector<T>& _vector) const {
	if (size > _vector.size)
		return false;
	if (size < _vector.size)
		return true;
	for (size_t i = 0; i < size; i++)
	{
		if (_array[i] < _vector._array[i])
			return true;
		else if (_array[i] > _vector._array[i])
			return false;
	}
	return false;
}

template <typename T>
bool Vector<T>::operator> (const Vector<T>& _vector) const {
	if (size > _vector.size)
		return true;
	if (size < _vector.size)
		return false;
	for (size_t i = 0; i < size; i++)
	{
		if (_array[i] > _vector._array[i])
			return true;
		else if (_array[i] < _vector._array[i])
			return false;
	}
	return false;
}

template <typename T>
void Vector<T>::push_back(const T& element) {
	resize(size + 1);
	getBack() = element;
}
