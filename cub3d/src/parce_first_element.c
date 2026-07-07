/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_first_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:20:40 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/18 22:09:24 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(char *str)
{
	write(2, "ERROR1\n", 7);
	while (str && *str)
		write(2, str++, 1);
	write(2, "\n", 1);
	exit(1);
}

void	chek_direction(char *str, char **direct)
{
	int		i;

	i = -1;
	while (direct && direct[++i])
	{
		if (str_comp(str, direct[i]))
		{
			free(direct[i]);
			direct[i] = ft_strdup("");
			break ;
		}
	}
	if (!direct || !direct[i])
		ft_error("the first elements not complete");
}

int	check_first_element(char **arry)
{
	int		i;
	char	**str;
	char	**direct;

	i = 0;
	direct = ft_split("NO SO WE EA C F", ' ');
	if (size_of_arry(arry) <= 6)
		ft_error("map not complete");
	while (arry && arry[i] && i < 6)
	{
		str = ft_split(arry[i++], ' ');
		if (size_of_arry(str) < 2)
			ft_error("");
		chek_direction(str[0], direct);
		ft_free(str);
	}
	ft_free(direct);
	return (1);
}
