#include <iostream>

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include "ICharacter.hpp"


class ICharacter;

class AMateria
{
AMateria& operator=(const AMateria& oth);
protected:
    std::string type;
public:
    AMateria();
    AMateria(std::string const & type);
    AMateria(const AMateria& oth);
    std::string const & getType() const;
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
    virtual ~AMateria();
};

#endif