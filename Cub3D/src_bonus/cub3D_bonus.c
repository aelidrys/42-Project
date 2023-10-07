/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:27:29 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/21 20:26:19 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cheak_wall(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (is_in_str("1hjiklmnopqrts ", map[i]))
			i++;
		else
			ft_puterr("Error\ninvalid wall");
	}
}

void	check_s(char **map, int i, int j)
{
	if (ft_strlen(map[i - 1]) <= j || ft_strlen(map[i + 1]) <= j || j == 0)
		ft_puterr("Error\ninvalid position of character");
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' '
		|| map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
		ft_puterr("Error\ninvalid position of character");
}

void	cheak_map(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map[j])
		j++;
	cheak_wall(map[0]);
	cheak_wall(map[j - 1]);
	while (map[i + 1])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_in_str("1hjiklmnopqrts ", map[i][j]))
				check_s(map, i, j);
			j++;
		}
		i++;
	}
}

char	**get_map(char *file)
{
	int		fd;
	char	**map;
	char	*maping;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_puterr("Error\n in open file");
	}
	maping = get_next_line(fd);
	check_nwline(maping);
	map = ft_split(maping, '\n');
	return (map);
}
