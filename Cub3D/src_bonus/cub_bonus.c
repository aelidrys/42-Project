/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:22:27 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/22 14:46:36 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_img(t_info *cub)
{
	cub->img_d = malloc(20 * sizeof(t_img *));
	cub->img_d[0] = new_img(cub, "door/d1.xpm", 'a');
	cub->img_d[1] = new_img(cub, "door/d2.xpm", 'b');
	cub->img_d[2] = new_img(cub, "door/d3.xpm", 'c');
	cub->img_d[3] = new_img(cub, "door/d4.xpm", 'd');
	cub->img_d[4] = new_img(cub, "door/d5.xpm", 'e');
	cub->img_d[5] = new_img(cub, "door/d6.xpm", 'f');
	cub->img_d[6] = new_img(cub, "door/d7.xpm", 'g');
	cub->img_d[7] = new_img(cub, "img/robot8.xpm", 'h');
	cub->img_d[8] = new_img(cub, "img/robot2.xpm", 'i');
	cub->img_d[9] = new_img(cub, "img/robot6.xpm", 'j');
	cub->img_d[10] = new_img(cub, "img/robot3.xpm", 'k');
	cub->img_d[11] = new_img(cub, "img/wpblckj.xpm", 'l');
	cub->img_d[12] = new_img(cub, "img/wpblckj.xpm", 'm');
	cub->img_d[13] = new_img(cub, "img/W_7.xpm", 'n');
	cub->img_d[14] = new_img(cub, "img/wpblck.xpm", 'o');
	cub->img_d[15] = new_img(cub, "img/stone_k.xpm", 'p');
	cub->img_d[16] = new_img(cub, "img/stone_s.xpm", 'q');
	cub->img_d[17] = new_img(cub, "img/stone_a.xpm", 'r');
	cub->img_d[18] = new_img(cub, "img/elevator.xpm", 's');
	cub->img_d[19] = new_img(cub, "img/W_6.xpm", 't');
}

void	ft_init_var(t_info *cub)
{
	cub->start = 0;
	cub->stop_move = 0;
	cub->corner = 0;
	cub->size = 100;
	cub->m_r = 0;
	cub->m_l = 0;
	cub->m_d = 0;
	cub->m_u = 0;
	cub->l_cor = 0;
	cub->r_cor = 0;
	cub->open_d = 0;
	cub->check_o_d = 1;
	cub->check_shot = 0;
	cub->numb_shot = 0;
	cub->change_wap = 0;
	cub->x = get_position(cub->map).x * cub->size + cub->size / 2;
	cub->y = get_position(cub->map).y * cub->size + cub->size / 2;
	ft_init_img(cub);
	point_of_view(cub);
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
	cub->mini_img = malloc(sizeof(t_img));
	cub->img = NULL;
	cub->map0 = get_map(av[1]);
	check_first_element(cub->map0);
	cub->map = cub->map0 + 6;
	cheak_map(cub->map);
	check_cmp(cub->map);
	check_cmp_valid(cub->map);
	cub->mlx->ptr = mlx_init();
	ft_init_var(cub);
	store_info(cub->map0, cub);
	cub->mlx->win = mlx_new_window(cub->mlx->ptr, 1200, 1000, "CUB");
	cub->mini_img->ptr = mlx_new_image(cub->mlx->ptr, 350, 210);
	cub->mini_img->addr = mlx_get_data_addr(cub->mini_img->ptr,
			&cub->mini_img->bits_per_pixel,
			&cub->mini_img->line_length, &cub->mini_img->endian);
	cub->big_img->ptr = mlx_new_image(cub->mlx->ptr, 1200, 1000);
	cub->big_img->addr = mlx_get_data_addr(cub->big_img->ptr,
			&cub->big_img->bits_per_pixel,
			&cub->big_img->line_length, &cub->big_img->endian);
}
