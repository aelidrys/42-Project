# include "PhoneBook.hpp"

void PhoneBook::add()
{
	std::string ptr[5];

	ptr[0] = add_one("enter your first name : ", "invalid first name\n");
	ptr[1] = add_one("enter your last name : ", "invalid last name\n");
	ptr[2] = add_one("enter your nickname : ", "invalid nickname\n");

	while (is_not_digit(ptr[3]))
	{
		std::cout<<"enter your phone number : ";
		std::getline(std::cin,ptr[3]);
		if (std::cin.eof())
			exit(0);
		if (is_not_digit(ptr[3]))
			std::cout<<"invalid phone number\n";
	}
	ptr[4] = add_one("enter the darkest secret : ", "invalid darkest secret\n");
	if (num_of_cont < 8)
		c1[num_of_cont++].set_value(ptr);
	else
		replace(ptr);
}


std::string	PhoneBook::add_one(std::string prm, std::string err)
{
	std::string str;

	while (str == "")
	{
		if (std::cin.eof())
			exit(0);
		std::cout<<prm;
		std::getline(std::cin,str);
		if (str == "" && !std::cin.eof())
			std::cout<<err;
	}
	return (str);

}

int	PhoneBook::is_not_digit(std::string s1)
{
	int	i;

	i = 0;
	if (!s1.length())
		return (1);
	while (i < s1.length())
	{
		if (!(s1[i] >= '0' && s1[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void PhoneBook::replace(std::string *ptr)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		c1[i] = c1[i + 1];
		i++;
	}
	c1[7].set_value(ptr);
}

void	PhoneBook::search()
{
	std::string	ind;
	int		index;

	shaw_all();
	std::cout<<"enter the index of Contact : ";
	std::getline(std::cin,ind);
	if (std::cin.eof())
		exit(0);
	index = ind[0] - 49;
	if (index < 0 || index > 7 || ind.length() > 1)
		std::cout<<"enter always an index between [1,8]\n";
	else if (index >= num_of_cont)
		std::cout<<"no contact in this index\n";
	else
		c1[index].get_all();
}

void PhoneBook::shaw_all()
{
	int i;

	i = 0;
	if (num_of_cont)
	{
		std::cout<<std::setw(10)<<"index"<<"|";
		std::cout<<std::setw(10)<<"first_name"<<"|";
		std::cout<<std::setw(10)<<"last_name"<<"|";
		std::cout<<std::setw(10)<<"nickname"<<"\n";
	}
	while (i < num_of_cont)
	{
		std::cout<<std::setw(10)<<i + 1<<"|";
		c1[i++].get_value();
	}
}