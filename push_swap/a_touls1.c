/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_touls1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:12:12 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/13 08:12:23 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_push_swap.h"

t_stack	*new_stack(int val1)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	new->val = val1;
	new->i = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_stack(t_stack **stack1, t_stack *new1)
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

t_arg	*new_node(char *s1)
{
	t_arg	*new;

	new = (t_arg *)malloc(sizeof(t_arg));
	new->str = s1;
	new->next = NULL;
	return (new);
}

void	add_back(t_arg **arg1, t_arg *new1)
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

void	fill_stack(t_var *var)
{
	t_arg	*arg1;
	t_stack	*sta1;
	t_stack	*sta2;

	arg1 = var->arg;
	while (arg1)
	{
		add_stack(&var->stack_a, new_stack(str_to_int(arg1->str)));
		arg1 = arg1->next;
	}
	sta1 = var->stack_a;
	while (sta1)
	{
		sta2 = sta1->next;
		while (sta2)
		{
			if (sta1->val == sta2->val)
				print_str("Error\nduplicate number\n");
			sta2 = sta2->next;
		}
		sta1 = sta1->next;
	}
}
