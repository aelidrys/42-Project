#include "Fixed.hpp"


int main()
{

    Fixed F1;
    Fixed F2(F1);
    Fixed F3;
    
    F3 = F2;

    std::cout << F1.getRawBits() << std::endl;
    std::cout << F2.getRawBits() << std::endl;
    std::cout << F3.getRawBits() << std::endl;
}