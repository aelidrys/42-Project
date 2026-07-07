/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toulse3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:51:11 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/19 05:20:06 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	b_eat(t_var *var, t_philo *philo)
{
	sem_wait(var->sem_fork);
	b_print_msg(var, philo, "has taken a fork", 1);
	sem_wait(var->sem_fork);
	sem_wait(philo->var1->sem_1);
	gettimeofday(&philo->last_t_eat, NULL);
	sem_post(philo->var1->sem_1);
	b_print_msg(var, philo, "has taken a fork", 1);
	b_print_msg(var, philo, "is eating", 1);
	b_sleep(var->time_to_eat);
	sem_post(var->sem_fork);
	sem_post(var->sem_fork);
}

void	*b_is_died(void *phi1)
{
	t_philo	*philo;

	philo = (t_philo *)phi1;
	while (1)
	{
		sem_wait(philo->var1->sem_1);
		if (b_time_now() - (philo->last_t_eat.tv_sec * 1000
				+ philo->last_t_eat.tv_usec / 1000) >= philo->var1->time_to_die)
		{
			b_print_msg(philo->var1, philo, "is deid", 0);
			exit (1);
		}
		sem_post(philo->var1->sem_1);
	}
	return (0);
}

int	a_kill(t_var *var)
{
	int	x;

	x = -1;
	while (++x < var->n_of_philo)
		kill(var->pid[x], SIGKILL);
	return (0);
}
