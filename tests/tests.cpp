#include <cassert>
#include <iostream>
#include "../src/Preprocessor.h"
#include "../src/Environment.h"

void environment_test()
{
    Environment env;
    assert(env.get_value("HA") == "");
    env.set_value("HA", "VA");
    assert(env.get_value("HA") == "VA");
}

void preprocessor_substitute_test()
{
    Environment env;
    env.set_value("ABA", "VA");
    Preprocessor preprocessor;
    std::string str("echo $ABA $ $V vas");
    preprocessor.substitute_variables(env, str);
    assert(str == "echo VA   vas");
}

void preprocessor_update_environment_test()
{
    Environment env;
    Preprocessor preprocessor;
    std::string str("ABA=V");
    preprocessor.update_environment(env, str);
    assert(env.get_value("ABA") == "V");

}

int main()
{
    environment_test();
    preprocessor_substitute_test();
    preprocessor_update_environment_test();
    return 0;
}
