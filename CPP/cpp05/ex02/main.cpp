#include <exception>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

int main()
{ 
    AForm *ptr1 = new PresidentialPardonForm("Accused");
    // std::cout<<*ptr1<<std::endl;

    AForm *ptr2 = new RobotomyRequestForm("Car");
    // std::cout<<*ptr2<<std::endl;
    
    AForm *ptr3 = new ShrubberyCreationForm("Garden");
    // std::cout<<*ptr3<<std::endl;
    try{ 
        // Bureaucrat B1("Saife", 5);
        // std::cout<<B1<<std::endl<<std::endl;

        // Bureaucrat B2("Marike", 20);
        // std::cout<<B2<<std::endl<<std::endl;
        
        Bureaucrat B3("Lith", 100);
        std::cout<<B3<<std::endl<<std::endl;
  
        // B1.signForm(*ptr1);
        // B1.executeForm(*ptr1);
        // std::cout<<std::endl;

        // B2.signForm(*ptr2);
        // B2.executeForm(*ptr2);
        // B2.executeForm(*ptr2);
        // std::cout<<std::endl;
        
        B3.signForm(*ptr3);
        B3.executeForm(*ptr3);
        std::cout<<std::endl;


    }
    catch(std::exception& exp){
        std::cout<<exp.what()<<std::endl;
    }
    delete ptr1;
    delete ptr2;
    delete ptr3;
    return 0;
}