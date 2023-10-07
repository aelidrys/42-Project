/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:34:44 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/29 19:07:53 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_in_help1(int *i, int flags[2])
{
	flags[0] = 1;
	flags[1] = 1;
	(*i)++;
}

void	get_in_help2(int flags[2], char **error)
{
	flags[0] = 0;
	flags[1] = 0;
	*error = "minishell: syntax error near unexpected token `newline'";
}

void	get_in_help3(int *i, t_cmd *node, char **error)
{
	*i = -1;
	if (node->in != -1)
	{
		ft_putendl_fd(*error, 2);
		g_shell->g_status = 258;
	}
	else
		g_shell->g_status = 1;
}
