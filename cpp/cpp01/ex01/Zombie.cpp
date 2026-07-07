#include "Zombie.hpp"

void	Zombie::announce(void)
{
	std::cout<<name<<": BraiiiiiiinnnzzzZ...\n";
}

void	Zombie::set_name(std::string name1)
{
	name = name1;
}

Zombie::~Zombie()
{
	std::cout<<name<<" is destroyed\n";
}