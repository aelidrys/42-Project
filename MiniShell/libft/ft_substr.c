/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:43:47 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:43:50 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	int		i;
	size_t	j;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if ((unsigned int) slen < start)
		return (ft_strdup("\0"));
	else if (len > slen)
		tab = (char *) ft_calloc(slen + 1, sizeof(char));
	else
		tab = (char *) ft_calloc(len + 1, sizeof(char));
	if (!tab)
		return (NULL);
	j = 0;
	i = -1;
	while (s[++i])
		if (start <= (unsigned int) i && j < len)
			tab[j++] = s[i];
	return (tab);
}
