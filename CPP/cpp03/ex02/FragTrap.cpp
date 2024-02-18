#include "FragTrap.hpp"

FragTrap::FragTrap(){
    std::cout<<"FragTrap Defult Constructor called\n";
    name = "unmed";
    health_p = 100;
    energy_p = 100;
    attack_d = 30;
}

FragTrap::FragTrap(const std::string& _name): ClapTrap(_name){
    std::cout<<"FragTrap String Constructor called\n";
    name = _name;
    health_p = 100;
    energy_p = 100;
    attack_d = 30;
}

FragTrap::FragTrap(const FragTrap& other): ClapTrap(other){
    std::cout<<"FragTrap Copy Constactor called\n";
    *this = other;
}

FragTrap& FragTrap::operator=(const FragTrap& other){
    // std::cout<<"FragTrap Copy Assignement Operator called\n";
    if (this != &other){
        name = other.name;
        health_p = other.health_p;
        energy_p = other.energy_p;
        attack_d = other.attack_d;
    }
    return *this;
}


void FragTrap:: highFivesGuys(){
    std::cout<<"FragTrap "<<name;
    std::cout<<": give me the high fives guys\n";
}

FragTrap::~FragTrap(){
    std::cout<<"FragTrap Destrutor called\n";
}