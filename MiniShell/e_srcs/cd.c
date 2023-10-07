/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:31:30 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/27 18:37:33 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	apdate_pwd_and_oldpwd(t_shell *shell, t_env *env, int x)
{
	env = a_get_env(g_shell->env, "PWD");
	if (env)
	{
		free(env->val);
		env->val = g_shell->pwd;
	}
	env = a_get_env(g_shell->env, "OLDPWD");
	if (env)
	{
		free(env->val);
		env->val = g_shell->old_pwd;
	}
	else if (x)
	{
		g_shell->str = a_strjoin("OLDPWD=", g_shell->old_pwd, 0, 0);
		add_env(shell, g_shell->str);
		free(g_shell->str);
	}
}

int	a_go_to_directory(char *dir)
{
	char	*msg;
	char	buff[10000];
	char	*dir1;
	t_env	*env;

	env = a_get_env(g_shell->env, "HOME");
	if (!dir && !env)
	{
		a_printf("minishell: cd: %s\n", "HOME not set", NULL, 2);
		return (0);
	}
	if (!dir && env && !chdir(env->val))
		return (1);
	getcwd(buff, sizeof(buff));
	if (!chdir(dir))
		return (1);
	dir1 = a_strjoin(buff, "/", 0, 0);
	dir1 = a_strjoin(dir1, dir, 1, 0);
	msg = a_strjoin("minishell: cd: ", dir, 0, 0);
	if (chdir(dir1) == -1)
		perror(msg);
	free(dir1);
	free(msg);
	return (0);
}

void	a_cd(t_shell *shell, t_cmd *cmd, char *dir)
{
	char	buf[10000];

	getcwd(buf, sizeof(buf));
	g_shell->g_status = 1;
	if ((str_comp(dir, "-") && !g_shell->old_pwd) || (str_comp(dir, "-")
			&& !a_get_env(g_shell->env, "OLDPWD")))
		a_printf("%s\n", "minishell: cd: OLDPWD not set", NULL, 2);
	else if (str_comp(dir, "-") && a_get_env(g_shell->env, "OLDPWD")->val)
	{
		chdir(g_shell->old_pwd);
		g_shell->old_pwd = a_strjoin(buf, NULL, 0, 0);
		getcwd(buf, sizeof(buf));
		g_shell->pwd = a_strjoin(buf, NULL, 0, 0);
		a_printf("%s\n", g_shell->pwd, NULL, cmd->out);
		apdate_pwd_and_oldpwd(shell, NULL, 0);
		g_shell->g_status = 0;
	}
	else if (a_go_to_directory(dir))
	{
		g_shell->old_pwd = a_strjoin(buf, NULL, 0, 0);
		getcwd(buf, sizeof(buf));
		g_shell->pwd = a_strjoin(buf, NULL, 0, 0);
		apdate_pwd_and_oldpwd(shell, NULL, 1);
		g_shell->g_status = 0;
	}
}
