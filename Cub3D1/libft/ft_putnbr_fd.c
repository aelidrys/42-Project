/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 09:42:17 by abouassi          #+#    #+#             */
/*   Updated: 2022/11/01 15:18:53 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	nn;

	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
			nn = -nb;
	}
	else
		nn = nb;
	if (nn > 9)
	{
		ft_putnbr_fd((nn / 10), fd);
		nn %= 10;
	}
	ft_putchar_fd((nn + '0'), fd);
}
