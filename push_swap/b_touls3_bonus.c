/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_touls3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:27:55 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/15 06:42:24 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_push_swap_bonus.h"

int	comp_str_b(char *p, char *s)
{
	if (s && *s == '+')
		s++;
	if (p && *p == '+')
		p++;
	while (p && s && *s && *p)
	{
		if (*(p++) != *(s++))
			return (1);
	}
	if (*p == *s)
		return (0);
	return (1);
}

int	check_characters_b(char *s, int x)
{
	if (s && (s[x + 1] == '-' || s[x + 1] == '+') && s[x + 2])
		x++;
	while (s && s[++x])
	{
		if (!(s[x] >= 48 && s[x] <= 57) && s[x] != 32)
			return (0);
	}
	return (1);
}

void	print_str_b(char *s)
{
	while (s && *s)
		write(2, s++, 1);
	exit (0);
}

long	str_to_int_b(char *str)
{
	double	res;
	int		s;

	s = 1;
	res = 0;
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			s *= -1;
	}
	while (*str >= 48 && *str <= 57)
		res = res * 10 + *(str++) - 48;
	if (res > 2147483648 || (res == 2147483648 && s == 1))
		print_error_b(-3);
	return (res * s);
}

int	check_arg_b(t_var *var, t_arg *arg1)
{
	t_arg	*arg2;

	arg1 = var->arg;
	while (arg1)
	{
		if (!check_characters_b(arg1->str, -1))
			return (-1);
		arg1 = arg1->next;
	}
	arg1 = var->arg;
	while (arg1)
	{
		arg2 = arg1->next;
		while (arg2)
		{
			if (!comp_str_b(arg1->str, arg2->str))
				return (2);
			arg2 = arg2->next;
		}
		arg1 = arg1->next;
	}
	return (1);
}
