#include "functions.hpp"

int main(){
    Base *ptr0 = generate();
    std::cout<<"------------\n";
    identify(ptr0);// Ptr
    identify(*ptr0);//Ref
    std::cout<<"------------\n\n";
    Base *ptr1 = generate();
    identify(ptr1);// Ptr
    identify(*ptr1);//Ref
    std::cout<<"------------\n\n";
    Base *ptr2 = generate();
    identify(ptr2);// Ptr
    identify(*ptr2);//Ref
    std::cout<<"------------\n";
    delete ptr0;
    delete ptr1;
    delete ptr2;
}