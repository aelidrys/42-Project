/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:59:25 by aelidrys          #+#    #+#             */
/*   Updated: 2023/03/15 11:30:44 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				n;
	int				rhit_f;
	int				left_f;
	long			n_eating;
	long			last_t_eat;
	struct s_var	*var1;
}	t_philo;

typedef struct s_var
{
	long			x;
	long			current_time;
	long			n_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_of_eat;
	pthread_t		*th;
	t_philo			*philo;
	pthread_mutex_t	mutex_l_t_eat;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_x;
	pthread_mutex_t	mutex_n_eat;
	pthread_mutex_t	*mutex_f;
}	t_var;

int		a_start_simulation(t_var *var, t_philo *ph, char **av, int ac);
void	print_msg(t_var *var, t_philo *philo, char *s, int x);
void	new_philo(t_var *var, t_philo *philo1, int x);
int		is_died(t_var *var, t_philo *philo);
int		chek_finish(t_philo *philo, t_var *var);
void	a_sleep(t_var *var, t_philo *philo);
int		chek_numbers(t_var *var, int ac);
void	eat(t_var *var, t_philo *philo);
int		check_arg(char **av, int x);
int		check_characters(char *s);
void	ft_usleep(long time_2);
long	str_to_int(char *s);
void	print_str(char *s);
long	ft_time_now(void);

#endif