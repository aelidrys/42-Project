/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:42:41 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/22 10:35:29 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_right(t_info *data, int size)
{
	t_var	var;
	t_point	px;
	t_point	py;
	int		grid;

	if (data->m_r == 0)
		return ;
	grid = MOVE_SPEED;
	var.check = 1;
	var.cor_rd = ((M_PI * (data->corner + 90)) / 180.0000);
	det_direction(data, var.cor_rd);
	px = det_coord_x(data, var.cor_rd, "1", size);
	py = det_coord_y(data, var.cor_rd, "1", size);
	if ((py.r) < (px.r))
		px = py;
	if (px.r <= 20)
		var.check = 0;
	else if (20 > px.r - MOVE_SPEED)
		grid = px.r - 20;
	if (var.check)
	{
		data->x = data->x + cos(var.cor_rd) * grid;
		data->y = data->y - sin(var.cor_rd) * grid;
	}
}

void	move_left(t_info *data, int size)
{
	t_var	var;
	t_point	px;
	t_point	py;
	int		grid;

	if (data->m_l == 0)
		return ;
	grid = MOVE_SPEED;
	var.check = 1;
	var.cor_rd = ((M_PI * (data->corner - 90)) / 180.0000);
	det_direction(data, var.cor_rd);
	px = det_coord_x(data, var.cor_rd, "1", size);
	py = det_coord_y(data, var.cor_rd, "1", size);
	if ((py.r) < (px.r))
		px = py;
	if (px.r <= 20)
		var.check = 0;
	else if (20 > px.r - MOVE_SPEED)
		grid = px.r - 20;
	if (var.check)
	{
		data->x = data->x + cos(var.cor_rd) * grid;
		data->y = data->y - sin(var.cor_rd) * grid;
	}
}

void	move_down(t_info *data, int size)
{
	t_var	var;
	t_point	px;
	t_point	py;
	int		grid;

	if (data->m_d == 0)
		return ;
	grid = MOVE_SPEED;
	var.cor_rd = ((M_PI * (data->corner - 180)) / 180.0000);
	var.check = 1;
	det_direction(data, var.cor_rd);
	px = det_coord_x(data, var.cor_rd, "1", size);
	py = det_coord_y(data, var.cor_rd, "1", size);
	if ((py.r) < (px.r))
		px = py;
	if (px.r <= 20)
		var.check = 0;
	else if (20 > px.r - MOVE_SPEED)
		grid = px.r - 20;
	if (var.check)
	{
		data->y = data->y - sin(var.cor_rd) * grid;
		data->x = data->x + cos(var.cor_rd) * grid;
	}
}

void	move_up(t_info *data, int size)
{
	t_var	var;
	t_point	px;
	t_point	py;
	int		grid;

	if (data->m_u == 0)
		return ;
	grid = MOVE_SPEED;
	var.cor_rd = (M_PI * data->corner) / 180.0000;
	var.check = 1;
	det_direction(data, var.cor_rd);
	px = det_coord_x(data, var.cor_rd, "1", size);
	py = det_coord_y(data, var.cor_rd, "1", size);
	if ((py.r) < (px.r))
		px = py;
	if (px.r <= 20)
		var.check = 0;
	else if (20 > px.r - MOVE_SPEED)
		grid = px.r - 20;
	if (var.check)
	{
		data->y = data->y - sin(var.cor_rd) * grid;
		data->x = data->x + cos(var.cor_rd) * grid;
	}
}
