#include "Environment.h"

std::string Environment::get_value(const std::string& variable) const
{
    return variables_[variable];
}

void Environment::set_value(const std::string& variable, const std::string& value)
{
    variables_[variable] = value;
}
