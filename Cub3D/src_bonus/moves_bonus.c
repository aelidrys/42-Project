/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:42:41 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/22 08:44:10 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_coll(t_point p, t_info *data, t_var *var, int gd)
{
	float	cor;

	cor = var->cor_rd;
	if ((p.dir == 'S' || p.dir == 'N')
		&& is_coord_in_map_range(data, data->x + cos(cor) * gd,
			data->y, data->size))
		if (!prm_moves1(data->map, "1ahijklmnopqrts", (data->x + cos(cor) * gd)
				/ data->size, data->y / data->size))
			data->x = data->x + cos(cor) * gd;
	if ((p.dir == 'W' || p.dir == 'E')
		&& is_coord_in_map_range(data, data->x, data->y - sin(cor) * gd,
			data->size))
		if (!prm_moves1(data->map, "1ahijklmnopqrts", data->x / data->size,
				(data->y - sin(cor) * gd) / data->size))
			data->y = data->y - sin(cor) * gd;
}

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
	px = det_coord_x(data, var.cor_rd, "1abcdefghijklmnopqrts", size);
	py = det_coord_y(data, var.cor_rd, "1abcdefghijklmnopqrts", size);
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
	px = det_coord_x(data, var.cor_rd, "1abcdefghijklmnopqrts", size);
	py = det_coord_y(data, var.cor_rd, "1abcdefghijklmnopqrts", size);
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

	if (data->m_d == 0)
		return ;
	var.grid = MOVE_SPEED;
	var.cor_rd = ((M_PI * (data->corner - 180)) / 180.0000);
	var.check = 1;
	det_direction(data, var.cor_rd);
	px = det_coord_x(data, var.cor_rd, "1abcdefghijklmnopqrts", size);
	py = det_coord_y(data, var.cor_rd, "1abcdefghijklmnopqrts", size);
	if ((py.r) < (px.r))
		px = py;
	if (px.r <= 20)
		var.check = 0;
	else if (20 > px.r - MOVE_SPEED)
		var.grid = px.r - 19;
	if (var.check)
	{
		data->y = data->y - sin(var.cor_rd) * var.grid;
		data->x = data->x + cos(var.cor_rd) * var.grid;
	}
	else
		check_coll(px, data, &var, var.grid);
}

void	move_up(t_info *data, int size)
{
	t_var	var;
	t_point	px;
	t_point	py;

	if (data->m_u == 0)
		return ;
	var.grid = MOVE_SPEED;
	var.cor_rd = (M_PI * data->corner) / 180.0000;
	var.check = 1;
	det_direction(data, var.cor_rd);
	px = det_coord_x(data, var.cor_rd, "1abcdefghijklmnopqrts", size);
	py = det_coord_y(data, var.cor_rd, "1abcdefghijklmnopqrts", size);
	if ((py.r) < (px.r))
		px = py;
	if (px.r <= 20 && check_door_moves(data, &px))
		var.check = 0;
	else if (20 > px.r - MOVE_SPEED && check_door_moves(data, &px))
		var.grid = px.r - 19;
	if (var.check)
	{
		data->y = data->y - sin(var.cor_rd) * var.grid;
		data->x = data->x + cos(var.cor_rd) * var.grid;
	}
	else
		check_coll(px, data, &var, var.grid);
}
