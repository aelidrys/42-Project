/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:42:53 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:42:57 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	if (!dstsize)
		return (ft_strlen(src));
	i = -1;
	while (src[++i] && (size_t)i < (dstsize - 1))
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}
