/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_touls4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:14:05 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/12 08:30:45 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_push_swap.h"

t_stack	*last_stack(t_var *var, int c)
{
	t_stack	*sta1;

	if (c == 'b')
		sta1 = var->stack_b;
	if (c == 'a')
		sta1 = var->stack_a;
	while (sta1 && sta1->next)
		sta1 = sta1->next;
	return (sta1);
}

void	push_and_rotate(t_var *var, int max)
{
	pa(var);
	if (var->stack_b && var->stack_b->i < last_stack(var, 'a')->i
		&& var->stack_b->i != max && var->x <= var->end - var->x && var->y)
		rr(var);
	else if (var->stack_a && var->stack_a->i != max)
		ra(var, 1);
	var->y++;
}

void	reverse_rotate(t_var *var, int *max)
{
	if (var->stack_a && last_stack(var, 'a')->i == *max && var->y)
	{
		if (var->stack_b && var->stack_b->i < last_stack(var, 'a')->i
			&& var->stack_b->i != *max && var->y > 0
			&& var->x > var->end - var->x)
		{
			rrr(var);
			*max -= 1;
			var->y--;
		}
		return ;
	}
	if (var->stack_a && last_stack(var, 'a')->i == *max && var->y)
	{
		rra(var, 1);
		*max -= 1;
		var->y--;
	}
	if (var->stack_b && var->stack_b->i < last_stack(var, 'a')->i
		&& var->stack_b->i != *max && var->y > 0 && var->x > var->end - var->x)
		rrb(var, 1);
}
