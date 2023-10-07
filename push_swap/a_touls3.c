/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_touls3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:40:49 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/14 12:26:53 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_push_swap.h"

int	expand_range(t_var *var, int max)
{
	a_range(var, max);
	(void)max;
	if (var->strt == -1)
		return (-1);
	var->strt -= var->x / 2;
	var->end += var->x / 2;
	return (1);
}

void	complet_push(t_var *var)
{
	int	max;

	max = num_of_stacks(var, 'a');
	while (max--)
	{
		pb(var);
		if (var->stack_b->i < var->mid)
			rb(var, 1);
	}
}

void	push_to_b(t_var *var, t_stack *sta)
{
	(void)sta;
	pb(var);
	if (!(var->stack_a->i >= var->strt && var->stack_a->i < var->end))
	{
		if (var->stack_b->i < var->mid)
			rr(var);
	}
	else if (var->stack_b->i < var->mid)
		rb(var, 1);
	var->x--;
}

void	push_range(t_var *var, int max)
{
	a_range(var, max);
	var->mid = max / 2;
	var->strt = var->mid - var->x / 2;
	var->end = var->mid + var->x / 2;
	while (!is_sorting(var->stack_a, 0))
	{
		if (var->stack_a->i >= var->strt && var->stack_a->i < var->end)
			push_to_b(var, var->stack_a);
		if (!var->x)
			expand_range(var, max);
		while (!(var->stack_a->i >= var->strt && var->stack_a->i < var->end))
			ra(var, 1);
	}
	complet_push(var);
}
