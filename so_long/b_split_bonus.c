/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_split_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:53:36 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/31 08:32:11 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_so_long_bonus.h"

static	int	a_strnum(char const *s, char c)
{
	int		z;
	int		q;

	z = 0;
	q = 0;
	while (s[z] && s[z] == c)
		z++;
	while (s[z])
	{
		if (s[z] != c)
		{
			if (s[z + 1] == c || s[z + 1] == '\0')
				q++;
		}
		z++;
	}
	return (q);
}

static	int	a_copy(const char *s, char **p, char c)
{
	int	y;
	int	x;
	int	b;

	b = 0;
	while (*s)
	{
		x = 0;
		y = 0;
		while (*s && *s == c)
			s++;
		while (s[x] && s[x] != c)
			x++;
		if (x != 0)
		{
			p[b] = (char *)malloc((x + 1) * sizeof(char));
			if (!p[b])
				return (0);
			while (y < x)
				p[b][y++] = *((char *)s++);
			p[b++][y] = '\0';
		}
	}
	p[b] = NULL;
	return (1);
}

char	**spl(char const *s, char c)
{
	char	**p;
	int		x;

	x = 0;
	if (!s)
		return (NULL);
	p = (char **)malloc((a_strnum(s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	if (a_copy(s, p, c) == 0)
	{
		while (p[x])
			free(p[x++]);
		free(p);
		return (NULL);
	}
	return (p);
}

int	ft_exit(void)
{
	print_str("YOU ARE EXIT FROM THE GAME\n");
	return (0);
}
