#include "ClapTrap.hpp"

int main()
{
    ClapTrap C0("Racon");
    ClapTrap C1("Panda");

    // panda attack Racon
    C1.attack("Racon");
    C0.takeDamage(5);

    // Racon attack Panda
    C0.attack("Panda");
    C1.takeDamage(5);

    // panda attack Racon
    C1.attack("Racon");
    C0.takeDamage(5);

    // Racon attack Panda
    C0.attack("Panda");

    // Racon beRepaired
    C0.beRepaired(1);
    C0.attack("Panda");
    C1.takeDamage(5);
    
}