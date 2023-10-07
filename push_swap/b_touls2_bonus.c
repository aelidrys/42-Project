/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_touls2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:22:12 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/14 09:02:38 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_push_swap_bonus.h"

int	get_arg_b(t_var *var, char **av, int x, int y)
{
	char	**s;
	int		a;

	a = 0;
	y = -1;
	while (av[++y])
	{
		s = spl_b(av[y], ' ');
		if (s && !*s)
			print_str_b("Error\n");
		x = -1;
		while (s[++x])
			add_back_b(&var->arg, new_node_b(s[x]));
		free(s);
	}
	return (check_arg_b(var, NULL));
}

void	add_front_b(t_stack **stack1, t_stack *new1)
{
	if (new1)
	{
		new1->next = *stack1;
		*stack1 = new1;
	}
}

int	is_sorting_b(t_stack *stack1, int x)
{
	if (!stack1)
		return (-1);
	x = stack1->i;
	while (stack1)
	{
		if (x++ != stack1->i)
			return (0);
		stack1 = stack1->next;
	}
	return (1);
}

int	num_of_stacks_b(t_var *var, int c)
{
	int		x;
	t_stack	*stack1;

	x = 0;
	if (var && var->stack_a && c == 'a')
	{
		stack1 = var->stack_a;
		while (stack1)
		{
			stack1 = stack1->next;
			x++;
		}
	}
	if (var && var->stack_b && c == 'b')
	{
		stack1 = var->stack_b;
		while (stack1)
		{
			stack1 = stack1->next;
			x++;
		}
	}
	return (x);
}

void	a_ranking_stacks_b(t_var *var, t_stack *sta1, int i, int val1)
{
	while (sta1)
	{
		while (sta1 && sta1->i != -1)
			sta1 = sta1->next;
		if (!sta1)
			break ;
		val1 = sta1->val;
		sta1 = var->stack_a;
		while (sta1)
		{
			if (sta1->i == -1 && sta1->val < val1)
				val1 = sta1->val;
			sta1 = sta1->next;
		}
		sta1 = var->stack_a;
		while (sta1 && sta1->val != val1)
			sta1 = sta1->next;
		if (sta1 && sta1->i == -1)
			sta1->i = i++;
		sta1 = var->stack_a;
	}
}
