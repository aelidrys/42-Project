#ifndef PERSIDENTIALPARDONFORM_HPP
#define PERSIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm: public AForm
{
std::string target;
public:
    PresidentialPardonForm();
    PresidentialPardonForm(const std::string& target);
    PresidentialPardonForm(const PresidentialPardonForm& oth);
    PresidentialPardonForm& operator=(const PresidentialPardonForm& oth);
    const std::string& getTarget() const;
    void execute(Bureaucrat const & executor) const;
    ~PresidentialPardonForm();
};

#endif