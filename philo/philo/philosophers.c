/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:04:32 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/18 07:50:01 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	status_of_philo(t_var *var, t_philo *philo1)
{
	int	x;

	x = 0;
	if (philo1->n % 2 == 0)
		ft_usleep(10);
	while (philo1 && var->n_of_eat == -1)
	{
		eat(var, philo1);
		a_sleep(var, philo1);
		print_msg(var, philo1, "is thinking", 1);
	}
	while (var->n_of_eat != -1 && x++ < var->n_of_eat)
	{
		eat(var, philo1);
		a_sleep(var, philo1);
		print_msg(var, philo1, "is thinking", 1);
	}
}

int	a_start_simulation(t_var *var, t_philo *philo, char **av, int ac)
{
	if ((ac != 5 && ac != 6) || !check_arg(av, 1))
		return (0);
	var->n_of_philo = str_to_int(av[1]);
	var->time_to_die = str_to_int(av[2]);
	var->time_to_eat = str_to_int(av[3]);
	var->time_to_sleep = str_to_int(av[4]);
	var->n_of_eat = -1;
	if (ac == 6)
		var->n_of_eat = str_to_int(av[5]);
	if (!chek_numbers(var, ac))
		return (0);
	var->mutex_f = malloc(var->n_of_philo * sizeof(pthread_mutex_t));
	var->th = malloc(var->n_of_philo * sizeof(pthread_t));
	philo = malloc(var->n_of_philo * sizeof(t_philo));
	ac = -1;
	while (++ac < var->n_of_philo)
		new_philo(var, &philo[ac], ac + 1);
	var->philo = philo;
	return (1);
}

void	a_init_mutex(t_var *var, int a)
{
	while (a < var->n_of_philo)
		pthread_mutex_init(&var->mutex_f[a++], NULL);
	pthread_mutex_init(&var->mutex_l_t_eat, NULL);
	pthread_mutex_init(&var->mutex_print, NULL);
	pthread_mutex_init(&var->mutex_n_eat, NULL);
	pthread_mutex_init(&var->mutex_x, NULL);
}

void	*rotine(void *philo)
{
	t_philo	*philox;

	philox = (t_philo *)philo;
	status_of_philo(philox->var1, philox);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_var	*var;
	int		a;

	var = malloc(sizeof(t_var));
	var->philo = NULL;
	var->x = 0;
	if (!a_start_simulation(var, NULL, av, ac))
		return (0);
	a_init_mutex(var, 0);
	var->current_time = ft_time_now();
	a = -1;
	while (++a < var->n_of_philo)
		pthread_create(&var->th[a], NULL, rotine, (void *)&var->philo[a]);
	a = -1;
	while (++a < var->n_of_philo)
		pthread_detach(var->th[a]);
	is_died(var, NULL);
	return (0);
}
