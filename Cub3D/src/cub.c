/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:22:27 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/22 10:32:49 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_var(t_info *cub)
{
	cub->stop_move = 0;
	cub->m_r = 0;
	cub->m_l = 0;
	cub->m_d = 0;
	cub->m_u = 0;
	cub->l_cor = 0;
	cub->r_cor = 0;
	cub->size = 100;
	cub->x = get_position(cub->map).x * cub->size + cub->size / 2;
	cub->y = get_position(cub->map).y * cub->size + cub->size / 2;
}

int	get_color(t_img *img, int x, int y)
{
	char	*dst;
	int		color;

	if (x < 0 || x >= img->width || y < 0 || y >= img->heigth)
		return (0);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(int *)dst;
	return (color);
}

int	is_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
		if (c == str[i++])
			return (1);
	return (0);
}

int	prm_moves1(char **map, char *str, int x, int y)
{
	if (is_in_str(str, map[y][x]))
		return (1);
	return (0);
}

void	start_cub(t_info *cub, char **av)
{
	check_name_map(av[1]);
	cub->mlx = malloc(sizeof(t_mlx));
	cub->big_img = malloc(sizeof(t_img));
	cub->img = NULL;
	cub->map0 = get_map(av[1]);
	check_first_element(cub->map0);
	cub->map = cub->map0 + 6;
	cheak_map(cub->map);
	check_cmp(cub->map);
	check_cmp_valid(cub->map);
	cub->mlx->ptr = mlx_init();
	cub->mlx->win = mlx_new_window(cub->mlx->ptr, 1200, 1000, "CUB");
	ft_init_var(cub);
	point_of_view(cub);
	store_info(cub->map0, cub);
	cub->big_img->ptr = mlx_new_image(cub->mlx->ptr, 1200, 1000);
	cub->big_img->addr = mlx_get_data_addr(cub->big_img->ptr,
			&cub->big_img->bits_per_pixel,
			&cub->big_img->line_length, &cub->big_img->endian);
}
