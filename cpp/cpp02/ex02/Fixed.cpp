#include "Fixed.hpp"


const int Fixed::fraction = 8;

Fixed::Fixed() {
    // std::cout<<"Defult constuctor is called\n";
    fp_num = 0;
};

Fixed::Fixed(const int x) {
    fp_num = x<<8;
}

Fixed::Fixed(const float x) {
    fp_num = roundf(x * 256);
}

Fixed::Fixed(const Fixed& F) {
    // std::cout<<"copy constuctor is called\n";
    *this = F;
};


Fixed& Fixed::operator=(const Fixed& other) {
    // std::cout<<"copy assignment operator is called\n";
    if (this != &other)
    {
        fp_num = other.getRawBits(); 
    }
    return (*this);
};

int Fixed::getRawBits(void) const {
    // std::cout<<"getRawBits member function called\n";
    return (fp_num);
}

void Fixed::setRawBits( int const raw ){
    // std::cout<<"setRawBits member function called\n";
    fp_num = raw;
}

float Fixed::toFloat(void) const {
    return (fp_num / 256.0);
}

int Fixed::toInt( void ) const {
    return(fp_num / 256);
}

Fixed::~Fixed(){
    // std::cout<<"destructor is called\n";
};

bool Fixed::operator>(const Fixed &other) const{
    return (fp_num > other.fp_num);
}

bool Fixed::operator<(const Fixed &other) const {
    return (fp_num < other.fp_num);
}

bool Fixed::operator>=(const Fixed &other) const{
    return (fp_num >= other.fp_num);
}

bool Fixed::operator<=(const Fixed &other) const{
    return (fp_num <= other.fp_num);
}

bool Fixed::operator==(const Fixed &other) const{
    return (fp_num == other.fp_num);
}

bool Fixed::operator!=(const Fixed &other) const{
    return (fp_num != other.fp_num);
}

Fixed Fixed::operator+(const Fixed &other) const{
    return (Fixed(toFloat() + other.toFloat()));
}

Fixed Fixed::operator-(const Fixed &other) const{
    return (Fixed(toFloat() - other.toFloat()));
}

Fixed Fixed::operator*(const Fixed &other) const{
    return (Fixed(toFloat()*other.toFloat()));
}

Fixed Fixed::operator/(const Fixed &other) const{
    return (Fixed(toFloat()/other.toFloat()));
}

Fixed&  Fixed::operator++(){
    ++fp_num;
    return (*this);
}

Fixed  Fixed::operator++(int){
    Fixed Copy = *this;
    ++fp_num;
    return (Copy);
}

Fixed&  Fixed::operator--(){
    --fp_num;
    return (*this);
}

Fixed  Fixed::operator--(int){
    Fixed Copy = *this;
    --fp_num;
    return (Copy);
}

Fixed& Fixed::min(Fixed& F1, Fixed& F2){
    if (F2 < F1)
        return F2;
    return F1;
}

Fixed& Fixed::max(Fixed& F1, Fixed& F2){
    if (F2 > F1)
        return F2;
    return F1;
}

const Fixed& Fixed::min(const Fixed& F1, const Fixed& F2){
    if (F2 < F1)
        return F2;
    return F1;
}

const Fixed& Fixed::max(const Fixed& F1, const Fixed& F2){
    if (F2 > F1)
        return F2;
    return F1;
}

std::ostream& operator<<(std::ostream& os, const Fixed& obj) {
    os << obj.toFloat();
    return os;
}
