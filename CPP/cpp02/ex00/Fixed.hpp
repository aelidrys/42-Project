#include <iostream>

#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed
{
int fp_num;
static const int fraction;
public:
    Fixed();
    Fixed(const Fixed &F);
    Fixed& operator=(const Fixed &other);
    int getRawBits(void) const;
    void setRawBits(int const raw);
    ~Fixed();
};

#endif