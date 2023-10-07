/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_instructions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 06:59:13 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/12 08:30:17 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_push_swap.h"

void	ra(t_var *var, int s)
{
	t_stack	*stack1;

	if (var && var->stack_a && var->stack_a->next)
	{
		stack1 = var->stack_a;
		var->stack_a = var->stack_a->next;
		stack1->next = NULL;
		add_stack(&var->stack_a, stack1);
		if (s)
			write(1, "ra\n", 3);
	}
}

void	rb(t_var *var, int s)
{
	t_stack	*stack1;

	if (var && var->stack_b && var->stack_b->next)
	{
		stack1 = var->stack_b;
		var->stack_b = var->stack_b->next;
		stack1->next = NULL;
		add_stack(&var->stack_b, stack1);
		if (s)
			write(1, "rb\n", 3);
	}
}

void	rr(t_var *var)
{
	ra(var, 0);
	rb(var, 0);
	write (1, "rr\n", 3);
}

void	rra(t_var *var, int s)
{
	t_stack	*stack1;

	if (var && var->stack_a && var->stack_a->next)
	{
		stack1 = var->stack_a;
		while (stack1->next->next)
			stack1 = stack1->next;
		add_front(&var->stack_a, stack1->next);
		stack1->next = NULL;
		if (s)
			write(1, "rra\n", 4);
	}
}

void	rrb(t_var *var, int s)
{
	t_stack	*stack1;

	if (var && var->stack_b && var->stack_b->next)
	{
		stack1 = var->stack_b;
		while (stack1->next->next)
			stack1 = stack1->next;
		add_front(&var->stack_b, stack1->next);
		stack1->next = NULL;
		if (s)
			write(1, "rrb\n", 4);
	}
}
