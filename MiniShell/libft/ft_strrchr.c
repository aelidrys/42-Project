/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:43:30 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:43:33 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	int		i;

	last = NULL;
	i = -1;
	while (s[++i])
		if (s[i] == (char) c)
			last = (char *) &s[i];
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	return (last);
}
