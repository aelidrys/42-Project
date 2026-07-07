/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toulse2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:35:03 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/19 05:19:42 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	b_new_philo(t_var *var, t_philo *philo, int x)
{
	philo->n = x;
	philo->y = 0;
	philo->th = malloc(sizeof(pthread_t));
	gettimeofday(&philo->last_t_eat, NULL);
	philo->var1 = var;
}

long	b_time_now(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	b_sleep(long time_2)
{
	long	time;

	time = b_time_now();
	while (b_time_now() - time < time_2)
		usleep(100);
}

void	b_sleeping(t_var *var, t_philo *philo)
{
	b_print_msg(var, philo, "is sleeping", 1);
	b_sleep(var->time_to_sleep);
}

void	b_print_msg(t_var *var, t_philo *philo, char *s, int x)
{
	sem_wait(var->sem_print);
	printf("%ld ms %d %s\n", b_time_now() - philo->start_time, philo->n, s);
	if (x)
		sem_post(var->sem_print);
}
