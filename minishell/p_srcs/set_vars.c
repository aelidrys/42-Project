/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:16:04 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/25 14:16:12 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_shlvl(t_shell *sh)
{
	char	*str;
	char	*num;

	str = mini_getenv("SHLVL", sh->envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	sh->envp = mini_setenv("SHLVL", num, sh->envp, 5);
	free(num);
}

void	set_path(t_shell *sh)
{
	char	*str;

	str = mini_getenv("PATH", sh->envp, 4);
	if (!str)
		sh->envp = mini_setenv("PATH", \
			"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", sh->envp, 4);
	free(str);
}

void	set_arg0(t_shell *sh, char *arg)
{
	char	*str;

	str = mini_getenv("_", sh->envp, 1);
	if (!str)
		sh->envp = mini_setenv("_", arg, sh->envp, 1);
	free(str);
}
