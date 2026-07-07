/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:40:58 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:41:01 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printunbr_no_option(unsigned int n)
{
	int		res;
	char	*tab;

	if (!n)
		return (ft_printchar_no_option('0'));
	tab = ft_uitoa(n);
	res = ft_printstr_no_option(tab);
	free(tab);
	return (res);
}

static int	ft_print_prefix(t_option option, int len)
{
	int	res;

	res = 0;
	if (option.width > len && !option.justify)
		res += ft_putset(' ', option.width - len);
	else if (option.width > len && option.justify == '0')
		res += ft_putset('0', option.width - len);
	return (res);
}

static int	ft_reused_part(char *s, t_option option, int len)
{
	int	res;

	res = 0;
	res += ft_print_prefix(option, len);
	res += ft_putset('0', option.precision - len);
	res += ft_printstr_no_option(s);
	if (option.width > len && option.justify == '-')
		res += ft_putset(' ', option.width - len);
	return (res);
}

int	ft_printunbr(unsigned int n, t_option option)
{
	int		len;
	int		res;
	char	*s;

	if (!n)
		return (ft_reused_part("0", option, 1));
	s = ft_uitoa(n);
	len = ft_strlen(s);
	res = ft_reused_part(s, option, len);
	free(s);
	return (res);
}
