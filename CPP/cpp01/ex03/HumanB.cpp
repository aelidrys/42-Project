#include "HumanB.hpp"

HumanB::HumanB(std::string H_name)
{
	name = H_name;
	W = NULL;
}

void	HumanB::setWeapon(Weapon &W1)
{
	W = &W1;
}

void	HumanB::attack()
{
	if (W != NULL)
		std::cout<<name<<" attacks with their "<<W->getType()<<"\n";
	else
		std::cout<<name<<" attacks with their "<<"None"<<"\n";
}