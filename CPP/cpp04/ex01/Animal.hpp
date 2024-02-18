# include <iostream>

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

class Animal
{
protected:
    std::string type;
public:
    Animal();
    Animal(const std::string& _type);
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    const std::string& getType() const;
    virtual void makeSound();
    virtual ~Animal();
};

#endif