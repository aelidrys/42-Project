/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:11:20 by abouassi          #+#    #+#             */
/*   Updated: 2022/10/30 10:24:10 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*d;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	if (start > j || len <= 0)
		return (ft_strdup(""));
	if (len > j - start)
		len = j - start;
	d = (char *)malloc(len + 1);
	if (!d)
		return (NULL);
	while (i < len)
	{
		d[i] = s[start];
		i++;
		start++;
	}
	d[i] = '\0';
	return (d);
}
