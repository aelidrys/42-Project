/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toulse1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:14:09 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/14 16:04:47 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	b_print_str(char *s)
{
	while (s && *s)
		write (2, s++, 1);
}

int	b_check_characters(char *s)
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

int	b_check_arg(char **av, int x)
{
	while (av[x])
	{
		if (!b_check_characters(av[x++]))
		{
			b_print_str("Error\nInvalid character\n");
			return (0);
		}
	}
	return (1);
}

long	b_str_to_int(char *s)
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
			b_print_str("Error\nTo large number\n");
	}
	return (n * signe);
}

int	b_chek_numbers(t_var *var, int ac)
{
	if (var->n_of_eat <= 0 && ac == 6)
	{
		b_print_str("Error\nInvalid number\n");
		return (0);
	}
	if (var->n_of_philo <= 0 || var->time_to_die <= 0
		|| var->time_to_eat < 0 || var->time_to_sleep < 0)
	{
		b_print_str("Error\nInvalid number\n");
		return (0);
	}
	return (1);
}
