#pragma once
#ifndef POLYNOM_H
#define POLYNOM_H

#include "monom.h"
#include "tsinglelinkedlist.h"
#include <string>
#include <algorithm>
#include <map>
#include <exception>
#include <climits>
#include <cmath>





template <typename T>
class Polynom
{

private:
    TSingleLinkedList<Monom<T>> list_monom;
    std::vector<std::string> names_of_variables;
    bool AreNamesEqual(const std::vector<std::string>& names1, const std::vector<std::string>& names2) const
    {
        if (names1.size() != names2.size())
            return false;

        size_t size = names1.size();
        for (size_t i = 0; i < size; i++)
        {
            if (names1[i] != names2[i])
                return false;
        }
        return true;
    }
public:
    Iterator<Monom<T>> begin() {
        return list_monom.begin();
    };
    Iterator<Monom<T>> end() {
        return list_monom.end();
    };
    Iterator<Monom<T>> tail() {
        return list_monom.tail();
    };
    Polynom()
    {
        list_monom = TSingleLinkedList<Monom<T>>();
        list_monom.Add(Monom<T>());
    }
    Polynom(const TSingleLinkedList<Monom<T>>& monoms, const std::vector<std::string>& variables) : list_monom(monoms)
    {   
        names_of_variables = variables;
        std::sort(names_of_variables.begin(), names_of_variables.end());
    }
    Polynom(const std::vector<std::string> variables) : names_of_variables(variables), list_monom() {}
    std::vector<std::string> GetNamesOfVariables() const
    {
        return names_of_variables;
    }
    int position(const std::string& name);
    int MonomDegree(const Monom<T>& monom, const std::string& name);
    bool operator==(const Polynom& polynom) const
    {
        return (names_of_variables == polynom.names_of_variables) && (list_monom == polynom.list_monom);
    }

    friend std::ostream& operator<< (std::ostream& stream, const Polynom& polynom)
    {
        for (Iterator<Monom<T>> it = polynom.list_monom.begin(); it != polynom.list_monom.end(); it++)
        {
            auto degrees = (*it).GetDegrees();
            if ((*it).coeff >= 0)
                stream << "+" << (*it).coeff;
            else
                stream << (*it).coeff;
            for (size_t i = 0; i < degrees.size(); i++)
            {
                stream << polynom.names_of_variables[i] << '^' << degrees[i];
            }
        }
        return stream;
    }
    friend Polynom<T> operator* (const Monom<T>& monom, const Polynom<T>& polynom)
    {
        return polynom * monom;
    }
    friend Polynom<T> operator* (const T& scalar, const Polynom<T>& polynom)
    {
        return polynom * scalar;
    }
    Polynom<T> operator* (const T& scalar) const;
    Polynom<T> operator/ (const T& scalar) const;
    Polynom operator*(const Polynom<T>& polynom) const;
    Polynom operator*(const Monom<T>& monom) const;
    Polynom operator+(const Polynom<T>& polynom) const;
    Polynom operator+(const Monom<T>& monom) const;
    Polynom operator-(const Monom<T>& monom) const;
    Polynom operator-(const Polynom<T>& polynom) const;

    int MaxDegree(size_t num);
    int MinDegree(size_t num);
    Polynom& BringingSimiliar();
    T Calculate(const std::vector<T>& variables)
    {
        if(variables.size() != names_of_variables.size())
            throw std::invalid_argument("incorrect count of parameters");
        T sum = 0;
        for (auto it = list_monom.begin(); it != list_monom.end(); ++it)
        {
            std::vector<int> degrees = (*it).GetDegrees();
            T monom_sum = (*it).coeff;
            for (size_t i = 0; i < variables.size(); i++)
            {
                monom_sum *= pow(variables[i], degrees[i]);
            }
            sum += monom_sum;
        }
        return sum;
    } 
};

template <typename T>
int Polynom<T>::MinDegree(size_t num)
{
    int min_power = INT_MAX;
    for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
    {
        int degree = (*it).GetDegree(num);
            if (degree < min_power)
            {
                min_power = degree;
            }
    }
    return min_power;
}

template <typename T>
int Polynom<T>::MaxDegree(size_t num)
{
    int max_power = INT_MIN;
    for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
    {
        int degree = (*it).GetDegree(num);
            if (degree > max_power)
            {
                max_power = degree;
            }
    }
    return max_power;
}

template <typename T>
int Polynom<T>::position(const std::string& name)
{
    int size = name.size();
    for (int i = 0; i < size; i++)
    {
        if (names_of_variables[i] == name)
            return i;
    }
    return -1;
}

template <typename T>
Polynom<T> Polynom<T>::operator-(const Polynom<T>& polynom) const
{
    if (!AreNamesEqual(names_of_variables, polynom.names_of_variables))
        throw std::invalid_argument("names of variables are different");

    TSingleLinkedList<Monom<T>> new_list_monom;

    TSingleLinkedList<Monom<T>> polynom_copy(polynom.list_monom);

    for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
    {
        bool flag = false;
        for (Iterator<Monom<T>> it2 = polynom_copy.begin(); it2 != polynom_copy.end(); )
        {
            if ((*it).IsEqualDegrees(*it2))
            {
                new_list_monom.Add(*it - *it2);
                polynom_copy.Remove(it2);
                flag = true;
                break;
            }
            else
            {
                it2++;
            }
        }
        if (!flag)
        {
            new_list_monom.Add(*it);
        }
    }
    for (Iterator<Monom<T>> it2 = polynom_copy.begin(); it2 != polynom_copy.end(); it2++)
    {
        new_list_monom.Add(*it2 * T(-1));
    }
    return Polynom(new_list_monom, names_of_variables);
}

template <typename T>
Polynom<T> Polynom<T>::operator* (const T& scalar) const
{
    TSingleLinkedList<Monom<T>> new_list_monom;
    for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
    {
        new_list_monom.Add(*it * scalar);
    }
    return Polynom<T>(new_list_monom, names_of_variables);
}

template<typename T>
inline Polynom<T> Polynom<T>::operator/(const T& scalar) const
{
    TSingleLinkedList<Monom<T>> new_list_monom;
    for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
    {
        new_list_monom.Add(*it / scalar);
    }
    return Polynom<T>(new_list_monom, names_of_variables);
}

template <typename T>
int Polynom<T>::MonomDegree(const Monom<T>& monom, const std::string& name)
{
    int pos = position(name);
    if (pos > -1)
    {
        return monom[pos];
    }
    throw std::out_of_range("this variable is not in polynom");
}

template <typename T>
Polynom<T>& Polynom<T>::BringingSimiliar()
{
    for (auto it = list_monom.begin(); it != list_monom.end(); it++)
    {
        for (auto it2 = it + 1; it2 != list_monom.end(); it2++)
        {
            if ((*it).IsEqualDegrees(*it2))
            {
                (*it).coeff += (*it2).coeff;
                list_monom.Remove(it2);
          }
        }
    }
    return *this;
}

template <typename T>
Polynom<T> Polynom<T>::operator+(const Polynom<T>& polynom) const
{
    if (!AreNamesEqual(names_of_variables, polynom.names_of_variables))
        throw std::invalid_argument("names of variables are different");

    TSingleLinkedList<Monom<T>> new_list_monom;

    TSingleLinkedList<Monom<T>> polynom_copy(polynom.list_monom);

    for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
    {
        bool flag = false;
        for (Iterator<Monom<T>> it2 = polynom_copy.begin(); it2 != polynom_copy.end(); )
        {
            if ((*it).IsEqualDegrees(*it2))
            {
                new_list_monom.Add(*it + *it2);
                polynom_copy.Remove(it2);
                flag = true;
                break;
            }
            else
            {
                it2++;
            }
        }
        if (!flag)
        {
            new_list_monom.Add(*it);
        }
    }
    for (Iterator<Monom<T>> it2 = polynom_copy.begin(); it2 != polynom_copy.end(); it2++)
    {
        new_list_monom.Add(*it2);
    }
    return Polynom(new_list_monom, names_of_variables);
}

template<typename T>
inline Polynom<T> Polynom<T>::operator+(const Monom<T>& monom) const
{
    Polynom<T> new_pol(*this);
    new_pol.list_monom.Add(monom);
}

template<typename T>
inline Polynom<T> Polynom<T>::operator-(const Monom<T>& monom) const
{
    Polynom<T> new_pol(*this);
    new_pol.list_monom.Add(monom*(-1));
}

template <typename T>
Polynom<T> Polynom<T>::operator*(const Monom<T>& monom) const
{
    TSingleLinkedList<Monom<T>> new_list_monom;
    for (Iterator<Monom<T>> it2 = list_monom.begin(); it2 != list_monom.end(); it2++)
    {
        new_list_monom.Add(*it2 * monom);
    }
    return Polynom<T>(new_list_monom, names_of_variables);
}

template <typename T>
Polynom<T> Polynom<T>::operator*(const Polynom<T>& polynom) const
{
    TSingleLinkedList<Monom<T>> new_list_monom;
    for (Iterator<Monom<T>> it2 = polynom.list_monom.begin(); it2 != polynom.list_monom.end(); it2++)
    {
        for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
        {
            new_list_monom.Add(*it * (*it2));
        }
    }
    return Polynom<T>(new_list_monom, names_of_variables);
}

#endif
