#include "Character.hpp"

Character::Character(){
    // std::cout<<"Character Defult Consructor Called\n";
    x = 0;
    box = new Box;
    name = "unamed";
}

Character::Character(const std::string& name1){
    // std::cout<<"Character String Constuctor Called\n";
    x = 0;
    box = new Box;
    name = name1;
}

Character::Character(const Character& oth){
    // std::cout<<"Character Copy Constuctor Called\n";
    x = 0;
    box = new Box;
    *this = oth;
}

 Character& Character::operator=(const Character& oth){
    // std::cout<<"Character Copy Assignement Called\n";
    for (int i = 0; i < x; i++)
        delete slots[i];
    if (this != &oth){
        x = oth.x;
        name = oth.getName();
        for (int i = 0; i < x; i++){
            if (oth.slots[i])
                slots[i] = oth.slots[i]->clone();
            else
                slots[i] = NULL;
        }
    }
    return *this;
}

std::string const & Character::getName() const{
    return (name);
}

void Character::equip(AMateria* m){
    if (x < 4)
        slots[x++] = m;
    // else
    //     box->add(m);
}

void Character::unequip(int idx){
    if (idx >= 0 && idx < x){
    //     if (slots[idx])
	// 	    box->add(slots[idx]);
        slots[idx] = NULL;
    }
}

void Character::use(int idx, ICharacter& target){
    if (idx >= 0 && idx < x)
        if (slots[idx])
            slots[idx]->use(target);
}

Character::~Character(){
    // std::cout<<"Character Destructor Called\n";
    for (int i = 0; i < x; i++)
         box->add(slots[i]);
    delete box;
}
