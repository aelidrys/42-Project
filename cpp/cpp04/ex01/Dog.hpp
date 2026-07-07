#include "Animal.hpp"
#include "Brain.hpp"

#ifndef COG_HPP
#define COG_HPP

class Dog: public Animal
{
Brain* ptr_brain;
public:
    Dog();
    Dog(const std::string& _type);
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    void makeSound();
    ~Dog();
};

#endif