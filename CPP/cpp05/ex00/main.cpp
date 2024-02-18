#include "Bureaucrat.hpp"

int main()
{
    try{

        Bureaucrat B1("Dwawiny", 150);
        Bureaucrat B2(B1);
        B1.decrmntGrade();
        std::cout<<B1<<std::endl;
    }
    catch (std::exception& exp){
        std::cout<<exp.what()<<std::endl;
    }
    return 0;
}