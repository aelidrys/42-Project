/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_gest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:19:57 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/27 18:27:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_double_redirect(char **args, int a)
{
	if (str_comp(args[a], ">") && str_comp(args[a + 1], "<"))
	{
		error_handling(11, NULL);
		g_shell->g_status = 258;
		return (1);
	}
	if ((args[a + 2] && args[a + 3] && str_comp(args[a + 2], "<")
			&& str_comp(args[a + 3], "<")) && !args[a + 4])
	{
		error_handling(13, NULL);
		g_shell->g_status = 258;
		return (1);
	}
	else if ((args[a + 2] && args[a + 3] && str_comp(args[a + 2], ">")
			&& str_comp(args[a + 3], ">")) && !args[a + 4])
	{
		error_handling(14, NULL);
		g_shell->g_status = 258;
		return (1);
	}
	return (0);
}

int	is_input_redirect(char **args, int a)
{
	return (str_comp(args[a], "<") && str_comp(args[a + 1], "<"));
}

int	check_invalid_redirect(char **args, int a)
{
	if (((str_comp(args[a + 2], "|") || str_comp(args[a + 2], "<")
				|| str_comp(args[a + 2], ">"))))
	{
		if (str_comp(args[a + 2], "|"))
			error_handling(10, NULL);
		else if (str_comp(args[a + 2], "<"))
			error_handling(11, NULL);
		else
			error_handling(12, NULL);
		g_shell->g_status = 258;
		return (1);
	}
	return (0);
}

int	check_status(void)
{
	return (g_shell->g_status == 1 || g_shell->g_status == 258);
}

void	clear_herdoc(void)
{
	t_herdoc	*hdc;

	while (g_shell->hdc)
	{
		hdc = g_shell->hdc;
		g_shell->hdc = g_shell->hdc->next;
		free(hdc);
	}
}
