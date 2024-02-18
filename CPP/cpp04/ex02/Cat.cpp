# include "Cat.hpp"

Cat::Cat(){
    std::cout<<"Cat-> Defult Constuctor Called\n";
    ptr_brain = new Brain;
    type = "Cat";
}

Cat::Cat(const std::string& _type): Animal(type){
    std::cout<<"Cat-> String Constuctor Called\n";
    ptr_brain = new Brain;
    type = _type;
}

Cat::Cat(const Cat& other): Animal(other){
    std::cout<<"Cat-> Copy Constuctor Called\n";
    ptr_brain = new Brain;
    *this = other;
}

Cat& Cat::operator=(const Cat& other){
    std::cout<<"Cat-> Copy Assignement Called\n";
    if (this != &other){
        type = other.getType();
        *ptr_brain = *(other.ptr_brain);
    }
    return *this;
}
void Cat::makeSound() const{
    std::cout<<"CatSound-> Miio Miio Miio\n";
}

Cat::~Cat(){
    delete ptr_brain;
    std::cout<<"Cat-> Destructor Called\n";
}