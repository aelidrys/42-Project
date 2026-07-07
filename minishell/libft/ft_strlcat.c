/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:42:47 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:42:50 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dsize;
	size_t	ssize;
	size_t	res;

	dsize = ft_strlen(dst);
	ssize = ft_strlen(src);
	if (dsize < dstsize)
		res = ssize + dsize;
	else
		res = ssize + dstsize;
	if (!dstsize)
		return (res);
	i = 0;
	while ((dsize + i < dstsize - 1) && src[i])
	{
		dst[dsize + i] = src[i];
		i++;
	}
	dst[dsize + i] = '\0';
	return (res);
}
