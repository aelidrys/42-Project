#include "HumanA.hpp"


HumanA::HumanA(std::string H_name, Weapon &W1): W(W1)
{
	name = H_name;
}

void	HumanA::attack()
{
	std::cout<<name<<" attacks with their "<<W.getType()<<"\n";
}
