#ifndef ROBOTOMYREQUESTFROM_HPP
#define ROBOTOMYREQUESTFROM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
std::string target;
public:
    RobotomyRequestForm();
    RobotomyRequestForm(const std::string& target);
    RobotomyRequestForm(const RobotomyRequestForm& oth);
    RobotomyRequestForm& operator=(const RobotomyRequestForm& oth);
    const std::string& getTarget() const;
    void execute(Bureaucrat const & executor) const;
    ~RobotomyRequestForm();
};

#endif