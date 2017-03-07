#include "Preprocessor.h"
#include <iostream>

void Preprocessor::substitute_variables(const Environment& environment, std::string& str)
{
    auto begin = str.begin();
    while (begin != str.end())
    {
        if (*begin == '$')
        {
            auto end = begin;
            ++end;
            while (std::isalpha(*end) && end != str.end())
            {
                ++end;
            }
            str.replace(begin, end, environment.get_value(str.substr(std::distance(str.begin(), begin + 1), std::distance(begin, end - 1)))); 
            begin = str.begin();
        }
        ++begin;
    }
}

void Preprocessor::update_environment(Environment& environment, const std::string& str)
{
    auto begin = str.begin();
    while (begin != str.end())
    {
        if (*begin == '=')
        {
            auto middle = begin;
            auto end = begin;
            --begin;
            ++end;
            while (std::isalpha(*begin) && begin != str.begin())
            {
                --begin;
            }

            while (std::isalpha(*end) && end != str.end())
            {
                ++end;
            }

            auto varibale = str.substr(std::distance(str.begin(), begin), std::distance(begin, middle)); 
            auto value = str.substr(std::distance(str.begin(), middle + 1), std::distance(middle + 1, end)); 
            environment.set_value(varibale, value);
            begin = end;
            continue;
        }
        ++begin;
    }
}
