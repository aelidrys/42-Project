/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:44:26 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:44:30 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_unblen(unsigned int n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*tab;
	size_t	i;

	i = ft_unblen(n);
	tab = (char *) ft_calloc(i + 1, sizeof(char));
	if (!tab)
		return (NULL);
	while (n)
	{
		tab[(i--) - 1] = (n % 10) + 48;
		n /= 10;
	}
	return (tab);
}
