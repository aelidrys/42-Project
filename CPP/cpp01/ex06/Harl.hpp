#include <iostream>

#ifndef HARL_HHP
#define HARL_HHP

class Harl
{
private:
	void	debug(void);
	void	info(void);
	void	warning(void);
	void	error(void);
public:
	void	complain(std::string level);
};

#endif