/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:30:14 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/18 14:16:00 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	free(str);
}

int	str_comp(char *s1, char *s2)
{
	size_t	x;

	x = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[x] && s2[x])
	{
		if (s1[x] != s2[x])
			return (0);
		x++;
	}
	if (s1[x] != s2[x])
		return (0);
	return (1);
}

char	**get_element(char *str)
{
	int		i;
	int		j;
	char	**elm;

	if (!str)
		return (0);
	elm = malloc(3 * sizeof(char *));
	i = 0;
	while (str && str[i] == ' ')
		i++;
	j = i;
	while (str && str[j] != ' ')
		j++;
	elm[0] = malloc(j + 1 * sizeof(char));
	j = 0;
	while (str && str[i] != ' ')
		elm[0][j++] = str[i++];
	while (str && str[i] == ' ')
		i++;
	elm[1] = ft_strdup(str + i);
	elm[2] = NULL;
	return (elm);
}

int	size_of_arry(char **arry)
{
	int	size;

	size = 0;
	while (arry && arry[size])
		size++;
	return (size);
}
