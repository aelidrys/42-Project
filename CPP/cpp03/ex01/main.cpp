#include "ScavTrap.hpp"

int main()
{
    ScavTrap S0("Lmohalhil");
    ScavTrap S1("Ibno_aabad");
    
    // Lmohalhil attack Ibno_aabad
    S1.attack("Lmohalhil");
    S0.takeDamage(50);
    
    // Ibno_aabad attack Lmohalhil
    S0.attack("Ibno_aabad");
    S1.takeDamage(50);
    
    // Lmohalhil attack Ibno_aabad
    S1.attack("Lmohalhil");
    S0.takeDamage(50);

    // Ibno_aabad attack Lmohalhil
    S0.attack("Ibno_aabad");

    // Lmohalhil beRepaired points
    S0.beRepaired(1);

    // Lmohalhil attack Ibno_aabad
    S0.attack("Ibno_aabad");
    S1.takeDamage(50);

    // Ibno_aabad gaurdGate
    S1.guardGate();
    
}