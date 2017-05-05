#pragma once

#include <string>
#include <map>

class Environment
{
public:
    /*
     * Get environment varibale. If variable is not exists return std::string()
     */
    std::string get_value(const std::string& variable) const;

    /*
     * Set environment variable
     */
    void set_value(const std::string& variable, const std::string& value); 

private:
    mutable std::map<std::string, std::string> variables_;
};
