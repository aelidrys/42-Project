/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_push_swap.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:29:57 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/12 08:19:55 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_PUSH_SWAP_H
# define A_PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_arg
{
	char			*str;
	struct s_arg	*next;
}	t_arg;

typedef struct s_stack
{
	int				i;
	int				val;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_var
{
	int		x;
	int		y;
	int		strt;
	int		end;
	int		mid;
	t_arg	*arg;
	t_stack	*stack_a;
	t_stack	*stack_b;
}	t_var;

void	a_ranking_stacks(t_var *var, t_stack *sta, int i, int val);
int		get_arg(t_var *var, char **av, int x, int y);
void	push_and_rotate(t_var *var, int max);
void	add_stack(t_stack **stack1, t_stack *new1);
void	add_front(t_stack **stack1, t_stack *new1);
void	reverse_rotate(t_var *var, int *max);
void	push_to_b(t_var *var, t_stack *sta);
int		is_sorting(t_stack *stack1, int x);
int		check_arg(t_var *var, t_arg *arg1);
void	add_back(t_arg **arg1, t_arg *new1);
int		expand_range(t_var *var, int max);
int		num_of_stacks(t_var *var, int c);
int		check_characters(char *s, int x);
void	push_range(t_var *var, int max);
t_stack	*last_stack(t_var *var, int c);
void	a_range(t_var *var, int max);
char	**spl(char const *s, char c);
int		comp_str(char *p, char *s);
void	fill_stack(t_var *var);
void	rra(t_var *var, int s);
void	rrb(t_var *var, int s);
long	str_to_int(char *str);
void	sa(t_var *var, int s);
void	sb(t_var *var, int s);
void	ra(t_var *var, int s);
void	rb(t_var *var, int s);
t_stack	*new_stack(int val1);
t_arg	*new_node(char *s1);
void	print_str(char *s);
void	print_error(int x);
void	rrr(t_var *var);
void	ss(t_var *var);
void	pa(t_var *var);
void	pb(t_var *var);
void	rr(t_var *var);

#endif