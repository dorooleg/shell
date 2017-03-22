#include <iostream> 
#include <cmath>
#include <string> 
#include <vector> 
#include <locale>
#include <regex>
#include <fstream>
#include <deque>
#include "boost/program_options.hpp" 

bool is_match(const std::string& regex, const std::string& text);

template<typename InputStream>
void process_grep(InputStream&& input, const std::string& regex, size_t size_output);
 
int main(int argc, char** argv)
{ 
    using namespace std;

    namespace po = boost::program_options; 
    po::options_description desc("Grep options");
    desc.add_options() 
                  (",i", "") 
                  (",w", "")
                  (",A", po::value<int>())
                  ("input", po::value<vector<string>>());
      
    boost::program_options::positional_options_description p;
    p.add("input", -1);

    po::variables_map vm; 
    po::store(po::command_line_parser(argc, argv)
                .options(desc)
                .positional(p)
                .run(), vm); 

    if (vm.count("input"))
    {
        vector<string> positional_parameters = vm["input"].as< vector<string> >();
        auto& regex = positional_parameters[0];

        if (vm.count("-i")) 
        {
            for (auto& v : positional_parameters)
            {
                std::transform(v.begin(), v.end(), v.begin(), ::tolower);
            }
        } 

        if (vm.count("-w"))
        {
            regex = "\\b" + regex + "\\b";
        } 

        int size_output = 1;
        if (vm.count("-A")) 
        {
            size_output = vm["-A"].as<int>() + 1;
        } 

        if (size_output < 0)
        {
            std::cerr << "-A must be positive" << std::endl;
            return EXIT_FAILURE; 
        }

        regex = ".*" + regex + ".*";

        if (positional_parameters.size() == 1)
        {
            process_grep(std::cin, regex, size_output);
            return EXIT_SUCCESS;
        }

        auto it = ++positional_parameters.begin();
        while (it != positional_parameters.end())
        {
            process_grep(std::ifstream(*it), regex, size_output);
            ++it;
        }

        return EXIT_SUCCESS;
    }

    std::cerr << "Count paramters is invalid" << std::endl;

    return EXIT_FAILURE;
}

bool is_match(const std::string& regex, const std::string& text)
{
    const std::regex base_regex(regex);
    std::smatch base_match;
    return std::regex_match(text, base_match, base_regex) && base_match.size() > 0;
}

template<typename InputStream>
void process_grep(InputStream&& input, const std::string& regex, size_t size_output)
{
    std::string line;
    std::deque<std::string> queue;
    while (std::getline(input, line))
    {
        queue.push_back(line);
        if (queue.size() == size_output && is_match(regex, queue.front()))
        {
            for (const auto& v : queue)
            {
                std::cout << v << std::endl;
            }
            queue.pop_front();
        }
    }

    while (!queue.empty())
    {
        if (is_match(regex, queue.front()))
        {
            for (const auto& v : queue)
            {
                std::cout << v << std::endl;
            }
        }
        queue.pop_front();
    }
}
