#include "Zombie.hpp"

int	main()
{
	Zombie zombie("zombi1");
	Zombie *ptr_zombie;
	randomChump("random_zombie");
	std::cout<<"------------\n\n";
	ptr_zombie = newZombie("NewZombie");
	ptr_zombie->announce();
	delete ptr_zombie;
	std::cout<<"------------\n\n";
	zombie.announce();

}
