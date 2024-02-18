#ifndef INTERN_HPP
#define INTERN_HPP

#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

class Intern
{
public:
    Intern();
    Intern(const Intern& oth);
    Intern& operator=(const Intern& oth);
    AForm* makeForm(const std::string& name, const std::string& target);
    ~Intern();
};

#endif