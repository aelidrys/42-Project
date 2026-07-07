#include "Serializer.hpp"

Serializer::Serializer(){
    // std::cout<<"Serializer: Defult Constructor Called\n"<<std::endl;
}


Serializer::Serializer(const Serializer& oth){
    // std::cout<<"Serializer: Copy Constructor Called\n"<<std::endl;
    *this = oth;
}

Serializer& Serializer::operator=(const Serializer& oth){
    if (this != &oth){
        ;
    }
    return *this;
}

uintptr_t  Serializer::serialize(Data* ptr){
    return reinterpret_cast<uintptr_t>(ptr);
}


Data* Serializer::deserialize(uintptr_t raw){
    return reinterpret_cast<Data *>(raw);
}

Serializer::~Serializer(){
    // std::cout<<"Serializer Destructor Called"<<std::endl;
}