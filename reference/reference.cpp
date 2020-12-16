#include <iostream>

int main()
{
    int val2 = 10;
    int val = 5;
    int& refVal = val;
    std::cout << "refVal is " << refVal << std::endl;
    refVal = val2;
    std::cout << "after reassignment refVal is " << refVal << std::endl;

    return 0;

}