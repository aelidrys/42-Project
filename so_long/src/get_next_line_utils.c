/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_get_next_line_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:42:37 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/31 08:32:58 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2, int a)
{
	char	*p;
	int		x;
	int		y;

	x = 0;
	y = 0;
	p = malloc(a_lent(s1) + a + 1 * sizeof(char));
	if (!p)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && s1[y])
		p[x++] = s1[y++];
	free(s1);
	y = 0;
	while (s2 && s2[y] && y < a)
		p[x++] = s2[y++];
	p[x] = '\0';
	return (p);
}

size_t	a_lent(char *s)
{
	size_t	a;

	a = 0;
	if (!s)
		return (0);
	while (s[a])
		a++;
	return (a);
}


char	*ft_strdup1(char *s1, int a, int j)
{
	char	*d;
	int		q;
	int		x;

	x = j;
	q = 0;
	d = malloc(a + 1 * sizeof(char));
	if (!d)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && s1[j] && q < a)
		d[q++] = s1[j++];
	if (x)
		free(s1);
	d[q] = '\0';
	return (d);
}

char	*ft_strdup(char *s1, int n, char **s)
{
	char	*d;
	int		q;

	q = 0;
	d = malloc(n + 1 * sizeof(char));
	if (!d || a_lent(s1) == 0)
	{
		if (d)
			free(d);
		free(s1);
		*s = NULL;
		return (NULL);
	}
	while (s1[q] && q < n)
	{
		d[q] = ((char *)s1)[q];
		q++;
	}
	free(s1);
	*s = NULL;
	d[q] = '\0';
	return (d);
}
