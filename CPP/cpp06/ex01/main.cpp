#include "Serializer.hpp"

int main(){
    Data *ptr1 = new Data;
    ptr1->x = 9;
    Data *ptr2;
    uintptr_t raw;

    raw = Serializer::serialize(ptr1);
    std::cout<<"raw = "<<raw<<std::endl;
    std::cout<<"&x = "<<(uintptr_t)&ptr1->x<<std::endl;

    ptr2 = Serializer::deserialize(raw);
    std::cout<<"x = "<<ptr2->x<<std::endl;
    delete ptr1;
}