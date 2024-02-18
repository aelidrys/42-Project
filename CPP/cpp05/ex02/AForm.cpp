#include "AForm.hpp"

const char* AForm::GradeTooHighException::what() const throw(){
    return "Grade is too hight";
}

const char* AForm::GradeTooLowException::what() const throw(){
    return "Grade is too low";
}

AForm::AForm(): name("unamed"), Signe_Grade(150), Exec_Grade(150){
    // std::cout<<"AForm: Defult Constructor Called\n";
    Signed = false;
}

AForm::AForm(const std::string& n, const int& s_g, const int& e_g): name(n), Signe_Grade(s_g), Exec_Grade(e_g){
    Signed = false;
    if (Signe_Grade < 1 || Exec_Grade < 1)
        throw GradeTooHighException();
    if (Signe_Grade > 150 || Exec_Grade > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm& oth): name(oth.getName()), Signe_Grade(oth.getSigne_Grade()), Exec_Grade(oth.getExec_Grade()){
    // std::cout<<"Copy Constructor Called";
    *this = oth;
}

AForm& AForm::operator=(const AForm& oth){
    // std::cout<<"Copy Assignment Called";
    if (this != &oth)
        Signed = oth.getSigned();
    return *this;
}

const std::string& AForm::getName() const{
    return name;
}

const int& AForm::getSigne_Grade() const{
    return Signe_Grade;
}

const int& AForm::getExec_Grade() const{
    return Exec_Grade;
}

const bool& AForm::getSigned() const{
    return Signed;
}

void AForm::beSigned(const Bureaucrat& B){
    if (B.getGrade() > getSigne_Grade())
        throw GradeTooLowException();
    Signed = 1;
}

AForm::~AForm(){
    // std::cout<<"AForm: Destructor Called\n";
}

std::ostream& operator<<(std::ostream& os, const AForm& obj){
    os<<"<<  Form Name: "<<obj.getName()<<"  >>\n";
    os<<"       with Signe_Grade = "<<obj.getSigne_Grade()<<std::endl;
    os<<"         and Exec_Grade = "<<obj.getExec_Grade()<<std::endl;
    if (obj.getSigned())
        os<<"       Status: Signed Form\n";
    else
        os<<"       Status: Not Signed Form\n";
    return os;
}

