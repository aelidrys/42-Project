#ifndef SHRUBBERYCRETIONFORM_HPP
#define SHRUBBERYCRETIONFORM_HPP

#include <fstream>
#include "AForm.hpp"

class ShrubberyCreationForm: public AForm
{
std::string target;
public:
    ShrubberyCreationForm();
    ShrubberyCreationForm(const std::string& target);
    ShrubberyCreationForm(const ShrubberyCreationForm& oth);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& oth);
    const std::string& getTarget() const;
    void execute(Bureaucrat const & executor) const;
    void creat_ASCII_tree() const;
    ~ShrubberyCreationForm();
};

#endif