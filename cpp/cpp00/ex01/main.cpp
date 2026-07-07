# include "PhoneBook.hpp"

int	main()
{
	std::string	cmd;
	PhoneBook	P1;

	while (1)
	{
		std::cout<<"phonebooh-> ";
		std::getline(std::cin,cmd);
		if (std::cin.eof())
			return (0);
		if (cmd == "ADD")
			P1.add();
		else if (cmd == "SEARCH")
			P1.search();
		else if (cmd == "EXIT")
			return (0);
		else if (cmd != "")
			std::cout<<"invalid command\n";
	}

}
