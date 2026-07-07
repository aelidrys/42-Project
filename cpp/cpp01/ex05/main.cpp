#include "Harl.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout<<"No level\n";
		return (0);
	}
	Harl h1;
	h1.complain(av[1]);
}