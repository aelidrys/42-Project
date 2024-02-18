#include <iostream>

void	lower_case(char *str)
{
	while (str && *str)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str += 32;
		str++;
	}
}

void	uppere_case(char *str)
{
	while (str && *str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
}

int main(int ac, char **av)
{
	int	i;

	i = 1;
	if (av[1])
	{
		while (av[i])
		{
			lower_case(av[i]);
			uppere_case(av[i]);
			std::cout<<av[i];
			i++;
			// if (av[i])
			// 	std::cout<<' ';
		}
		std::cout<<std::endl;
	}
	else
		std::cout<<"* LOUD AND UNBEARABLE FEEDBACK NOISE *"<<std::endl;
}