/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:28:50 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/27 18:27:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	whit_newline(char **s)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (s && s[x])
	{
		y = 0;
		if (s[x][y] == '-' && s[x][y + 1] == 'n')
		{
			while (s[x][++y] == 'n')
				;
			if (s[x][y])
				return (x);
		}
		else
			return (x);
		x++;
	}
	return (x);
}

void	a_echo(t_cmd *cmd, char **s)
{
	size_t	x;

	x = whit_newline(s);
	g_shell->g_status = 0;
	if (x)
	{
		while (s[x])
		{
			write(cmd->out, s[x], a_strlen(s[x]));
			if (s[x++ + 1])
				write(cmd->out, " ", 1);
		}
		return ;
	}
	while (s[x])
	{
		a_printf("%s", s[x], NULL, cmd->out);
		if (s[x++ + 1])
			a_printf("%s", " ", NULL, cmd->out);
	}
	a_printf("%s", "\n", NULL, cmd->out);
}
