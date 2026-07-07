/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wapean_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:21:39 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/22 15:59:11 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	draw_wapeans(t_info *cub)
{
	if (!cub->check_shot && cub->change_wap == 0)
		draw_wap(cub, cub->mlx->i_w0, 400, 600);
	else if (!cub->check_shot && cub->change_wap == 1)
		draw_wap(cub, cub->mlx->k_0, 400, 600);
	if (cub->check_shot)
	{
		cub->numb_shot++;
		if (cub->change_wap == 0)
			put_pistol(cub);
		else if (cub->change_wap == 1)
			put_knife(cub);
		if (cub->numb_shot == 12)
		{
			cub->numb_shot = 0;
			cub->check_shot = 0;
		}
	}
	return (0);
}

void	change_wap(t_info *cub)
{
	if (cub->change_wap == 0)
	{
		mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win,
			cub->mlx->i_c, 1000, 0);
	}
	if (cub->change_wap == 1)
	{
		mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win,
			cub->mlx->i_c1, 1000, 0);
	}
}

void	draw_wap(t_info *cub, void *img, int x, int y)
{
	mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, img, x, y);
}

void	put_pistol(t_info *cub)
{
	if (cub->numb_shot == 1 || cub->numb_shot == 2)
		draw_wap(cub, cub->mlx->i_w1, 400, 600);
	if (cub->numb_shot == 3 || cub->numb_shot == 4)
		draw_wap(cub, cub->mlx->i_w2, 400, 600);
	if (cub->numb_shot == 5 || cub->numb_shot == 6)
		draw_wap(cub, cub->mlx->i_w3, 400, 600);
	if (cub->numb_shot == 7 || cub->numb_shot == 8)
		draw_wap(cub, cub->mlx->i_w3, 400, 600);
	if (cub->numb_shot == 9 || cub->numb_shot == 10)
		draw_wap(cub, cub->mlx->i_w1, 400, 600);
	if (cub->numb_shot == 11 || cub->numb_shot == 12)
		draw_wap(cub, cub->mlx->i_w0, 400, 600);
}

void	put_knife(t_info *cub)
{
	if (cub->numb_shot == 1 || cub->numb_shot == 2)
		draw_wap(cub, cub->mlx->k_1, 400, 600);
	if (cub->numb_shot == 3 || cub->numb_shot == 4)
		draw_wap(cub, cub->mlx->k_2, 400, 600);
	if (cub->numb_shot == 5 || cub->numb_shot == 6)
		draw_wap(cub, cub->mlx->k_3, 400, 600);
	if (cub->numb_shot == 7 || cub->numb_shot == 8)
		draw_wap(cub, cub->mlx->k_3, 400, 600);
	if (cub->numb_shot == 9 || cub->numb_shot == 10)
		draw_wap(cub, cub->mlx->k_1, 400, 600);
	if (cub->numb_shot == 11 || cub->numb_shot == 12)
		draw_wap(cub, cub->mlx->k_0, 400, 600);
}
