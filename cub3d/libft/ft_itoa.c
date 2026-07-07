/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:29:54 by abouassi          #+#    #+#             */
/*   Updated: 2022/10/29 14:57:51 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_of_n(int n)
{
	int	k;

	k = 0;
	if (n < 0)
	{
		n *= -1;
		k++;
	}
	while (n > 0)
	{
		k++;
		n = n / 10;
	}
	return (k);
}

void	convert_n(char *dst, int len, int n)
{
	int	i;

	i = 0;
	dst[len] = '\0';
	if (n < 0)
	{
		dst[i] = '-';
		i++;
	}
	len--;
	if (n < 0)
		n *= -1;
	while (n > 0 && len >= 0)
	{
		dst[len] = (n % 10) + '0';
		n = n / 10;
		len --;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*dst;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = len_of_n(n);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	convert_n(dst, len, n);
	return (dst);
}
