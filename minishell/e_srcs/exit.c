/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:37:51 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/27 18:27:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exit(t_cmd *cmd)
{
	char	*s;

	if (!cmd->cmmd[1])
		return (1);
	s = cmd->cmmd[1];
	if (s && !*s)
		s = NULL;
	while (s && *s == ' ' && *(s + 1))
		s++;
	if (s && (*s == '+' || *s == '-') && *(s + 1))
		s++;
	while (s && *s >= '0' && *s <= '9')
		s++;
	while (s && *s == ' ')
		s++;
	if (s && !*s)
		return (1);
	a_printf("minishell: exit: %s: %s\n", cmd->cmmd[1],
		"numeric argument required", 2);
	return (0);
}

void	a_exit(t_shell *shell, t_cmd *cmd)
{
	int	fd;

	(void)shell;
	fd = cmd->out;
	if (fd == -2)
		fd = 1;
	if (!cmd || !cmd->cmmd)
		return ;
	a_printf("%s\n", "exit", NULL, 2);
	if (!check_exit(cmd))
		exit(255);
	if (cmd->cmmd[1] && cmd->cmmd[2])
	{
		g_shell->g_status = 1;
		a_printf("minishell: exit: %s\n", "too many arguments", NULL, 2);
	}
	else
		exit(str_to_int(cmd->cmmd[1]));
}
