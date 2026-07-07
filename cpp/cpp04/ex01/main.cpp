#include "Cat.hpp"
#include "Dog.hpp"

int main(){
    // // my test
    // Animal *ptr[4];

    // for (int i=0;i<2;i++){
    //     ptr[i] = new Dog();
    // }
    // for (int i=0;i<2;i++){
    //     ptr[i+2] = new Cat();
    // }
    // for (int i=0;i<4;i++){
    //     delete ptr[i];
    // }

    // test of subject
    const Animal* j = new Dog();
    Animal* const i = new Cat();
    delete j;
    delete i;
}