#include "Zombie.hpp"

int	main()
{
	Zombie	*Zomb;
	int		N;

	N = 5;
	Zomb = zombieHorde(N,"ge3fer");
	for (int i=0;i < N;i++)
		Zomb[i].announce();
	delete[] Zomb;
}
