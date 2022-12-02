#include <iostream>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    fork();
    std::cout << "pouf" << std::endl;
    return 0;
}
