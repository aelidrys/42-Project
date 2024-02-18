#include "Fixed.hpp"

const int Fixed::fraction = 8;

Fixed::Fixed()
{
    std::cout<<"Defult constuctor called\n";
    fp_num = 0;
};

Fixed::Fixed(const Fixed& F)
{
    std::cout<<"copy constuctor called\n";
    *this = F;
};

int Fixed::getRawBits(void) const
{
    std::cout<<"getRawBits member function called\n";
    return (fp_num);
}

void Fixed::setRawBits( int const raw )
{
    std::cout<<"setRawBits member function called\n";
    fp_num = raw;
}

Fixed& Fixed::operator=(const Fixed& other)
{
    std::cout<<"copy assignment operator called\n";
    if (this != &other)
    {
        fp_num = other.getRawBits(); 
    }
    return (*this);
};

Fixed::~Fixed()
{
    std::cout<<"destructor called\n";
};