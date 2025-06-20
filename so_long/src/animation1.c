/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_animation1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 06:50:52 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/29 08:48:33 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	anim_of_sheep(t_gam *gam, int x, int y)
{
	while (gam->map[y])
	{
		x = 0;
		while (gam->map[y][x])
		{
			if (gam->n == 50001)
				gam->n = 0;
			if (gam->map[y][x] == 'C')
			{
				if (gam->n == 0)
					put_img(gam, x * 50, y * 50, 'C');
				if (gam->n == 32000)
					put_img(gam, x * 50, y * 50, 'c');
			}
			x++;
		}
		y++;
	}
	gam->n++;
}

int	sw_enmy(t_gam *gam, int a, int b, int c)
{
	sw1_img(gam, a, b);
	return (c);
}

void	enemy_movs(t_gam *gam, int x, int y, int c)
{
	if ((gam->map[y][x + 1] == '0' || gam->map[y][x + 1] == 'P') && c < 3
		&& (gam->map[y - 1][x + 1] == '0' || gam->map[y - 1][x + 1] == 'P'
		|| gam->map[y + 1][x + 1] == '0' || gam->map[y + 1][x + 1] == 'P'))
		c = sw_enmy(gam, 'R', 'A', gam->map[y][x + 1]);
	else if ((gam->map[y + 1][x] == '0' || gam->map[y + 1][x] == 'P')
		&& c < 6 && c > 2 && (gam->map[y + 1][x + 1] != '1'
		|| gam->map[y + 1][x - 1] != '1'))
		c = sw_enmy(gam, 'D', 'A', gam->map[y + 1][x]);
	else if ((gam->map[y][x - 1] == '0' || gam->map[y][x - 1] == 'P') && c < 9
		&& c > 5 && (gam->map[y - 1][x - 1] != '1'
		|| gam->map[y + 1][x - 1] != '1'))
		c = sw_enmy(gam, 'L', 'A', gam->map[y][x - 1]);
	else if ((gam->map[y - 1][x] == '0' || gam->map[y - 1][x] == 'P') && c > 8
		&& (gam->map[y - 1][x + 1] != '1' || gam->map[y - 1][x - 1] != '1'))
		c = sw_enmy(gam, 'U', 'A', gam->map[y - 1][x]);
	if (c == 'P')
		print_str("YOU LOST\n");
}

void	anim_of_enemy(t_gam *gam, int x, int y, int n)
{
	if (n == 0 || n == 10000 || n == 20000 || n == 30000 || n == 40000)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.n, x, y);
	if (n == 0)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.a1, x, y);
	if (n == 10000)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.a2, x, y);
	if (n == 20000)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.a3, x, y);
	if (n == 30000)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.a4, x, y);
	if (n == 40000)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.a5, x, y);
}

int	a_animation(t_gam *gam)
{
	t_enmy	*tmp;

	tmp = gam->a;
	anim_of_sheep(gam, 0, 0);
	if (gam->n_c++ == 50002)
		gam->n_c = 0;
	while (gam->a)
	{	
		gam->a->d = (rand() % 12);
		anim_of_enemy(gam, gam->a->x * 50, gam->a->y * 50, gam->n_c);
		if (gam->n_c == 50000)
			enemy_movs(gam, gam->a->x, gam->a->y, gam->a->d);
		gam->a = gam->a->next;
	}
	gam->a = tmp;
	return (0);
}
