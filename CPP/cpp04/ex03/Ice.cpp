#include "Ice.hpp"

Ice::Ice(){
    // std::cout<<"Ice: Defult Consructor Called\n";
    type = "ice";
}

Ice::Ice(const std::string& n_type): AMateria(n_type){
    // std::cout<<"Ice: Copy Consructor Called\n";
    type = n_type;
}

Ice::Ice(const Ice& oth): AMateria(oth){
    *this = oth;
}

AMateria* Ice::clone() const{
    return (new Ice(type));
}

Ice& Ice::operator=(const Ice& oth){
    if (this != &oth){
        type = oth.getType();
    }
    return *this;
}

void Ice::use(ICharacter& target){
    std::cout<<"* shoots an ice bolt at "<<target.getName()<<" *\n";
}

Ice::~Ice(){
    // std::cout<<"Ice: Destructor Called\n";
}
