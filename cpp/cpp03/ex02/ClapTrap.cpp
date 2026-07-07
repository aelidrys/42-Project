#include "ClapTrap.hpp"

ClapTrap::ClapTrap(){
    std::cout<<"ClapTrap Defult constactor called\n";
    name = "unamed";
    health_p = 10;
    energy_p = 10;
    attack_d = 0;
}

ClapTrap::ClapTrap(std::string name1){
    std::cout<<"ClapTrap string constactor called\n";
    name = name1;
    health_p = 10;
    energy_p = 10;
    attack_d = 0;
}

ClapTrap::ClapTrap(const ClapTrap &C0){
    std::cout<<"ClapTrap Copy Constactor called\n";
    *this = C0;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other){
    // std::cout<<"ClapTrap Copy assignement operator called\n";
    if (this != &other){
        name = other.name;
        health_p = other.health_p;
        energy_p = other.energy_p;
        attack_d = other.attack_d;
    }
    return (*this);
}

void ClapTrap::attack(const std::string& target){
    if (energy_p && health_p){
        std::cout<<"ClapTrap "<<name<<" attacks "<<target<<", causing ";
        std::cout<<attack_d<<" points of damage!\n";
        energy_p--;
    }
    else
        std::cout<<"ClapTrap "<<name<<" can't attack\n";
}

void ClapTrap::takeDamage(unsigned int amount){
    if (health_p){
        if (health_p < amount){
            std::cout<<"ClapTrap "<<name<<" takeDamage: "<<health_p<<" points\n";
            health_p = 0;
        }
        else{
            health_p -= amount;
            std::cout<<"ClapTrap "<<name<<" takeDamage: "<<amount<<" points\n";
        }
    }
    else
        std::cout<<"ClapTrap "<<name<<" no health point left"<<"\n";
}

void ClapTrap::beRepaired(unsigned int amount){
    if (energy_p){
        std::cout<<"ClapTrap "<<name<<" beRepaired: "<<amount<<" points\n";
        health_p += amount;
        energy_p--;
    }
    else
        std::cout<<"ClapTrap "<<name<<" can't beRepaired\n";
}

ClapTrap::~ClapTrap(){
    std::cout<<"ClapTrap Destactor called\n";
}