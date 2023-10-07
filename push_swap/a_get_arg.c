/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_get_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:04:02 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/14 08:57:24 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_push_swap.h"

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

void	print_error(int x)
{
	if (x == -1)
		print_str("Error\ninvalid character\n");
	if (x == 2)
		print_str("Error\nduplicate number\n");
	if (x == -3)
		print_str("Error\nlarge number\n");
}

int	get_arg(t_var *var, char **av, int x, int y)
{
	char	**s;
	int		a;

	a = 0;
	y = -1;
	while (av[++y])
	{
		s = spl(av[y], ' ');
		if (s && !*s)
			print_str("Error\nempty string\n");
		x = -1;
		while (s[++x])
			add_back(&var->arg, new_node(s[x]));
		free(s);
	}
	return (check_arg(var, NULL));
}
