/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cub_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:13:25 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/21 10:52:20 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_myray(t_info *cub, float corner)
{
	int		r;
	double	cor_rd;
	float	x;
	float	y;

	cor_rd = ((M_PI * corner) / 180.0000);
	x = 175;
	y = 105;
	r = 0;
	while (r <= 20)
	{
		my_mlx_pixel_put(cub->mini_img, x, y, 0x00FDFD96);
		x = x + cos(cor_rd);
		y = y - sin(cor_rd);
		r++;
	}
}

void	draw_mini_ray(t_info *cub)
{
	float	cor_l;
	float	cor_r;

	cor_l = cub->corner - 30;
	cor_r = cub->corner + 30;
	while (cor_l <= cor_r)
	{
		draw_myray(cub, cor_l);
		cor_l++;
	}
}

void	print_image_square(t_info *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + M_G)
	{
		j = x;
		while (j < x + M_G)
		{
			my_mlx_pixel_put(data->mini_img, j, i, color);
			j++;
		}
		i++;
	}
}

void	print_mini_map(t_info *cub, t_var var, int x, int y)
{
	if ((y >= 0 && y < size_of_arry(cub->map)
			&& x <= ft_strlen(cub->map[y]) && x >= 0))
	{
		if (is_in_str("1hijklmnopqrst", cub->map[y][x]))
			print_image_square(cub, (x - var.s_x) * M_G,
				(y - var.s_y) * M_G, 0x00D3D3D3);
		else if ((cub->map[y][x] == '0' || cub->map[y][x] == 'N'
				|| cub->map[y][x] == 'W'
					|| cub->map[y][x] == 'S' || cub->map[y][x] == 'E'))
			print_image_square(cub, (x - var.s_x) * M_G,
				(y - var.s_y) * M_G, 0x0036454F);
		else if (is_in_str("abcdefg", cub->map[y][x]))
			print_image_square(cub, (x - var.s_x) * M_G,
				(y - var.s_y) * M_G, 0x000000CD);
		else
			print_image_square(cub, (x - var.s_x) * M_G,
				(y - var.s_y) * M_G, 0x00FF000080);
	}
	else
		print_image_square(cub, (x - var.s_x) * M_G,
			(y - var.s_y) * M_G, 0x00FF000080);
}

void	draw_mini_map(t_info *cub)
{
	t_var	var;

	var.org_x = cub->x / cub->size;
	var.org_y = cub->y / cub->size;
	var.x = 0;
	var.y = 0;
	var.s_x = var.org_x - 12;
	var.s_y = var.org_y - 7;
	var.end_x = var.org_x + 12;
	var.end_y = var.org_y + 7;
	var.y = var.s_y;
	while (var.y <= var.end_y)
	{
		var.x = var.s_x;
		while (var.x <= var.end_x)
		{
			print_mini_map(cub, var, var.x, var.y);
			var.x++;
		}
		(var.y++);
	}
	draw_mini_ray(cub);
	put_pix_mini(cub->mini_img, 175 - M_G / 2, 105 - M_G / 2, 0x00FF0000);
	mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win,
		cub->mini_img->ptr, 0, 0);
}
