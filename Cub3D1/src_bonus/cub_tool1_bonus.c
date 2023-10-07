/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tool1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:01:55 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/21 08:14:29 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb_to_int(int color1, int color2, int color3)
{
	int	rgbtoint;

	rgbtoint = (color1 * 65536) + (color2 * 256) + color3;
	return (rgbtoint);
}

int	my_color(char *color)
{
	int		rgbtoint;
	char	**col;

	col = ft_split(color, ',');
	if (size_of_arry(col) != 3)
		ft_error("invalid rgb");
	rgbtoint = rgb_to_int(ft_atoi(col[0]), ft_atoi(col[1]), ft_atoi(col[2]));
	ft_free(col);
	return (rgbtoint);
}

void	point_of_view(t_info *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N')
				data->corner = 90;
			if (data->map[i][j] == 'E')
				data->corner = 0;
			if (data->map[i][j] == 'W')
				data->corner = 180;
			if (data->map[i][j] == 'S')
				data->corner = 270;
			j++;
		}
		i++;
	}
}

void	check_name_map(char *nmap)
{
	if (!nmap || ft_strcmp(&nmap[ft_strlen(nmap) - 4], ".cub") != 0)
	{
		ft_puterr("Erorr name\n");
	}
}

t_info	get_position(char **str)
{
	int		x;
	int		y;
	t_info	pos;

	x = 0;
	while (str[x])
	{
		y = 0;
		while (str[x][y])
		{
			if (str[x][y] == 'W' || str[x][y] == 'E'
				|| str[x][y] == 'N' || str[x][y] == 'S')
			{
				pos.y = x;
				pos.x = y;
				return (pos);
			}
			y++;
		}
		x++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}
