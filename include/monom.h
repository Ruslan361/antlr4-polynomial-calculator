#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class Monom
{
private:
    std::vector<int> degrees;
public:
    T coeff;
    Monom() : Monom(0, {0})
    {

    }
    Monom(const T& coef, const std::vector<T>& degrees)
    {
        this->coeff = coef;
        this->degrees = degrees;
    }
    bool IsEqualDegrees(const std::vector<T>& degrees) const;
    int GetDegree(size_t num)
    {
        return degrees[num];
    }
    bool IsEqualDegrees(const Monom<T>& monom) const
    {
        return IsEqualDegrees(monom.degrees);
    }
    std::vector<int> GetDegrees() const
    {
        return degrees;
    }
    friend Monom<T> operator*(const T& scalar, const Monom<T>& monom)
    {
        return Monom<T>(monom.coeff * scalar, monom.degrees);
    }
    friend Monom<T> operator/(const T& scalar, const Monom<T>& monom)
    {
        return Monom<T>(monom.coeff / scalar, monom.degrees);
    }
    Monom operator+(const Monom& monom) const;
    Monom operator-(const Monom& monom) const;
    Monom operator*(const Monom& monom) const;
    Monom operator*(const T& monom) const;
    Monom operator/(const T& monom) const;
    Monom& operator=(const Monom& monom)
    {
        coeff = monom.coeff;
        degrees = monom.degrees;
    }
    bool operator==(const Monom& monom) const
    {
        return IsEqualDegrees(monom.degrees) && (monom.coeff == coeff);
    }
    bool operator!=(const Monom& monom) const
    {
        return !(*this == monom);
    }
    int operator[](size_t p)
    {
        return degrees[p];
    }
};

template <typename T>
Monom<T> Monom<T>::operator*(const Monom<T>& monom) const
{
    size_t this_derees_size = degrees.size();
    size_t monom_degrees_size = monom.degrees.size();

    size_t min_degree = this_derees_size < monom_degrees_size ? this_derees_size : monom_degrees_size;
    size_t max_degree = this_derees_size > monom_degrees_size ? this_derees_size : monom_degrees_size;

    std::vector<int> new_degree(max_degree);
    size_t i;
    for (i = 0; i < min_degree; i++)
    {
        new_degree[i] = degrees[i] + monom.degrees[i];
    }
    if (this_derees_size < monom_degrees_size)
    {
        for (; i < max_degree; i++)
        {
            new_degree[i] = monom.degrees[i];
        }
    }
    else
    {
        for (; i < max_degree; i++)
        {
            new_degree[i] = degrees[i];
        }
    }
    return Monom(coeff * monom.coeff, new_degree);
}

template<typename T>
inline Monom<T> Monom<T>::operator*(const T& scalar) const
{
    return Monom(coeff * scalar, degrees);
}

//template<typename T>


template<typename T>
inline Monom<T >Monom<T>::operator/(const T& scalar) const
{
    return Monom(coeff / scalar, degrees);
}

template <typename T>
Monom<T> Monom<T>::operator+(const Monom<T>& monom) const
{
    if(!IsEqualDegrees(monom.degrees))
        throw std::invalid_argument("You can not sum different monoms");
    return Monom<T>(coeff + monom.coeff, degrees);
}

template <typename T>
Monom<T> Monom<T>::operator-(const Monom<T>& monom) const
{
    if(!IsEqualDegrees(monom.degrees))
        throw std::invalid_argument("You can not sub different monoms");
    return Monom<T>(coeff - monom.coeff, degrees);
}

template <typename T>
bool Monom<T>::IsEqualDegrees(const std::vector<T>& degrees) const
{
    if (degrees.size() != this->degrees.size())
        return false;
    size_t size = degrees.size();
    for (size_t i = 0; i < size; i++)
    {
        if (degrees[i] != this->degrees[i])
            return false;
    }
    return true;
}
