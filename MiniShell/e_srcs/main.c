/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:14:03 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/29 19:30:04 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_here(char *line)
{
	char	**spl;

	spl = ft_split_space_quoted(line, " ");
	if (!spl)
		error_handling(1, NULL);
	if (spl)
		check(spl, g_shell);
}

void	execution(void)
{
	cmd_list();
	if (list_size(g_shell->cmd, 0) == 1)
		one_cmd(g_shell, g_shell->cmd);
	else if (g_shell->cmd)
		multible_cmd(g_shell, g_shell->cmd, 0);
	free_cmd((t_cmd *)g_shell->cmd);
	g_shell->cmd = NULL;
}

void	minishell(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		dup2(2, 1);
		line = readline("minishell$ ");
		dup2(g_shell->old_out, 1);
		if (!line)
			break ;
		if (a_strlen(line))
			add_history(line);
		pars_here(line);
		execution();
		free(line);
	}
}

void	a_start(t_shell *shell, char **env1, int x)
{
	char buff[10000];

	x = -1;
	g_shell->old_in = dup(0);
	g_shell->old_out = dup(1);
	g_shell->env = NULL;
	g_shell->cmd = NULL;
	g_shell->pid = NULL;
	g_shell->old_pwd = NULL;
	g_shell->quotes = NULL;
	g_shell->hdc = NULL;
	g_shell->flag = 0;
	g_shell->ex_st = 0;
	g_shell->g_status = 0;
	if (!env1[0])
	{
		add_back(&g_shell->env, new_env(a_strjoin("PWD=", getcwd(buff, 10000), 0, 0), 1));
		add_back(&g_shell->env, new_env("SHLVL=1", 0));
	}
	while (env1[++x])
		add_back(&g_shell->env, new_env(env1[x], 0));
	delete_env(shell, "OLDPWD", 0);
	add_back(&g_shell->env, new_env("OLDPWD", 0));
	sort_env(g_shell->env);
}

int	main(int ac, char **av, char **env)
{
	g_shell = malloc(sizeof(t_shell));
	setup_term();
	init_shell(g_shell, av, env);
	a_start(g_shell, env, ac);
	signal(SIGINT, sigint_hand);
	signal(SIGQUIT, SIG_IGN);
	minishell();
	a_printf("%s\n", "exit", NULL, g_shell->old_out);
	exit(0);
}
