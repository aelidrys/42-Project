/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:48:32 by abouassi          #+#    #+#             */
/*   Updated: 2023/06/07 09:53:40 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line(int fd, char *str)
{
	char	*buff;
	int		ret;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[ret] = '\0';
		str = ft_strjoin_get(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ptr = read_line(fd, ptr);
	if (!ptr)
		return (NULL);
	return (ptr);
}
