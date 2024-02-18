#include "Weapon.hpp"

# ifndef HumanB_hpp
# define HumanB_hpp

class HumanB
{
private:
	std::string	name;
	Weapon		*W;
public:
	HumanB(std::string H_name);
	void	setWeapon(Weapon &W1);
	void	attack();
};


#endif
