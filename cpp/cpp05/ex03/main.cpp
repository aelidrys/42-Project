#include <exception>
#include "Bureaucrat.hpp"
#include "Intern.hpp"

int main()
{
    // presidential pardon
    // robotomy request
    // shrubbery creation

    Intern I1;
    
    AForm *ptr1 = I1.makeForm("robotomy request1", "Car");
    std::cout<<std::endl;
    if (ptr1)
        std::cout<<*ptr1<<std::endl;

    try{
        if (ptr1){
        Bureaucrat B1("Saife", 5);
        std::cout<<B1<<std::endl<<std::endl;

  
        B1.signForm(*ptr1);
        B1.executeForm(*ptr1);
        std::cout<<std::endl;
        } 

    }
    catch(std::exception& exp){
        std::cout<<exp.what()<<std::endl;
    }
    delete ptr1;
    return 0;
}