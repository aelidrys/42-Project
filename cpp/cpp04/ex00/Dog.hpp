#include "Animal.hpp"

#ifndef COG_HPP
#define COG_HPP

class Dog: public Animal
{
public:
    Dog();
    Dog(const std::string& _type);
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    void makeSound() const;
    ~Dog();
};

#endif