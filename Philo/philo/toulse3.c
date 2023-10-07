/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toulse3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:09:44 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/18 07:48:44 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_var *var, t_philo *philo, char *s, int x)
{
	pthread_mutex_lock(&var->mutex_print);
	if (!x)
	{
		printf("%ld ms %d %s\n", ft_time_now() - var->current_time, philo->n, s);
		return ;
	}
	printf("%ld ms %d %s\n", ft_time_now() - var->current_time, philo->n, s);
	pthread_mutex_unlock(&var->mutex_print);
}

int	chek_finish(t_philo *philo, t_var *var)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	var->x = -1;
	while (++y < var->n_of_philo)
	{
		pthread_mutex_lock(&var->mutex_n_eat);
		if (philo[y].n_eating == 0)
			x++;
		if (x == var->n_of_philo)
			return (0);
		pthread_mutex_unlock(&var->mutex_n_eat);
	}
	return (1);
}

int	is_died(t_var *var, t_philo *philo)
{
	if (!var)
		return (0);
	philo = var->philo;
	while (1)
	{
		if (!chek_finish(philo, var))
		{
			pthread_mutex_lock(&var->mutex_print);
			return (0);
		}
		pthread_mutex_lock(&var->mutex_l_t_eat);
		var->x = -1;
		while (++var->x < var->n_of_philo)
		{
			if (ft_time_now() - philo[var->x].last_t_eat >= var->time_to_die)
			{
				print_msg(var, &philo[var->x], "died", 0);
				return (0);
			}
		}
		pthread_mutex_unlock(&var->mutex_l_t_eat);
	}
	return (0);
}

int	chek_numbers(t_var *var, int ac)
{
	if (var->n_of_eat <= 0 && ac == 6)
	{
		print_str("Error\nInvalid number\n");
		return (0);
	}
	if (var->n_of_philo <= 0 || var->time_to_die <= 0
		|| var->time_to_eat < 0 || var->time_to_sleep < 0)
	{
		print_str("Error\nInvalid number\n");
		return (0);
	}
	return (1);
}
