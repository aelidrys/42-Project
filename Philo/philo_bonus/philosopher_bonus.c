/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:11:43 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/19 05:18:31 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	b_start_simulation(t_var *var, t_philo *philo, char **av, int ac)
{
	if ((ac != 5 && ac != 6) || !b_check_arg(av, 1))
		return (0);
	var->n_of_philo = b_str_to_int(av[1]);
	var->time_to_die = b_str_to_int(av[2]);
	var->time_to_eat = b_str_to_int(av[3]);
	var->time_to_sleep = b_str_to_int(av[4]);
	var->n_of_eat = -1;
	if (ac == 6)
		var->n_of_eat = b_str_to_int(av[5]);
	if (!b_chek_numbers(var, ac))
		return (0);
	philo = malloc(var->n_of_philo * sizeof(t_philo));
	var->th = malloc(var->n_of_philo * sizeof(pthread_t));
	var->pid = malloc(var->n_of_philo * sizeof(pid_t));
	ac = -1;
	while (++ac < var->n_of_philo)
		b_new_philo(var, &philo[ac], ac + 1);
	var->philo = philo;
	var->current_time = b_time_now() + var->n_of_philo * 10;
	return (1);
}

void	*b_philo_status(void *philo1)
{
	t_philo	*philo;
	int		x;

	x = 0;
	philo = (t_philo *)philo1;
	pthread_create(philo->th, NULL, b_is_died, (void *)philo1);
	sem_wait(philo->var1->sem_2);
	philo->start_time = b_time_now();
	gettimeofday(&philo->last_t_eat, NULL);
	if (philo->n % 2 == 0)
		b_sleep(philo->var1->n_of_philo);
	while (philo->var1->n_of_eat == -1)
	{
		b_eat(philo->var1, philo);
		b_sleeping(philo->var1, philo);
		b_print_msg(philo->var1, philo, "is thinkig", 1);
	}
	while (philo->var1->n_of_eat != -1 && x++ < philo->var1->n_of_eat)
	{
		b_eat(philo->var1, philo);
		b_sleeping(philo->var1, philo);
		b_print_msg(philo->var1, philo, "is thinkig", 1);
	}
	exit(0);
}

void	b_init_sem(t_var *var)
{
	var->sem_fork = sem_open("sem", O_CREAT, 0644, var->n_of_philo);
	var->sem_2 = sem_open("sem2", O_CREAT, 0644, 0);
	var->sem_print = sem_open("sem_p", O_CREAT, 0644, 1);
	var->sem_1 = sem_open("sem_1", O_CREAT, 0644, 1);
	sem_unlink("sem_1");
	sem_unlink("sem");
	sem_unlink("sem2");
	sem_unlink("sem_p");
}

int	main(int ac, char **av)
{
	t_var	*var;
	int		x;

	x = -1;
	var = malloc(sizeof(t_var));
	if (!b_start_simulation(var, NULL, av, ac))
		return (0);
	b_init_sem(var);
	while (++x < var->n_of_philo)
	{
		var->pid[x] = fork();
		if (!var->pid[x])
		{
			b_philo_status(&var->philo[x]);
			exit(0);
		}
	}
	x = -1;
	while (++x < var->n_of_philo)
		sem_post(var->sem_2);
	while (waitpid(-1, &x, 0) != -1)
		if (WEXITSTATUS(x) == 1)
			return (a_kill(var));
}
