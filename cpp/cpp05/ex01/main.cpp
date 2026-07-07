#include <exception>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    try{

        Bureaucrat B1("Dwawiny", 20);
        std::cout<<B1<<std::endl<<std::endl;
        
        Form F1("Form1",20,20);
        std::cout<<F1<<std::endl;

        try{
            B1.decrmntGrade();
            std::cout<<B1<<std::endl;
            B1.signForm(F1);
        }
        catch(std::exception& exp){
            std::cout<<exp.what()<<std::endl;
        }
        B1.incrmntGrade();
        std::cout<<std::endl<<B1<<std::endl;
        B1.signForm(F1);
    }
    catch(std::exception& exp){
        std::cout<<exp.what()<<std::endl;
    }
    return 0;
}