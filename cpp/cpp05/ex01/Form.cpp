#include "Form.hpp"

const char* Form::GradeTooHighException::what() const throw(){
    return "Grade is too hight";
}

const char* Form::GradeTooLowException::what() const throw(){
    return "Grade is too low";
}

Form::Form(): name("unamed"), Signe_Grade(150), Exec_Grade(150){
    // std::cout<<"Form: Defult Constructor Called\n";
    Signed = false;
}

Form::Form(const std::string& n, const int& s_g, const int& e_g): name(n), Signe_Grade(s_g), Exec_Grade(e_g){
    Signed = false;
    if (Signe_Grade < 1 || Exec_Grade < 1)
        throw GradeTooHighException();
    if (Signe_Grade > 150 || Exec_Grade > 150)
        throw GradeTooLowException();
}

Form::Form(const Form& oth): name(oth.getName()), Signe_Grade(oth.getSigne_Grade()), Exec_Grade(oth.getExec_Grade()){
    // std::cout<<"Copy Constructor Called";
    *this = oth;
}

Form& Form::operator=(const Form& oth){
    // std::cout<<"Copy Assignment Called";
    if (this != &oth)
        Signed = oth.getSigned();
    return *this;
}

const std::string& Form::getName() const{
    return name;
}

const int& Form::getSigne_Grade() const{
    return Signe_Grade;
}

const int& Form::getExec_Grade() const{
    return Exec_Grade;
}

const bool& Form::getSigned() const{
    return Signed;
}

void Form::beSigned(const Bureaucrat& B){
    if (B.getGrade() > getSigne_Grade())
        throw GradeTooLowException();
    Signed = 1;
}

Form::~Form(){
    // std::cout<<"Form: Destructor Called\n";
}

std::ostream& operator<<(std::ostream& os, const Form& obj){
    os<<"<<  Form Name: "<<obj.getName()<<"  >>\n";
    os<<"       with Signe_Grade = "<<obj.getSigne_Grade()<<std::endl;
    os<<"         and Exec_Grade = "<<obj.getExec_Grade()<<std::endl;
    if (obj.getSigned())
        os<<"       Status: Signed Form\n";
    else
        os<<"       Status: Not Signed Form\n";
    return os;
}

