#include "AMateria.hpp"

#ifndef CURE_HPP
#define CURE_HPP

class Cure : public AMateria
{
public:
    Cure();
    Cure(const std::string& type);
    Cure(const Cure& oth);
    Cure& operator=(const Cure& oth);
    AMateria* clone() const;
    void use(ICharacter& target);
    ~Cure();
};

#endif