#include <iostream>

#ifndef BRAIN_HPP
#define BRAIN_HPP

class Brain
{
std::string arry[100];
public:
    Brain();
    Brain(const std::string& idea);
    Brain(const Brain& other);
    Brain& operator=(const Brain& other);
    const std::string& getadea(const int& i) const;
    ~Brain();
};

#endif
