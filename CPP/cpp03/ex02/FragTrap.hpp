#include "ClapTrap.hpp"

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

class FragTrap: public ClapTrap{
public:
    FragTrap();
    FragTrap(const std::string& _name);
    FragTrap(const FragTrap& other);
    FragTrap& operator=(const FragTrap& other);
    void highFivesGuys();
    ~FragTrap();
};

#endif