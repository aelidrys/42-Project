/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_instructions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:53:36 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/12 08:30:00 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_push_swap.h"

void	sa(t_var *var, int s)
{
	int	val1;
	int	i1;

	if (var && var->stack_a && var->stack_a->next)
	{
		val1 = var->stack_a->val;
		i1 = var->stack_a->i;
		var->stack_a->val = var->stack_a->next->val;
		var->stack_a->i = var->stack_a->next->i;
		var->stack_a->next->val = val1;
		var->stack_a->next->i = i1;
		if (s)
			write(1, "sa\n", 3);
	}
}

void	sb(t_var *var, int s)
{
	int	val1;
	int	i1;

	if (var && var->stack_b && var->stack_b->next)
	{
		val1 = var->stack_b->val;
		i1 = var->stack_a->i;
		var->stack_b->val = var->stack_b->next->val;
		var->stack_b->i = var->stack_b->next->i;
		var->stack_b->next->val = val1;
		var->stack_b->next->i = i1;
		if (s)
			write(1, "sb\n", 3);
	}
}

void	ss(t_var *var)
{
	sa(var, 0);
	sb(var, 0);
	write(1, "ss\n", 3);
}

void	pa(t_var *var)
{
	t_stack	*stack1;

	if (var && var->stack_b)
	{
		stack1 = var->stack_b;
		var->stack_b = var->stack_b->next;
		add_front(&var->stack_a, stack1);
		write(1, "pa\n", 3);
	}
}

void	pb(t_var *var)
{
	t_stack	*stack1;

	if (var && var->stack_a)
	{
		stack1 = var->stack_a;
		var->stack_a = var->stack_a->next;
		add_front(&var->stack_b, stack1);
		write(1, "pb\n", 3);
	}
}
