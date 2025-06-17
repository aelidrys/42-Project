/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_get_next_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:30:05 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/31 08:35:43 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	chek_line(char *p)
{
	size_t	x;

	x = 0;
	if (!p)
		return (0);
	while (p[x])
		if (p[x++] == '\n')
			return (x);
	return (0);
}

char	*ft_free(char *s, char *d)
{
	if (s)
		free(s);
	if (d)
		free(d);
	return (NULL);
}

char	*read_line(int fd, char *d)
{
	char	*s;
	int		x;

	x = 1;
	s = calloc(BUFFER_SIZE + 1, 1);
	while (1)
	{
		x = read(fd, s, BUFFER_SIZE);
		if (x == -1)
			return (ft_free(s, d));
		if (x == 0)
			break ;
		s[x] = '\0';
		d = ft_strjoin(d, s, x);
	}
	free(s);
	return (d);
}

char	*get_next_line(int fd)
{
	static char	*p;

	if (fd < 0)
		return (0);
	return (read_line(fd, p));
}
