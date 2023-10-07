/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:44:47 by abouassi          #+#    #+#             */
/*   Updated: 2022/10/30 17:29:54 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*s1;

	s1 = (char *)str;
	i = ft_strlen(s1);
	if ((char)c == '\0')
	{
		return (&s1[i]);
	}
	while (i >= 0)
	{
		if (s1[i] == (char)c)
		{
			return (&s1[i]);
		}
		i--;
	}
	return (0);
}
