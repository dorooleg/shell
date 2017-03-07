#ifndef PREPROCESS_H
#define PREPROCESS_H

#include "Environment.h"

class Preprocessor
{
public:
    /*
     * Substiute environment variables 
     */
    void substitute_variables(const Environment& environment, std::string& str);

    /*
     * Update environmetn variables
     */
    void update_environment(Environment& environment, const std::string& str);
};

#endif //PREPROCESS_H
