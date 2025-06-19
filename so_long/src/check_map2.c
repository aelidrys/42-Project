/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_check_map2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:34:10 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/29 08:48:47 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flod_fill(char **map1, int x, int y, int n)
{
	if (!map1)
		return ;
	if (map1[x][y] != 'P')
		map1[x][y] = '2';
	if (map1[x][y + 1] == 'C' || map1[x][y + 1] == '0')
		flod_fill(map1, x, y + 1, n);
	if (map1[x + 1][y] == 'C' || map1[x + 1][y] == '0')
		flod_fill(map1, x + 1, y, n);
	if (x > 0 && (map1[x - 1][y] == 'C' || map1[x - 1][y] == '0'))
		flod_fill(map1, x - 1, y, n);
	if (y > 0 && (map1[x][y - 1] == 'C' || map1[x][y - 1] == '0'))
		flod_fill(map1, x, y - 1, n);
}

int	valid_path(t_gam *gam, int x, int y, int n)
{
	if (!a_sersh(gam->map1, 'P', &x, &y))
		print_error(-1);
	flod_fill(gam->map1, x, y, n);
	a_sersh(gam->map1, 'E', &x, &y);
	if (gam->map1[x + 1][y] != '2' && gam->map1[x][y + 1] != '2'
		&& gam->map1[x - 1][y] != '2' && gam->map1[x][y - 1] != '2')
		return (-5);
	if (a_sersh_n(gam->map1, 'C'))
		return (-5);
	return (check_enmy(gam, 0, 0));
}

int	check_enmy(t_gam *gam, int x, int y)
{
	while (gam->map1 && gam->map1[y])
	{
		x = 0;
		while (gam->map1[y][x])
		{
			if ((gam->map1[y][x] == 'A' && (gam->map1[y][x + 1] == '1'
				|| gam->map1[y][x + 1] == 'E') && (gam->map1[y][x - 1] == '1'
				|| gam->map1[y][x - 1] == 'E')) || (gam->map1[y][x] == 'A'
				&& (gam->map1[y + 1][x] == '1' || gam->map1[y + 1][x] == 'E')
				&& (gam->map1[y - 1][x] == '1' || gam->map1[y - 1][x] == 'E')))
				return (5);
			if ((gam->map1[y][x] == 'A' && (gam->map1[y][x + 1] == '1'
				|| gam->map1[y][x + 1] == 'E') && (gam->map1[y][x - 1] == '1'
				|| gam->map1[y][x - 1] == 'E')) || (gam->map1[y][x] == 'A'
				&& (gam->map1[y + 1][x] == '1' || gam->map1[y + 1][x] == 'E')
				&& (gam->map1[y - 1][x] == '1' || gam->map1[y - 1][x] == 'E')))
				return (5);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_characters(t_gam *gam, int x, int y)
{
	y = -1;
	while (gam->map1[++y])
	{
		x = -1;
		while (gam->map1[y][++x])
		{
			if (gam->map1[y][x] != '0' && gam->map1[y][x] != '1'
				&& gam->map1[y][x] != 'C' && gam->map1[y][x] != 'E'
				&& gam->map1[y][x] != 'P' && gam->map1[y][x] != 'A')
				return (0);
		}
	}
	return (1);
}
