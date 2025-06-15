/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_mlx_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:45:40 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/22 12:40:46 by aelidrys         ###   ########.fr       */
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
	printf("color>>24 = %d",color>>24)

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

void	get_xpm_file(t_info *cub)
{
	int	h;
	int	w;

	cub->mlx->i_w0 = mlx_xpm_file_to_image(cub->mlx->ptr, "w/p_0.xpm", &w, &h);
	cub->mlx->i_w1 = mlx_xpm_file_to_image(cub->mlx->ptr, "w/p_1.xpm", &w, &h);
	cub->mlx->i_w2 = mlx_xpm_file_to_image(cub->mlx->ptr, "w/p_2.xpm", &w, &h);
	cub->mlx->i_w3 = mlx_xpm_file_to_image(cub->mlx->ptr, "w/p_3.xpm", &w, &h);
	cub->mlx->i_c = mlx_xpm_file_to_image(cub->mlx->ptr, "w/icn.xpm", &w, &h);
	cub->mlx->i_c1 = mlx_xpm_file_to_image(cub->mlx->ptr, "w/icn1.xpm", &w, &h);
	cub->mlx->k_0 = mlx_xpm_file_to_image(cub->mlx->ptr, "w/k_0.xpm", &w, &h);
	cub->mlx->k_1 = mlx_xpm_file_to_image(cub->mlx->ptr, "w/k_1.xpm", &w, &h);
	cub->mlx->k_2 = mlx_xpm_file_to_image(cub->mlx->ptr, "w/k_2.xpm", &w, &h);
	cub->mlx->k_3 = mlx_xpm_file_to_image(cub->mlx->ptr, "w/k_3.xpm", &w, &h);
	cub->mlx->p_s = new_img(cub, "w/p_s.xpm", 'z');
	remove_bground(cub->mlx->p_s, 1);
	// remove_bground(cub->mlx->p_s, 2);
}

int	mouse_view(int x, int y, t_info *cub)
{
	if (cub->start == 0)
		return (0);
	if (x < 0 || x > 1200 || y < 0 || y > 1000)
		return (0);
	if (x > cub->x_mouse)
		cub->corner += 10;
	if (x < cub->x_mouse)
		cub->corner -= 10;
	cub->x_mouse = x;
	cub->y_mouse = y;
	return (0);
}

int	input_key(int key, t_info *cub)
{
	if (key == 65307)
		exit(0);
	if (!cub->start)
		return (0);
	if (key == 100)
		cub->m_r = 1;
	if (key == 97)
		cub->m_l = 1;
	if (key == 65364 || key == 115)
		cub->m_d = 1;
	if (key == 65362 || key == 119)
		cub->m_u = 1;
	return (0);
}
