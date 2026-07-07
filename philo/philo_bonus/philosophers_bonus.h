/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:53:23 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/18 18:52:04 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				n;
	int				y;
	long			n_eating;
	long			l_t_eat;
	long			start_time;
	pthread_t		*th;
	struct timeval	last_t_eat;
	struct s_var	*var1;
}	t_philo;

typedef struct s_var
{
	int				x;
	long			current_time;
	long			n_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_of_eat;
	pid_t			*pid;
	pthread_t		*th;
	t_philo			*philo;
	sem_t			*sem_fork;
	sem_t			*sem_print;
	sem_t			*sem_2;
	sem_t			*sem_1;
}	t_var;

int		b_start_simulation(t_var *var, t_philo *philo, char **av, int ac);
void	b_print_msg(t_var *var, t_philo *philo, char *s, int x);
void	b_new_philo(t_var *var, t_philo *philo, int x);
void	b_sleeping(t_var *var, t_philo *philo);
int		b_chek_numbers(t_var *var, int ac);
void	b_eat(t_var *var, t_philo *philo);
void	*b_philo_status(void *philo1);
int		b_check_arg(char **av, int x);
int		b_check_characters(char *s);
void	*b_is_died(void *phi1);
long	b_str_to_int(char *s);
void	b_print_str(char *s);
void	b_sleep(long time_2);
int		a_kill(t_var *var);
long	b_time_now(void);

#endif