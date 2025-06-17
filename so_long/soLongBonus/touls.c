/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_touls_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:55:48 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/01 06:25:29 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	arg_lent(char **p)
{
	size_t	n;

	n = 0;
	while (p[n])
		n++;
	return (n);
}

int	a_sersh(char **map, char c, int *x, int *y)
{
	int	a;
	int	b;

	a = 0;
	while (map[a])
	{
		b = 0;
		while (map[a][b])
		{
			if (map[a][b++] == c)
			{
				*x = a;
				*y = b - 1;
				return (1);
			}
		}
		a++;
	}
	return (0);
}

int	a_sersh_n(char **map, char c)
{
	int	a;
	int	b;
	int	x;

	a = 0;
	x = 0;
	while (map[a])
	{
		b = 0;
		while (map[a][b])
		{
			if (map[a][b++] == c)
				x++;
		}
		a++;
	}
	return (x);
}

void	print_str(char *s)
{
	int werror = 0;
	while (s && *s)
		werror = write (1, s++, 1);
	exit (werror < 0 ? 1 : 0);
}

void	print_error(int x)
{
	if (x == -5)
		print_str("Error\nInvalid path\n");
	if (x == -4)
		print_str("Error\nTwo or more exits\n");
	if (x == -3)
		print_str("Error\nCollectible not found\n");
	if (x == -2)
		print_str("Error\nTwo or more players\n");
	if (x == -1)
		print_str("Error\nPlayer does not exist\n");
	if (x == 0)
		print_str("Error\nExtra new line\n");
	if (x == 2)
		print_str("Error\nInvalid map\n");
	if (x == 3)
		print_str("Error\nIvalid wall\n");
	if (x == 4)
		print_str("Error\nThe exit does not exist\n");
	if (x == 5)
		print_str("Error\nInvalid posission of enemy\n");
	if (x == 6)
		print_str("Error\nInvalid character in map\n");
	if (x == 7)
		print_str("Error\nin convert from xpm file to image\n");
}
