#include "MateriaSource.hpp"

MateriaSource::MateriaSource(){
    index = 0;
    // std::cout<<"MateriaSource: Defult Constructor Called\n";
}

MateriaSource::MateriaSource(const MateriaSource& oth){
    // std::cout<<"MateriaSource: Copy Constructor Called\n";
    index = 0;
    *this = oth;
}

// MateriaSource::MateriaSource(){}

MateriaSource& MateriaSource::operator=(const MateriaSource& oth){
	for (int i = 0; i < index; i++)
        delete learned_m[i];
    if (this != &oth){
        index = oth.index;
        for (int i = 0; i < index; i++){
           if (oth.learned_m[i])
                learned_m[i] = oth.learned_m[i]->clone();
           else
                learned_m[i] = NULL;
        }
    }
    return *this;
}

AMateria* MateriaSource::createMateria(std::string const & type){
    int i = index-1;
    while (index && i >= 0){
        if (type == learned_m[i]->getType())
            return learned_m[i]->clone();
        i--;
    }
    std::cout<<"canout Create Matireia "<<type<<"\n";
    return 0;
}

void MateriaSource::learnMateria(AMateria *m){
    if (index < 4)
        learned_m[index++] = m;
    else
        delete m;
}

MateriaSource::~MateriaSource(){
    // std::cout<<"MareriaSource: Destructor Called\n";
    for (int i = 0; i < index; i++)
        delete learned_m[i];
}

