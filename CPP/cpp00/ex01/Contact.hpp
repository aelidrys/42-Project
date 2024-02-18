# include <iostream>
#include <iomanip>
# ifndef Contact_hpp
# define Contact_hpp

class  Contact
{
private:
	std::string	_phone_number;
	std::string	_first_name;
	std::string	_last_name;
	std::string	_nickname;
	std::string	_darkest_secret;
	void	print_str(std::string str);

public:
	void	set_value(std::string *ptr);
	void	get_value();
	void	get_all();
};

#endif
