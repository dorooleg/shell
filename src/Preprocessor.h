#pragma once

#include "Environment.h"

/*
* Preprocessing shell line. Working with environment variables
*/
class Preprocessor
{
public:
    /*
     * Substiute environment variables 
     */
    static void substitute_variables(const Environment& environment, std::string& str);

    /*
     * Update environmetn variables
     */
    static void update_environment(Environment& environment, const std::string& str);
};
