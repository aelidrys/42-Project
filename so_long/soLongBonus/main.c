/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_so_long_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:42:55 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/29 08:48:28 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	std_gam(t_gam *gam)
{
	int	x;
	int	y;

	y = 0;
	while (gam->map[y])
	{
		x = 0;
		while (gam->map[y][x])
		{
			if (gam->map[y][x] != 'P')
				put_img(gam, x * 50, y * 50, gam->map[y][x]);
			if (gam->map[y][x] == 'P')
				put_p(gam, x * 50, y * 50, 'N');
			x++;
		}
		y++;
	}
}

void	read_map(t_gam *gam, char *s, int fd)
{
	char	*p;
	int		x;

	x = 0;
	if (!s)
		print_str("no agrement\n");
	while (s[x])
		x++;
	x--;
	fd = open(s, O_RDONLY);
	if (fd == -1)
	{
		perror(s);
		exit (0);
	}
	if (x < 4 || s[x] != 'r' || s[x - 1] != 'e' || s[x - 2] != 'b'
		|| s[x - 3] != '.' || s[x - 4] == '/')
		print_str("invalid file_name\n");
	p = get_next_line(fd);
	if (!p)
		print_str("file is empty\n");
	gam->map = spl(p, '\n');
	print_error(check_map(gam, p));
	free(p);
}

int	main(int a, char **av)
{
	t_gam	gam;

	gam.m_x = 0;
	gam.m_y = 0;
	gam.x = 0;
	gam.n = 0;
	gam.n_sheps = 0;
	gam.movs = 0;
	gam.n_c = 0;
	read_map(&gam, av[1], a);
	gam.mlx = mlx_init();
	a_xpm_to_imge(&gam, 0, 0);
	gam.win = mlx_new_window(gam.mlx, a_lent(gam.map[0]) * 50,
	arg_lent(gam.map) * 50, "WOLF & SHEEP");
	std_gam(&gam);
	printf("Welcome to WOLF & SHEEP\n");
	gam.n_sheps = a_sersh_n(gam.map, 'C');
	enmy_pos(&gam, 0, 0);
	mlx_loop_hook(gam.mlx, a_animation, &gam);
	mlx_hook(gam.win, 2, (1L<<0), a_event, &gam);
	mlx_hook(gam.win, 17, (1L<<0), ft_exit, 0);
	mlx_loop(gam.mlx);
}
