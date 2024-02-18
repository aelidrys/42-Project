#include "Cure.hpp"
#include "Ice.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"

int main()
{
    // IMateriaSource* src = new MateriaSource();
    // src->learnMateria(new Cure());
    // src->learnMateria(new Ice());

    // Character C1("c1");
    // Character C2("c1");
    // C2.equip(src->createMateria("cure"));
    // C2.equip(src->createMateria("ice"));
    // C2.equip(src->createMateria("cure"));
    // C2.equip(src->createMateria("ice"));
    
    // C1.equip(src->createMateria("cure"));
    // C1.equip(src->createMateria("ice"));
    // C2.unequip(0);
    // C2.unequip(1);
    // // C2.unequip(2);
    // // C2.unequip(3);

    // C1 = C2;
    // C1.use(0,C2);
    // C1.use(1,C2);
    // C1.use(2,C2);
    // C1.use(3,C2);
    // delete src;


    // create a Mareria Source and fill it
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Cure());
    src->learnMateria(new Ice());

    // create first Character and fill its slots by Mareria
    ICharacter* me = new Character("me");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    me->equip(tmp);

    // create second Character and use the Mareria of <me> with him
    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);
    me->use(2, *bob);
    // cleaning
    delete bob;
    delete me;
    delete src;
    system("leaks Character");
    return 0;
}