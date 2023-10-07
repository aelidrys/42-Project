/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:26:03 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/21 12:35:07 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_exit(void)
{
	write(1, "YOU ARE EXIT FROM CUB\n", 22);
	exit (0);
}

int	main(int ac, char **av)
{
	t_info	*cub;

	(void)ac;
	cub = malloc(sizeof(t_info));
	start_cub(cub, av);
	draw_cub3d(cub);
	mlx_hook(cub->mlx->win, 17, 0, ft_exit, NULL);
	mlx_hook(cub->mlx->win, 2, 0, a_event, cub);
	mlx_hook(cub->mlx->win, 3, 0, input_key_relese, cub);
	mlx_loop_hook(cub->mlx->ptr, draw_cub3d, cub);
	mlx_loop(cub->mlx->ptr);
}
