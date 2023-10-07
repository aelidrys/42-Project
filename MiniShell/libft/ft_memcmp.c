/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:39:10 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:39:13 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	signed int		i;

	str1 = (void *)s1;
	str2 = (void *)s2;
	i = -1;
	while ((size_t)++i < n)
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	return (0);
}
