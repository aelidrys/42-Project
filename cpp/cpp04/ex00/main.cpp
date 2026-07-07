#include "Cat.hpp"
#include "Dog.hpp"

int main(){
    const Animal* meta = new Animal();
    const Animal* i = new Cat();
    const Animal* j = new Dog();
    std::cout<<"\n";
    std::cout <<"type of Animal is a "<< i->getType() << "\n";
    std::cout <<"type of Animal is a "<< j->getType() << "\n";
    i->makeSound(); //will output the cat sound!
    j->makeSound(); //will output the dog sound!
    meta->makeSound();
    delete meta;
    delete j;
    delete i;
}