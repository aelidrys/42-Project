/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_touls4_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:32:49 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/13 08:15:19 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_push_swap_bonus.h"

t_stack	*new_stack_b(int val1)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	new->val = val1;
	new->i = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_stack_b(t_stack **stack1, t_stack *new1)
{
	t_stack	*tmp;

	if (stack1 && new1)
	{
		if (*stack1)
		{
			tmp = *stack1;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new1;
			new1->prev = tmp;
		}
		else
			*stack1 = new1;
	}
}

t_arg	*new_node_b(char *s1)
{
	t_arg	*new;

	new = (t_arg *)malloc(sizeof(t_arg));
	new->str = s1;
	new->next = NULL;
	return (new);
}

void	add_back_b(t_arg **arg1, t_arg *new1)
{
	t_arg	*tmp;

	if (arg1 && new1)
	{
		if (*arg1)
		{
			tmp = *arg1;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new1;
		}
		else
			*arg1 = new1;
	}
}

void	fill_stack_b(t_var *var)
{
	t_arg	*arg1;
	t_stack	*sta1;
	t_stack	*sta2;

	arg1 = var->arg;
	while (arg1)
	{
		add_stack_b(&var->stack_a, new_stack_b(str_to_int_b(arg1->str)));
		arg1 = arg1->next;
	}
	sta1 = var->stack_a;
	while (sta1)
	{
		sta2 = sta1->next;
		while (sta2)
		{
			if (sta1->val == sta2->val)
				print_str_b("Error\nduplicate number\n");
			sta2 = sta2->next;
		}
		sta1 = sta1->next;
	}
}
