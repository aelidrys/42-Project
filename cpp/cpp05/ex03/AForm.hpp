#include <iostream>

#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"


class Bureaucrat;

class AForm
{
const std::string name;
const int Signe_Grade; 
const int Exec_Grade;
bool Signed;
public:
    class GradeTooHighException: public std::exception
    {
    public:
        const char* what() const throw();
    };
    class GradeTooLowException: public std::exception
    {
    public:
        const char* what() const throw();
    };
    AForm();
    AForm(const std::string& n, const int& s_g, const int& e_g);
    AForm(const AForm& oth);
    AForm& operator=(const AForm& oth);
    void beSigned(const Bureaucrat& B);
    const std::string& getName() const;
    const int& getSigne_Grade() const;
    const int& getExec_Grade() const;
    const bool& getSigned() const;
    virtual void execute(Bureaucrat const & executor) const = 0;
    virtual ~AForm();
};

std::ostream& operator<<(std::ostream& os, const AForm& obj);

#endif