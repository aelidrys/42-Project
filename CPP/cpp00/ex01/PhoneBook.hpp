# include <iostream>
# include "Contact.hpp"

# ifndef PhoneBook_hpp
# define PhoneBook_hpp

class PhoneBook
{
private:
	int		num_of_cont;
	Contact	c1[8];
	void	shaw_all();
	void	replace(std::string *ptr);
	int		is_not_digit(std::string s1);
	std::string	add_one(std::string prm, std::string err);

public:
	void	add();
	void	search();

};

#endif
