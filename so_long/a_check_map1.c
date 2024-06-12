/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_check_map1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 08:56:18 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/29 08:49:31 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_so_long.h"

int	comp_tab(int *tab, char **map, int n)
{
	int	x;
	int	y;

	x = -1;
	tab = malloc(n * sizeof(int));
	while (map[++x])
		tab[x] = a_lent(map[x]);
	x = 0;
	while (tab && x + 1 < n)
	{
		y = x + 1;
		while (y < n)
		{
			if (tab[x] != tab[y++])
			{
				free(tab);
				return (0);
			}
		}
		x++;
	}
	free(tab);
	return (1);
}

int	comp_str(char *s)
{
	int	x;

	x = 0;
	while (s[x + 1])
		if (s[x++] != '1')
			return (0);
	return (1);
}

int	valid_map(t_gam *gam, int n, int x, int y)
{
	y = a_lent(gam->map1[0]) - 1;
	if (!comp_str(gam->map1[0]) || !comp_str(gam->map1[n - 1]))
		return (3);
	while (gam->map1[x])
	{
		if (gam->map1[x][0] != '1' || gam->map1[x][y] != '1')
			return (3);
		x++;
	}
	if (!check_characters(gam, 0, 0))
		return (6);
	if (a_sersh_n(gam->map1, 'P') == 0)
		return (-1);
	if (a_sersh_n(gam->map1, 'P') > 1)
		return (-2);
	if (a_sersh_n(gam->map1, 'C') == 0)
		return (-3);
	if (!a_sersh_n(gam->map1, 'E'))
		return (4);
	if (a_sersh_n(gam->map1, 'E') > 1)
		return (-4);
	return (valid_path(gam, 0, 0, arg_lent(gam->map1)));
}

int	check_new_line(char *p)
{
	while (p && *p)
	{
		if (*p == '\n' && *(p + 1) == '\n')
			return (0);
		p++;
	}
	if (p && *p == '\0' && *(p - 1) == '\n')
		return (0);
	return (1);
}

int	check_map(t_gam *gam, char *p)
{

	gam->map1 = spl(p, '\n');
	if (!gam->map1)
	{
		write (1, "Error\n", 6);
		exit (0);
	}
	if (!check_new_line(p))
		return (0);
	if (comp_tab(NULL, gam->map1, arg_lent(gam->map1)) != 1)
		return (2);
	if (arg_lent(gam->map1) < 3)
		return (2);
	return (valid_map(gam, arg_lent(gam->map1), 0, 0));
}
