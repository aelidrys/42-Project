#include "ShrubberyCreationForm.hpp"


ShrubberyCreationForm::ShrubberyCreationForm(): target("unamed"){
    // std::cout<<"Sh_Form: Defult Constructor Called\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target1): AForm("Sh_Form",145,137){
    target = target1;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& oth): AForm(oth){
    *this = oth;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& oth){
    if (this != &oth){
        target = oth.getTarget();
    }
    return *this;
}

const std::string& ShrubberyCreationForm::getTarget() const{
    return target;
}

void ShrubberyCreationForm::creat_ASCII_tree() const{
    int y = 0;
    int x = 8;
    std::fstream out_file;
    out_file.open((target+"_shrubbery").c_str(), std::ios::out);
    for (int i = 0; i < x; i++)
    {
        for (int i = 0; i < x-y; i++)
            out_file<<" ";
        out_file<<"/";
        for (int i = x-y; i < x+y; i++)
            out_file<<".";
        out_file<<"\\";
        for (int i = x+y; i < x*2; i++)
            out_file<<" ";
        y++;  
        out_file<<"\n";
    }
    out_file<<"  \\------------/  \n";
    out_file<<"        ||        \n";
    out_file<<"        ||        \n";
    out_file<<"        ||        \n";
    out_file.close();
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const{
    if (executor.getGrade() > getExec_Grade() || !getSigned())
        throw GradeTooLowException();   
    creat_ASCII_tree();
}


ShrubberyCreationForm::~ShrubberyCreationForm(){
    // std::cout<<"Sh_Form: Destructor Constructor Called\n";
}
