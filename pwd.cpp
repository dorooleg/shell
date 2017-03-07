#include <iostream>
#include <unistd.h> 

int main()
{
    char *path = nullptr;
    path = getcwd(nullptr, 0);
    if (path != nullptr) {
        std::cout << path << std::endl;
    }
    return 0;
}
