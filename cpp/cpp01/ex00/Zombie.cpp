#include "Zombie.hpp"

Zombie::Zombie(std::string name1)
{
	name = name1;
}

Zombie::~Zombie()
{
	std::cout<<name<<" is destroyed\n";
}

void	Zombie::announce(void)
{
	std::cout<<name<<": BraiiiiiiinnnzzzZ...\n";
}
