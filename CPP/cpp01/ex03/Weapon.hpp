#include <iostream>

# ifndef Weapon_hpp
# define Weapon_hpp

class	Weapon
{
private:
	std::string type;
public:
	Weapon(){};
	Weapon(std::string type1);
	const std::string&	getType();
	void	setType(std::string type1);
};

#endif
