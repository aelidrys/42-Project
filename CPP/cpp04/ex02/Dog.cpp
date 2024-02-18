# include "Dog.hpp"

Dog::Dog(){
    std::cout<<"Dog-> Defult Constuctor Called\n";
    ptr_brain = new Brain;
    type = "Dog";
}

Dog::Dog(const std::string& _type): Animal(type){
    std::cout<<"Dog-> String Constuctor Called\n";
    ptr_brain = new Brain;
    type = _type;
}

Dog::Dog(const Dog& other): Animal(other){
    std::cout<<"Dog-> Copy Constuctor Called\n";
    ptr_brain = new Brain;
    *this = other;
}

Dog& Dog::operator=(const Dog& other){
    std::cout<<"Dog-> Copy Assignement Called\n";
    if (this != &other){
        type = other.getType();
        *ptr_brain = *(other.ptr_brain);
    }
    return *this;
}

void Dog::makeSound() const{
    std::cout<<"DogSound-> Huff Huff Huff\n";
}

Dog::~Dog(){
    //  for (int i =0; i < 100; i++){
    //     std::cout<<ptr_brain->getadea(i)<<" <"<<i<<">\n";
    // }
    delete ptr_brain;
    std::cout<<"Dog-> Destructor Called\n";
}