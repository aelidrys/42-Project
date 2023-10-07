/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:16:12 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/22 16:00:15 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put1(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1200 || y < 0 || y >= 1000)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	stop_movs(t_info *cub)
{
	cub->m_r = 0;
	cub->m_l = 0;
	cub->m_u = 0;
	cub->m_d = 0;
	cub->l_cor = 0;
	cub->r_cor = 0;
}

int	input_key_relese(int key, t_info *cub)
{
	if (key == 259)
		stop_movs(cub);
	if (key == 2)
		cub->m_r = 0;
	if (key == 0)
		cub->m_l = 0;
	if (key == 125 || key == 1)
		cub->m_d = 0;
	if (key == 126 || key == 13)
		cub->m_u = 0;
	if (key == 124)
		cub->l_cor = 0;
	if (key == 123)
		cub->r_cor = 0;
	return (0);
}

void	motion(t_info *cub)
{
	move_right(cub, cub->size);
	move_left(cub, cub->size);
	move_down(cub, cub->size);
	move_up(cub, cub->size);
	if (cub->l_cor == 1)
		cub->corner += 2;
	if (cub->r_cor == 1)
		cub->corner -= 2;
}

void	det_direction(t_info *cub, float cor_rd)
{
	if (cos(cor_rd) < 0)
		cub->x_d = -1;
	if (cos(cor_rd) >= 0)
		cub->x_d = 1;
	if (sin(cor_rd) > 0)
		cub->y_d = -1;
	if (sin(cor_rd) < 0)
		cub->y_d = 1;
}
