/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_get_next_line_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:30:05 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/15 14:25:59 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_push_swap_bonus.h"

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

int	newlin_check1(char *d, int a)
{
	if (d[a + 1] != 'a' && d[a + 1] != 'b' && d[a + 1] != 'r')
		return (0);
	if ((d[a + 1] == 'a' || d[a + 1] == 'b') && d[a + 2] != '\n')
		return (0);
	if ((d[a + 1] == 'r' && d[a + 2] != 'a' && d[a + 2] != 'b'
			&& d[a + 2] != '\n' && d[a + 2] != 'r')
		|| ((d[a + 2] == 'r' || d[a + 2] == 'a' || d[a + 2] == 'b')
			&& d[a + 3] != '\n'))
		return (0);
	return (1);
}

int	newlin_check(char *d, char *s, int a)
{
	if (s && *s == '\n')
	{
		a = a_lent(d) - 1;
		if (d[a] && d[a] == '\n')
			a--;
		if (a == -1 || d[a] == '\n')
			return (0);
		while (a > 0 && d[a - 1] != '\n')
			a--;
		if (d[a] && d[a] != 'r' && d[a] != 's' && d[a] != 'p')
			return (0);
		if ((d[a] && d[a] == 'p' && d[a + 1] != 'b' && d[a + 1] != 'a')
			|| (d[a] && d[a] == 'p' && d[a + 1] && d[a + 2] != '\n'))
			return (0);
		if ((d[a] && d[a] == 's' && d[a + 1] != 'a' && d[a + 1] != 'b'
				&& d[a + 1] != 's') || (d[a] && d[a] == 's' && d[a + 1]
				&& d[a + 2] != '\n'))
			return (0);
		if (d[a] && d[a] == 'r')
			return (newlin_check1(d, a));
	}
	return (1);
}

char	*get_next_line(int fd, char *d, char *s, int x)
{
	if (fd < 0)
		return (0);
	s = malloc(2 * sizeof(char));
	while (1)
	{
		x = read(fd, s, 1);
		if (x == -1)
		{
			free(s);
			free(d);
			return (NULL);
		}
		if (x == 0)
			break ;
		s[x] = '\0';
		d = ft_strjoin(d, s, x);
		if (!newlin_check(d, s, 0))
		{
			free(s);
			free(d);
			print_str_b("Error\n");
		}
	}
	free(s);
	return (d);
}
