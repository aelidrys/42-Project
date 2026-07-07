#include "Animal.hpp"

#ifndef CAT_HPP
#define CAT_HPP

class Cat: public Animal
{
public:
    Cat();
    Cat(const std::string& _type);
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    void makeSound() const;
    ~Cat();
};

#endif