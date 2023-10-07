/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:26:03 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/22 11:26:35 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_exit(void)
{
	write(1, "YOU ARE EXIT FROM CUB\n", 22);
	exit (0);
}

int	draw_game(t_info *cub)
{
	if (cub->start == 0)
		return (0);
	motion(cub);
	draw_cub3d(cub);
	open_door(cub);
	return (0);
}

void	start_game(t_info *cub, float width, float heigth)
{
	int		x;
	int		y;
	t_img	*img;

	width = 0;
	img = new_img(cub, "img/start.xpm", 'A');
	x = 0;
	while (x < 1200)
	{
		heigth = 0;
		y = 0;
		while (y < 1000)
		{
			my_mlx_pixel_put1(cub->big_img, x, y,
				get_color(img, width, heigth));
			heigth += 0.1;
			y++;
		}
		width += 0.083;
		x++;
	}
	mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, cub->big_img->ptr,
		0, 0);
	free(img);
}

int	main(int ac, char **av)
{
	t_info	*cub;

	(void)ac;
	cub = malloc(sizeof(t_info));
	start_cub(cub, av);
	get_xpm_file(cub);
	start_game(cub, 0, 0);
	mlx_hook(cub->mlx->win, 17, 0, ft_exit, NULL);
	mlx_hook(cub->mlx->win, 2, 0, a_event, cub);
	mlx_hook(cub->mlx->win, 3, 0, input_key_relese, cub);
	mlx_hook(cub->mlx->win, 6, 0, mouse_view, cub);
	mlx_loop_hook(cub->mlx->ptr, draw_game, cub);
	mlx_loop(cub->mlx->ptr);
}
