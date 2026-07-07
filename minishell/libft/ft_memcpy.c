/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:39:16 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:39:19 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;
	int		i;

	if (!dst && !src)
		return (NULL);
	d = dst;
	s = (void *)src;
	i = -1;
	while ((size_t)++i < n)
		d[i] = s[i];
	return (d);
}
