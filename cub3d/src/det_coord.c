/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   det_coord.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 08:58:20 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/22 11:24:53 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_coord_in_map_range(t_info *cub, int x, int y, int size)
{
	float	x1;
	float	y1;

	x1 = x / size;
	y1 = y / size;
	if (y1 <= 0 || x1 <= 0)
		return (0);
	if (y1 >= size_of_arry(cub->map) - 1
		|| x1 >= ft_strlen(cub->map[(int)y1]) - 1)
		return (0);
	return (1);
}

void	det_distance_r(t_point *p, t_info *cub)
{
	p->r = sqrt(pow((cub->x - p->x), 2) + pow((cub->y - p->y), 2));
	if (p->r == -2147483648)
		p->r = p->r + 1 * -1;
}

void	init_x_y(t_info *cub, t_point *p, int s, int size)
{
	if (s == 0)
	{
		p->x = cub->x;
		if (cub->x_d == -1)
		{
			p->dir = 'W';
			p->x = (floor(cub->x / size) * size) + size;
		}
		else
			p->dir = 'E';
	}
	if (s == 1)
	{
		p->y = cub->y;
		if (cub->y_d == -1)
		{
			p->dir = 'N';
			p->y = (floor(cub->y / size) * size) + size;
		}
		else
			p->dir = 'S';
	}
}

t_point	det_coord_y(t_info *cub, float cor_rad, char *str, int size)
{
	int		kx;
	t_point	p;

	init_x_y(cub, &p, 0, size);
	while (1)
	{
		kx = 0;
		if (cub->x_d == 1)
		{
			p.x = (floor(p.x / size) * size) + size;
			p.y = cub->y - ((p.x - cub->x) * tan(cor_rad));
		}
		if (cub->x_d == -1)
		{
			kx = 1;
			p.x -= size;
			p.y = cub->y + ((cub->x - p.x) * tan(cor_rad));
		}
		if (!is_coord_in_map_range(cub, p.x - (size * kx), p.y, size)
			|| prm_moves1(cub->map, str, (p.x / size) - kx, (p.y / size)))
			break ;
	}
	det_distance_r(&p, cub);
	return (p);
}

t_point	det_coord_x(t_info *cub, float cor_rd, char *str, int size)
{
	int		ky;
	t_point	p;

	init_x_y(cub, &p, 1, size);
	while (1)
	{
		ky = 0;
		if (cub->y_d == 1)
		{
			p.y = (floor(p.y / size) * size) + size;
			p.x = cub->x - ((p.y - cub->y) / tan(cor_rd));
		}
		if (cub->y_d == -1)
		{
			ky = 1;
			p.y -= size;
			p.x = cub->x + ((cub->y - p.y) / tan(cor_rd));
		}
		if (!is_coord_in_map_range(cub, p.x, p.y - (size * ky), size)
			|| prm_moves1(cub->map, str, (p.x / size), (p.y / size) - ky))
			break ;
	}
	det_distance_r(&p, cub);
	return (p);
}
