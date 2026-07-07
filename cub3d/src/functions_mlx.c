/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:45:40 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/18 19:08:59 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_img*data, int x, int y, int color)
{
	char	*dst;

	if (x >= 350 || y >= 210)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_pix_mini(t_img*img, float x, float y, int color)
{
	float	i;
	float	j;

	i = y;
	while (i < y + M_G)
	{
		j = x;
		while (j < x + M_G)
		{
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

int	input_key(int key, t_info *cub)
{
	if (key == 2)
		cub->m_r = 1;
	if (key == 0)
		cub->m_l = 1;
	if (key == 125 || key == 1)
		cub->m_d = 1;
	if (key == 126 || key == 13)
		cub->m_u = 1;
	if (key == 53)
		exit(0);
	return (0);
}
