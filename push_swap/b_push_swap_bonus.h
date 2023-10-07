/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_push_swap_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:29:57 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/12 13:02:22 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_PUSH_SWAP_BONUS_H
# define B_PUSH_SWAP_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "b_get_next_line_bonus.h"

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
	char	*s;
	char	**p;
	char	**fun;
	t_arg	*arg;
	t_stack	*stack_a;
	t_stack	*stack_b;
}	t_var;

void	a_ranking_stacks_b(t_var *var, t_stack *sta1, int i, int val1);
int		get_arg_b(t_var *var, char **av, int x, int y);
void	add_stack_b(t_stack **stack1, t_stack *new1);
void	add_front_b(t_stack **stack1, t_stack *new1);
int		is_sorting_b(t_stack *stack1, int x);
int		check_arg_b(t_var *var, t_arg *arg1);
void	add_back_b(t_arg **arg1, t_arg *new1);
int		num_of_stacks_b(t_var *var, int c);
int		check_characters_b(char *s, int x);
char	**spl_b(char const *s, char c);
int		comp_str_b(char *p, char *s);
void	fill_stack_b(t_var *var);
long	str_to_int_b(char *str);
t_stack	*new_stack_b(int val1);
t_arg	*new_node_b(char *s1);
void	print_error_b(int x);
void	print_str_b(char *s);
void	b_rra(t_var *var);
void	b_rrb(t_var *var);
void	b_sa(t_var *var);
void	b_sb(t_var *var);
void	b_ra(t_var *var);
void	b_rb(t_var *var);
void	b_rrr(t_var *var);
void	b_ss(t_var *var);
void	b_pa(t_var *var);
void	b_pb(t_var *var);
void	b_rr(t_var *var);

#endif