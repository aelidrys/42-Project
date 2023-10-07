/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:01:41 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/25 11:40:49 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_pid(t_shell *sh)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		error_handling(8, NULL);
		ft_free_envp(&sh->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_envp(&sh->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	sh->id = pid - 1;
}

void	init_vars(t_shell *sh, char *str, char **argv)
{
	(void)str;
	set_shlvl(sh);
	set_path(sh);
	set_arg0(sh, argv[0]);
}

void	init_shell(t_shell *sh, char **argv, char **envp)
{
	char	*str;

	sh->commands = NULL;
	str = NULL;
	sh->envp = ft_dup_envp(envp);
	shell_pid(sh);
	init_vars(sh, str, argv);
}

void	check(char **str, t_shell *sh)
{
	parsing(str, sh);
}
