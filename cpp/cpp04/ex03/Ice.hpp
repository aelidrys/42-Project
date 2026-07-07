#include "AMateria.hpp"

#ifndef ICE_HPP
#define ICE_HPP

class Ice : public AMateria 
{
public:
    Ice();
    Ice(const std::string& type);
    Ice(const Ice& oth);
    Ice& operator=(const Ice& oth);
    AMateria* clone() const;
    void use(ICharacter& target);
    ~Ice();
};

#endif