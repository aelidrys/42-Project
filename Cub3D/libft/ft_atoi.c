/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:18:32 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/21 20:54:49 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puter(char *err)
{
	ft_putendl_fd(err, 2);
	exit(1);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strlen(str) <= 3 && ft_isdigit(str[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	rslt;

	i = 0;
	rslt = 0;
	sign = 1;
	if (is_number(str))
		ft_puter("Error  RGB not valid\n");
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rslt = (rslt * 10) + (str[i] - '0');
		i++;
	}
	if (rslt > 255)
		ft_puter("Error  this RGB size not valid\n");
	return ((rslt * sign));
}
