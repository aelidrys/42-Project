/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_imge_to_win_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 08:45:55 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/29 08:48:52 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (k == 'A')
	{
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.n, x, y);
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.a1, x, y);
	}
	if (k == 'C')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.c1, x, y);
	if (k == 'c')
		mlx_put_image_to_window(gam->mlx, gam->win, gam->img.c2, x, y);
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
	if (c == 'P')
	{
		gam->map[gam->p.y][gam->p.x] = '0';
		if (k == 'L')
			put_img(gam, (gam->p.x--) * 50, gam->p.y * 50, '0');
		if (k == 'R')
			put_img(gam, (gam->p.x++) * 50, gam->p.y * 50, '0');
		if (k == 'D')
			put_img(gam, gam->p.x * 50, (gam->p.y++) * 50, '0');
		if (k == 'U')
			put_img(gam, gam->p.x * 50, (gam->p.y--) * 50, '0');
		gam->map[gam->p.y][gam->p.x] = c;
		put_p(gam, gam->p.x * 50, gam->p.y * 50, k);
		return ;
	}
	gam->map[gam->a->y][gam->a->x] = '0';
	if (k == 'L')
		put_img(gam, (gam->a->x--) * 50, gam->a->y * 50, '0');
	if (k == 'R')
		put_img(gam, (gam->a->x++) * 50, gam->a->y * 50, '0');
	if (k == 'D')
		put_img(gam, gam->a->x * 50, (gam->a->y++) * 50, '0');
	if (k == 'U')
		put_img(gam, gam->a->x * 50, (gam->a->y--) * 50, '0');
	gam->map[gam->a->y][gam->a->x] = c;
}

void	plyr_movs(t_gam *gam, int x, int y, int s)
{
	char	p[12];
	if (gam->map[y][x] == 'C'){
		int count_c = a_sersh_n(gam->map, 'C');
		printf("\rCollected Sheps: %d/%d", gam->n_sheps - (count_c - 1), gam->n_sheps);
		fflush(stdout);
	}
	ft_itoa(++gam->movs, p);
	mlx_put_image_to_window(gam->mlx, gam->win, gam->img.w, 0, 0);
	mlx_put_image_to_window(gam->mlx, gam->win, gam->img.w, 0, 1);
	mlx_string_put(gam->mlx, gam->win, 0, 0, 0x800000, p);
	if (gam->map[y][x] == 'e')
		print_str("YOU WIN\n");
	if (gam->map[y][x] == 'A')
		print_str("YOU LOST\n");
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

static int player_can_move(t_gam *gam, int x, int y)
{
	if (gam->map[y][x] == '1' || gam->map[y][x] == 'E')
		return (0);
	return (1);
}

int	a_event(int k, t_gam *gam)
{
	if (k == 65307)
		print_str("YOU ARE EXIT FROM THE GAME\n");
	if (!a_sersh(gam->map, 'P', &gam->p.y, &gam->p.x))
		return (0);
	if ((k == 65361) && player_can_move(gam, gam->p.x - 1, gam->p.y))// left
		plyr_movs(gam, gam->p.x - 1, gam->p.y, 0);
	if ((k == 65363) && player_can_move(gam, gam->p.x + 1, gam->p.y))//right
		plyr_movs(gam, gam->p.x + 1, gam->p.y, 1);
	if ((k == 65362) && player_can_move(gam, gam->p.x, gam->p.y - 1))//up
		plyr_movs(gam, gam->p.x, gam->p.y - 1, 2);
	if ((k == 65364) && player_can_move(gam, gam->p.x, gam->p.y + 1))//down
		plyr_movs(gam, gam->p.x, gam->p.y + 1, 3);
	if (a_sersh_n(gam->map, 'C') == 0
		&& a_sersh(gam->map, 'E', &gam->m_y, &gam->m_x))
	{
		gam->map[gam->m_y][gam->m_x] = 'e';
		put_img(gam, gam->m_x * 50, gam->m_y * 50, 'e');
	}
	return (k);
}
