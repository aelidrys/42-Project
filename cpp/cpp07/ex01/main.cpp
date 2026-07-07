#include "iter.hpp"

int main(){
    long *ptr = new long[10];
    for (int i = 0 ; i < 10 ; i++)
        ptr[i] = i*i+4*i-2;
    iter(ptr, 10, ft_aply<long>);
    delete ptr;
}