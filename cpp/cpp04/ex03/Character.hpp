#include "ICharacter.hpp"
#include "Box.hpp"

#ifndef CHARACTER_HPP
#define CHARACTER_HPP



class Character : public ICharacter
{
int x;
Box *box;
std::string name;
AMateria *slots[4];
public:
    Character();
    Character(const std::string& name1);
    Character(const Character& oth);
    Character& operator=(const Character& oth);
    std::string const & getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
    ~Character();
};

#endif