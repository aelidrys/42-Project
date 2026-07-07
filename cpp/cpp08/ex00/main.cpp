#include "easyfind.hpp"
#include <vector>

int main(){
    unsigned int len = 10;
    std::vector<int> array(len);
    for (unsigned int i = 0; i < len; i++)
        array[i] = i*i-9*i+8;
    for (unsigned int i = 0; i < len; i++)
        std::cout<<"array["<<i<<"] = "<<array[i]<<std::endl;
    std::cout<<std::endl;
    easyfind(array,8);
}