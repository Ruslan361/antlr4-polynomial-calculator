#include <iostream>
#include "polynom.h"

std::vector<std::string> SplitPolynom(const std::string& polynom)
{
    std::vector<std::string> monoms;
    std::string current;
    for (char c : polynom)
    {
        if((c == '+'))
        {
            //std::cout << current << '\n';
            monoms.push_back(current);
            current = "";
        } 
        else if (c == '-')
        {
            //std::cout << current << '\n';
            monoms.push_back(current);
            current = "-";
        }
        else
        {
            current += c;
        }
    }
    monoms.push_back(current);
    //std::cout << current;
    return monoms;
}

Monom<int> MonomFromString(std::string monom, const std::vector<std::string>& names_of_variables)
{
    int mul = 1;
    if (monom[0] == '-')
    {
        mul = -1;
        monom.erase(0,1);
    }
    size_t size = monom.size();

    int coeff = 0;
    std::vector<int> degrees(names_of_variables.size());
    std::fill(degrees.begin(), degrees.end(), 0);


    int i = 0;
    while (isdigit(monom[i]) && i < monom.size())
    {
        coeff *= 10;
        coeff += int(monom[0] - '0');
        i++;
    }
    if (!isdigit(monom[0]))
        coeff = 1;

    std::string current;
    for (; i < monom.size(); i++)
    {
        current += monom[i];
        auto it = find(names_of_variables.begin(), names_of_variables.end(), current);
        if (it != names_of_variables.end())
        {
            int index = it - names_of_variables.begin();
            if ((i+2 < monom.size()) && (monom[i+1] == '^') && isdigit(monom[i+2]))
            {
                degrees[index] = monom[i+2] - '0';
                i+=2;
            }
            else
            {
                degrees[index] = 1;
            }
            current = "";
        }
    }
    if (!current.empty())
        throw std::invalid_argument("something went wrong");
    /*
    std::cout << coeff << std::endl;
    for (int d : degrees)
    {
        std::cout << d << '\n';
    }
    */
    return Monom<int>(coeff, degrees);
}

Polynom<int> PolynomFromString(const std::string& polynom, const std::vector<std::string> names_of_variables)
{
    TSingleLinkedList<Monom<int>> list_monom;
    std::vector<std::string> monoms = SplitPolynom(polynom);
    for (size_t i = 0; i < monoms.size(); i++)
    {
        list_monom.Add(MonomFromString(monoms[i], names_of_variables));
    }
    return Polynom<int>(list_monom, names_of_variables);
}

int main()
{
    std::cout << "Enter number of variables" << std::endl;
    size_t num_of_variables;
    std::cin >> num_of_variables;
    std::vector<std::string> names_of_variables;
    std::sort(names_of_variables.begin(), names_of_variables.end());

    std::cout << "Enter names of variables" << std::endl;
    for (size_t i = 0; i < num_of_variables; i++)
    {
        std::string current;
        std::cin >> current;
        names_of_variables.push_back(current);
    }
    std::cout << "Enter polynom like this" << std::endl;
    std::cout << "1";
    for (std::string str: names_of_variables)
    {
        std::cout << str << "^2"; 
    }
    std::cout << std::endl;
    
    std::string polynom;
    //std::getline(std::cin, polynom);
    std::cin >> polynom;
    Polynom<int> p1 = PolynomFromString(polynom, names_of_variables);

    std::cin >> polynom;
    Polynom<int> p2 = PolynomFromString(polynom, names_of_variables);

    std::cout << "sum" << std::endl;
    std::cout << p1 + p2;
    std::cout << std::endl;
    std::cout << "sub" << std::endl;
    std::cout << p1 - p2;
    std::cout << std::endl;
}