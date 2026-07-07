#include "Harl.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"

void	Harl::debug(void)
{
	std::cout<<"$$-> name of level is debug\n";
}

void	Harl::info(void)
{
	std::cout<<"$$-> name of level is info\n";
}

void	Harl::warning(void)
{
	std::cout<<"$$-> name of level is warning\n";
}

void	Harl::error(void)
{
	std::cout<<"$$-> name of level is error\n";
}

void	Harl::complain(std::string level)
{
	int	index;

	index = (level == "debug") + (level == "info")*2
		+ (level == "warning")*3 + (level == "error")*4;
	switch (index)
	{
		case 1:
			debug();
		case 2:
			info();
		case 3:
			warning();
		case 4:
			error();
			break;
		default:
			std::cout<<"<< "<<level<<" >> : invalid level\n";
			break;
	}
}

#pragma GCC diagnostic pop
