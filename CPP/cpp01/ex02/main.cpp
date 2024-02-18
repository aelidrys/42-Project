#include <iostream>

int main()
{
	std::string	str;
	std::string	*PTR;
	std::string	&REF = str;

	str = "HI THIS IS BRAIN";
	PTR = &str;
	std::cout<<"address of str      = "<<&str<<"\n";
	std::cout<<"address held by PTR = "<<PTR<<"\n";
	std::cout<<"address held by REF = "<<&REF<<"\n";
	std::cout<<"----------------\n";
	std::cout<<"value of string variable = "<<str<<"\n";
	std::cout<<"value pointed to by PTR  = "<<*PTR<<"\n";
	std::cout<<"value pointed to by REF  = "<<REF<<"\n";
}