/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 06:30:21 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/27 18:27:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	a_pwd(t_cmd *cmd)
{
	char	dir[10000];

	if (cmd->cmmd[1] && cmd->cmmd[1][0] == '-')
	{
		if (a_strlen(cmd->cmmd[1]) > 2)
			cmd->cmmd[1][2] = '\0';
		a_printf("minishell: pwd: %s%s\n", cmd->cmmd[1], ": invalid option", 2);
		g_shell->g_status = 1;
		return ;
	}
	getcwd(dir, sizeof(dir));
	a_printf("%s\n", dir, NULL, cmd->out);
	g_shell->g_status = 0;
}

void	a_env(t_env *env, char *option, int fd)
{
	if (option)
	{
		a_printf("%s %s\n", "minishell: env:",
			"work with no options or arguments", fd);
		g_shell->g_status = 1;
		return ;
	}
	while (env)
	{
		if (env->val)
			a_printf("%s=%s\n", env->key, env->val, fd);
		env = env->next;
	}
	g_shell->g_status = 0;
}

int	builtine(t_shell *shell, t_cmd *cmd)
{
	if (!shell || !cmd)
		return (-1);
	else if (str_comp("echo", cmd->cmmd[0]))
		a_echo(cmd, cmd->cmmd + 1);
	else if (str_comp("cd", cmd->cmmd[0]))
		a_cd(shell, cmd, cmd->cmmd[1]);
	else if (str_comp("pwd", cmd->cmmd[0]))
		a_pwd(cmd);
	else if (str_comp("export", cmd->cmmd[0]))
		a_export(cmd, shell);
	else if (str_comp("unset", cmd->cmmd[0]))
		a_unset(shell, cmd);
	else if (str_comp("env", cmd->cmmd[0]))
		a_env(g_shell->env, cmd->cmmd[1], cmd->out);
	else if (str_comp("exit", cmd->cmmd[0]))
		a_exit(shell, cmd);
	else
		return (0);
	return (1);
}
