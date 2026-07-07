#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
int index;
AMateria *learned_m[4];
public:
    MateriaSource();
    MateriaSource(const MateriaSource& oth);
    MateriaSource& operator=(const MateriaSource& oth);
    AMateria* createMateria(std::string const & type);
    void learnMateria(AMateria*);
    ~MateriaSource();
};

#endif