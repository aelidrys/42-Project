#include "ScavTrap.hpp"

ScavTrap::ScavTrap(){
    std::cout<<"ScavTrap Defult Constructor called\n";
    name = "unmed";
    health_p = 100;
    energy_p = 50;
    attack_d = 20;
}

ScavTrap::ScavTrap(const std::string& _name): ClapTrap(_name){
    std::cout<<"ScavTrap String Constructor called\n";
    name = _name;
    health_p = 100;
    energy_p = 50;
    attack_d = 20;
}

ScavTrap::ScavTrap(const ScavTrap& other): ClapTrap(other){
    std::cout<<"ScavTrap Copy Constactor called\n";
    *this = other;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other){
    // std::cout<<"ScavTrap Copy Assignement Operator called\n";
    if (this != &other){
        name = other.name;
        health_p = other.health_p;
        energy_p = other.energy_p;
        attack_d = other.attack_d;
    }
    return *this;
}

void ScavTrap::attack(const std::string& target){
    if (energy_p && health_p){
        std::cout<<"ScavTrap "<<name<<" attacks "<<target<<", causing ";
        std::cout<<attack_d<<" points of damage!\n";
        energy_p--;
    }
    else
        std::cout<<"ScavTrap "<<name<<" can't attack\n";
}

void ScavTrap::guardGate(){
    std::cout<<"ScavTrap "<<name;
    std::cout<<" is now in Gate keeper mode\n";
}

ScavTrap::~ScavTrap(){
    std::cout<<"ScavTrap Destrutor called\n";
}