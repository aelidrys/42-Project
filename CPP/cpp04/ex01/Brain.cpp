#include "Brain.hpp"

Brain::Brain(){
    std::cout<<"Brain-> Defult Constructor Called\n";
    for (int i = 0; i < 100; i++)
        arry[i] = "No Iedea";
}

Brain::Brain(const std::string& idea){
    std::cout<<"Brain-> String Constructor Called\n";
    for (int i = 0; i < 100; i++)
        arry[i] = idea;
}

Brain::Brain(const Brain& other){
    std::cout<<"Brain-> Copy Constructor Called\n";
    *this = other;
}

Brain& Brain::operator=(const Brain& other){
    std::cout<<"Brain-> Copy Assignement Called\n";
    if (this != &other){
        for (int i = 0; i < 100; i++)
            arry[i] = other.getadea(i);
    }
    return *this;
}

const std::string& Brain::getadea(const int& i) const{
    if (i > 0 && i < 100)
        return arry[i];
    return arry[0];
}

Brain::~Brain(){
    std::cout<<"Brain-> Destructor Called\n";
}
