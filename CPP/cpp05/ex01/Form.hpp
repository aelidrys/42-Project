#include <iostream>

#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"


class Bureaucrat;

class Form
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
    Form();
    Form(const std::string& n, const int& s_g, const int& e_g);
    Form(const Form& oth);
    Form& operator=(const Form& oth);
    void beSigned(const Bureaucrat& B);
    const std::string& getName() const;
    const int& getSigne_Grade() const;
    const int& getExec_Grade() const;
    const bool& getSigned() const;
    ~Form();
};

std::ostream& operator<<(std::ostream& os, const Form& obj);

#endif