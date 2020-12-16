#include <cstdio>
#include <cstdlib>

#include <iostream>

int main()
{
    char cstring1[] {"Blue"};
    const char* cstring2 {"constblue"};
    char* cstring3 {"string3"};

    std::cout << cstring1 << sizeof(cstring1) << std::endl;
    std::cout << cstring2 << sizeof(cstring2) << std::endl;

    cstring1[2] = 'v';
    std::cout << cstring1 << std::endl;

    cstring3[3] = 'x';
    // std::cout << cstring3 << std::endl;


    return 0;
}