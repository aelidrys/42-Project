#include <iostream>
#include "Array.hpp"
#include <stdlib.h>
#include <math.h>

#define MAX_VAL 750
int main(int, char**)
{


    try{
        Array<std::string> tab(-5);
        Array<std::string> tab1(2);
         for (int i = 0; i < 5; i++)
            tab[i] = "abcdefjhigklmn"[i%10];
        for (int i = 0; i < 5; i++)
            std::cout<<"tab["<<i<<"] = "<<tab[i]<<std::endl;
        std::cout<<std::endl;
        tab1 = tab;
        tab1[tab.size()-1] += "Y";
        for (int i = 0; i < 5; i++)
            std::cout<<"tab1["<<i<<"] = "<<tab1[i]<<std::endl;
    }
    catch(std::exception& exp){
        std::cout<<exp.what()<<std::endl;
    }



    // try{
    //     Array<int> numbers(MAX_VAL);
    //     int* mirror = new int[MAX_VAL];
    //     srand(time(NULL));
    //     for (int i = 0; i < MAX_VAL; i++)
    //     {
    //         const int value = rand();
    //         numbers[i] = value;
    //         mirror[i] = value;
    //     }
    //     //SCOPE
    //     {
    //         Array<int> tmp = numbers;
    //         Array<int> test(tmp);
    //     }

    //     for (int i = 0; i < MAX_VAL; i++)
    //     {
    //         if (mirror[i] != numbers[i])
    //         {
    //             std::cerr << "didn't save the same value!!" << std::endl;
    //             return 1;
    //         }
    //     }
    //     try
    //     {
    //         numbers[-2] = 0;
    //     }
    //     catch(const std::exception& e)
    //     {
    //         std::cerr << e.what() << '\n';
    //     }
    //     try
    //     {
    //         numbers[MAX_VAL] = 0;
    //     }
    //     catch(const std::exception& e)
    //     {
    //         std::cerr << e.what() << '\n';
    //     }

    //     for (int i = 0; i < MAX_VAL; i++)
    //     {
    //         numbers[i] = rand();
    //     }
    //     delete [] mirror;//
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    return 0;
}