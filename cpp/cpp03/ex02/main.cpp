#include "FragTrap.hpp"

int main()
{
    FragTrap F0("Neptune");
    FragTrap F1("Zohal");

    F0.attack("Zohal");
    F1.takeDamage(100);

    F1.attack("Neptune");
    F0.beRepaired(50);
    
    F1.attack("Neptune");
    F0.highFivesGuys();
    
}