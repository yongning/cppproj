#include <cstdio>
#include <iostream>
#include <array>

int main()
{
    std::array<int, 5> array1;

    for (size_t i{0}; i < array1.size(); i++) {
        array1[i] = 0;
    }

    for (size_t i{0}; i < array1.size(); i++) {
        std::cout << "array data is" << array1.at(i) ;
    }

    return 0;
}