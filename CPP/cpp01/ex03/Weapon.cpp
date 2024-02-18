#include "Weapon.hpp"

Weapon::Weapon(std::string type1)
{
	type = type1;
}

const std::string&	Weapon::getType()
{
	return (type);
}

void	Weapon::setType(std::string type1)
{
	type = type1;
}
