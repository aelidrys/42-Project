/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:29:23 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/22 12:40:02 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_walls(t_info *cub, t_point p)
{
	int	a;
	int	i;
	int	start;

	i = 0;
	a = (cub->size / (p.r * fabs(cos(((cub->r_corner - cub->corner) * M_PI)
						/ 180)))) * 500;
	if (p.dir == 'N')
		draw_north_walls(cub, p, a);
	if (p.dir == 'S')
		draw_south_walls(cub, p, a);
	if (p.dir == 'E')
		draw_east_walls(cub, p, a);
	if (p.dir == 'W')
		draw_west_walls(cub, p, a);
	if (a >= 500)
		a = 500;
	start = (1000 - a * 2) / 2;
	while (i <= start)
	{
		my_mlx_pixel_put1(cub->big_img, cub->width, i, cub->c);
		my_mlx_pixel_put1(cub->big_img, cub->width, 500 + a + i++, cub->f);
	}
}

t_point	ray_cast(t_info *cub, float cor_rad, char *str)
{
	t_point	px;
	t_point	py;

	det_direction(cub, cor_rad);
	px = det_coord_x(cub, cor_rad, str, cub->size);
	py = det_coord_y(cub, cor_rad, str, cub->size);
	if (px.r > py.r)
		px = py;
	return (px);
}

int	rays_casting(t_info *cub, float corner, char *str)
{
	t_point	p;
	float	cor_rad;

	corner = cub->corner + 30;
	cub->r_corner = cub->corner - 30;
	cub->width = 0;
	while (corner >= cub->r_corner)
	{
		cor_rad = (M_PI * cub->r_corner) / 180.0;
		p = ray_cast(cub, cor_rad, str);
		draw_walls(cub, p);
		cub->r_corner += 0.05;
		cub->width++;
	}
	return (0);
}

int	a_event(int key, t_info *cub)
{
	if (key == 49)
		cub->start = 1;
	input_key(key, cub);
	if (cub->start == 0)
		return (0);
	if ((int)cub->corner == 360)
		cub->corner = 0;
	if (key == 124)
		cub->l_cor = 1;
	if (key == 123)
		cub->r_cor = 1;
	if (key == 48)
		cub->check_shot = 1;
	if (key == 6)
	{
		if (cub->change_wap == 1)
			cub->change_wap = 0;
		else
			cub->change_wap++;
	}
	if (key == 259)
		stop_movs(cub);
	motion(cub);
	return (0);
}

int	draw_cub3d(t_info *cub)
{
	rays_casting(cub, 0, "1ahijklmnopqrts");
	mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, cub->big_img->ptr,
		0, 0);
	rays_casting(cub, 0, "1abcdefghijklmnopqrts");
	mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, cub->big_img->ptr,
		0, 0);
	change_wap(cub);
	mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, cub->mlx->p_s,
		580, 480);
	if (!cub->check_shot && !cub->change_wap)
		mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, cub->mlx->i_w0,
			400, 600);
	if (!cub->check_shot && cub->change_wap)
		mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, cub->mlx->k_0,
			400, 600);
	draw_mini_map(cub);
	draw_wapeans(cub);
	return (0);
}
