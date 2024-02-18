#include "functions.hpp"

Base    *generate(void){
    timeval T;
    gettimeofday(&T,NULL);
    time_t x = T.tv_usec % 3;
    if (!x)
        return new A;
    if (x == 1)
        return new B;
    return new C;
}

void    identify(Base* p){
    if (dynamic_cast<A*>(p))
        std::cout<<"Type = A\n";
    if (dynamic_cast<B*>(p))
        std::cout<<"Type = B\n";
    if (dynamic_cast<C*>(p))
        std::cout<<"Type = C\n";
}

void    identify(Base& p){
    try{
        dynamic_cast<A&>(p);
        std::cout<<"Type = A\n";
    }
    catch(std::exception& exp){
        (void)exp;
    }
    try{
        dynamic_cast<B&>(p);
        std::cout<<"Type = B\n";
    }
    catch(std::exception& exp){
        (void)exp;
    }
    try{
        dynamic_cast<C&>(p);
        std::cout<<"Type = C\n";
    }
    catch(std::exception& exp){
        (void)exp;
    }
}
