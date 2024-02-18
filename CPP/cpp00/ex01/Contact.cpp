# include "Contact.hpp"

void	Contact::set_value(std::string *ptr)
{
	_first_name = ptr[0];
	_last_name = ptr[1];
	_nickname = ptr[2];
	_phone_number = ptr[3];
	_darkest_secret = ptr[4];
}

void	Contact::print_str(std::string str)
{
	if (str.length() > 10)
	{
		str[9] = '.';
		str.resize(10);
	}
	std::cout<<std::setw(10)<<str;
}

void	Contact::get_value()
{
	print_str(_first_name);
	std::cout<<"|";
	print_str(_last_name);
	std::cout<<"|";
	print_str(_nickname);
	std::cout<<"\n";
}

void	Contact::get_all()
{
	std::cout<<"first_name     : "<<_first_name<<"\n";
	std::cout<<"last_name      : "<<_last_name<<"\n";
	std::cout<<"nickname       : "<<_nickname<<"\n";
	std::cout<<"phone_numder   : "<<_phone_number<<"\n";
	std::cout<<"darkest_secret : "<<_darkest_secret<<"\n";
}
