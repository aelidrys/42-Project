#include <iostream>
#include <cmath>

#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed
{
int fp_num;
static const int fraction;
public:
    Fixed();
    Fixed(const int x);
    Fixed(const float x);
    Fixed(const Fixed &F);
    Fixed&  operator=(const Fixed &other);
    int     getRawBits(void) const;
    void    setRawBits(int const raw);
    float   toFloat( void ) const;
    int     toInt( void ) const;
    ~Fixed();
};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif