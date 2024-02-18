#include <iostream>

# ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

class ClapTrap
{
protected:
    std::string name;
    unsigned int health_p;
    unsigned int energy_p;
    unsigned int attack_d;
public:
    ClapTrap();
    ClapTrap(std::string name1);
    ClapTrap(const ClapTrap& C0);
    ClapTrap& operator=(const ClapTrap& other);
    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
    ~ClapTrap();
};

#endif