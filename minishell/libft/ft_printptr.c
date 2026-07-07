/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:40:41 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:40:44 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_ptrlen(unsigned long long ptr)
{
	size_t	len;

	if (!ptr)
		return (1);
	len = 0;
	while (ptr)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}

int	ft_printptr(unsigned long long ptr, t_option option)
{
	int	res;

	res = ft_printstr_no_option("0x");
	res += ft_ptrlen(ptr);
	if (option.width > res && option.justify == '0')
		res += ft_putset('0', option.width - res);
	ft_putptr_fd(ptr, 1);
	if (option.width > res && option.justify == '-')
		res += ft_putset(' ', option.width - res);
	return (res);
}
