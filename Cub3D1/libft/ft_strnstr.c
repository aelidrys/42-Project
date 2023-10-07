/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 08:51:41 by abouassi          #+#    #+#             */
/*   Updated: 2022/10/30 16:07:24 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hay;
	char	*nee;

	if (!haystack && len == 0)
		return (NULL);
	hay = (char *)haystack;
	nee = (char *)needle;
	i = 0;
	if (!nee[i])
		return (hay);
	while (i < len && hay[i] != '\0')
	{
		j = 0;
		while (hay[i + j] == nee[j] && nee[j] != '\0')
		{
			if (nee[j + 1] == '\0' && j < len - i)
				return (&hay[i]);
			j++;
		}
		i++;
	}
	return (0);
}
