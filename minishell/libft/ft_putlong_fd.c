/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:41:28 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:41:32 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putlong_fd(long long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd(45, fd);
		ft_putlong_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putlong_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + 48, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}
