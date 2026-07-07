/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:41:18 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/22 12:51:37 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	a_strlen(char *s)
{
	size_t	x;

	x = 0;
	if (!s)
		return (0);
	while (s[x])
		x++;
	return (x);
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

int	ft_comper(char *min_str, char *str)
{
	size_t	x;

	x = 0;
	if (!min_str || !str)
		return (0);
	while (str[x] && min_str[x] && str[x] == min_str[x])
	{
		if (str[x] != min_str[x])
			break ;
		x++;
	}
	if (str[x] >= min_str[x])
		return (1);
	return (0);
}

char	*a_strjoin(char *s1, char *s2, int s, int x)
{
	char	*d;

	x = 0;
	if (!s1 && !s2)
		return (0);
	d = malloc((a_strlen(s1) + a_strlen(s2) + 2) * sizeof(char));
	while (s1 && s1[x])
	{
		d[x] = s1[x];
		x++;
	}
	if (s == 1)
		free(s1);
	if (s == 2)
		d[x++] = '/';
	while (s2 && *s2)
		d[x++] = *(s2++);
	d[x] = '\0';
	return (d);
}

int	str_to_int(char *s)
{
	char			*p;
	unsigned long	res;
	int				sing;

	res = 0;
	sing = 1;
	p = s;
	while (s && *s == ' ' && *(s + 1))
		s++;
	if (s && (*s == '+' || *s == '-') && *(s + 1))
	{
		if (*(s++) == '-')
			sing *= -1;
	}
	while (res <= 9223372036854775807 && s && *s >= '0' && *s <= '9')
		res = res * 10 + (*(s++) - 48);
	while (s && *s == ' ')
		s++;
	if ((sing == -1 && res - 1 > 9223372036854775807)
		|| (sing == 1 && res > 9223372036854775807))
	{
		a_printf("minishell: exit: %s: %s\n", p, "numeric argument required", 2);
		return (255);
	}
	return (sing * res);
}
