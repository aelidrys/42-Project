/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:40:32 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:40:37 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printnbr_no_option(int n)
{
	ft_putlong_fd(n, 1);
	return (ft_nblen(n));
}

static int	ft_print_prefix(int n, t_option option, int len)
{
	int	res;

	res = 0;
	if (n < 0)
		res += ft_printchar_no_option('-');
	else if (option.prefix[0] == '+')
		res += ft_printchar_no_option('+');
	else if (option.prefix[0] == ' ')
		res += ft_printchar_no_option(' ');
	if (option.width > len && !option.justify)
		res += ft_putset(' ', option.width - len);
	else if (option.width > len && option.justify == '0')
		res += ft_putset('0', option.width - len);
	return (res);
}

int	ft_printnbr(int n, t_option option)
{
	int		len;
	int		res;
	char	*s;

	res = 0;
	len = ft_nblen(n);
	res += ft_print_prefix(n, option, len);
	s = ft_itoa(n);
	res += ft_putset('0', option.precision - len + (n < 0));
	res += ft_printstr_no_option(&s[(n < 0)]);
	if (option.width > len && option.justify == '-')
		res += ft_putset(' ', option.width - len);
	free(s);
	return (res);
}
