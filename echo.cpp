#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

/*
 * Utility display a list of arguments on cout 
 */
int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
