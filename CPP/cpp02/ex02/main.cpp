#include "Fixed.hpp"

int main(void) {

    Fixed F1;
    Fixed const F2( Fixed( 5.05f ) * Fixed( 2 ) );
    std::cout << F1 << "\n";
    std::cout << ++F1 << "\n";
    std::cout << F1 << "\n";
    std::cout << F1++ << "\n";
    std::cout << F1 << "\n";
    std::cout << F2 << "\n";
    std::cout << Fixed::max( F1, F2 ) << "\n";
    return 0;
}