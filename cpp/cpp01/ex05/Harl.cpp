#include "Harl.hpp"

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
	if (level != "debug" && level != "info" && level != "warning" && level != "error"){
		std::cout<<"<< "<<level<<" >> : invalid level\n";
		return ;
	}
	mf_ptr ptr[] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	index = (level == "debug") * 0 + (level == "info") + (level == "warning") * 2
		+ (level == "error") * 3;
	(this->*ptr[index])();
}
