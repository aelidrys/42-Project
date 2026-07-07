/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:10:04 by abouassi          #+#    #+#             */
/*   Updated: 2022/10/30 17:04:38 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	s_size;
	size_t	d_size;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	s_size = ft_strlen(src);
	d_size = ft_strlen(dst);
	i = 0;
	j = 0;
	i = d_size;
	if (d_size >= dstsize)
		return (dstsize + s_size);
	while (i < dstsize - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (s_size + d_size);
}
