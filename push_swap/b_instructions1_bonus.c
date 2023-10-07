/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_instructions1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:53:36 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/12 12:51:45 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_push_swap_bonus.h"

void	b_sa(t_var *var)
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
	}
}

void	b_sb(t_var *var)
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
	}
}

void	b_ss(t_var *var)
{
	b_sa(var);
	b_sb(var);
}

void	b_pa(t_var *var)
{
	t_stack	*stack1;

	if (var && var->stack_b)
	{
		stack1 = var->stack_b;
		var->stack_b = var->stack_b->next;
		add_front_b(&var->stack_a, stack1);
	}
}

void	b_pb(t_var *var)
{
	t_stack	*stack1;

	if (var && var->stack_a)
	{
		stack1 = var->stack_a;
		var->stack_a = var->stack_a->next;
		add_front_b(&var->stack_b, stack1);
	}
}
