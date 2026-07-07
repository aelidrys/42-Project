#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>

template<class T1>
void swap(T1& a, T1& b){
    T1 tmp = a;
    a = b;
    b = tmp;
}


template<class T1>
T1 min(T1 a, T1 b){
    if (a < b)
        return (a);
    return (b);
}

template<class T1>
T1 max(T1 a, T1 b){
    if (a > b)
        return (a);
    return (b);
}

#endif