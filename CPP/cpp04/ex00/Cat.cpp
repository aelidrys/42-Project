# include "Cat.hpp"

Cat::Cat(){
    std::cout<<"Cat-> Defult Constuctor Called\n";
    type = "Cat";
}

Cat::Cat(const std::string& _type): Animal(type){
    std::cout<<"Cat-> String Constuctor Called\n";
    type = _type;
}

Cat::Cat(const Cat& other): Animal(other){
    std::cout<<"Cat-> Copy Constuctor Called\n";
    *this = other;
}

Cat& Cat::operator=(const Cat& other){
    if (this != &other){
        type = other.getType();
    }
    return *this;
}
void Cat::makeSound() const{
    std::cout<<"CatSound-> Miio Miio Miio\n";
}

Cat::~Cat(){
    std::cout<<"Cat-> Destructor Called\n";
}