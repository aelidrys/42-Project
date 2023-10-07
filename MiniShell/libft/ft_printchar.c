/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:39:59 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:40:02 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printchar_no_option(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printchar(char c, t_option option)
{
	int	res;

	res = 0;
	if (option.width > 1 && option.justify == '0')
		res += ft_putset('0', option.width - 1);
	else if (option.width > 1 && option.justify != '-')
		res += ft_putset(' ', option.width - 1);
	res += ft_printchar_no_option(c);
	if (option.width > 1 && option.justify == '-')
		res += ft_putset(' ', option.width - 1);
	return (res);
}
