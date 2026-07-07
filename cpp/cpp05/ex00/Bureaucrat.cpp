#include "Bureaucrat.hpp"


const char* Bureaucrat::GradeTooHighException::what() const throw(){
    const char* msg = "Grade is too hight";
    return msg;
}

const char* Bureaucrat::GradeTooLowException::what() const throw(){
    return "Grade is too low";
}

Bureaucrat::Bureaucrat():  name("unamed"), grade(150){
    // std::cout<<"Bureaucrat: Defult Constructor\n";
}

Bureaucrat::Bureaucrat(const std::string& name1, int g): name(name1){
    std::cout<<"Bureaucrat: Parametries Constructor Called\n";
    if (g > 150)
        throw GradeTooLowException();
    if (g < 1)
        throw GradeTooHighException();
    grade = g;
}

Bureaucrat::Bureaucrat(const Bureaucrat& oth): name(getName()){
    *this = oth;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& oth){
    if (this != &oth){
        grade = oth.getGrade();
    }
    return *this;
}

int Bureaucrat::getGrade() const{
    return grade;
}

const std::string& Bureaucrat::getName() const{
    return name;
}

void Bureaucrat::incrmntGrade(){
	if (grade - 1 < 1)
		throw GradeTooHighException();
    --grade;
}


void Bureaucrat::decrmntGrade(){
    if (grade + 1 > 150)
        throw GradeTooLowException();
    ++grade;
}

Bureaucrat::~Bureaucrat(){
    // std::cout<<"Bureaucrat: Destructor Called\n";
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj){
    os<<obj.getName()<<", bureaucrat grade "<<obj.getGrade();
    return os;
}

