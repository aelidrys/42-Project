/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:27:39 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/18 18:46:50 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_cmp(char **map)
{
	int	i;
	int	j;
	int	check;

	check = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'N' || map[i][j] == 'S')
			{
				if (check)
					ft_puterr("Error");
				check++;
			}
			j++;
		}
		i++;
	}
	if (!check)
		ft_puterr("Error\n<!> no PLAYER <!>");
}

void	check_cmp_valid(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_in_str("0 1NSEW", map[i][j]))
			{
				ft_puterr("Error");
			}
			j++;
		}
		i++;
	}
}

void	check_mult_new(char *map, int i)
{
	while (map[i] && map[i] == '\n')
	{
		i++;
	}
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
		{
			ft_puterr("Error");
		}
		i++;
	}
}

void	check_nwline(char *map)
{
	int	i;
	int	check;
	int	k;

	k = 0;
	check = 0;
	i = 0;
	while (map[i])
	{
		while (map[i] && map[i] != '\n')
		{
			i++;
			k++;
		}
		if (k != 0)
			check++;
		k = 0;
		if (!map[i] || check == 6)
			break ;
		i++;
	}
	check_mult_new(map, i);
}

void	store_info(char **map, t_info *cub)
{
	int		i;
	char	**line;

	cub->img = NULL;
	i = 0;
	while (i < 6)
	{
		line = get_element(map[i]);
		if (!ft_strncmp(line[0], "NO", 2))
			add_img(&cub->img, new_img(cub, line[1], 'N'));
		if (!ft_strncmp(line[0], "SO", 2))
			add_img(&cub->img, new_img(cub, line[1], 'S'));
		if (!ft_strncmp(line[0], "WE", 2))
			add_img(&cub->img, new_img(cub, line[1], 'W'));
		if (!ft_strncmp(line[0], "EA", 2))
			add_img(&cub->img, new_img(cub, line[1], 'E'));
		if (!ft_strncmp(line[0], "F", 1))
			cub->f = my_color(line[1]);
		if (!ft_strncmp(line[0], "C", 1))
			cub->c = my_color(line[1]);
		ft_free(line);
		i++;
	}
}
