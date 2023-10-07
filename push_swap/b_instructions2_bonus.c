/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_instructions2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 06:59:13 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/12 12:51:57 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_push_swap_bonus.h"

void	b_ra(t_var *var)
{
	t_stack	*stack1;

	if (var && var->stack_a && var->stack_a->next)
	{
		stack1 = var->stack_a;
		var->stack_a = var->stack_a->next;
		stack1->next = NULL;
		add_stack_b(&var->stack_a, stack1);
	}
}

void	b_rb(t_var *var)
{
	t_stack	*stack1;

	if (var && var->stack_b && var->stack_b->next)
	{
		stack1 = var->stack_b;
		var->stack_b = var->stack_b->next;
		stack1->next = NULL;
		add_stack_b(&var->stack_b, stack1);
	}
}

void	b_rr(t_var *var)
{
	b_ra(var);
	b_rb(var);
}

void	b_rra(t_var *var)
{
	t_stack	*stack1;

	if (var && var->stack_a && var->stack_a->next)
	{
		stack1 = var->stack_a;
		while (stack1->next->next)
			stack1 = stack1->next;
		add_front_b(&var->stack_a, stack1->next);
		stack1->next = NULL;
	}
}

void	b_rrb(t_var *var)
{
	t_stack	*stack1;

	if (var && var->stack_b && var->stack_b->next)
	{
		stack1 = var->stack_b;
		while (stack1->next->next)
			stack1 = stack1->next;
		add_front_b(&var->stack_b, stack1->next);
		stack1->next = NULL;
	}
}
