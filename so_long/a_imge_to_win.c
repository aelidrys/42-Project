/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_imge_to_win.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 08:45:55 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/29 08:49:40 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_so_long.h"

int	put_p(t_gam *gam, int x, int y, int k)
{
	if (k == 'N')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->p.p_d, x, y);
	if (k == 'R' && gam->b[1] != 1 && gam->b[1] != 2)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->p.p1_r, x, y);
	if (k == 'R' && gam->b[1] == 1)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->p.p2_r, x, y);
	if (k == 'R' && gam->b[1] == 2)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->p.p3_r, x, y);
	if (k == 'L' && gam->b[0] != 1 && gam->b[0] != 2)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->p.p1_l, x, y);
	if (k == 'L' && gam->b[0] == 1)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->p.p2_l, x, y);
	if (k == 'L' && gam->b[0] == 2)
		mlx_put_image_to_window(gam->mlx, gam->win, gam->p.p3_l, x, y);
	if (k == 'D')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->p.p_d, x, y);
	if (k == 'U')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->p.p_u, x, y);
	return (1);
}

int	put_img(t_gam *gam, int x, int y, int k)
{
	if (k == 'C')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.c1, x, y);
	if (k == '1')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.w, x, y);
	if (k == '0')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.n, x, y);
	if (k == 'E')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.e0, x, y);
	if (k == 'e')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.ef, x, y);
	return (1);
}

void	sw1_img(t_gam *gam, int k, int c)
{
	gam->map[gam->p.y][gam->p.x] = '0';
	if (k == 'L')
		put_img(gam, (gam->p.x--) * 70, gam->p.y * 70, '0');
	if (k == 'R')
		put_img(gam, (gam->p.x++) * 70, gam->p.y * 70, '0');
	if (k == 'D')
		put_img(gam, gam->p.x * 70, (gam->p.y++) * 70, '0');
	if (k == 'U')
		put_img(gam, gam->p.x * 70, (gam->p.y--) * 70, '0');
	gam->map[gam->p.y][gam->p.x] = c;
	put_p(gam, gam->p.x * 70, gam->p.y * 70, k);
}

void	plyr_movs(t_gam *gam, int x, int y, int s)
{
	print_numbr(++gam->movs, gam->movs);
	if (gam->map[y][x] == 'e')
		print_str("YOU WIN\n");
	if (s == 0 || s == 1)
	{
		if (gam->b[s] == 3)
			gam->b[s] = 0;
		gam->b[s]++;
	}
	if (s == 0)
		sw1_img(gam, 'L', 'P');
	if (s == 1)
		sw1_img(gam, 'R', 'P');
	if (s == 2)
		sw1_img(gam, 'U', 'P');
	if (s == 3)
		sw1_img(gam, 'D', 'P');
}

int	a_event(int k, t_gam *gam)
{
	if (k == 53)
		print_str("YOU ARE EXIT FROM THE GAME\n");
	if (!a_sersh(gam->map, 'P', &gam->p.y, &gam->p.x))
		return (0);
	if ((k == 123 || k == 0) && gam->map[gam->p.y][gam->p.x - 1] != 'E'
		&& gam->map[gam->p.y][gam->p.x - 1] != '1')
		plyr_movs(gam, gam->p.x - 1, gam->p.y, 0);
	if ((k == 124 || k == 2) && gam->map[gam->p.y][gam->p.x + 1] != 'E'
		&& gam->map[gam->p.y][gam->p.x + 1] != '1')
		plyr_movs(gam, gam->p.x + 1, gam->p.y, 1);
	if ((k == 126 || k == 13) && gam->map[gam->p.y - 1][gam->p.x] != 'E'
		&& gam->map[gam->p.y - 1][gam->p.x] != '1')
		plyr_movs(gam, gam->p.x, gam->p.y - 1, 2);
	if ((k == 125 || k == 1) && gam->map[gam->p.y + 1][gam->p.x] != 'E'
		&& gam->map[gam->p.y + 1][gam->p.x] != '1')
		plyr_movs(gam, gam->p.x, gam->p.y + 1, 3);
	if (a_sersh_n(gam->map, 'C') == 0
		&& a_sersh(gam->map, 'E', &gam->m_y, &gam->m_x))
	{
		gam->map[gam->m_y][gam->m_x] = 'e';
		put_img(gam, gam->m_x * 70, gam->m_y * 70, 'e');
	}
	return (0);
}
