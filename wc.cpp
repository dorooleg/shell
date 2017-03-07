#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

size_t count_words(const std::string& path)
{
    std::ifstream infile(path);
    std::istream_iterator<std::string> in(infile);
    std::istream_iterator<std::string> end;
    return std::distance(in, end);
}

size_t count_lines(const std::string& path)
{
    std::ifstream infile(path);
    infile.unsetf(std::ios_base::skipws);
    return std::count(std::istream_iterator<char>(infile),
                      std::istream_iterator<char>(), 
                      '\n');
}

size_t count_bytes(const std::string& path)
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    return file.tellg();
}
    
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Count arguments must be greater than 0" << std::endl;
        return 1;
    }
    
    for (int i = 1; i < argc; i++)
    {
        std::cout << count_lines(argv[i]) << " " 
                 << count_words(argv[i]) << " " 
                 << count_bytes(argv[i]) << " " 
                 << argv[i] << std::endl;
    }

    return 0;
}
