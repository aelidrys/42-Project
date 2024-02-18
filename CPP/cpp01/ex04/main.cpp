#include "Clsrpl.hpp"

int main(int ac, char **av)
{
	if (ac < 4)
	{
		std::cout<<"parameters not complet"<<"\n";
		return (1);
	}
	if (av[2][0] == '\0')
	{
		std::cout<<"s1 should not be empty"<<"\n";
		return (1);

	}
	Clsrpl	rpl(av[1], av[2], av[3]);
	rpl.replace();
}