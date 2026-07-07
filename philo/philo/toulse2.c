/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toulse2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:53:32 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/16 09:22:22 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	new_philo(t_var *var, t_philo *philo, int x)
{
	philo->n = x;
	philo->n_eating = var->n_of_eat;
	philo->last_t_eat = ft_time_now();
	philo->rhit_f = var->x++;
	if (var->x >= var->n_of_philo)
		var->x = 0;
	philo->left_f = var->x;
	philo->var1 = var;
}

void	eat(t_var *var, t_philo *philo)
{
	if (!var || !philo)
		return ;
	pthread_mutex_lock(&var->mutex_f[philo->left_f]);
	print_msg(var, philo, "has taken a fork", 1);
	pthread_mutex_lock(&var->mutex_f[philo->rhit_f]);
	print_msg(var, philo, "has taken a fork", 1);
	print_msg(var, philo, "is eating", 1);
	pthread_mutex_lock(&var->mutex_l_t_eat);
	philo->last_t_eat = ft_time_now();
	pthread_mutex_unlock(&var->mutex_l_t_eat);
	ft_usleep(var->time_to_eat);
	pthread_mutex_lock(&var->mutex_n_eat);
	philo->n_eating--;
	pthread_mutex_unlock(&var->mutex_n_eat);
	pthread_mutex_unlock(&var->mutex_f[philo->rhit_f]);
	pthread_mutex_unlock(&var->mutex_f[philo->left_f]);
}

long	ft_time_now(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_usleep(long time_2)
{
	long	time;

	time = ft_time_now();
	while (ft_time_now() - time < time_2)
		usleep(100);
}

void	a_sleep(t_var *var, t_philo *philo)
{
	print_msg(var, philo, "is sleeping", 1);
	ft_usleep(var->time_to_sleep);
}
