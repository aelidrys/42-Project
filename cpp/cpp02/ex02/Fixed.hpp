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
    bool  operator>(const Fixed &other) const;
    bool  operator<(const Fixed &other) const;
    bool  operator>=(const Fixed &other) const;
    bool  operator<=(const Fixed &other) const;
    bool  operator==(const Fixed &other) const;
    bool  operator!=(const Fixed &other) const;
    Fixed  operator+(const Fixed &other) const;
    Fixed  operator-(const Fixed &other) const;
    Fixed  operator*(const Fixed &other) const;
    Fixed  operator/(const Fixed &other) const;
    Fixed&  operator++();
    Fixed  operator++(int);
    Fixed&  operator--();
    Fixed  operator--(int);
    int     getRawBits(void) const;
    void    setRawBits(int const raw);
    float   toFloat( void ) const;
    int     toInt( void ) const;
    static Fixed& min(Fixed& F1, Fixed& F2);
    static Fixed& max(Fixed& F1, Fixed& F2);
    static const Fixed& min(const Fixed& F1, const Fixed& F2);
    static const Fixed& max(const Fixed& F1, const Fixed& F2);
    ~Fixed();
};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif