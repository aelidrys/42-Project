#include <iostream>
#include <exception>

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

class Bureaucrat
{
const std::string name;
int grade;
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
    Bureaucrat();
    Bureaucrat(const std::string& name1, int g);
    Bureaucrat(const Bureaucrat& oth);
    Bureaucrat& operator=(const Bureaucrat& oth);
    void incrmntGrade();
    void decrmntGrade();
    int getGrade() const;
    const std::string& getName() const;
    ~Bureaucrat();
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj);

#endif