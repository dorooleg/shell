#include "Preprocessor.h"
#include <iostream>

void Preprocessor::substitute_variables(const Environment& environment, std::string& str)
{
    auto begin = str.begin();
    while (begin != str.end())
    {
        if (*begin == '\'')
        {
            ++begin;
            while (*begin != '\'' && begin != str.end())
            {
                ++begin;
            }
            continue;
        }

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
        if (*begin == '\'')
        {
            ++begin;
            while (begin != str.end() && *begin != '\'')
            {
                ++begin;
            }
            continue;
        }

        if (*begin == '=')
        {
            auto middle = begin;
            auto value_middle = begin;
            auto end = begin;
            --begin;
            ++end;
            while (begin != str.begin() && !std::isspace(*begin) )
            {
                --begin;
            }

            while (!std::isalpha(*begin) && *begin != '=')
            {
                ++begin;
            }

            if (end != str.end() && *end == '\'')
            {
                value_middle++;
                ++end;
                while (end != str.end() && *end != '\'')
                {
                    ++end;
                }

            }
            else if (end != str.end() && *end == '\"')
            {
                value_middle++;
                ++end;
                while (end != str.end() && *end != '\"')
                {
                    ++end;
                }

            }
            else while (end != str.end() && !std::isspace(*end))
            {
                ++end;
            }

            auto varibale = str.substr(std::distance(str.begin(), begin), std::distance(begin, middle)); 
            auto value = str.substr(std::distance(str.begin(), value_middle + 1), std::distance(value_middle + 1, end)); 
            environment.set_value(varibale, value);
            begin = end;
            continue;
        }
        ++begin;
    }
}
