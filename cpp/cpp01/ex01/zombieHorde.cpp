#include "Zombie.hpp"


Zombie* zombieHorde(int N, std::string name)
{
	Zombie *ptr_zombie;

	if (N < 0)
		return (NULL);
	ptr_zombie = new Zombie[N];
	while(N--)
		ptr_zombie[N].set_name(name);

	return (ptr_zombie);
}
