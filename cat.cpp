#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

/*
 * Utility displays the contents of a file
 */
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Count arguments must be greater than 0" << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        std::ifstream t(argv[i]);
        std::string str((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
        std::cout << str;
    }

    return 0;
}
