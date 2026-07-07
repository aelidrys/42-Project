#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template<typename T2>
void ft_aply(T2 parm){
    std::cout << parm << std::endl;
}

template<typename T1, typename T2>
void iter(T1 *arry, long len, void fun(T2 parm)){
    int i = 0;
    while (i < len)
        fun(arry[i++]);
}

#endif