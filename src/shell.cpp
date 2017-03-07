#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include <sys/wait.h>
#include "Environment.h"
#include "Preprocessor.h"

void split(const std::string& s, char delim, std::vector<std::string>& tokens)
{
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim))
    {
        tokens.push_back(item);
    }

    if (tokens.size() == 0)
    {
       tokens.push_back(s); 
    }
}

int main()
{
    Preprocessor preprocessor;
    Environment environment;
    std::string input;
    while (std::getline(std::cin, input))
    {
        preprocessor.substitute_variables(environment, input);
        preprocessor.update_environment(environment, input);
        std::vector<std::string> commands;
        split(input, '|', commands);

        if (!commands.empty() && commands[0] == "exit")
        {
            exit(0);
        }
        
        std::vector<int[2]> pfds(commands.size() - 1);
        for (auto& pfd : pfds)
        {
            if (pipe(pfd) < 0)
            {
                exit(1);
            }
        }

        for (int i = 0; i < commands.size(); i++)
        {
            int pid = fork();
            if (pid == 0)
            {
                if (i != 0)
                    dup2(pfds[i - 1][0], 0);

                if (i != commands.size() - 1)
                    dup2(pfds[i][1], 1);

                for (const auto& pfd : pfds)
                {
                    close(pfd[0]);
                    close(pfd[1]);
                }

                int res = std::system(commands[i].c_str());
                exit(res);
            }
            else if (pid < 0)
            {
                exit(1);
            }
        }

        for (const auto& pfd : pfds)
        {
            close(pfd[0]);
            close(pfd[1]);
        }
        
        wait(nullptr);
    }
}
