#include "Fixed.hpp"

int main( void ) {

    Fixed       F1;
    Fixed const F2(10);
    Fixed const F3(42.42f);
    Fixed const F4(F2);

    F1 = Fixed( 1234.4321f );
    std::cout << "a is " << F1 << "\n";
    std::cout << "b is " << F2 << "\n";
    std::cout << "c is " << F3 << "\n";
    std::cout << "d is " << F4 << "\n";

    std::cout << "a is " << F1.toInt() << " as integer\n";
    std::cout << "b is " << F2.toInt() << " as integer\n";
    std::cout << "c is " << F3.toInt() << " as integer\n";
    std::cout << "d is " << F4.toInt() << " as integer\n";
    return 0;
}