#include "Weapon.hpp"

# ifndef HumanA_hpp
# define HumanA_hpp

class HumanA
{
private:
	std::string	name;
	Weapon		&W;
public:
	HumanA(std::string H_name, Weapon &W1);
	void	attack();
};

#endif