#include "Fixed.hpp"


const int Fixed::fraction = 8;

Fixed::Fixed()
{
    std::cout<<"Defult constuctor called\n";
    fp_num = 0;
};

Fixed::Fixed(const int x)
{
    std::cout<<"int constuctor called\n";
    fp_num = x<<8;
}

Fixed::Fixed(const float x)
{
    std::cout<<"float constuctor called\n";
    fp_num = roundf(x * 256);
}

Fixed::Fixed(const Fixed& F)
{
    std::cout<<"copy constuctor called\n";
    *this = F;
};


Fixed& Fixed::operator=(const Fixed& other)
{
    std::cout<<"copy assignment operator called\n";
    if (this != &other)
    {
        fp_num = other.getRawBits(); 
    }
    return (*this);
};

int Fixed::getRawBits(void) const
{
    // std::cout<<"getRawBits member function called\n";
    return (fp_num);
}

void Fixed::setRawBits( int const raw )
{
    // std::cout<<"setRawBits member function called\n";
    fp_num = raw;
}

float Fixed::toFloat(void) const
{
    return (fp_num / 256.0);
}

int Fixed::toInt( void ) const
{
    return(fp_num / 256);
}

Fixed::~Fixed()
{
    std::cout<<"destructor called\n";
};


std::ostream& operator<<(std::ostream& os, const Fixed& obj) {
    os << obj.toFloat();
    return os;
}
