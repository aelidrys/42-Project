#include "RobotomyRequestForm.hpp"
#include <math.h>

RobotomyRequestForm::RobotomyRequestForm(): target("robotomy request"){
    // std::cout<<"Robo_Form: Defult Constructor Called\n";
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target1): AForm("robotomy request",72,45){
    target = target1;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& oth): AForm(oth){
    *this = oth;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& oth){
    if (this != &oth){
        target = oth.getTarget();
    }
    return *this;
}

const std::string& RobotomyRequestForm::getTarget() const{
    return target;
}


void RobotomyRequestForm::execute(Bureaucrat const & executor) const{
    if (executor.getGrade() > 45 || !getSigned())
        throw GradeTooLowException();
    if (time(NULL) % 2)
        std::cout<<target<<" has been robotomized successfully\n";
    else
        std::cout<<"the robotomy failed\n";
}

RobotomyRequestForm::~RobotomyRequestForm(){
    // std::cout<<"Robo_Form: Destructor Constructor Called\n";
}
