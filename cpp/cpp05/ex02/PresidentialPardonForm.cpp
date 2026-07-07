#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(): target("unamed"){
    // std::cout<<"PR_Form: Defult Constructor Called\n";
}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target1): AForm("PR_Form",25,5){
    target = target1;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& oth): AForm(oth){
    *this = oth;
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& oth){
    if (this != &oth){
        target = oth.getTarget();
    }
    return *this;
}

const std::string& PresidentialPardonForm::getTarget() const{
    return target;
}


void PresidentialPardonForm::execute(Bureaucrat const & executor) const{
    if (executor.getGrade() > getExec_Grade() || !getSigned())
        throw GradeTooLowException();
    std::cout<<target<<" has been pardoned by Zaphod Beeblebrox\n";
}

PresidentialPardonForm::~PresidentialPardonForm(){
    // std::cout<<"PR_Form: Destructor Constructor Called\n";
}