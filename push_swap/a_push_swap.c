/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_push_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:27:20 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/15 14:31:08 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_push_swap.h"

void	rev_push_a(t_var *var, t_stack *stack1, int x, int i)
{
	while (!is_sorting(var->stack_a, 0))
	{
		var->end = num_of_stacks(var, 'a');
		stack1 = var->stack_a;
		x = 0;
		while (stack1 && stack1->i != i && x++ != -10)
			stack1 = stack1->next;
		if (var->end > 1 && var->stack_a->i == var->stack_a->next->i + 1)
			sa(var, 1);
		if (stack1 && x > 0 && x <= var->end - x)
			while (var->stack_a->i != i)
				ra(var, 1);
		else if (stack1 && x > 0)
			while (var->stack_a->i != i)
				rra(var, 1);
		else if (var->stack_a && var->stack_a->i == i)
		{
			pb(var);
			i++;
		}
	}
	while (var->stack_b)
		pa(var);
}

void	rev_push_a1(t_var *var, t_stack *stack1, int max)
{
	while (var->stack_b && var->stack_b->i != max)
		rb(var, 1);
	pa(var);
	max--;
	var->end = num_of_stacks(var, 'b');
	while (var->end)
	{
		stack1 = var->stack_b;
		var->x = 0;
		while (stack1 && stack1->i != max && var->x++ != -10)
			stack1 = stack1->next;
		var->end = num_of_stacks(var, 'b');
		if (var->stack_b && var->stack_b->i == max && max-- != -1)
			pa(var);
		else if ((var->stack_b && var->stack_b->i > last_stack(var, 'a')->i)
			|| (var->stack_b && !var->y))
			push_and_rotate(var, max);
		reverse_rotate(var, &max);
		if (var->stack_b && var->stack_b->i < last_stack(var, 'a')->i
			&& var->stack_b->i != max && var->x <= var->end - var->x && var->y)
			rb(var, 1);
	}
	while (var->y--)
		rra(var, 1);
}

void	a_range(t_var *var, int max)
{
	int	x;

	x = 0;
	if (max >= 20 && max <= 100)
		var->x = 32;
	if (max > 100)
		var->x = 80;
	if (max > 600)
		var->x = 120;
}

void	sort_stack(t_var *var, char **av, int max)
{
	var->arg = NULL;
	var->y = 0;
	print_error(get_arg(var, av + 1, -1, 0));
	fill_stack(var);
	a_ranking_stacks(var, var->stack_a, 0, 0);
	if (!is_sorting(var->stack_a, 0))
	{
		max = num_of_stacks(var, 'a');
		if (max >= 20)
		{
			push_range(var, max);
			rev_push_a1(var, var->stack_b, max - 1);
		}
		else
			rev_push_a(var, var->stack_b, 0, 0);
	}
}

int	main(int ac, char **av)
{
	t_var	var;

	if (av[1])
		sort_stack(&var, av, ac);
	else
		print_str("no argument\n");
}
