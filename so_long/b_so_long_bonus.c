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

#include "b_so_long_bonus.h"

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
				put_img(gam, x * 70, y * 70, gam->map[y][x]);
			if (gam->map[y][x] == 'P')
				put_p(gam, x * 70, y * 70, 'N');
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

	gam.n = 0;
	read_map(&gam, av[1], a);
	gam.mlx = mlx_init();
	a_xpm_to_imge(&gam, 0, 0);
	gam.win = mlx_new_window(gam.mlx, a_lent(gam.map[0]) * 70,
			arg_lent(gam.map) * 70, "WOLF & SHEEP");
	std_gam(&gam);
	enmy_pos(&gam, 0, 0);
	mlx_loop_hook(gam.mlx, a_animation, &gam);
	mlx_hook(gam.win, 2, 40, a_event, &gam);
	mlx_hook(gam.win, 17, 0, ft_exit, 0);
	mlx_loop(gam.mlx);
}
