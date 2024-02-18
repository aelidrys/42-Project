#include "Animal.hpp"
#include "Brain.hpp"

#ifndef CAT_HPP
#define CAT_HPP

class Cat: public Animal
{
Brain* ptr_brain;
public:
    Cat();
    Cat(const std::string& _type);
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    void makeSound();
    ~Cat();
};

#endif