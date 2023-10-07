/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_push_swap_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:55:32 by aelidrys          #+#    #+#             */
/*   Updated: 2023/02/13 12:27:56 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_push_swap_bonus.h"

int	a_comp_str(char *s, char *p)
{
	if (!s || !p)
		return (0);
	while (*s && *p)
		if (*(s++) != *(p++))
			return (0);
	if (*s == *p)
		return (1);
	return (0);
}

void	do_instruction(t_var *var, int x)
{
	if (x == 0)
		b_sa(var);
	if (x == 1)
		b_sb(var);
	if (x == 2)
		b_ss(var);
	if (x == 3)
		b_ra(var);
	if (x == 4)
		b_rb(var);
	if (x == 5)
		b_rr(var);
	if (x == 6)
		b_rra(var);
	if (x == 7)
		b_rrb(var);
	if (x == 8)
		b_rrr(var);
	if (x == 9)
		b_pb(var);
	if (x == 10)
		b_pa(var);
}

int	read_instructions(t_var *var, int a, int b)
{
	char	*p;

	a_ranking_stacks_b(var, var->stack_a, 0, 0);
	p = "sa sb ss ra rb rr rra rrb rrr pb pa";
	var->s = get_next_line(0, NULL, NULL, 1);
	var->p = spl_b(var->s, '\n');
	var->fun = spl_b(p, ' ');
	while (var->p && var->p[++a])
	{
		b = -1;
		while (var->fun && var->fun[++b])
			if (a_comp_str(var->p[a], var->fun[b]))
				do_instruction(var, b);
	}
	return (is_sorting_b(var->stack_a, 0) && !var->stack_b);
}

int	main(int ac, char **av)
{
	t_var	var;

	if (!av[1])
		exit(0);
	print_error_b(get_arg_b(&var, av + 1, -1, ac));
	fill_stack_b(&var);
	if (read_instructions(&var, -1, -1) == 1)
		print_str_b("OK\n");
	else
		print_str_b("KO\n");
}
