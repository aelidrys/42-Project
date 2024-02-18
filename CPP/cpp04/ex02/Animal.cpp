# include "Animal.hpp"

Animal::Animal(){
    std::cout<<"Animal-> Defult Constructor Called\n";
    type = "undefined";
}

Animal::Animal(const std::string& _type){
    std::cout<<"Animal-> String Constructor Called\n";
    type = _type;
}

Animal::Animal(const Animal& other){
    std::cout<<"Animal-> Copy Constructor Called\n";
    *this = other;
}

Animal& Animal::operator=(const Animal& other){
    std::cout<<"Animal-> Copy Assignement Called\n";
    if (this != &other){
        type = other.getType();
    }
    return *this;
}



const std::string& Animal::getType() const{
    return type;
}

void Animal::makeSound() const{
    std::cout<<"!!! You should not call this method !!!\n";
}

Animal::~Animal(){
    std::cout<<"Animal-> Destructor Called\n";
}
