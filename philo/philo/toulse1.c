/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toulse1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:22:42 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/13 09:08:02 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_str(char *s)
{
	while (s && *s)
		write (2, s++, 1);
}

int	check_characters(char *s)
{
	int	x;

	x = 0;
	while (s && *s == ' ')
		s++;
	if (s && (*s == '+' || *s == '-'))
		s++;
	while (s && *s)
	{
		x = 1;
		if (!(*s >= '0' && *s <= '9'))
			return (0);
		s++;
	}
	return (x);
}

int	check_arg(char **av, int x)
{
	while (av[x])
	{
		if (!check_characters(av[x++]))
		{
			print_str("Error\nInvalid character\n");
			return (0);
		}
	}
	return (1);
}

long	str_to_int(char *s)
{
	long	n;
	int		signe;

	n = 0;
	signe = 1;
	while (s && *s == ' ')
		s++;
	if (s && (*s == '+' || *s == '-'))
	{
		if (*(s++) == '-')
			signe = -1;
	}
	while (s && *s >= '0' && *s <= '9')
	{
		n = n * 10 + (*(s++) - 48);
		if (n > 2147483648 || (n > 2147483647 && signe == 1))
			print_str("Error\nTo large number\n");
	}
	return (n * signe);
}
