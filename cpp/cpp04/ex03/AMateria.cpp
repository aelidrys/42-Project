#include "AMateria.hpp"

AMateria::AMateria(){
    // std::cout<<"AMateria: constructor Called\n";
    type = "unamed";
}

AMateria::AMateria(std::string const & type1){
    type = type1;
}

AMateria::AMateria(const AMateria& oth){
    *this = oth;
}

AMateria& AMateria::operator=(const AMateria& oth){
    if (this != &oth){
        ;
    }
    return *this;
}

std::string const & AMateria::getType() const{
    return type;
}

void AMateria::use(ICharacter& target){
    (void)target;
    std::cout<<"you should not call this method\n";
}

AMateria::~AMateria(){
    // std::cout<<"AMateria: Destructor Called\n";
}