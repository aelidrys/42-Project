#include "Cure.hpp"

Cure::Cure(){
    // std::cout<<"Cure: Defult Consructor Called\n";
    type = "cure";
}

Cure::Cure(const std::string& n_type): AMateria(n_type){
    // std::cout<<"Cure: String Consructor Called\n";
    type = n_type;
}

Cure::Cure(const Cure& oth): AMateria(oth){
    // std::cout<<"Cure: Copy Consructor Called\n";
    *this = oth;
}

AMateria* Cure::clone() const{
    // std::cout<<"Cure: Copy Assignement Called\n";
    return (new Cure(type));
}

Cure& Cure::operator=(const Cure& oth){
    if (this != &oth){
        type = oth.getType();
    }
    return *this;
}

void Cure::use(ICharacter& target){
    std::cout<<"* heals "<<target.getName()<<" s wounds *\n";
}

Cure::~Cure(){
    // std::cout<<"Cure: Destructor Called\n";
}
