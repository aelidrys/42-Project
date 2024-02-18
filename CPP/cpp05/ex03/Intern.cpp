#include "Intern.hpp"

Intern::Intern(){
    // std::cout<<"Intern: Defult Constructor Called\n";
}

Intern::Intern(const Intern& oth){
    // std::cout<<"Intern: Copy Cinstructor Called\n";
    *this = oth;
}

Intern& Intern::operator=(const Intern& oth){
    // std::cout<<"Intern: Copy Assignment Called\n";
    if (this != &oth){
        ;
    }
    return *this;
}

AForm* Intern::makeForm(const std::string& name, const std::string& target){
    int cond = (name == "presidential pardon")+(name == "robotomy request")*2+(name == "shrubbery creation")*3;
    AForm *F1 = NULL;
    switch (cond)
    {
    case 1:
        F1 = new PresidentialPardonForm(target);
        break;
    case 2:
        F1 = new RobotomyRequestForm(target);
        break;
    case 3:
        F1 = new ShrubberyCreationForm(target);
        break;
    default:
        std::cout<<"Intern Canno't Create Form "<<name<<"\n";
        return NULL;
    }
    std::cout<<"Intern creates Form: "<<name<<"\n";
    return F1;
}

Intern::~Intern(){
    // std::cout<<"Intern: Destructor Called\n";
}