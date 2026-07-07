/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:23:59 by abouassi          #+#    #+#             */
/*   Updated: 2022/10/29 17:32:36 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_freeall(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static int	check_nbword(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			word++;
		i++;
	}
	return (word);
}

static	char	**git_split(char **split, char *s, char c)
{
	size_t	j;
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			split[x] = malloc((j + 1) * sizeof(char));
			if (!split[x])
				return (ft_freeall(split));
			ft_strlcpy(split[x], &s[i], j + 1);
			x++;
			i = i + j;
		}
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		numword;
	int		i;
	int		x;

	if (!s)
	{
		return (NULL);
	}
	i = 0;
	x = 0;
	split = NULL;
	numword = check_nbword((char *)s, c);
	split = malloc((numword + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[numword] = 0;
	return (git_split(split, (char *)s, c));
}
