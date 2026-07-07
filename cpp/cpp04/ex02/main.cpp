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
    // (void)ptr;
    // for (int i=0;i<4;i++){
    //     delete ptr[i];
    // }

    // test of subject
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    delete j;//should not create a leak
    delete i;
}