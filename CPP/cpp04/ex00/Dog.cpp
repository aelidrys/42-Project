# include "Dog.hpp"

Dog::Dog(){
    std::cout<<"Dog-> Defult Constuctor Called\n";
    type = "Dog";
}

Dog::Dog(const std::string& _type): Animal(type){
    std::cout<<"Dog-> String Constuctor Called\n";
    type = _type;
}

Dog::Dog(const Dog& other): Animal(other){
    std::cout<<"Dog-> Copy Constuctor Called\n";
    *this = other;
}

Dog& Dog::operator=(const Dog& other){
    if (this != &other){
        type = other.getType();
    }
    return *this;
}

void Dog::makeSound() const{
    std::cout<<"DogSound-> Huff Huff Huff\n";
}

Dog::~Dog(){
    std::cout<<"Dog-> Destructor Called\n";
}