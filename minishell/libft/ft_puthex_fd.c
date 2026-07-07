/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:41:19 by yrimah            #+#    #+#             */
/*   Updated: 2023/01/08 12:41:22 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_puthex_fd(unsigned int n, int fd, int uppercase)
{
	if (n > 15)
	{
		ft_puthex_fd(n / 16, fd, uppercase);
		ft_puthex_fd(n % 16, fd, uppercase);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + 48, fd);
		else
		{
			if (uppercase)
				ft_putchar_fd(n - 10 + 65, fd);
			else
				ft_putchar_fd(n - 10 + 97, fd);
		}
	}
}
