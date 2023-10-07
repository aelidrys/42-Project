/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_touls2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:41:31 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/12 08:30:32 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_push_swap.h"

void	rrr(t_var *var)
{
	rra(var, 0);
	rrb(var, 0);
	write (1, "rrr\n", 4);
}

void	add_front(t_stack **stack1, t_stack *new1)
{
	if (new1)
	{
		new1->next = *stack1;
		*stack1 = new1;
	}
}

int	num_of_stacks(t_var *var, int c)
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

int	is_sorting(t_stack *stack1, int x)
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

void	a_ranking_stacks(t_var *var, t_stack *stack1, int i, int val1)
{
	while (stack1)
	{
		while (stack1 && stack1->i != -1)
			stack1 = stack1->next;
		if (!stack1)
			break ;
		val1 = stack1->val;
		stack1 = var->stack_a;
		while (stack1)
		{
			if (stack1->i == -1 && stack1->val < val1)
				val1 = stack1->val;
			stack1 = stack1->next;
		}
		stack1 = var->stack_a;
		while (stack1 && stack1->val != val1)
			stack1 = stack1->next;
		if (stack1 && stack1->i == -1)
			stack1->i = i++;
		stack1 = var->stack_a;
	}
}
